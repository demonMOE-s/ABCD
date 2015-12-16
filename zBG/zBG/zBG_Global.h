#ifndef ___$zBG__GLOBAL_
#define ___$zBG__GLOBAL_

#include <d3d9.h>
#include <d3dx9.h>
#include <XAudio2.h>
#include <dinput.h>
#include "zBG_Marco.h"
#include "zBG_List.h"
#include "zBG_Sound.h"
#include "zBG_Background_Buffer_m.h"

#define OAM_DISABLE_BIT  0x01 
#define OAM_VERTFILP_BIT 0x80
#define OAM_HORIFILP_BIT 0x40
#define OAM_BACKITOS_BIT 0x20
#define PICTURE_PITCH    2048 /* 64 Tile every Line */
#define PPITH_DWORD		 512
#define ASM_BEGIN		__asm {
#define	ASM_END			}

EXTERN ALIGN sound_slot			wave_slot[128]; /* wave gen */
EXTERN ALIGN sprite_OAM_s		sprite_OAM[256];/* sprite OAM */
EXTERN ALIGN ntCTRL_s			ntCTRL; /* NameTable Control Struct */
EXTERN ALIGN alpha_s			apCTRL;
EXTERN ALIGN DWORD				NameTable0[32*28*4]; /* NameTable0 4K VRAM For Scrolling */
EXTERN ALIGN DWORD				NameTable0Attr[33*29*8*8]; /* NameTable0 Attr */
EXTERN ALIGN DWORD				NameTable1[32*28*1]; /* NameTable1 1K VRAM For NES's UI[Font Data etc...] */
EXTERN ALIGN DWORD				NameTable2[32*28*1]; /* - -... another Nametable */
EXTERN ALIGN DWORD				NesEmuVideoBufferLine[(256+8*2)*(224+8*2)]; /* NES's Video Buffer */ 
EXTERN u8						GloBal_Key_Buffer_Status[8]; /* GloBal Key Info */
EXTERN u8						GloBal_Key_Mapper_Buffer[8]; /* GloBal Key Mapper Buffer */


EXTERN pfun entry;
EXTERN pwfun NativeQueryPerformanceCounter;
EXTERN __int64 t64Xsend;
EXTERN __int64 t64Begin;
EXTERN __int64 t64Qfreq;
EXTERN u32						Alpha_Count;
EXTERN u32*						Sprite_Chr;
EXTERN u32*						BackGround_Chr;
EXTERN u32*						Sprite_PooL;
EXTERN u32*						BackGround_PooL;
EXTERN zBG_List*				Image_List;
EXTERN IDirect3D9*				IBaseD3d;
EXTERN IXAudio2*				IBaseAudio;
EXTERN IXAudio2MasteringVoice* IBaseAudioDevice;
EXTERN IDirectInput8*			IBaseInput;
EXTERN IDirectInputDevice8*		JoyPad;
EXTERN IDirect3DDevice9*		IBaseGraphics;
EXTERN IDirect3DSurface9*		IBaseVram;
EXTERN D3DLOCKED_RECT			GVPointer;

#endif 