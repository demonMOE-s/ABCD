#ifndef ___$zBG__BACKGROUND_BUFFER_MAIN_
#define ___$zBG__BACKGROUND_BUFFER_MAIN_

#include "zBG_DirectX_Driver.h"

#define VERT 1
#define HORI 0

typedef struct _sprite_OAM {
	u32 Tile_Id;
	u32 Attrs;
	u32 PosX;
	u32 PosY;
} sprite_OAM_s;

typedef struct _ntCTRL {
	
	u32 SCR0_x; /* for X scrolling range 0 ~ 31 NT0 */
	u32 SCR0_y; /* for Y scrolling range 0 ~ 27 NT0 */
	u32 SCR0_fine_x; /* for tile X mini scrolling 0 ~ 7 NT0 */
	u32 SCR0_fine_y; /* for tile Y mini scrolling 0 ~ 7 NT0 */
	u32 VMR0_x; /* write vram pos x NT0 */
	u32 VMR0_y; /* write vram pos y NT0 */
	u32 VMR1_x; /* write vram pos x NT1 */
	u32 VMR1_y; /* write vram pos y NT1 */
	u32 VMR2_x; /* write vram pos x NT2 */
	u32 VMR2_y; /* write vram pos y NT2 */
	u32 Tran_Id;/* Trans's Tile ID */
	u32 Tran_Color;/* Tran's Color */ 
	u32 ntPagePointerSCR0;/* scroll page select NT0 */
	u32 ntPagePointerVMR0;/* write vram pgae select NT0 */
	u32 Tran_Buffer[4]; /* for movdqa */
	u32 Tran_Level_look_up_table[40]; /* etc ... */ 
	u32 ntPageWriteBSC_s0;/* vram inc type NT0 */
	u32 ntPageWriteBSC_s1;/* vram inc type NT1 */
	u32 ntPageWriteBSC_s2;/* vram inc type NT2 */
	bool_ bdisnt0;
	bool_ bdisnt1;
	bool_ bdisnt2;
} ntCTRL_s;

typedef struct _dsf {
	u32 IX;
	u32 IY;
	u32 RX;
	u32 RY;
} distance_s;

typedef struct _dccsds {
	
	u32 ALLScreenCount;
	u32 Nt1ScreenCount;
	u32 Nt2ScreenCount;
	bool_ bALLReverse;
	distance_s Nt1Rect;
	distance_s Nt2Rect;
} alpha_s;

#endif