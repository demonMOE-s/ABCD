#include "zBG_DirectX_Driver.h"
#include "zBG_Global.h"

BOOL STDWIN32_CALL zBG_init_directx_base(void) {
	
	if(S_OK!=CoInitializeEx(NULL, COINIT_MULTITHREADED)) return FALSE; /* init MultiThread COM - for IXAudio2 Ready */

	IBaseD3d=
		Direct3DCreate9(D3D_SDK_VERSION);	/* IDirect3D Base Get */
	if(IBaseD3d==NULL) goto __final;
	if(S_OK!=XAudio2Create(&IBaseAudio, 0, XAUDIO2_DEFAULT_PROCESSOR)) /* IXAudio2 Base Get */
				   goto __final;
	if(S_OK!=DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION,&IID_IDirectInput8,(void **)&IBaseInput,NULL)) /* IDirectInput8 Base Get */
				   goto __final;
	if(S_OK!=IBaseAudio->lpVtbl->CreateMasteringVoice(IBaseAudio, &IBaseAudioDevice, XAUDIO2_DEFAULT_CHANNELS,XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL))
				   goto __final;

	return TRUE; /* do ret */
	
__final:
	if (IBaseD3d != NULL)		IBaseD3d->lpVtbl->Release(IBaseD3d);		IBaseD3d=NULL;
	if (IBaseInput != NULL)		IBaseInput->lpVtbl->Release(IBaseInput);	IBaseInput=NULL;
	if (IBaseAudio != NULL) 	IBaseAudio->lpVtbl->Release(IBaseAudio);	IBaseAudio=NULL;
	CoUninitialize();		return FALSE; /* release ret */
}

void STDWIN32_CALL zBG_destroy_directx_base(void) {

	if (IBaseD3d != NULL)		IBaseD3d->lpVtbl->Release(IBaseD3d);		/* destory IDirect3D Base */
	if (IBaseInput != NULL)		IBaseInput->lpVtbl->Release(IBaseInput);	/* destory IDirectInput8 Base */
	if (IBaseAudioDevice != NULL) IBaseAudioDevice->lpVtbl->DestroyVoice(IBaseAudioDevice);
	if (IBaseAudio != NULL) 	IBaseAudio->lpVtbl->Release(IBaseAudio);	CoUninitialize(); /* destory IXAudio2-COM Quit */
}







