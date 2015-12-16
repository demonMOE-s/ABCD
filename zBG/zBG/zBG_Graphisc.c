#include "zBG_Graphisc.h"
#include "zBG_Global.h"
#include "zBG_dlmalloc.h"

BOOL STDWIN32_CALL zBG_init_Screen(HWND hwnd) {

#define __TRYS_(x){if(S_OK!=x) goto __final;}
#define __DCOM_(x){if(NULL!=x) x->lpVtbl->Release(x);x=NULL;}

	D3DPRESENT_PARAMETERS d3dpp = {0};
	d3dpp.BackBufferFormat      = D3DFMT_X8R8G8B8;
	d3dpp.SwapEffect            = D3DSWAPEFFECT_DISCARD; 
	d3dpp.Flags					= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	d3dpp.hDeviceWindow         = hwnd;
	d3dpp.Windowed              = TRUE;
	d3dpp.PresentationInterval  = D3DPRESENT_INTERVAL_IMMEDIATE;	/* disable VSync */ 

	__TRYS_(IBaseD3d->lpVtbl->CreateDevice(IBaseD3d,0,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&IBaseGraphics));
	__TRYS_(IBaseGraphics->lpVtbl->GetBackBuffer(IBaseGraphics,0,0,D3DBACKBUFFER_TYPE_MONO,&IBaseVram));
	__TRYS_(IBaseVram->lpVtbl->LockRect(IBaseVram,&GVPointer,NULL,D3DLOCK_DISCARD | D3DLOCK_NOOVERWRITE));
	__TRYS_(IBaseVram->lpVtbl->UnlockRect(IBaseVram));

	return TRUE;

__final:
	__DCOM_(IBaseVram);
	__DCOM_(IBaseGraphics);

#undef __TRYS_
#undef __DCOM_

	return FALSE;
}

void STDWIN32_CALL zBG_destroy_Screen(void) {

	IBaseVram->lpVtbl->Release(IBaseVram);
	IBaseGraphics->lpVtbl->Release(IBaseGraphics);
	//IBaseD3d->lpVtbl->Release(IBaseD3d);
}

void* STDWIN32_CALL zBG_image_from_file_ansi(char* fn, int width, int height) {

	DWORD poll_X;
	DWORD poll_Y;
	DWORD* pSource_Data = NULL;
	DWORD* pImage_Data = NULL; /* init */
	D3DLOCKED_RECT Texture_Rect = {0};
	IDirect3DTexture9* Image_Texture = NULL; /* init */
	STATIC INT bInitL_List = FALSE;

	if (bInitL_List == FALSE) {
	/* Init List */
		if (FALSE == create_list(&Image_List))	return NULL;
		bInitL_List = TRUE;
	}
	if (S_OK != D3DXCreateTextureFromFileExA(IBaseGraphics,
											fn,
											width,
											height,
											D3DX_FROM_FILE, /* disable mipmap chain */
											0,
											D3DFMT_UNKNOWN,
											D3DPOOL_MANAGED,
											D3DX_DEFAULT, 
											D3DX_DEFAULT,
											D3DCOLOR_XRGB(0,0,0), 
											NULL, 
											NULL,
											&Image_Texture
											) ) {
		return NULL;
	}
	if (S_OK != Image_Texture->lpVtbl->LockRect(Image_Texture, 
												0, 
												&Texture_Rect, 
												NULL, 
												D3DLOCK_READONLY
												) ) {
		Image_Texture->lpVtbl->Release(Image_Texture);
		return NULL;
	}
	pImage_Data = dlmemalign(16, height*width*4);
	pSource_Data= Texture_Rect.pBits;

	for (poll_Y = 0; poll_Y != height; poll_Y ++) {
		for (poll_X = 0; poll_X != width; poll_X ++) {
			pImage_Data[poll_Y*width+poll_X] = pSource_Data[poll_Y*Texture_Rect.Pitch/4+poll_X];
		}
	}
	Image_Texture->lpVtbl->UnlockRect(Image_Texture,0);
	Image_Texture->lpVtbl->Release(Image_Texture);
	insert_list(Image_List,pImage_Data);
	return pImage_Data;
}

ZBG_API BOOL STDWIN32_CALL ZlLoadChr(char* fnBG, char* fnSP, int h0, int h1, int Trans_ID) {
	u32 i;
	ntCTRL.Tran_Id = Trans_ID;
	Sprite_PooL = zBG_image_from_file_ansi(fnSP,512,h1);
	BackGround_PooL = zBG_image_from_file_ansi(fnBG,512,h0);
	if (NULL == (Sprite_PooL)
	||  NULL == (BackGround_PooL)) return FALSE;
	Sprite_Chr = dlmemalign(16,h1*512*4);
	BackGround_Chr = dlmemalign(16, h0*512*4);
	memcpy(Sprite_Chr,Sprite_PooL,h1*512*4);
	memcpy(BackGround_Chr,BackGround_Chr,h0*512*4);
	ntCTRL.Tran_Color = BackGround_PooL[((Trans_ID&63)<<3)+((Trans_ID>>6)<<3)*PPITH_DWORD];
	for (i=0;i!=4;i++) { // Fill Color
		ntCTRL.Tran_Buffer[i] = ntCTRL.Tran_Color;
	}
	for (i=0;i!=64;i++) { // dis OAM
		sprite_OAM[i].Attrs |= OAM_DISABLE_BIT;
	}
	for (i=0;i!=32*28*4;i++) { // reset BG0
		NameTable0[i] = Trans_ID;
	}
	for (i=0;i!=32*28;i++) { // reset BG1
		NameTable1[i] = Trans_ID;
	}
	for (i=0;i!=32*28;i++) { // reset BG1
		NameTable2[i] = Trans_ID;
	}
	return TRUE;
}

void STDWIN32_CALL zBG_image_release(void) {

	zBG_List* zBG_Poll_cur = Image_List;

	if (Image_List == NULL)	return;
	if (Image_List->data == NULL) return;

	while(TRUE) {
		dlfree(zBG_Poll_cur->data);
		if (NULL == zBG_Poll_cur->next) {
			delete_list(Image_List);
			return;
		}
		zBG_Poll_cur = zBG_Poll_cur->next;
	}
	dlfree(Sprite_Chr);
	dlfree(BackGround_Chr);
}

void* STDWIN32_CALL zBG_image_from_resource_ansi(int resID, int width, int height) {

	IDirect3DTexture9* Image_Texture = NULL; /* init */
}





