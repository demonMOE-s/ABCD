/* ------------------------------- Inline_Misc0.h -------------------------------------- */ 

				__asm {
					push	esi 
					push	edi 					
					mov		edi, [sTotal]
					mov		esi, [pTile_Cur]
					lea		edi, [edi*4]
					add		edi, [pEmuVideoBuffer]
/*---------------------------- 0 - fetch align ------------------------*/
					movaps	xmm0, [esi+000h+00000h]
					movaps	xmm1, [esi+010h+00000h]
					movaps  xmm2, [esi+000h+00800h]
					movaps  xmm3, [esi+010h+00800h]
					movaps	xmm4, [esi+000h+01000h]
					movaps	xmm5, [esi+010h+01000h]
					movaps  xmm6, [esi+000h+01800h]
					movaps  xmm7, [esi+010h+01800h]
/*---------------------------- 0 - write unalign ------------------------*/
					movups	[edi+000h+00000h], xmm0
					movups	[edi+010h+00000h], xmm1
					movups  [edi+000h+1088], xmm2
					movups  [edi+010h+1088], xmm3
					movups	[edi+000h+2176], xmm4 
					movups	[edi+010h+2176], xmm5
					movups  [edi+000h+1088*3], xmm6
					movups  [edi+010h+1088*3], xmm7
/*---------------------------- 1 - fetch align ------------------------*/
					movaps	xmm0, [esi+000h+02000h]
					movaps	xmm1, [esi+010h+02000h]
					movaps  xmm2, [esi+000h+02800h]
					movaps  xmm3, [esi+010h+02800h]
					movaps	xmm4, [esi+000h+03000h]
					movaps	xmm5, [esi+010h+03000h]
					movaps  xmm6, [esi+000h+03800h]
					movaps  xmm7, [esi+010h+03800h]
/*---------------------------- 1 - write unalign ------------------------*/
					movups	[edi+000h+1088*4], xmm0
					movups	[edi+010h+1088*4], xmm1
					movups  [edi+000h+1088*5], xmm2
					movups  [edi+010h+1088*5], xmm3
					movups	[edi+000h+1088*6], xmm4 
					movups	[edi+010h+1088*6], xmm5
					movups  [edi+000h+1088*7], xmm6
					movups  [edi+010h+1088*7], xmm7
					pop edi 
					pop esi
				}
