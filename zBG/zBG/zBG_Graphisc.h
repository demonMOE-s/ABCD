#ifndef ___$zBG__GRAPHISC_
#define ___$zBG__GRAPHISC_

#include "zBG_DirectX_Driver.h"

void STDWIN32_CALL zBG_Graphics_Render(void);
BOOL STDWIN32_CALL zBG_init_Screen(HWND hwnd);
void STDWIN32_CALL zBG_destroy_Screen(void);
void STDWIN32_CALL zBG_image_release(void);

#endif 


