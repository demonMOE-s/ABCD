#include "zBG_Background_Buffer_m.h"
#include "zBG_Global.h"

ZBG_API void STDWIN32_CALL Nt0SetWriteIncType(u32 inc0, u32 inc1) {

	ntCTRL.ntPageWriteBSC_s0 = inc0;
	ntCTRL.ntPageWriteBSC_s1 = inc1;
}

ZBG_API void STDWIN32_CALL NtHackBgChr(u32 pool_id, u32 chr_id) {
	
	u32* sptr = &BackGround_Chr[((chr_id&63)<<3)+((chr_id>>6)<<3)*PPITH_DWORD];
	u32* bptr = &BackGround_PooL[((pool_id&63)<<3)+((pool_id>>6)<<3)*PPITH_DWORD];
#include "Inline_Misc3.h"
}

ZBG_API void STDWIN32_CALL NtHackSpChr(u32 pool_id, u32 chr_id) {

	u32* sptr = &Sprite_Chr[((chr_id&63)<<3)+((chr_id>>6)<<3)*PPITH_DWORD];
	u32* bptr = &Sprite_PooL[((pool_id&63)<<3)+((pool_id>>6)<<3)*PPITH_DWORD];
#include "Inline_Misc3.h"
}

ZBG_API void STDWIN32_CALL Nt0SetWritePage(u32 index) {

	ntCTRL.ntPagePointerVMR0 = index & 3;
}

ZBG_API void STDWIN32_CALL Nt0SetScrollPage(u32 index) {

	ntCTRL.ntPagePointerSCR0 = index & 3;
}

ZBG_API void STDWIN32_CALL Nt0SetScroll(u32 x, u32 y, u32 fx, u32 fy) {

	ntCTRL.SCR0_x=x&31;
	ntCTRL.SCR0_y=y>27?27:y;
	ntCTRL.SCR0_fine_x=fx&7;
	ntCTRL.SCR0_fine_y=fy&7;
}

ZBG_API void STDWIN32_CALL NtaSetWriteAddress(u32 x0, u32 y0, u32 x1, u32 y1) {

	ntCTRL.VMR0_x=x0&31;
	ntCTRL.VMR0_y=y0>27?27:y0;
	ntCTRL.VMR1_x=x1&31;
	ntCTRL.VMR1_y=y1>27?27:y1;
}

ZBG_API void STDWIN32_CALL NtaSetWriteTileIdEx(u32 page, u32 x, u32 y, u32 tid) {

	if (page>4)
		NameTable2[x+y*32]=tid;
	else if (page == 4)
		NameTable1[x+y*32]=tid;
	else 
		NameTable0[page*28*32+x+y*32]=tid;
}

ZBG_API void STDWIN32_CALL Nt0SetWriteTileId(u32 Tile_Id) {

	ntCTRL.VMR0_x=ntCTRL.VMR0_x&31;
	ntCTRL.VMR0_y=ntCTRL.VMR0_y>27?27:ntCTRL.VMR0_y;
	NameTable0[32*28*ntCTRL.ntPagePointerVMR0+ntCTRL.VMR0_x+ntCTRL.VMR0_y*32]=Tile_Id;
	if (ntCTRL.ntPageWriteBSC_s0 == VERT) ntCTRL.VMR0_y++;
	else 
	{
		ntCTRL.VMR0_x++;
	}
}

ZBG_API void STDWIN32_CALL Nt1SetWriteTileId(u32 Tile_Id) {

	ntCTRL.VMR1_x=ntCTRL.VMR1_x&31;
	ntCTRL.VMR1_y=ntCTRL.VMR1_y>27?27:ntCTRL.VMR1_y;
	NameTable1[ntCTRL.VMR1_x+ntCTRL.VMR1_y*32]=Tile_Id;
	if (ntCTRL.ntPageWriteBSC_s1 == VERT) ntCTRL.VMR1_y++;
	else 
	{
		ntCTRL.VMR1_x++;
	}
}

