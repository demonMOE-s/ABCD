/* ------------------------------- NameTable 100% render -------------------------------------- */ 
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
	if (ntCTRL.Tran_Id != Tile_Id) 
			/* not TransTile ? */ {
#include "Inline_Misc1.h"
		} 
	}		
}
#ifndef NT1_MARCO
	goto SP_MIX;
#else 
	goto NT2_CHECK;
#endif