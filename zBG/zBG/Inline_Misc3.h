/* ------------------------------- Inline_Misc3.h -------------------------------------- */ 
			__asm {
					push	esi 
					push	edi 					
					mov 	esi,  [sptr]
					mov		edi,  [bptr]
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
					movaps	[edi+000h+00000h], xmm0
					movaps	[edi+010h+00000h], xmm1
					movaps  [edi+000h+00800h], xmm2
					movaps  [edi+010h+00800h], xmm3
					movaps	[edi+000h+01000h], xmm4 
					movaps	[edi+010h+01000h], xmm5
					movaps  [edi+000h+01800h], xmm6
					movaps  [edi+010h+01800h], xmm7
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
					movaps	[edi+000h+02000h], xmm0
					movaps	[edi+010h+02000h], xmm1
					movaps  [edi+000h+02800h], xmm2
					movaps  [edi+010h+02800h], xmm3
					movaps	[edi+000h+03000h], xmm4 
					movaps	[edi+010h+03000h], xmm5
					movaps  [edi+000h+03800h], xmm6
					movaps  [edi+010h+03800h], xmm7
					pop edi 
					pop esi
				}