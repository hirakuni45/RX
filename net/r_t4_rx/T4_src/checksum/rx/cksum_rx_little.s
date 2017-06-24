 .file	"cksum_rx_little.s"
 .section	.text.ck
.global		__cksum
__cksum:                           ; function: _cksum
;uint16 _cksum(uchar *data, uint16 nbytes, uint16 sum0);
	and		#0ffffh,	r2			;arg2 uint16
	and		#0ffffh,	r3			;arg3 uint16



	cmp         #0, r2
	beq         CKSUM_ZERO_EXIT

	btst	#0, r1
	beq	CKSUM_EVEN

;   data is odd


	add	#-1, r1
	movu.w	[r1+], r4
	revw	r3, r3

	revw	r4, r4

	and	#0ffH, r4

	revw	r4, r4

	add	r4, r3
	add	#-1, r2

	shlr	#3, r2, r15
	beq	CKSUM_ODD_NEXT4

?:
	movu.w	[r1+], r5
	movu.w	[r1+], r4
	add	r5, r3
	movu.w	[r1+], r5
	add	r4, r3
	movu.w	[r1+], r4
	add	r5, r3
	add	r4, r3
	sub	#1, r15
	bne	?-

CKSUM_ODD_NEXT4:
	btst	#2, r2
	beq	CKSUM_ODD_NEXT2
	movu.w	[r1+], r5
	movu.w	[r1+], r4
	add	r5, r3
	add	r4, r3

CKSUM_ODD_NEXT2:
	btst	#1, r2
	beq	CKSUM_ODD_NEXT1
	movu.w	[r1+], r5
	add	r5, r3

CKSUM_ODD_NEXT1:
	btst	#0, r2
	beq	CKSUM_ODD_NBYTES_NOT_ODD
	movu.w	[r1], r5

	revw	r5, r5

	and	#0ff00H, r5

	revw	r5, r5

	add	r5, r3

CKSUM_ODD_NBYTES_NOT_ODD:
	mov.l	#0000ffffh, r4
	shlr	#16, r3, r5
	and	r4, r3
	add	r5, r3
	shlr	#16, r3, r5
	and	r4, r3
	add	r5, r3
	revw	r3, r1

	revw	r1, r1

	not	r1
	movu.w	r1, r1
	rts




CKSUM_EVEN:


	shlr	#3, r2, r15
	beq	CKSUM_EVEN_NEXT4

?:
	movu.w	[r1+], r5
	movu.w	[r1+], r4
	add	r5, r3
	movu.w	[r1+], r5
	add	r4, r3
	movu.w	[r1+], r4
	add	r5, r3
	add	r4, r3
	sub	#1, r15
	bne	?-

CKSUM_EVEN_NEXT4:
	btst	#2, r2
	beq	CKSUM_EVEN_NEXT2
	movu.w	[r1+], r5
	movu.w	[r1+], r4
	add	r5, r3
	add	r4, r3

CKSUM_EVEN_NEXT2:
	btst	#1, r2
	beq	CKSUM_EVEN_NEXT1
	movu.w	[r1+], r5
	add	r5, r3

CKSUM_EVEN_NEXT1:
	btst	#0, r2
	beq	CKSUM_EVEN_NBYTES_NOT_ODD
	movu.w	[r1], r5

	revw	r5, r5

	and	#0ff00H, r5

	revw	r5, r5

	add	r5, r3

CKSUM_EVEN_NBYTES_NOT_ODD:
	mov.l	#0000ffffh, r4
	shlr	#16, r3, r5
	and	r4, r3
	add	r5, r3
	shlr	#16, r3, r5
	and	r4, r3
	add	r5, r3

CKSUM_EXIT:

	revw	r3, r3

	not	r3
	movu.w	r3, r1
	rts

CKSUM_ZERO_EXIT:

	revw	r3, r3

	not	r3, r1
	movu.w	r1, r1
	rts

	.end
