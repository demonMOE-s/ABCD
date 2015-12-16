/* ------------------------------- Inline_Misc1.h -------------------------------------- */ 

			__asm {
					push	esi 
					push	edi 	
					push	eax 
					push	ebx 
					mov		eax, 16 
					mov		ebx, 1072
					mov		edi, [sTotal]
					mov		esi, [pTile_Cur]
					lea		edi, [edi*4]
					add		edi, [pEmuVideoUpdate]
					pcmpeqd xmm6, xmm6 
					movups  xmm7, [ntCTRL.Tran_Buffer]
/*---------------------------- 0 - Bpotop ------------------------*/ 
					movaps	xmm0, [esi+000h+00000h]
					movaps	xmm1, [esi+010h+00000h]
					movaps  xmm2, [esi+000h+00800h]
					movaps  xmm3, [esi+010h+00800h]
					movaps  xmm4, xmm0 
					movaps  xmm5, xmm1
					pcmpeqd xmm4, xmm7 
					pcmpeqd xmm5, xmm7
					pxor    xmm4, xmm6 
					pxor	xmm5, xmm6
					maskmovdqu xmm0, xmm4
					movaps  xmm4, xmm2 
					movaps  xmm0, xmm3 
					add		edi,  eax 
					maskmovdqu xmm1, xmm5
					pcmpeqd xmm4, xmm7 
					pcmpeqd xmm0, xmm7
					pxor    xmm4, xmm6 
					pxor	xmm0, xmm6
					add		edi,  ebx 
					maskmovdqu xmm2, xmm4
					add		edi,  eax 
					maskmovdqu xmm3, xmm0 
					add		edi,  ebx 
/*---------------------------- 0 - Bpotom ------------------------*/ 
					movaps	xmm0, [esi+000h+01000h]
					movaps	xmm1, [esi+010h+01000h]
					movaps  xmm2, [esi+000h+01800h]
					movaps  xmm3, [esi+010h+01800h]
					movaps  xmm4, xmm0 
					movaps  xmm5, xmm1
					pcmpeqd xmm4, xmm7 
					pcmpeqd xmm5, xmm7
					pxor    xmm4, xmm6 
					pxor	xmm5, xmm6
					maskmovdqu xmm0, xmm4
					movaps  xmm4, xmm2 
					movaps  xmm0, xmm3 
					add		edi,  eax 
					maskmovdqu xmm1, xmm5
					pcmpeqd xmm4, xmm7 
					pcmpeqd xmm0, xmm7
					pxor    xmm4, xmm6 
					pxor	xmm0, xmm6
					add		edi,  ebx 
					maskmovdqu xmm2, xmm4
					add		edi,  eax 
					maskmovdqu xmm3, xmm0 
					add		edi,  ebx 
/*---------------------------- 1 - Bpotop ------------------------*/ 	
					movaps	xmm0, [esi+000h+02000h]
					movaps	xmm1, [esi+010h+02000h]
					movaps  xmm2, [esi+000h+02800h]
					movaps  xmm3, [esi+010h+02800h]
					movaps  xmm4, xmm0 
					movaps  xmm5, xmm1
					pcmpeqd xmm4, xmm7 
					pcmpeqd xmm5, xmm7
					pxor    xmm4, xmm6 
					pxor	xmm5, xmm6
					maskmovdqu xmm0, xmm4
					movaps  xmm4, xmm2 
					movaps  xmm0, xmm3 
					add		edi,  eax 
					maskmovdqu xmm1, xmm5
					pcmpeqd xmm4, xmm7 
					pcmpeqd xmm0, xmm7
					pxor    xmm4, xmm6 
					pxor	xmm0, xmm6
					add		edi,  ebx 
					maskmovdqu xmm2, xmm4
					add		edi,  eax 
					maskmovdqu xmm3, xmm0 
					add		edi,  ebx 
/*---------------------------- 1 - Bpotom ------------------------*/ 
					movaps	xmm0, [esi+000h+03000h]
					movaps	xmm1, [esi+010h+03000h]
					movaps  xmm2, [esi+000h+03800h]
					movaps  xmm3, [esi+010h+03800h]
					movaps  xmm4, xmm0 
					movaps  xmm5, xmm1
					pcmpeqd xmm4, xmm7 
					pcmpeqd xmm5, xmm7
					pxor    xmm4, xmm6 
					pxor	xmm5, xmm6
					maskmovdqu xmm0, xmm4
					movaps  xmm4, xmm2 
					movaps  xmm0, xmm3 
					add		edi,  eax 
					maskmovdqu xmm1, xmm5
					pcmpeqd xmm4, xmm7 
					pcmpeqd xmm0, xmm7
					pxor    xmm4, xmm6 
					pxor	xmm0, xmm6
					add		edi,  ebx 
					maskmovdqu xmm2, xmm4
					add		edi,  eax 
					maskmovdqu xmm3, xmm0 
					add		edi,  ebx 
					pop		ebx 
					pop		eax 
					pop		edi 
					pop		esi 
				}
