#ifndef ___$zBG__INPUT_
#define ___$zBG__INPUT_

#include "zBG_DirectX_Driver.h"

#define KEY_DOWN    2 
#define KEY_UP      4 
#define KEY_FIRST   1
#define KEY_DISCARD 0

BOOL STDWIN32_CALL zBG_set_keyboard(HWND hwnd);

void STDWIN32_CALL zBG_destory_keyboard(void);

ZBG_API void STDWIN32_CALL ZlSetPadMapper( u8 Key_A,
												u8 Key_B,
												u8 Key_Select,
												u8 Key_Start,
												u8 Key_Up,
												u8 Key_Down,
												u8 Key_Left,
												u8 Key_Right );

#endif 