ZBG_API void STDWIN32_CALL NtaCopyNoOverLeadUpPageRange (u32 page, u32 seqinx, u32 x, u32 y, u32 rx, u32 ry) {

	u32* 
	vpointer= (page >= 5  ? &NameTable2[x] 
						  : page == 4 
						  ? &NameTable1[x] : &NameTable0[page*28*32+x]) + y * 32;
	u32 tseqinx=seqinx;
	u32 lx,ly;

	if ( (rx == 0) 
	  || (ry == 0) ) return;

	for (ly=0; ly!=ry; ly++) {
		for (lx=0; lx!=rx; lx++) {
			vpointer[lx+ly*32]=seqinx; 
			seqinx++;
		}
		tseqinx += 64;
		seqinx = tseqinx;
	}
}

ZBG_API void STDWIN32_CALL NtaCopyPageRange (u32 page, u32* data, u32 x, u32 y, u32 sx, u32 sy) {

	u32 $x;
	u32 $y;
	u32 $xt;
	u32 $sx;
	u32 $sy;
	u32 $page = page;
	u32 $paget = page;
	u32 loop_x;
	u32 loop_y;
	
	if (page<4
	&& sx != 0
	&& sy != 0) {
/* in range */
		$x = x & 31;
		$xt = $x;
		$y = y > 27 ? 27 : y;
		$sx = sx > 32 ? 32 : sx;
		$sy = sy > 28 ? 28 : sy;
		for (loop_y = 0; loop_y != $sy; loop_y++) {
			for (loop_x = 0; loop_x != $sx; loop_x++) {
				NameTable0[$page*28*32+$x+$y*32] = data[loop_x+loop_y*32];
			}
			$x = $xt;
			$page = $paget;
		}
	}
}

ZBG_API void STDWIN32_CALL NtaCopyMiges (u32 page, u32 tileId, u32 x, u32 y, u32 rx, u32 ry) {

	u32* 
	vpointer= (page >= 5  ? &NameTable2[x] 
						  : page == 4 
						  ? &NameTable1[x] : &NameTable0[page*28*32+x]) + y * 32;
	u32 lx,ly;

	if ( (rx == 0) 
	  || (ry == 0) ) return;

	for (ly=0; ly!=ry; ly++) {
		for (lx=0; lx!=rx; lx++) {
			vpointer[lx+ly*32]=tileId; 
		}
	}
}

ZBG_API u32 STDWIN32_CALL NtaGetTileId(u32 page, u32 x, u32 y) {

	if (page>4) 
		return NameTable2[32*y+x];
	else if (page == 4)
		return NameTable1[32*y+x];
	else
		return NameTable0[28*32*page+32*y+x];
}

ZBG_API void* STDWIN32_CALL NtaSetPageTile(u32 page, u32 id) {

	int i;
	if (page>4) {
		for(i=0;i!=28*32;i++)	NameTable2[i]=id;
	} else if (page == 4) {
		for(i=0;i!=28*32;i++)	NameTable1[i]=id;
	} else {
		for(i=0;i!=28*32;i++)	NameTable0[page*28*32+i]=id;
	}
}

ZBG_API void STDWIN32_CALL NtaCopyPage(u32 page, u32* data) {

	if (page>4)
		memcpy(&NameTable2[0],&data[0],28*32*4);
	else if (page == 4)
		memcpy(&NameTable1[0],&data[0],28*32*4);
	else
		memcpy(&NameTable0[page*28*32],&data[0],28*32*4);
}

ZBG_API void STDWIN32_CALL NtaSoftwareDisable(u32 page) {

	NtaSetPageTile(page,ntCTRL.Tran_Id);
}

ZBG_API void STDWIN32_CALL NtaHardwareDisable(u32 page) {

	if (page>4)
		ntCTRL.bdisnt2=TRUE;
	else if (page == 4)
		ntCTRL.bdisnt1=TRUE;
	else
		ntCTRL.bdisnt0=TRUE;
}

ZBG_API void STDWIN32_CALL NtaHardwareThaw(u32 page) {

	if (page>4)
		ntCTRL.bdisnt2=FALSE;
	else if (page == 4)
		ntCTRL.bdisnt1=FALSE;
	else
		ntCTRL.bdisnt0=FALSE;
}