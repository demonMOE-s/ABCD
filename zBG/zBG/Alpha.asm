		.686                      ; create 32 bit code
		.mmx
		.xmm                     
		.model flat, stdcall      ; 32 bit memory model
		option casemap :none      ; case sensitive

	byt equ byte ptr
	wot equ word ptr
	dwot equ dword ptr
	qdwot equ mmword ptr 
	qqdwot equ xmmword ptr
	extrn GVPointer:far
.data 
	include TLB.inc
.code

; ref from http://blog.csdn.net/u013550545/article/details/49689275 

s32alpha proc C ; lpsrc, spitch, xpos, ypos, width, height, ahpc
		option prologue:none, epilogue:none

		push 		ebx 					; U - save old frame
		push 		ebp 					; V - save old frame 
		push 		esi 					; U - save old frame 
		push 		edi 					; V - save old frame 	
		mov 		edi, 	[esp+16+4]		; U - load vram pointer
		mov 		eax, 	[esp+16+28]		; V - load alpha count 
		test 		ah, 	ah 				; U - not MAX ?
		je 			@F						; V - JCC 
		pop 		edi 	
		pop 		esi 
		pop 		ebp 
		pop 		ebx 
		ret 						
	align  16
	@@:
		mov 		ebx, 	[esp+16+8]		; U - ebx <- pitch 
		mov 		ecx, 	[esp+16+12]		; V - ecx <- xpos 	
		mov 		esi, 	ebx				; U - esi <- pitch 
		mov			ebp, 	[esp+16+16]		; V - ebp <- ypos		
		imul 		ebx, 	ebp				; N - ebx <- height*pitch	
		lea 		edi, 	[edi+ecx*4] 	
		mov 		ecx, 	[esp+16+20]	
		add 		edi, 	ebx				; + Y POS	
		lea 		edx, 	[ecx*4]			; edx <- width * 4
		mov 		ebp, 	[esp+16+24]
		sub 		esi, 	edx				; RVA pitch
		mov			ebx,	ecx				; save 
		cmp			ecx,	8				
		jb			LN
		and			ecx,	7				; do mod 
		je			L8 
		movd		xmm4,	esp				; save stack 
		shl 		eax, 	4				; eax = TLB index
		mov			esp,	ecx				; esp = ecx = mini widtch  
		shr 		ebx, 	3				; ebx = large width cnt  
		movdqa 		xmm7, 	qqdwot[eax+AlphaTLB] 
		pcmpeqb		xmm5, 	xmm5
		psrlw 		xmm5, 	8     
		pxor 		xmm6, 	xmm6
		mov 		edx, 	32				; per deal pixels block bytes 
		mov 		eax, 	ebx				; eax = ebx 
	align 16
	msc_loop:
		movdqu 		xmm0, 	qqdwot[edi] 
		movdqu 		xmm2, 	qqdwot[edi+16]			
		movdqa 		xmm1, 	xmm0 
		punpcklbw 	xmm0, 	xmm6	
		pmulhuw 	xmm0, 	xmm7
		punpckhbw 	xmm1, 	xmm6	
		pmulhuw 	xmm1, 	xmm7
		movdqa 		xmm3, 	xmm2	
		punpcklbw 	xmm2, 	xmm6
		packuswb 	xmm0, 	xmm1 			
		pmulhuw 	xmm2, 	xmm7
		punpckhbw 	xmm3, 	xmm6
		pmulhuw 	xmm3, 	xmm7	
		packuswb 	xmm2, 	xmm3
		movdqu qqdwot[edi], xmm0
		movdqu qqdwot[edi+16], xmm2	
		lea 		edi, 	[edi+edx]
		mov 		ebp, 	ebp
		dec 		eax
		jne 		msc_loop
	@@:
		movd 		xmm0, 	dwot[edi]  
		punpcklbw 	xmm0, 	xmm6
		pmulhuw 	xmm0, 	xmm7
		packuswb 	xmm0, 	xmm0 
		movd 	dwot[edi], 	xmm0
		add			edi,	4
		sub			ecx,	1 
		jne			@B
		mov			eax,	ebx
		add 		edi, 	esi 
		mov 		ecx, 	esp
		dec 		ebp 
		jne 		msc_loop
		movd		esp,	xmm4
		pop 		edi 
		pop 		esi 
		pop 		ebp 
		pop 		ebx 
		ret		
	align 16
	L8:
		shr 		ebx, 	3
		mov 		edx, 	32
		lea 		eax, 	[eax*4]
		mov 		ecx, 	ebx 
		movdqa 		xmm7, 	qqdwot[eax*4+AlphaTLB] 
		pcmpeqb		xmm5, 	xmm5
		psrlw 		xmm5, 	8     
		pxor 		xmm6, 	xmm6
	align 16
	@@:
		movdqu 		xmm0, 	qqdwot[edi] 
		movdqu 		xmm2, 	qqdwot[edi+16]			
		movdqa 		xmm1, 	xmm0 
		punpcklbw 	xmm0, 	xmm6	
		pmulhuw 	xmm0, 	xmm7
		punpckhbw 	xmm1, 	xmm6	
		pmulhuw 	xmm1, 	xmm7
		movdqa 		xmm3, 	xmm2	
		punpcklbw 	xmm2, 	xmm6
		packuswb 	xmm0, 	xmm1 			
		pmulhuw 	xmm2, 	xmm7
		punpckhbw 	xmm3, 	xmm6
		pmulhuw 	xmm3, 	xmm7	
		packuswb 	xmm2, 	xmm3
		movdqu qqdwot[edi], xmm0
		movdqu qqdwot[edi+16], xmm2	
		lea 		edi, 	[edi+edx]
		mov 		ebp, 	ebp
		dec 		ecx
		jne 		@B
		add 		edi, 	esi 
		mov 		ecx, 	ebx
		dec 		ebp 
		jne 		@B
		pop 		edi 
		pop 		esi 
		pop 		ebp 
		pop 		ebx 
		ret						
	align 16 
	LN:
		mov 		edx, 	4
		lea 		eax, 	[eax*4]
		mov 		ecx, 	ebx 		
		movq 		mm7, 	qdwot[eax*4+AlphaTLB] 
		pcmpeqb		mm5, 	mm5
		psrlw 		mm5, 	8     
		pxor 		mm6, 	mm6
	align 16 
	@@:
		movd 		mm0, 	dwot[edi]  
		punpcklbw 	mm0, 	mm6
		pmulhuw 	mm0, 	mm7
		packuswb 	mm0, 	mm0 
		movd 	dwot[edi], 	mm0
		lea 		edi, 	[edi+edx]
		mov 		ebp, 	ebp
		dec 		ecx
		jne 		@B
		add 		edi, 	esi 
		mov 		ecx, 	ebx
		dec 		ebp 
		jne 		@B
		emms
		pop 		edi 
		pop 		esi 
		pop 		ebp 
		pop 		ebx 
		ret	

