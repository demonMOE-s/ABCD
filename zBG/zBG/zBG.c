#include "zBG_DirectX_Driver.h"
#include "zBG_Timing.h"
#include "zBG_Input.h"
#include "zBG_Graphisc.h"
#include "zBG_Global.h"
#include "zBG_Sound.h"

pfun entry;

STATIC FORCEINLINE BOOL STDWIN32_CALL zBG_poll_key_status(void) {

	u32 PoLL_Index;
	STATIC ALIGN u8 _ALL_Key_Buffer_Status[256];
	ALIGN u8 _Key_Buffer_Status_Cur[8];
	STATIC ALIGN u8 _Key_Buffer_Status_Last[8];

	if (S_OK != JoyPad->lpVtbl->GetDeviceState(JoyPad,256,&_ALL_Key_Buffer_Status[0])) {

		if(S_OK != JoyPad->lpVtbl->Acquire(JoyPad)) {

			MessageBox(NULL,TEXT("IDirectInput8 Crash!!!"),TEXT("FATAL-ERROR"),MB_ICONERROR);
			return FALSE;
		} else {
			if ( S_OK != JoyPad->lpVtbl->GetDeviceState(JoyPad,256,&_ALL_Key_Buffer_Status[0])) {
				return FALSE;
			}
		}
	}
	for (PoLL_Index=0; PoLL_Index != 8; PoLL_Index ++) {

		_Key_Buffer_Status_Cur[PoLL_Index] = _ALL_Key_Buffer_Status[GloBal_Key_Mapper_Buffer[PoLL_Index]] & 0x80;
		if (_Key_Buffer_Status_Cur[PoLL_Index]) {
			if (_Key_Buffer_Status_Last[PoLL_Index]) 	GloBal_Key_Buffer_Status[PoLL_Index] = KEY_DOWN;
			else 										GloBal_Key_Buffer_Status[PoLL_Index] = KEY_DOWN | KEY_FIRST;
		} else {
			if (_Key_Buffer_Status_Last[PoLL_Index])	GloBal_Key_Buffer_Status[PoLL_Index] = KEY_UP;
			else 										GloBal_Key_Buffer_Status[PoLL_Index] = KEY_DISCARD;
		}
	}
	for (PoLL_Index=0; PoLL_Index != 8; PoLL_Index ++) {

		_Key_Buffer_Status_Last[PoLL_Index] = _Key_Buffer_Status_Cur[PoLL_Index];
	}

	return TRUE;
}
STATIC FORCEINLINE u32 c32alpha(u32 irgb, u32 percent) {

	u32
		r = irgb & 0x000000FF,
		g = irgb & 0x0000FF00,
		b = irgb & 0x00FF0000;
	//a = irgb & 0xFF000000;

	r = ((r * percent) >> 8) & 0x000000FF;
	g = ((g * percent) >> 8) & 0x0000FF00;
	b = ((b * percent) >> 8) & 0x00FF0000;
	//a = ((a * percent) >> 8) & 0xFF000000;

	return (r | g | b);
}





