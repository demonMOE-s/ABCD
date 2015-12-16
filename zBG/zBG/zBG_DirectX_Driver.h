#ifndef ___$zBG__DIRECTX_DRVIER_
#define ___$zBG__DIRECTX_DRVIER_

#include <d3d9.h>
#include <d3dx9.h>
#include <XAudio2.h>
#include <dinput.h>
#include "zBG_Marco.h"
#include "zBG_List.h"
#include "zBG_Background_Buffer_m.h"

typedef int (*__cdecl pfun)(u32* palpha, void* oam, void* s,INT n, INT ne);
typedef long (__stdcall* pwfun)(void* a, void* b);

BOOL STDWIN32_CALL zBG_init_directx_base(void);
void STDWIN32_CALL zBG_destroy_directx_base(void);

#endif 