s32alpha endp

nes5StepAlphaALLScreen proc C ; step count 0 ~ 4 (RGB 00000000[~0] -$ 100% color), lpsrc
		option prologue:none, epilogue:none

		push 		ebx 					; U - save old frame
		push 		ebp 					; V - save old frame 
		push 		esi 					; U - save old frame 
		push 		edi 					; V - save old frame 	
		mov			eax,	[esp+16+4]		; U - fetch step count 
		mov			edi,	DWORD PTR [GVPointer+4]	; V/N fetch VPointer 
		cmp			eax,	5				; U - 
		jb			_BST					; V/N 
		mov			ebx,	DWORD PTR[GVPointer+0]	; U - fetch Pitch 
		mov			esi,	[esp+16+8]		; V - fecth SPointer
		mov			eax,	224
		sub			ebx,	1024 
		mov			edx,	1 
		mov			ecx,	8				; U loop_x 
		mov			ebp,	128
		align 16 
		@@:
; -------------------------------------------------------
;           fetch mem 
; -------------------------------------------------------
		movdqa	xmm0, qqdwot[esi+000h]
		movdqa	xmm1, qqdwot[esi+010h]
		movdqa  xmm2, qqdwot[esi+020h]
		movdqa  xmm3, qqdwot[esi+030h]
		movdqa	xmm4, qqdwot[esi+040h]
		movdqa	xmm5, qqdwot[esi+050h]
		movdqa  xmm6, qqdwot[esi+060h]
		movdqa  xmm7, qqdwot[esi+070h]
