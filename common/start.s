# ===============================================================
#
# RX スタート・アップ
# Copyright 2016 Kunihito Hiramatsu
#
# ===============================================================
	.text
	.global _start
	.type	_start,@function
_start:

# スタックの設定（SP：__stack、USP：__stack - 128）
	mov.l	#__stack, r5
	mvtc	r5, isp
	sub		#128,r5
	mvtc	r5, usp

# 割り込みベクタの設定
	.extern _interrupt_vectors
	mov.l	#_interrupt_vectors, r5
	mvtc	r5,intb

# I レジスタを設定し、割り込みを許可する
	mov.l	#0x00010000, r5
	mvtc	r5,psw

# PMレジスタを設定し、ユーザモードに移行する、ユーザースタックに切り替わる
	mvfc	psw,r1
	or		#0x00100000, r1
	push.l	r1

# UレジスタをセットするためにRTE命令を実行する
	mvfc	pc,r1
	add		#10,r1
	push.l	r1
	rte
	nop
	nop
	nop
	nop
	nop

# ワーク RAM の初期化
#	mov	#__bssstart, r1
#	mov	#0, r2
#	mov	#__stack, r3
#	sstr.l

# 初期値付き変数の初期化
	mov	#__datastart, r1
	mov	#__romdatastart, r2
	mov	#__romdatacopysize, r3
	smovf

# .bss セクションの初期化
	mov	#__bssstart, r1
	mov	#0, r2
	mov	#__bsssize, r3
	sstr.l

# init() 関数から開始
	.extern	_init
	bra		_init

	.global	_rx_run_preinit_array
	.type	_rx_run_preinit_array,@function
_rx_run_preinit_array:
	mov	#__preinit_array_start,r1
	mov	#__preinit_array_end,r2
	bra.a	_rx_run_inilist

	.global	_rx_run_init_array
	.type	_rx_run_init_array,@function
_rx_run_init_array:
	mov	#__init_array_start,r1
	mov	#__init_array_end,r2
	mov	#4, r3
	bra.a	_rx_run_inilist

	.global	_rx_run_fini_array
	.type	_rx_run_fini_array,@function
_rx_run_fini_array:
	mov	#__fini_array_start,r2
	mov	#__fini_array_end,r1
	mov	#-4, r3

# 初期化リスト
_rx_run_inilist:
next_inilist:
	cmp	r1,r2
	beq.b	done_inilist
	mov.l	[r1],r4
	cmp	#-1, r4
	beq.b	skip_inilist
	cmp	#0, r4
	beq.b	skip_inilist
	pushm	r1-r3
	jsr	r4
	popm	r1-r3

skip_inilist:
	add	r3,r1
	bra.b	next_inilist
done_inilist:
	rts

    .section .data
    .global ___dso_handle
    .weak   ___dso_handle
___dso_handle:
    .long    0

	.text
	.global	_set_intr_level
_set_intr_level:
	and		#15,r1
	shll	#24,r1
	or		#0x100000,r1
	mvtc	r1,psw
	rts

	.global _exit
_exit:
	wait
	bra		_exit
