#ifndef NT1_MARCO
	NT2_$25_SCANLINE_RENDER:
#else 
	NT1_$25_SCANLINE_RENDER:
#endif
/* ------------------------------- NameTable2 alpha 25% render -------------------------------------- */ 
for (yPoLL=0;yPoLL!=28;yPoLL++) {
	for (xPoLL=0;xPoLL!=32;xPoLL++) {
		/* -------------------------- line render -------------------------------- */
		sTotal = (xPoLL << 3) + yPoLL*2176;
	#ifndef NT1_MARCO
		Tile_Id = NameTable2[xPoLL+(yPoLL<<5)]; // get tile id 
	#else 
		Tile_Id = NameTable1[xPoLL+(yPoLL<<5)]; // get tile id 
	#endif
		pTile_Cur = &BackGround_PooL[((Tile_Id&63)<<3)+((Tile_Id>>6)<<3)*PPITH_DWORD]; // lock area
#ifndef NT1_MARCO
		if (!((xPoLL >= apCTRL.Nt2Rect.IX)
			&&	(yPoLL >= apCTRL.Nt2Rect.IY)
			&&  (apCTRL.Nt2Rect.IX  + apCTRL.Nt2Rect.RX) > xPoLL
			&&  (apCTRL.Nt2Rect.IY  + apCTRL.Nt2Rect.RY) > yPoLL))
#else 
		if (!((xPoLL >= apCTRL.Nt1Rect.IX)
			&&	(yPoLL >= apCTRL.Nt1Rect.IY)
			&&  (apCTRL.Nt1Rect.IX  + apCTRL.Nt1Rect.RX) > xPoLL
			&&  (apCTRL.Nt1Rect.IY  + apCTRL.Nt1Rect.RY) > yPoLL)) 
#endif
		{
			if (ntCTRL.Tran_Id != Tile_Id) 
				/* not TransTile ? */ {
				#if 0
					for (my=0;my!=8;my++) {
						/* draw 8 * 8 martix */ 
						if (pTile_Cur[PPITH_DWORD*my+0]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+0+my*272] = pTile_Cur[PPITH_DWORD*my+0];
						if (pTile_Cur[PPITH_DWORD*my+1]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+1+my*272] = pTile_Cur[PPITH_DWORD*my+1];
						if (pTile_Cur[PPITH_DWORD*my+2]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+2+my*272] = pTile_Cur[PPITH_DWORD*my+2];
						if (pTile_Cur[PPITH_DWORD*my+3]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+3+my*272] = pTile_Cur[PPITH_DWORD*my+3];
						if (pTile_Cur[PPITH_DWORD*my+4]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+4+my*272] = pTile_Cur[PPITH_DWORD*my+4];
						if (pTile_Cur[PPITH_DWORD*my+5]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+5+my*272] = pTile_Cur[PPITH_DWORD*my+5];
						if (pTile_Cur[PPITH_DWORD*my+6]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+6+my*272] = pTile_Cur[PPITH_DWORD*my+6];
						if (pTile_Cur[PPITH_DWORD*my+7]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+7+my*272] = pTile_Cur[PPITH_DWORD*my+7];
					}
				#else		
					#include "Inline_Misc1.h"
				#endif
			}
		} 
		else 
		{
			if (ntCTRL.Tran_Id != Tile_Id) 
				/* not TransTile ? */ {
					for (my=0;my!=8;my++) {
						/* draw 8 * 8 martix */ 
						if (pTile_Cur[PPITH_DWORD*my+0]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+0+my*272] = c32alpha(pTile_Cur[PPITH_DWORD*my+0], 64);
						if (pTile_Cur[PPITH_DWORD*my+1]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+1+my*272] = c32alpha(pTile_Cur[PPITH_DWORD*my+1], 64);
						if (pTile_Cur[PPITH_DWORD*my+2]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+2+my*272] = c32alpha(pTile_Cur[PPITH_DWORD*my+2], 64);
						if (pTile_Cur[PPITH_DWORD*my+3]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+3+my*272] = c32alpha(pTile_Cur[PPITH_DWORD*my+3], 64);
						if (pTile_Cur[PPITH_DWORD*my+4]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+4+my*272] = c32alpha(pTile_Cur[PPITH_DWORD*my+4], 64);
						if (pTile_Cur[PPITH_DWORD*my+5]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+5+my*272] = c32alpha(pTile_Cur[PPITH_DWORD*my+5], 64);
						if (pTile_Cur[PPITH_DWORD*my+6]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+6+my*272] = c32alpha(pTile_Cur[PPITH_DWORD*my+6], 64);
						if (pTile_Cur[PPITH_DWORD*my+7]!=ntCTRL.Tran_Color) pEmuVideoUpdate[xPoLL*8+yPoLL*272*8+7+my*272] = c32alpha(pTile_Cur[PPITH_DWORD*my+7], 64);
					}
			}
		}
	}		
}
#ifndef NT1_MARCO
	goto SP_MIX;
#else 
	goto NT2_CHECK;
#endif