STATIC FORCEINLINE void STDWIN32_CALL zBG_Graphics_Render(void) {

	u32 xPos;
	u32 yPos;
	u32 xSave;
	u32 yPoLL;
	u32 xPoLL;
	u32 ntPage;
	u32 sTotal;
	u32 Index;
	u32 mx;
	u32 my;
	u32 ntPage_s;
	u32* ptr_OAM;
	u32* pTile_Cur;
	u32 Tile_Id;
	u32 yTotal = 0;
	u32 yPosNiYos;
	u32 real_alpha_color;
	u32 tc = ntCTRL.Tran_Color;
	u32* pEmuVideoBuffer;
	u32* pEmuVideoUpdate;
	xSave=ntCTRL.SCR0_x;
	xPos=ntCTRL.SCR0_x;
	yPos=ntCTRL.SCR0_y;
	yPosNiYos=yPos<<5;

	ntPage = ntCTRL.ntPagePointerSCR0;
	ntPage_s = ntPage;
	pEmuVideoUpdate = &NesEmuVideoBufferLine[273*8];
	pEmuVideoBuffer = &NesEmuVideoBufferLine[8-ntCTRL.SCR0_fine_x+272*(8-ntCTRL.SCR0_fine_y)];
	if (ntCTRL.bdisnt0 == TRUE)	goto NT1_CHECK;
/* ------------------------------- NameTable0 render -------------------------------------- */ 
	for (yPoLL=0;yPoLL!=29;yPoLL++) {
		for (xPoLL=0;xPoLL!=33;xPoLL++) {
		/* -------------------------- line render -------------------------------- */
			sTotal = (xPoLL << 3) + yTotal;
			Tile_Id = NameTable0[ntPage*896+xPos+yPosNiYos]; // get tile id 
			pTile_Cur = &BackGround_PooL[((Tile_Id&63)<<3)+((Tile_Id>>6)<<3)*PPITH_DWORD]; // lock area
#include "Inline_Misc0.h"
			if (++xPos == 32)
			/* switch hori page */ {
			ntPage ^= 1;
				xPos = 0;
			}		
		}		
		if (++yPos == 28)
		/* switch vert page */ {	
			ntPage_s ^= 2;
			yPos = 0;
		}	
		xPos = xSave;	
		ntPage = ntPage_s;
		yTotal += 2176;
		yPosNiYos=yPos<<5;
	}
NT1_CHECK:
if (ntCTRL.bdisnt1==TRUE) goto NT2_CHECK;
#define OPEN_NT1 1
#define OPEN_NT2 1
	switch (apCTRL.Nt1ScreenCount) {
#if OPEN_NT1
	case 0:
		goto NT1_$0_SCANLINE_RENDER;
	case 1: 
		goto NT1_$25_SCANLINE_RENDER;
	case 2:
		goto NT1_$50_SCANLINE_RENDER;
	case 3: 
		goto NT1_$75_SCANLINE_RENDER;
#endif 
	default:
		break;
	}

#if OPEN_NT1
#define NT1_MARCO 
#include "NT$100.h"
#include "NT$0.h"
#include "NT$25.h"
#include "NT$50.h"
#include "NT$75.h"
#endif
#undef NT1_MARCO 
NT2_CHECK:
if (ntCTRL.bdisnt2==TRUE) goto SP_MIX;
	switch (apCTRL.Nt2ScreenCount) {
#if	OPEN_NT2
	case 0:
		goto NT2_$0_SCANLINE_RENDER;
	case 1: 
		goto NT2_$25_SCANLINE_RENDER;
	case 2:
		goto NT2_$50_SCANLINE_RENDER;
	case 3: 
		goto NT2_$75_SCANLINE_RENDER;
#endif 
	default:
		break;
	}
#if OPEN_NT2
#include "NT$100.h"
#include "NT$0.h"
#include "NT$25.h"
#include "NT$50.h"
#include "NT$75.h"
#endif 
SP_MIX:
/* ------------------------------- Sprite mixer -------------------------------------- */ 
	for (Index=255;Index!=-1;Index--) {

		u32 px = sprite_OAM[Index].PosX;
		u32 py = sprite_OAM[Index].PosY;
		u32 at = sprite_OAM[Index].Attrs;
		u32 id = sprite_OAM[Index].Tile_Id; /* cache reduce */ 
		/* -------------------------- OAM test -------------------------------- */
		if (0 == (at & OAM_DISABLE_BIT)) 
		/* enable this OAM ? */ {
			if (ntCTRL.Tran_Id != id)
			/* not TransTile ? */ {
				if (py < 232
				&&  px < 256)
				/* in Range ? */ {
					u32 ix = 0;
					u32 ex = 1;
					u32 rx = 8;
					u32 hx = 0;
					u32 iy = 0;
					u32 ey = 1;
					u32 ry = 8;
					u32 hy = 0;
					u32 ep = 0;

					if (sprite_OAM[Index].Attrs & OAM_VERTFILP_BIT) 
					/* vert flip */ {
						iy = 7;
						ey = -1;
						ry = -1;
					}
					if (sprite_OAM[Index].Attrs & OAM_HORIFILP_BIT)
					/* hori flip */ {
						ix = 7;
						ep = 7;
						ex = -1;
						rx = -1;
					}
					ptr_OAM = &pEmuVideoUpdate[py*272+px];
					pTile_Cur = &Sprite_PooL[((id&63)<<3)+((id>>6)<<3)*PPITH_DWORD]; // lock area
					if (at & OAM_BACKITOS_BIT)
					/* background sprite ? */ {
						for (iy = iy; iy != ry; iy += ey) {
							for (ix = ep; ix != rx; ix += ex) {
							/* ------------------- line render ------------------ */
								if (ptr_OAM[hx+hy*272] != tc) {
									ptr_OAM[hy*272+hx] = pTile_Cur[PPITH_DWORD*iy+ix];
								}
								hx++;
							}
							hx = 0; /* reset x pos */
							hy ++;
						}
					} else {
					/* foreground sprite ? */ 
						for (iy = iy; iy != ry; iy += ey) {
							for (ix = ep; ix != rx; ix += ex) {
							/* ------------------- line render ------------------ */
								if (pTile_Cur[PPITH_DWORD*iy+ix] != tc) {
									 ptr_OAM[hy*272+hx] = pTile_Cur[PPITH_DWORD*iy+ix];
								}
								hx++;
							}
							hx = 0; /* reset x pos */
							hy ++;
						}
					}
				}
			}
		}
	}
/* ------------------------------- Direct3D output -------------------------------------- */
//#include "Inline_Misc2.h"
//# 
/*==	100019CE A1 C0 CE 04 10       mov         eax,dword ptr [_IBaseGraphics (1004CEC0h)]  
==	100019D3 8B 08                mov         ecx,dword ptr [eax]  
==	100019D5 8B 51 44             mov         edx,dword ptr [ecx+44h]  
==	100019D8 6A 00                push        0  
==		100019DA 6A 00                push        0  
==		100019DC 6A 00                push        0  
==		100019DE 6A 00                push        0  
==		100019E0 50                   push        eax  
==		100019E1 FF D2                call        edx  == */
/*==	nes5StepAlphaALLScreen(4,pEmuVideoUpdate);
	//__asm int 3
	IBaseGraphics->lpVtbl->Present(IBaseGraphics,0,0,0,0); == */ {
	STATIC ALIGN DWORD DWORDTLB[16] =
		/* Mask */ {
			0x00000000, 0x00000000, 0x00000000, 0x00000000,
			0x40004000, 0x00004000, 0x40004000, 0x00004000,
			0x80008000, 0x00008000, 0x80008000, 0x00008000,
			0xC000C000, 0x0000C000, 0xC000C000, 0x0000C000
		
			};
	STATIC ALIGN DWORD REV_DWORDTLB[20] =
		/* Reverse Mask */ {
			0x00000000, 0x00000000, 0x00000000, 0x00000000,
			0xC000C000, 0x0000C000, 0xC000C000, 0x0000C000,
			0x80008000, 0x00008000, 0x80008000, 0x00008000,
			0x40004000, 0x00004000, 0x40004000, 0x00004000,
			0x00000000, 0x00000000, 0x00000000, 0x00000000
			};
			ASM_BEGIN
				
				push 		ebx 					; U - save old frame
				push 		ebp 					; V - save old frame 
				push 		esi 					; U - save old frame 
				push 		edi 					; V - save old frame 	
				mov			eax,	DWORD PTR[apCTRL.ALLScreenCount]	; U - fetch step count 
				mov			edi,	DWORD PTR[GVPointer+4]	; V/N fetch VPointer 
				mov			edx,	DWORD PTR[apCTRL.bALLReverse]
				mov			ecx,	ecx 
				test		edx,	edx 
				jne			reverse_proc
				cmp			eax,	4				; U - 
				jb			step_deal				; V/N 
				mov			ebx,	DWORD PTR[GVPointer+0]	; U - fetch Pitch 
				mov			esi,	[pEmuVideoUpdate]		; V - fecth SPointer
				mov			eax,	224
				sub			ebx,	1024 
				mov			edx,	1 
				mov			ecx,	8				; U loop_x 
				mov			ebp,	128
				align 16 
				mixleadup:
				; -------------------------------------------------------
				;           fetch mem 
				; -------------------------------------------------------
					movdqa	xmm0, [esi+000h]
					movdqa	xmm1, [esi+010h]
					movdqa  xmm2, [esi+020h]
					movdqa  xmm3, [esi+030h]
					movdqa	xmm4, [esi+040h]
					movdqa	xmm5, [esi+050h]
					movdqa  xmm6, [esi+060h]
					movdqa  xmm7, [esi+070h]
				; -------------------------------------------------------
				;           write mem 
				; -------------------------------------------------------
					movdqa	[edi+000h], xmm0
					movdqa	[edi+010h], xmm1
					movdqa  [edi+020h], xmm2
					movdqa  [edi+030h], xmm3
					movdqa	[edi+040h], xmm4 
					movdqa	[edi+050h], xmm5
					movdqa  [edi+060h], xmm6
					movdqa  [edi+070h], xmm7

					add		esi,	ebp
					add		edi,	ebp 
					sub		ecx,	edx 
					jne		mixleadup 
					add		esi,	64 
					add		edi,	ebx 
					mov		ecx,	8 
					sub		eax,	edx 
					jne		mixleadup 
					jmp		__outs
					align 16 
					step_deal:
						lea			eax,	[eax*4]			; U - *4
						mov			esi,	[pEmuVideoUpdate]		; V - fecth SPointer 
						movdqa 		xmm7, 	[eax*4+DWORDTLB]    
						pxor 		xmm6, 	xmm6	 
						mov			ebx,	DWORD PTR[GVPointer+0]	; U - fetch Pitch 
						mov			eax,	224
						sub			ebx,	1024 
						mov			edx,	1 
						mov			ecx,	16				; U loop_x 
						mov			ebp,	64 
					align 16
					step_loop:
						movdqa 		xmm0, 	[esi+000h]		 ; fetch P0
						movdqa 		xmm1, 	[esi+010h]		 ; fetch P1
						movdqa		xmm2, 	[esi+020h]		 ; fetch P2
						movdqa		xmm3,	[esi+030h]		 ; fetch P3
						movdqa 		xmm4,	xmm0			 ; xmm4 = xmm0 = P0 	
						punpcklbw 	xmm0, 	xmm6			 ; RGB cross-decomposition L0-L1 (P0)
						pmulhuw 	xmm0, 	xmm7			 ; RGB cross-mul get high L0-L1 (P0)
						movdqa		xmm5, 	xmm1 			 ; xmm5 = xmm1 = P1 	   
						punpckhbw 	xmm4, 	xmm6			 ; RGB cross-decomposition H0-H1 (P0)
						pmulhuw 	xmm4, 	xmm7			 ; RGB cross-mul get high H0-H1 (P0)
						punpcklbw 	xmm1, 	xmm6			 ; RGB cross-decomposition L0-L1 (P1)
						packuswb 	xmm0, 	xmm4			 ; P0  merge 	
						pmulhuw 	xmm1, 	xmm7			 ; RGB cross-mul get high L0-L1 (P1)		
						punpckhbw 	xmm5, 	xmm6			 ; RGB cross-decomposition H0-H1 (P1)
						movdqa		xmm4, 	xmm2 			 ; xmm4 = xmm2 = P2
						pmulhuw 	xmm5, 	xmm7			 ; RGB cross-mul get high H0-H1 (P1)	
						punpcklbw 	xmm2, 	xmm6			 ; RGB cross-decomposition L0-L1 (P2)
						packuswb 	xmm1, 	xmm5			 ; P1  merge 	
						pmulhuw 	xmm2, 	xmm7			 ; RGB cross-mul get high L0-L1 (P2)
						punpckhbw 	xmm4, 	xmm6			 ; RGB cross-decomposition H0-H1 (P2)
						movdqa		xmm5,	xmm3			 ; xmm5 = xmm3 = P3 
						pmulhuw 	xmm4, 	xmm7			 ; RGB cross-mul get high H0-H1 (P2)
						punpcklbw 	xmm3, 	xmm6			 ; RGB cross-decomposition L0-L1 (P3)
						packuswb 	xmm2, 	xmm4			 ; P2  merge 
						pmulhuw 	xmm3, 	xmm7			 ; RGB cross-mul get high L0-L1 (P3)
						punpckhbw 	xmm5, 	xmm6			 ; RGB cross-decomposition H0-H1 (P3)
						pmulhuw 	xmm5, 	xmm7			 ; RGB cross-mul get high H0-H1 (P3)
						packuswb 	xmm3, 	xmm5			 ; P3  merge 
						movdqa 		[edi+000h], xmm0		 ; write P0
						movdqa 		[edi+010h], xmm1		 ; write P1
						movdqa		[edi+020h], xmm2		 ; write P2
						movdqa		[edi+030h], xmm3		 ; write P3
						add			esi,	ebp				 ; next 64 bytes
						add			edi,	ebp				 ; next 64 bytes
						sub			ecx,	edx				 ; loop_x -- 
						jne			step_loop				 ; JCC contine/out 
						add			esi,	64				 ; next line 
						add			edi,	ebx				 ; next line 
						mov			ecx,	16
						sub			eax,	edx 
						jne			step_loop				 ; JCC contine/out 
						jmp			__outs
			align 16 
			reverse_proc:
				test		eax,	eax 
				jne			reverse_step_deal 
				mov			ebx,	DWORD PTR[GVPointer+0]	; U - fetch Pitch 
				mov			esi,	[pEmuVideoUpdate]		; V - fecth SPointer
				mov			eax,	224
				sub			ebx,	1024 
				mov			edx,	1 
				mov			ecx,	8				; U loop_x 
				mov			ebp,	128
				mov			esi,	ecx 
				pcmpeqd		xmm0,	xmm0 
				align 16 
				rev_mixleadup:
				; -------------------------------------------------------
				;           write mem 
				; -------------------------------------------------------
					movdqa	[edi+000h], xmm0
					movdqa	[edi+010h], xmm0
					movdqa  [edi+020h], xmm0
					movdqa  [edi+030h], xmm0
					movdqa	[edi+040h], xmm0
					movdqa	[edi+050h], xmm0
					movdqa  [edi+060h], xmm0
					movdqa  [edi+070h], xmm0

					add		edi,	ebp 
					sub		ecx,	edx 
					jne		rev_mixleadup 
					add		edi,	ebx 
					mov		ecx,	esi 
					sub		eax,	edx 
					jne		rev_mixleadup
					jmp		__outs
			align 16
			reverse_step_deal:
					cmp		eax,	5
					jb		$unname 
					mov		eax,	4 
				$unname:
					lea			eax,	[eax*4]			; U - *4
					mov			esi,	[pEmuVideoUpdate]		; V - fecth SPointer 
					movdqa 		xmm7, 	[eax*4+REV_DWORDTLB]    
					pxor 		xmm6, 	xmm6	 
					pcmpeqd		xmm5,	xmm5 
					mov			ebx,	DWORD PTR[GVPointer+0]	; U - fetch Pitch 
					mov			eax,	224
					sub			ebx,	1024 
					mov			edx,	1 
					mov			ecx,	32				; U loop_x 
					mov			ebp,	32
				align 16 
				reverse_step_loop:
						movdqa 		xmm0, 	[esi] 
						movdqa 		xmm1, 	[esi+16]		
						movdqa		xmm2,	xmm0 
						pxor		xmm0,	xmm5 ; reverse RGB 
						movdqa		xmm3,	xmm1 
						pxor		xmm1,	xmm5 ; reverse RGB 
						movdqa		xmm4,	xmm0 
						punpcklbw 	xmm0, 	xmm6
						punpckhbw 	xmm4, 	xmm6
						pmulhuw 	xmm4, 	xmm7
						pmulhuw 	xmm0, 	xmm7					
						packuswb 	xmm0, 	xmm4
						movdqa		xmm4,	xmm1 
						punpcklbw 	xmm1, 	xmm6
						punpckhbw 	xmm4, 	xmm6
						pmulhuw 	xmm4, 	xmm7
						pmulhuw 	xmm1, 	xmm7					
						packuswb 	xmm1, 	xmm4
						paddd		xmm0,	xmm2 
						paddd		xmm1,	xmm3 
						movdqa		[edi],	xmm0 
						movdqa		[edi+16], xmm1
						add			esi,	ebp				 ; next 32 bytes
						add			edi,	ebp				 ; next 32 bytes
						sub			ecx,	edx				 ; loop_x -- 
						jne			reverse_step_loop		 ; JCC contine/out 
						add			esi,	64				 ; next line 
						add			edi,	ebx				 ; next line 
						mov			ecx,	32
						sub			eax,	edx 
						jne			reverse_step_loop		 ; JCC contine/out 
				__outs:
			ASM_END 
						IDirect3DDevice9_Present(IBaseGraphics,0,0,0,0);
			ASM_BEGIN 
						pop			edi 
						pop			esi 
						pop			ebp 
						pop			ebx 
			ASM_END 
	}
}


