# ===============================================================
# R5F56218BNFP スタートアップ
# ===============================================================
	.text

# ===============================================================
# ハードウェアー・リセット
# ===============================================================
	.global _power_on_reset
_power_on_reset:
	.global _start
_start:

# スタックの設定
	.extern _usp_init
	mvtc	#_usp_init, usp
	.extern _isp_init
	mvtc	#_isp_init, isp

# 割り込みベクタの設定
	.extern _interrupt_vectors
	mov.l	#_interrupt_vectors, r5
	mvtc	r5,intb

	mov.l	#0x100, r5
	mvtc	r5,fpsw

# Iレジスタを設定し、割り込みを許可する
	mov.l	#0x00010000, r5
	mvtc	r5,psw

# PMレジスタを設定し、ユーザモードに移行する
	mvfc	psw,r1
	or		#0x100000, r1
	push.l	r1

# UレジスタをセットするためにRTE命令を実行する
	mvfc	pc,r1
	add		#0x0a,r1
	push.l	r1
	rte
	nop
	nop

# init() 関数から開始
	.extern	_init
	bsr		_init

	.global	_set_intr_level
_set_intr_level:
	and		#15,r1
	shll	#24,r1
	or		#0x100000,r1
	mvtc	r1,psw
	rts
	nop

	.global _exit
_exit:
	wait
	bra		_exit