/*
				pEmuVideoBuffer[sTotal+0] = pTile_Cur[0];
				pEmuVideoBuffer[sTotal+1] = pTile_Cur[1];
				pEmuVideoBuffer[sTotal+2] = pTile_Cur[2];
				pEmuVideoBuffer[sTotal+3] = pTile_Cur[3];
				pEmuVideoBuffer[sTotal+4] = pTile_Cur[4];
				pEmuVideoBuffer[sTotal+5] = pTile_Cur[5];
				pEmuVideoBuffer[sTotal+6] = pTile_Cur[6];
				pEmuVideoBuffer[sTotal+7] = pTile_Cur[7]; // 0
				pEmuVideoBuffer[sTotal+0+272] = pTile_Cur[0+PPITH_DWORD];
				pEmuVideoBuffer[sTotal+1+272] = pTile_Cur[1+PPITH_DWORD];
				pEmuVideoBuffer[sTotal+2+272] = pTile_Cur[2+PPITH_DWORD];
				pEmuVideoBuffer[sTotal+3+272] = pTile_Cur[3+PPITH_DWORD];
				pEmuVideoBuffer[sTotal+4+272] = pTile_Cur[4+PPITH_DWORD];
				pEmuVideoBuffer[sTotal+5+272] = pTile_Cur[5+PPITH_DWORD];
				pEmuVideoBuffer[sTotal+6+272] = pTile_Cur[6+PPITH_DWORD];
				pEmuVideoBuffer[sTotal+7+272] = pTile_Cur[7+PPITH_DWORD]; // 1
				pEmuVideoBuffer[sTotal+0+544] = pTile_Cur[0+PPITH_DWORD*2];
				pEmuVideoBuffer[sTotal+1+544] = pTile_Cur[1+PPITH_DWORD*2];
				pEmuVideoBuffer[sTotal+2+544] = pTile_Cur[2+PPITH_DWORD*2];
				pEmuVideoBuffer[sTotal+3+544] = pTile_Cur[3+PPITH_DWORD*2];
				pEmuVideoBuffer[sTotal+4+544] = pTile_Cur[4+PPITH_DWORD*2];
				pEmuVideoBuffer[sTotal+5+544] = pTile_Cur[5+PPITH_DWORD*2];
				pEmuVideoBuffer[sTotal+6+544] = pTile_Cur[6+PPITH_DWORD*2];
				pEmuVideoBuffer[sTotal+7+544] = pTile_Cur[7+PPITH_DWORD*2]; // 2 
				pEmuVideoBuffer[sTotal+0+816] = pTile_Cur[0+PPITH_DWORD*3];
				pEmuVideoBuffer[sTotal+1+816] = pTile_Cur[1+PPITH_DWORD*3];
				pEmuVideoBuffer[sTotal+2+816] = pTile_Cur[2+PPITH_DWORD*3];
				pEmuVideoBuffer[sTotal+3+816] = pTile_Cur[3+PPITH_DWORD*3];
				pEmuVideoBuffer[sTotal+4+816] = pTile_Cur[4+PPITH_DWORD*3];
				pEmuVideoBuffer[sTotal+5+816] = pTile_Cur[5+PPITH_DWORD*3];
				pEmuVideoBuffer[sTotal+6+816] = pTile_Cur[6+PPITH_DWORD*3];
				pEmuVideoBuffer[sTotal+7+816] = pTile_Cur[7+PPITH_DWORD*3];	// 3 			
				pEmuVideoBuffer[sTotal+0+1088] = pTile_Cur[0+PPITH_DWORD*4];
				pEmuVideoBuffer[sTotal+1+1088] = pTile_Cur[1+PPITH_DWORD*4];
				pEmuVideoBuffer[sTotal+2+1088] = pTile_Cur[2+PPITH_DWORD*4];
				pEmuVideoBuffer[sTotal+3+1088] = pTile_Cur[3+PPITH_DWORD*4];
				pEmuVideoBuffer[sTotal+4+1088] = pTile_Cur[4+PPITH_DWORD*4];
				pEmuVideoBuffer[sTotal+5+1088] = pTile_Cur[5+PPITH_DWORD*4];
				pEmuVideoBuffer[sTotal+6+1088] = pTile_Cur[6+PPITH_DWORD*4];
				pEmuVideoBuffer[sTotal+7+1088] = pTile_Cur[7+PPITH_DWORD*4]; // 4
				pEmuVideoBuffer[sTotal+0+1360] = pTile_Cur[0+PPITH_DWORD*5];
				pEmuVideoBuffer[sTotal+1+1360] = pTile_Cur[1+PPITH_DWORD*5];
				pEmuVideoBuffer[sTotal+2+1360] = pTile_Cur[2+PPITH_DWORD*5];
				pEmuVideoBuffer[sTotal+3+1360] = pTile_Cur[3+PPITH_DWORD*5];
				pEmuVideoBuffer[sTotal+4+1360] = pTile_Cur[4+PPITH_DWORD*5];
				pEmuVideoBuffer[sTotal+5+1360] = pTile_Cur[5+PPITH_DWORD*5];
				pEmuVideoBuffer[sTotal+6+1360] = pTile_Cur[6+PPITH_DWORD*5];
				pEmuVideoBuffer[sTotal+7+1360] = pTile_Cur[7+PPITH_DWORD*5]; // 5 
				pEmuVideoBuffer[sTotal+0+1632] = pTile_Cur[0+PPITH_DWORD*6];
				pEmuVideoBuffer[sTotal+1+1632] = pTile_Cur[1+PPITH_DWORD*6];
				pEmuVideoBuffer[sTotal+2+1632] = pTile_Cur[2+PPITH_DWORD*6];
				pEmuVideoBuffer[sTotal+3+1632] = pTile_Cur[3+PPITH_DWORD*6];
				pEmuVideoBuffer[sTotal+4+1632] = pTile_Cur[4+PPITH_DWORD*6];
				pEmuVideoBuffer[sTotal+5+1632] = pTile_Cur[5+PPITH_DWORD*6];
				pEmuVideoBuffer[sTotal+6+1632] = pTile_Cur[6+PPITH_DWORD*6];
				pEmuVideoBuffer[sTotal+7+1632] = pTile_Cur[7+PPITH_DWORD*6]; // 6 
				pEmuVideoBuffer[sTotal+0+1904] = pTile_Cur[0+PPITH_DWORD*7];
				pEmuVideoBuffer[sTotal+1+1904] = pTile_Cur[1+PPITH_DWORD*7];
				pEmuVideoBuffer[sTotal+2+1904] = pTile_Cur[2+PPITH_DWORD*7];
				pEmuVideoBuffer[sTotal+3+1904] = pTile_Cur[3+PPITH_DWORD*7];
				pEmuVideoBuffer[sTotal+4+1904] = pTile_Cur[4+PPITH_DWORD*7];
				pEmuVideoBuffer[sTotal+5+1904] = pTile_Cur[5+PPITH_DWORD*7];
				pEmuVideoBuffer[sTotal+6+1904] = pTile_Cur[6+PPITH_DWORD*7];
				pEmuVideoBuffer[sTotal+7+1904] = pTile_Cur[7+PPITH_DWORD*7]; // 7
				
				*/

				