#include "zBG_DirectX_Driver.h"
#include "zBG_List.h"
#include "zBG_Background_Buffer_m.h"
#include "zBG_Sound.h"

pfun entry;
pwfun NativeQueryPerformanceCounter;
__int64 t64Qfreq;
__int64 t64Xsend;
__int64 t64Begin;

ALIGN sound_slot		wave_slot[128]={0}; /* wave gen */
ALIGN sprite_OAM_s		sprite_OAM[256]={0};/* sprite OAM */
ALIGN ntCTRL_s			ntCTRL; /* NameTable Control Struct */
ALIGN alpha_s			apCTRL = {5,4,4,0,0,32,28,0,0,32,28 };
ALIGN DWORD				NameTable0[32*28*4]; /* NameTable0 4K VRAM For Scrolling */
ALIGN DWORD				NameTable0Attr[33*29*8*8]; 
ALIGN DWORD				NameTable1[32*28*1]; /* NameTable1 1K VRAM For NES's UI[Font Data etc...] */
ALIGN DWORD				NameTable2[32*28*1]; /* - -... another Nametable */
ALIGN DWORD				NesEmuVideoBufferLine[(256+8*2)*(224+8*2)]; /* NES's Video Buffer */ 
u8						GloBal_Key_Buffer_Status[8]; /* GloBal Key Info */
u8						GloBal_Key_Mapper_Buffer[8]; /* GloBal Key Mapper Buffer */
u32*					Sprite_Chr=NULL;
u32*					BackGround_Chr=NULL;
u32*					Sprite_PooL=NULL;
u32*					BackGround_PooL=NULL;
zBG_List*				Image_List=NULL;
IDirect3D9*				IBaseD3d=NULL;
IXAudio2*				IBaseAudio=NULL;
IXAudio2MasteringVoice* IBaseAudioDevice=NULL;
IDirectInput8*			IBaseInput=NULL;
IDirectInputDevice8*	JoyPad=NULL;
IDirect3DDevice9*		IBaseGraphics=NULL;
IDirect3DSurface9*		IBaseVram=NULL;
D3DLOCKED_RECT			GVPointer={0};