; -------------------------------------------------------
;           write mem 
; -------------------------------------------------------
		movdqa	qqdwot[edi+000h], xmm0
		movdqa	qqdwot[edi+010h], xmm1
		movdqa  qqdwot[edi+020h], xmm2
		movdqa  qqdwot[edi+030h], xmm3
		movdqa	qqdwot[edi+040h], xmm4 
		movdqa	qqdwot[edi+050h], xmm5
		movdqa  qqdwot[edi+060h], xmm6
		movdqa  qqdwot[edi+070h], xmm7

		add		esi,	ebp
		add		edi,	ebp 
		sub		ecx,	edx 
		jne		@B 
		add		esi,	64 
		add		edi,	ebx 
		mov		ecx,	8 
		sub		eax,	edx 
		jne		@B 
		pop 	edi 	
		pop 	esi 
		pop 	ebp 
		pop 	ebx 
		ret 

		align 16 
		_BST:
		lea			eax,	[eax*4]			; U - *4
		mov			esi,	[esp+16+8]		; V - fecth SPointer 
		movdqa 		xmm7, 	qqdwot[eax*4+DWORDTLB]    
		pxor 		xmm6, 	xmm6	 
		mov			ebx,	DWORD PTR[GVPointer+0]	; U - fetch Pitch 
		mov			eax,	224
		sub			ebx,	1024 
		mov			edx,	1 
		mov			ecx,	16				; U loop_x 
		mov			ebp,	64 

	align 16
	@@:
		movdqa 		xmm0, 	qqdwot[esi+000h] ; fetch P0
		movdqa 		xmm1, 	qqdwot[esi+010h] ; fetch P1
		movdqa		xmm2, 	qqdwot[esi+020h] ; fetch P2
		movdqa		xmm3,	qqdwot[esi+030h] ; fetch P3
		movdqa 		xmm4,	xmm0			 ; xmm4 = xmm0 = P0 	
		punpcklbw 	xmm0, 	xmm6			 ; RGB cross-decomposition L0-L1 (P0)
		pmulhuw 	xmm0, 	xmm7			 ; RGB cross-mul get high L0-L1 (P0)
		movdqa		xmm5, 	xmm1 			 ; xmm5 = xmm1 = P1 	   
		punpckhbw 	xmm4, 	xmm6			 ; RGB cross-decomposition H0-H1 (P0)
		pmulhuw 	xmm4, 	xmm7			 ; RGB cross-mul get high H0-H1 (P0)
		punpcklbw 	xmm1, 	xmm6			 ; RGB cross-decomposition L0-L1 (P1)
		packuswb 	xmm0, 	xmm4			 ; P0  merge 	
		pmulhuw 	xmm1, 	xmm7			 ; RGB cross-mul get high L0-L1 (P1)		
		punpckhbw 	xmm5, 	xmm6			 ; RGB cross-decomposition H0-H1 (P1)
		movdqa		xmm4, 	xmm2 			 ; xmm4 = xmm2 = P2
		pmulhuw 	xmm5, 	xmm7			 ; RGB cross-mul get high H0-H1 (P1)	
		punpcklbw 	xmm2, 	xmm6			 ; RGB cross-decomposition L0-L1 (P2)
		packuswb 	xmm1, 	xmm5			 ; P1  merge 	
		pmulhuw 	xmm2, 	xmm7			 ; RGB cross-mul get high L0-L1 (P2)
		punpckhbw 	xmm4, 	xmm6			 ; RGB cross-decomposition H0-H1 (P2)
		movdqa		xmm5,	xmm3			 ; xmm5 = xmm3 = P3 
		pmulhuw 	xmm4, 	xmm7			 ; RGB cross-mul get high H0-H1 (P2)
		punpcklbw 	xmm3, 	xmm6			 ; RGB cross-decomposition L0-L1 (P3)
		packuswb 	xmm2, 	xmm4			 ; P2  merge 
		pmulhuw 	xmm3, 	xmm7			 ; RGB cross-mul get high L0-L1 (P3)
		punpckhbw 	xmm5, 	xmm6			 ; RGB cross-decomposition H0-H1 (P3)
		pmulhuw 	xmm5, 	xmm7			 ; RGB cross-mul get high H0-H1 (P3)
		packuswb 	xmm3, 	xmm5			 ; P3  merge 
		movdqa 		qqdwot[edi+000h], xmm0   ; write P0
		movdqa 		qqdwot[edi+010h], xmm1   ; write P1
		movdqa		qqdwot[edi+020h], xmm2   ; write P2
		movdqa		qqdwot[edi+030h], xmm3   ; write P3
		add			esi,	ebp				 ; next 64 bytes
		add			edi,	ebp				 ; next 64 bytes
		sub			ecx,	edx				 ; loop_x -- 
		jne			@B						 ; JCC contine/out 
		add			esi,	64				 ; next line 
		add			edi,	ebx				 ; next line 
		mov			ecx,	16
		sub			eax,	edx 
		jne			@B						 ; JCC contine/out 
		pop 		edi 
		pop 		esi 
		pop 		ebp 
		pop 		ebx 
		ret							

		align 16
		DWORDTLB:	
			dd 000000000h, 000000000h, 000000000h, 000000000h
			dd 040004000h, 000004000h, 040004000h, 000004000h
			dd 080008000h, 000008000h, 080008000h, 000008000h
			dd 0C000C000h, 00000C000h, 0C000C000h, 00000C000h
			dd 0FF00FF00h, 00000FF00h, 0FF00FF00h, 00000FF00h
nes5StepAlphaALLScreen endp

	end