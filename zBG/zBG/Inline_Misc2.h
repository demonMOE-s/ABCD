/* ------------------------------- Inline_Misc2.h -------------------------------------- */ 

			__asm {
				mov	edi, [GVPointer.pBits]
				mov esi, [pEmuVideoUpdate]
				mov ebx, [GVPointer.Pitch]
				mov edx, 64
				mov ecx, 8
				mov eax, 128 
				sub	ebx, 1024
				push ebp
				mov ebp, 224
				align 16
				sse_entry:
				// fetch
					movaps	xmm0, [esi+000h]
					movaps	xmm1, [esi+010h]
					movaps  xmm2, [esi+020h]
					movaps  xmm3, [esi+030h]
					movaps	xmm4, [esi+040h]
					movaps	xmm5, [esi+050h]
					movaps  xmm6, [esi+060h]
					movaps  xmm7, [esi+070h]
				// write
					movaps	[edi+000h], xmm0
					movaps	[edi+010h], xmm1
					movaps  [edi+020h], xmm2
					movaps  [edi+030h], xmm3
					movaps	[edi+040h], xmm4 
					movaps	[edi+050h], xmm5
					movaps  [edi+060h], xmm6
					movaps  [edi+070h], xmm7

					add edi, eax 
					add esi, eax 
					dec ecx 
					jne sse_entry 
					add edi, ebx 
					add esi, edx 
					mov ecx, 8 
					dec ebp 
					jne sse_entry 
					pop ebp
			}