STATIC BOOL resize_client (	HWND hWnd,
						int nWidth,
						int nHeight,
						DWORD Style,
						DWORD ExStyle,
						BOOL bMenu	) 
{
	RECT rcWnd;
	if(!GetClientRect(hWnd, &rcWnd))
		return FALSE;

	if(nWidth != -1)
		rcWnd.right = nWidth;
	if(nHeight != -1)
		rcWnd.bottom = nHeight;

	if(!AdjustWindowRectEx(&rcWnd, Style, (!(Style & WS_CHILD) && (bMenu != NULL)), ExStyle))
		return FALSE;

	return SetWindowPos(hWnd, NULL, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
}

STATIC VOID center_window (HWND hWnd)
{
	RECT winRECT;
	GetWindowRect	( hWnd, &winRECT );

	SetWindowPos	( hWnd, NULL,
						(GetSystemMetrics(SM_CXSCREEN) - (winRECT.right - winRECT.left)) / 2,
						(GetSystemMetrics(SM_CYSCREEN) - (winRECT.bottom - winRECT.left)) / 2,
						0,0,
						SWP_NOSIZE
					);
}

STATIC __stdcall $PROC (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

		msg != WM_DESTROY 
			? DefWindowProc(hwnd, msg, wparam, lparam)
			: PostQuitMessage(0);
}

ZBG_API BOOL STDWIN32_CALL ZlInit(HINSTANCE hInstance, pfun proc_m) {

	HWND s_hwnd;
	WNDCLASSEXW	wcex = {

		sizeof(wcex), 	CS_HREDRAW | CS_VREDRAW  , 
		$PROC,		
		0,	
		0,
		hInstance,			LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW), (HBRUSH) GetStockObject(BLACK_BRUSH),
		NULL,			L"zBG~",	LoadIconW(GetModuleHandleA("zBG.DLL"),MAKEINTRESOURCEW(101)),
	}; 

	entry=proc_m;

	zBG_init_timing();
	RegisterClassExW(&wcex);
	if (FALSE == zBG_init_directx_base())	return FALSE;

	s_hwnd =	CreateWindowExW	(	WS_EX_LEFT,              
									L"zBG~", L"zbg rountine",        
									WS_OVERLAPPEDWINDOW&~WS_THICKFRAME,
									500, 581,
									2.0+6565.56*21, 2,
									NULL, NULL, 
									hInstance, NULL );

	resize_client(s_hwnd,256,224,WS_OVERLAPPEDWINDOW&~WS_THICKFRAME,WS_EX_LEFT,FALSE);
	center_window(s_hwnd);

	if (FALSE == zBG_set_keyboard(s_hwnd)) return FALSE;
	if (FALSE == zBG_init_Screen(s_hwnd))  return FALSE;
	
	ShowWindow(s_hwnd,SW_SHOWNORMAL);
	UpdateWindow(s_hwnd);


	return TRUE;
}

