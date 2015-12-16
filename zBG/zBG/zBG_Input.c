#include "zBG_Input.h"
#include "zBG_Global.h"

BOOL STDWIN32_CALL zBG_set_keyboard(HWND hwnd) {

#define __TRYS_(x){if(S_OK!=x) goto __final;}
#define __DCOM_(x){if(NULL!=x) x->lpVtbl->Release(x); x=NULL;}

	__TRYS_(IBaseInput->lpVtbl->CreateDevice(IBaseInput,&GUID_SysKeyboard,&JoyPad,NULL));
	__TRYS_(JoyPad->lpVtbl->SetCooperativeLevel(JoyPad,hwnd,DISCL_NONEXCLUSIVE | DISCL_BACKGROUND));
	__TRYS_(JoyPad->lpVtbl->SetDataFormat(JoyPad,&c_dfDIKeyboard));
	__TRYS_(JoyPad->lpVtbl->Acquire(JoyPad));

	return TRUE;

__final:
	__DCOM_(JoyPad);
#undef __TRYS_
#undef __DCOM_
	return FALSE;
}

void STDWIN32_CALL zBG_destory_keyboard(void) {

	JoyPad->lpVtbl->Unacquire(JoyPad);
	JoyPad->lpVtbl->Release(JoyPad);
}

ZBG_API void STDWIN32_CALL ZlSetPadMapper( u8 Key_A,
												u8 Key_B,
												u8 Key_Select,
												u8 Key_Start,
												u8 Key_Up,
												u8 Key_Down,
												u8 Key_Left,
												u8 Key_Right )
{
	GloBal_Key_Mapper_Buffer[0] = Key_A;
	GloBal_Key_Mapper_Buffer[1] = Key_B;
	GloBal_Key_Mapper_Buffer[2] = Key_Select;
	GloBal_Key_Mapper_Buffer[3] = Key_Start;
	GloBal_Key_Mapper_Buffer[4] = Key_Up;
	GloBal_Key_Mapper_Buffer[5] = Key_Down;
	GloBal_Key_Mapper_Buffer[6] = Key_Left;
	GloBal_Key_Mapper_Buffer[7] = Key_Right;
}

