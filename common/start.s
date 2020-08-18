# ===============================================================
/*!	@file
	@brief	RX スタート・アップ
    @author 平松邦仁 (hira@rvf-rc45.net)
	@copyright	Copyright (C) 2016, 2018 Kunihito Hiramatsu @n
				Released under the MIT license @n
				https://github.com/hirakuni45/RX/blob/master/LICENSE
*/
# ===============================================================
		.extern	__istack
		.extern	__ustack
		.text
		.global _start
		.type	_start,@function
_start:
		mvtc	#__istack, isp
		mvtc	#__ustack, usp

# 割り込みベクタの設定
		.extern _interrupt_vectors
		mvtc	#_interrupt_vectors, intb

/* setup FPSW */
		mvtc    #100h, fpsw

# RAM 全領域のゼロクリア
		mov	#__datastart, r1
		mov	#0, r2
		mov	#__istack, r3
		sub r1, r3
		sstr.b

# .bss セクションの消去
		mov	#__bssstart, r1
		mov	#0, r2
		mov	#__bssend, r3
		sub r1, r3
		sstr.b

# 初期値付き変数の初期化
		mov	#__datastart, r1
		mov	#__romdatastart, r2
		mov	#__romdatacopysize, r3
#ifdef __RX_ALLOW_STRING_INSNS__
		smovf		/* block copy R3 bytes from R2 to R1 */
#else
		cmp     #0, r3
		beq     2f

1:		mov.b   [r2+], r5
		mov.b   r5, [r1+]
		sub     #1, r3
		bne     1b
2:
#endif

# MEMWAIT を設定 (for RX71M by 240MHz)
.ifdef MEMWAIT
		mov #0x86610,r1
		mov # 0x00000001,r2
		mov.l r2,[r1] 
.endif

# I レジスタを設定し、割り込みを許可する
# 割り込みレベル最低（全ての割り込みを許可）
		mvfc	psw,r1
		or		#0x00010000,r1
		and		#0xf0ffffff,r1
		mvtc	r1,psw

# PMレジスタを設定し、ユーザモードに移行する、ユーザースタックに切り替わる
.ifndef NOT_USER
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
.endif

# init() 関数から開始
		.extern	_init
		bra		_init

		.global _turn_supervisor
_turn_supervisor:
		mvfc	psw,r1
		and		#0xffefffff,r1
		push.l	r1
		mvfc	pc,r1
		add		#10,r1
		push.l	r1
		rte
		nop
		nop
		nop
		nop
		nop
		rts

# 割り込み許可（スーパーバイザモード）
		.global _enable_interrupt
_enable_interrupt:
		push	r1
		mvfc	psw,r1
		or		#0x00010000, r1
		mvtc	r1,psw
		pop		r1
		rts


# 割り込み不許可（スーパーバイザモード）
		.global _disable_interrupt
_disable_interrupt:
		push	r1
		mvfc	psw,r1
		and		#0xFFFEFFFF, r1
		mvtc	r1,psw
		pop		r1
		rts

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
		push.l  r5
		mvfc    psw, r5
		shll    #24, r1
		and     #0xf0ffffff, r5
		or      r1, r5
		mvtc    r5, psw
		pop     r5
		rts

		.global _get_intr_level
_get_intr_level:
		mvfc	psw,r1
		shlr	#24,r1
		rts

		.global _exit
_exit:
		wait
		bra		_exit