ZBG_API BOOL STDWIN32_CALL ZlLoopEntry(void) {

	STATIC MSG msg={0};
	STATIC UINT FrameTicks=0,FramePhase=0,FrameTotal=0;
	__int64 t64temp;

	while( msg.message != WM_QUIT ) {
		if ( PeekMessageW( &msg, 0, 0, 0, PM_REMOVE ) )  {
			DispatchMessageW(&msg);
		} else {
			NativeQueryPerformanceCounter(&t64Begin,&t64temp);
			zBG_poll_key_status();
			entry(&wave_slot,&apCTRL.ALLScreenCount,&sprite_OAM[0],&GloBal_Key_Buffer_Status[0],FrameTicks,FramePhase,FrameTotal);
			zBG_Graphics_Render();
			if(++FrameTicks==60) 
			/* calc ticks */ {
				FrameTicks=0;
				FramePhase++;
			}
		$try:
			NativeQueryPerformanceCounter(&t64Xsend,&t64temp);
			if((t64Xsend-t64Begin)<t64Qfreq)
				goto $try; ++ FrameTotal;
		}
	}
	zBG_image_release();
	zBG_destory_keyboard();
	zBG_destroy_Screen();
	_destroy_wave_slot();
	zBG_destroy_directx_base();
	//destroyHAL();

}