/*
				pEmuVideoUpdate[sTotal+0] = pTile_Cur[0];
				pEmuVideoUpdate[sTotal+1] = pTile_Cur[1];
				pEmuVideoUpdate[sTotal+2] = pTile_Cur[2];
				pEmuVideoUpdate[sTotal+3] = pTile_Cur[3];
				pEmuVideoUpdate[sTotal+4] = pTile_Cur[4];
				pEmuVideoUpdate[sTotal+5] = pTile_Cur[5];
				pEmuVideoUpdate[sTotal+6] = pTile_Cur[6];
				pEmuVideoUpdate[sTotal+7] = pTile_Cur[7]; // 0
				pEmuVideoUpdate[sTotal+0+272] = pTile_Cur[0+PPITH_DWORD];
				pEmuVideoUpdate[sTotal+1+272] = pTile_Cur[1+PPITH_DWORD];
				pEmuVideoUpdate[sTotal+2+272] = pTile_Cur[2+PPITH_DWORD];
				pEmuVideoUpdate[sTotal+3+272] = pTile_Cur[3+PPITH_DWORD];
				pEmuVideoUpdate[sTotal+4+272] = pTile_Cur[4+PPITH_DWORD];
				pEmuVideoUpdate[sTotal+5+272] = pTile_Cur[5+PPITH_DWORD];
				pEmuVideoUpdate[sTotal+6+272] = pTile_Cur[6+PPITH_DWORD];
				pEmuVideoUpdate[sTotal+7+272] = pTile_Cur[7+PPITH_DWORD]; // 1
				pEmuVideoUpdate[sTotal+0+544] = pTile_Cur[0+PPITH_DWORD*2];
				pEmuVideoUpdate[sTotal+1+544] = pTile_Cur[1+PPITH_DWORD*2];
				pEmuVideoUpdate[sTotal+2+544] = pTile_Cur[2+PPITH_DWORD*2];
				pEmuVideoUpdate[sTotal+3+544] = pTile_Cur[3+PPITH_DWORD*2];
				pEmuVideoUpdate[sTotal+4+544] = pTile_Cur[4+PPITH_DWORD*2];
				pEmuVideoUpdate[sTotal+5+544] = pTile_Cur[5+PPITH_DWORD*2];
				pEmuVideoUpdate[sTotal+6+544] = pTile_Cur[6+PPITH_DWORD*2];
				pEmuVideoUpdate[sTotal+7+544] = pTile_Cur[7+PPITH_DWORD*2]; // 2 
				pEmuVideoUpdate[sTotal+0+816] = pTile_Cur[0+PPITH_DWORD*3];
				pEmuVideoUpdate[sTotal+1+816] = pTile_Cur[1+PPITH_DWORD*3];
				pEmuVideoUpdate[sTotal+2+816] = pTile_Cur[2+PPITH_DWORD*3];
				pEmuVideoUpdate[sTotal+3+816] = pTile_Cur[3+PPITH_DWORD*3];
				pEmuVideoUpdate[sTotal+4+816] = pTile_Cur[4+PPITH_DWORD*3];
				pEmuVideoUpdate[sTotal+5+816] = pTile_Cur[5+PPITH_DWORD*3];
				pEmuVideoUpdate[sTotal+6+816] = pTile_Cur[6+PPITH_DWORD*3];
				pEmuVideoUpdate[sTotal+7+816] = pTile_Cur[7+PPITH_DWORD*3];	// 3 			
				pEmuVideoUpdate[sTotal+0+1088] = pTile_Cur[0+PPITH_DWORD*4];
				pEmuVideoUpdate[sTotal+1+1088] = pTile_Cur[1+PPITH_DWORD*4];
				pEmuVideoUpdate[sTotal+2+1088] = pTile_Cur[2+PPITH_DWORD*4];
				pEmuVideoUpdate[sTotal+3+1088] = pTile_Cur[3+PPITH_DWORD*4];
				pEmuVideoUpdate[sTotal+4+1088] = pTile_Cur[4+PPITH_DWORD*4];
				pEmuVideoUpdate[sTotal+5+1088] = pTile_Cur[5+PPITH_DWORD*4];
				pEmuVideoUpdate[sTotal+6+1088] = pTile_Cur[6+PPITH_DWORD*4];
				pEmuVideoUpdate[sTotal+7+1088] = pTile_Cur[7+PPITH_DWORD*4]; // 4
				pEmuVideoUpdate[sTotal+0+1360] = pTile_Cur[0+PPITH_DWORD*5];
				pEmuVideoUpdate[sTotal+1+1360] = pTile_Cur[1+PPITH_DWORD*5];
				pEmuVideoUpdate[sTotal+2+1360] = pTile_Cur[2+PPITH_DWORD*5];
				pEmuVideoUpdate[sTotal+3+1360] = pTile_Cur[3+PPITH_DWORD*5];
				pEmuVideoUpdate[sTotal+4+1360] = pTile_Cur[4+PPITH_DWORD*5];
				pEmuVideoUpdate[sTotal+5+1360] = pTile_Cur[5+PPITH_DWORD*5];
				pEmuVideoUpdate[sTotal+6+1360] = pTile_Cur[6+PPITH_DWORD*5];
				pEmuVideoUpdate[sTotal+7+1360] = pTile_Cur[7+PPITH_DWORD*5]; // 5 
				pEmuVideoUpdate[sTotal+0+1632] = pTile_Cur[0+PPITH_DWORD*6];
				pEmuVideoUpdate[sTotal+1+1632] = pTile_Cur[1+PPITH_DWORD*6];
				pEmuVideoUpdate[sTotal+2+1632] = pTile_Cur[2+PPITH_DWORD*6];
				pEmuVideoUpdate[sTotal+3+1632] = pTile_Cur[3+PPITH_DWORD*6];
				pEmuVideoUpdate[sTotal+4+1632] = pTile_Cur[4+PPITH_DWORD*6];
				pEmuVideoUpdate[sTotal+5+1632] = pTile_Cur[5+PPITH_DWORD*6];
				pEmuVideoUpdate[sTotal+6+1632] = pTile_Cur[6+PPITH_DWORD*6];
				pEmuVideoUpdate[sTotal+7+1632] = pTile_Cur[7+PPITH_DWORD*6]; // 6 
				pEmuVideoUpdate[sTotal+0+1904] = pTile_Cur[0+PPITH_DWORD*7];
				pEmuVideoUpdate[sTotal+1+1904] = pTile_Cur[1+PPITH_DWORD*7];
				pEmuVideoUpdate[sTotal+2+1904] = pTile_Cur[2+PPITH_DWORD*7];
				pEmuVideoUpdate[sTotal+3+1904] = pTile_Cur[3+PPITH_DWORD*7];
				pEmuVideoUpdate[sTotal+4+1904] = pTile_Cur[4+PPITH_DWORD*7];
				pEmuVideoUpdate[sTotal+5+1904] = pTile_Cur[5+PPITH_DWORD*7];
				pEmuVideoUpdate[sTotal+6+1904] = pTile_Cur[6+PPITH_DWORD*7];
				pEmuVideoUpdate[sTotal+7+1904] = pTile_Cur[7+PPITH_DWORD*7]; // 7
				
				

				*/