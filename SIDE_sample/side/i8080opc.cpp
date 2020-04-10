/*
    I8080 emulator
    Copyright (c) 1996-2002,2003 Alessandro Scotti
    http://www.walkofmind.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include "i8080.h"

I8080::OpcodeInfo I8080::Opcode_[256] = {
    { &I8080::opcode_00,  4 },   // NOP
    { &I8080::opcode_01, 10 },   // LD   BC,nn
    { &I8080::opcode_02,  7 },   // LD   (BC),A
    { &I8080::opcode_03,  6 },   // INC  BC
    { &I8080::opcode_04,  5 },   // INC  B
    { &I8080::opcode_05,  5 },   // DEC  B
    { &I8080::opcode_06,  7 },   // LD   B,n
    { &I8080::opcode_07,  4 },   // RLCA
    { 0, 4 },
    { &I8080::opcode_09, 11 },   // ADD  HL,BC
    { &I8080::opcode_0a,  7 },   // LD   A,(BC)
    { &I8080::opcode_0b,  6 },   // DEC  BC
    { &I8080::opcode_0c,  5 },   // INC  C
    { &I8080::opcode_0d,  5 },   // DEC  C
    { &I8080::opcode_0e,  7 },   // LD   C,n
    { &I8080::opcode_0f,  4 },   // RRCA
    { 0, 4 },
    { &I8080::opcode_11, 10 },   // LD   DE,nn
    { &I8080::opcode_12,  7 },   // LD   (DE),A
    { &I8080::opcode_13,  6 },   // INC  DE
    { &I8080::opcode_14,  5 },   // INC  D
    { &I8080::opcode_15,  5 },   // DEC  D
    { &I8080::opcode_16,  7 },   // LD   D,n
    { &I8080::opcode_17,  4 },   // RLA
    { 0, 4 },
    { &I8080::opcode_19, 11 },   // ADD  HL,DE
    { &I8080::opcode_1a,  7 },   // LD   A,(DE)
    { &I8080::opcode_1b,  6 },   // DEC  DE
    { &I8080::opcode_1c,  5 },   // INC  E
    { &I8080::opcode_1d,  5 },   // DEC  E
    { &I8080::opcode_1e,  7 },   // LD   E,n
    { &I8080::opcode_1f,  4 },   // RRA
    { 0, 4 },
    { &I8080::opcode_21, 10 },   // LD   HL,nn
    { &I8080::opcode_22, 16 },   // LD   (nn),HL
    { &I8080::opcode_23,  6 },   // INC  HL
    { &I8080::opcode_24,  5 },   // INC  H
    { &I8080::opcode_25,  5 },   // DEC  H
    { &I8080::opcode_26,  7 },   // LD   H,n
    { &I8080::opcode_27,  4 },   // DAA
    { 0, 4 },
    { &I8080::opcode_29, 11 },   // ADD  HL,HL
    { &I8080::opcode_2a, 16 },   // LD   HL,(nn)
    { &I8080::opcode_2b,  6 },   // DEC  HL
    { &I8080::opcode_2c,  5 },   // INC  L
    { &I8080::opcode_2d,  5 },   // DEC  L
    { &I8080::opcode_2e,  7 },   // LD   L,n
    { &I8080::opcode_2f,  4 },   // CPL
    { 0, 4 },
    { &I8080::opcode_31, 10 },   // LD   SP,nn
    { &I8080::opcode_32, 13 },   // LD   (nn),A
    { &I8080::opcode_33,  6 },   // INC  SP
    { &I8080::opcode_34, 10 },   // INC  (HL)
    { &I8080::opcode_35, 10 },   // DEC  (HL)
    { &I8080::opcode_36, 10 },   // LD   (HL),n
    { &I8080::opcode_37,  4 },   // SCF
    { 0, 4 },
    { &I8080::opcode_39, 11 },   // ADD  HL,SP
    { &I8080::opcode_3a, 13 },   // LD   A,(nn)
    { &I8080::opcode_3b,  6 },   // DEC  SP
    { &I8080::opcode_3c,  5 },   // INC  A
    { &I8080::opcode_3d,  5 },   // DEC  A
    { &I8080::opcode_3e,  7 },   // LD   A,n
    { &I8080::opcode_3f,  4 },   // CCF
    { &I8080::opcode_40,  5 },   // LD   B,B
    { &I8080::opcode_41,  5 },   // LD   B,C
    { &I8080::opcode_42,  5 },   // LD   B,D
    { &I8080::opcode_43,  5 },   // LD   B,E
    { &I8080::opcode_44,  5 },   // LD   B,H
    { &I8080::opcode_45,  5 },   // LD   B,L
    { &I8080::opcode_46,  7 },   // LD   B,(HL)
    { &I8080::opcode_47,  5 },   // LD   B,A
    { &I8080::opcode_48,  5 },   // LD   C,B
    { &I8080::opcode_49,  5 },   // LD   C,C
    { &I8080::opcode_4a,  5 },   // LD   C,D
    { &I8080::opcode_4b,  5 },   // LD   C,E
    { &I8080::opcode_4c,  5 },   // LD   C,H
    { &I8080::opcode_4d,  5 },   // LD   C,L
    { &I8080::opcode_4e,  7 },   // LD   C,(HL)
    { &I8080::opcode_4f,  5 },   // LD   C,A
    { &I8080::opcode_50,  5 },   // LD   D,B
    { &I8080::opcode_51,  5 },   // LD   D,C
    { &I8080::opcode_52,  5 },   // LD   D,D
    { &I8080::opcode_53,  5 },   // LD   D,E
    { &I8080::opcode_54,  5 },   // LD   D,H
    { &I8080::opcode_55,  5 },   // LD   D,L
    { &I8080::opcode_56,  7 },   // LD   D,(HL)
    { &I8080::opcode_57,  5 },   // LD   D,A
    { &I8080::opcode_58,  5 },   // LD   E,B
    { &I8080::opcode_59,  5 },   // LD   E,C
    { &I8080::opcode_5a,  5 },   // LD   E,D
    { &I8080::opcode_5b,  5 },   // LD   E,E
    { &I8080::opcode_5c,  5 },   // LD   E,H
    { &I8080::opcode_5d,  5 },   // LD   E,L
    { &I8080::opcode_5e,  7 },   // LD   E,(HL)
    { &I8080::opcode_5f,  5 },   // LD   E,A
    { &I8080::opcode_60,  5 },   // LD   H,B
    { &I8080::opcode_61,  5 },   // LD   H,C
    { &I8080::opcode_62,  5 },   // LD   H,D
    { &I8080::opcode_63,  5 },   // LD   H,E
    { &I8080::opcode_64,  5 },   // LD   H,H
    { &I8080::opcode_65,  5 },   // LD   H,L
    { &I8080::opcode_66,  7 },   // LD   H,(HL)
    { &I8080::opcode_67,  5 },   // LD   H,A
    { &I8080::opcode_68,  5 },   // LD   L,B
    { &I8080::opcode_69,  5 },   // LD   L,C
    { &I8080::opcode_6a,  5 },   // LD   L,D
    { &I8080::opcode_6b,  5 },   // LD   L,E
    { &I8080::opcode_6c,  5 },   // LD   L,H
    { &I8080::opcode_6d,  5 },   // LD   L,L
    { &I8080::opcode_6e,  7 },   // LD   L,(HL)
    { &I8080::opcode_6f,  5 },   // LD   L,A
    { &I8080::opcode_70,  7 },   // LD   (HL),B
    { &I8080::opcode_71,  7 },   // LD   (HL),C
    { &I8080::opcode_72,  7 },   // LD   (HL),D
    { &I8080::opcode_73,  7 },   // LD   (HL),E
    { &I8080::opcode_74,  7 },   // LD   (HL),H
    { &I8080::opcode_75,  7 },   // LD   (HL),L
    { &I8080::opcode_76,  7 },   // HALT
    { &I8080::opcode_77,  7 },   // LD   (HL),A
    { &I8080::opcode_78,  5 },   // LD   A,B
    { &I8080::opcode_79,  5 },   // LD   A,C
    { &I8080::opcode_7a,  5 },   // LD   A,D
    { &I8080::opcode_7b,  5 },   // LD   A,E
    { &I8080::opcode_7c,  5 },   // LD   A,H
    { &I8080::opcode_7d,  5 },   // LD   A,L
    { &I8080::opcode_7e,  7 },   // LD   A,(HL)
    { &I8080::opcode_7f,  5 },   // LD   A,A
    { &I8080::opcode_80,  4 },   // ADD  A,B
    { &I8080::opcode_81,  4 },   // ADD  A,C
    { &I8080::opcode_82,  4 },   // ADD  A,D
    { &I8080::opcode_83,  4 },   // ADD  A,E
    { &I8080::opcode_84,  4 },   // ADD  A,H
    { &I8080::opcode_85,  4 },   // ADD  A,L
    { &I8080::opcode_86,  7 },   // ADD  A,(HL)
    { &I8080::opcode_87,  4 },   // ADD  A,A
    { &I8080::opcode_88,  4 },   // ADC  A,B
    { &I8080::opcode_89,  4 },   // ADC  A,C
    { &I8080::opcode_8a,  4 },   // ADC  A,D
    { &I8080::opcode_8b,  4 },   // ADC  A,E
    { &I8080::opcode_8c,  4 },   // ADC  A,H
    { &I8080::opcode_8d,  4 },   // ADC  A,L
    { &I8080::opcode_8e,  7 },   // ADC  A,(HL)
    { &I8080::opcode_8f,  4 },   // ADC  A,A
    { &I8080::opcode_90,  4 },   // SUB  B
    { &I8080::opcode_91,  4 },   // SUB  C
    { &I8080::opcode_92,  4 },   // SUB  D
    { &I8080::opcode_93,  4 },   // SUB  E
    { &I8080::opcode_94,  4 },   // SUB  H
    { &I8080::opcode_95,  4 },   // SUB  L
    { &I8080::opcode_96,  7 },   // SUB  (HL)
    { &I8080::opcode_97,  4 },   // SUB  A
    { &I8080::opcode_98,  4 },   // SBC  A,B
    { &I8080::opcode_99,  4 },   // SBC  A,C
    { &I8080::opcode_9a,  4 },   // SBC  A,D
    { &I8080::opcode_9b,  4 },   // SBC  A,E
    { &I8080::opcode_9c,  4 },   // SBC  A,H
    { &I8080::opcode_9d,  4 },   // SBC  A,L
    { &I8080::opcode_9e,  7 },   // SBC  A,(HL)
    { &I8080::opcode_9f,  4 },   // SBC  A,A
    { &I8080::opcode_a0,  4 },   // AND  B
    { &I8080::opcode_a1,  4 },   // AND  C
    { &I8080::opcode_a2,  4 },   // AND  D
    { &I8080::opcode_a3,  4 },   // AND  E
    { &I8080::opcode_a4,  4 },   // AND  H
    { &I8080::opcode_a5,  4 },   // AND  L
    { &I8080::opcode_a6,  7 },   // AND  (HL)
    { &I8080::opcode_a7,  4 },   // AND  A
    { &I8080::opcode_a8,  4 },   // XOR  B
    { &I8080::opcode_a9,  4 },   // XOR  C
    { &I8080::opcode_aa,  4 },   // XOR  D
    { &I8080::opcode_ab,  4 },   // XOR  E
    { &I8080::opcode_ac,  4 },   // XOR  H
    { &I8080::opcode_ad,  4 },   // XOR  L
    { &I8080::opcode_ae,  7 },   // XOR  (HL)
    { &I8080::opcode_af,  4 },   // XOR  A
    { &I8080::opcode_b0,  4 },   // OR   B
    { &I8080::opcode_b1,  4 },   // OR   C
    { &I8080::opcode_b2,  4 },   // OR   D
    { &I8080::opcode_b3,  4 },   // OR   E
    { &I8080::opcode_b4,  4 },   // OR   H
    { &I8080::opcode_b5,  4 },   // OR   L
    { &I8080::opcode_b6,  7 },   // OR   (HL)
    { &I8080::opcode_b7,  4 },   // OR   A
    { &I8080::opcode_b8,  4 },   // CP   B
    { &I8080::opcode_b9,  4 },   // CP   C
    { &I8080::opcode_ba,  4 },   // CP   D
    { &I8080::opcode_bb,  4 },   // CP   E
    { &I8080::opcode_bc,  4 },   // CP   H
    { &I8080::opcode_bd,  4 },   // CP   L
    { &I8080::opcode_be,  7 },   // CP   (HL)
    { &I8080::opcode_bf,  4 },   // CP   A
    { &I8080::opcode_c0,  5 },   // RET  NZ
    { &I8080::opcode_c1, 10 },   // POP  BC
    { &I8080::opcode_c2, 10 },   // JP   NZ,nn
    { &I8080::opcode_c3, 10 },   // JP   nn
    { &I8080::opcode_c4, 11 },   // CALL NZ,nn
    { &I8080::opcode_c5, 11 },   // PUSH BC
    { &I8080::opcode_c6,  7 },   // ADD  A,n
    { &I8080::opcode_c7, 11 },   // RST  0
    { &I8080::opcode_c8,  5 },   // RET  Z
    { &I8080::opcode_c9, 10 },   // RET
    { &I8080::opcode_ca, 10 },   // JP   Z,nn
    { 0, 4 },
    { &I8080::opcode_cc, 11 },   // CALL Z,nn
    { &I8080::opcode_cd, 17 },   // CALL nn
    { &I8080::opcode_ce,  7 },   // ADC  A,n
    { &I8080::opcode_cf, 11 },   // RST  8
    { &I8080::opcode_d0,  5 },   // RET  NC
    { &I8080::opcode_d1, 10 },   // POP  DE
    { &I8080::opcode_d2, 10 },   // JP   NC,nn
    { &I8080::opcode_d3, 10 },   // OUT  (n),A
    { &I8080::opcode_d4, 11 },   // CALL NC,nn
    { &I8080::opcode_d5, 11 },   // PUSH DE
    { &I8080::opcode_d6,  7 },   // SUB  n
    { &I8080::opcode_d7, 11 },   // RST  10H
    { &I8080::opcode_d8,  5 },   // RET  C
    { 0, 4 },
    { &I8080::opcode_da, 10 },   // JP   C,nn
    { &I8080::opcode_db, 10 },   // IN   A,(n)
    { &I8080::opcode_dc, 11 },   // CALL C,nn
    { 0, 4 },
    { &I8080::opcode_de,  7 },   // SBC  A,n
    { &I8080::opcode_df, 11 },   // RST  18H
    { &I8080::opcode_e0,  5 },   // RET  PO
    { &I8080::opcode_e1, 10 },   // POP  HL
    { &I8080::opcode_e2, 10 },   // JP   PO,nn
    { &I8080::opcode_e3,  4 },   // EX   (SP),HL
    { &I8080::opcode_e4, 11 },   // CALL PO,nn
    { &I8080::opcode_e5, 11 },   // PUSH HL
    { &I8080::opcode_e6,  7 },   // AND  n
    { &I8080::opcode_e7, 11 },   // RST  20H
    { &I8080::opcode_e8,  5 },   // RET  PE
    { &I8080::opcode_e9,  4 },   // JP   (HL)
    { &I8080::opcode_ea, 10 },   // JP   PE,nn
    { &I8080::opcode_eb,  4 },   // EX   DE,HL
    { &I8080::opcode_ec, 11 },   // CALL PE,nn
    { 0, 4 },
    { &I8080::opcode_ee,  7 },   // XOR  n
    { &I8080::opcode_ef, 11 },   // RST  28H
    { &I8080::opcode_f0,  5 },   // RET  P
    { &I8080::opcode_f1, 10 },   // POP  AF
    { &I8080::opcode_f2, 10 },   // JP   P,nn
    { &I8080::opcode_f3,  4 },   // DI
    { &I8080::opcode_f4, 11 },   // CALL P,nn
    { &I8080::opcode_f5, 11 },   // PUSH AF
    { &I8080::opcode_f6,  7 },   // OR   n
    { &I8080::opcode_f7, 11 },   // RST  30H
    { &I8080::opcode_f8,  5 },   // RET  M
    { &I8080::opcode_f9,  6 },   // LD   SP,HL
    { &I8080::opcode_fa, 10 },   // JP   M,nn
    { &I8080::opcode_fb,  4 },   // EI
    { &I8080::opcode_fc, 11 },   // CALL M,nn
    { 0, 4 },
    { &I8080::opcode_fe,  7 },   // CP   n
    { &I8080::opcode_ff, 11 }    // RST  38H
};

void I8080::opcode_00()    // NOP
{
}

void I8080::opcode_01()    // LD   BC,nn
{
    C = env_.readByte( PC++ );
    B = env_.readByte( PC++ );
}

void I8080::opcode_02()    // LD   (BC),A
{
    env_.writeByte( BC(), A );
}

void I8080::opcode_03()    // INC  BC
{
    if( ++C == 0 ) ++B;
}

void I8080::opcode_04()    // INC  B
{
    B = incByte( B );
}

void I8080::opcode_05()    // DEC  B
{
    B = decByte( B );
}

void I8080::opcode_06()    // LD   B,n
{
    B = env_.readByte( PC++ );
}

void I8080::opcode_07()    // RLCA
{
    A = (A << 1) | (A >> 7);
    F &= ~(AddSub | HalfCarry | Carry);
    if( A & 0x01 ) F |= Carry;
}

void I8080::opcode_09()    // ADD  HL,BC
{
    unsigned hl = HL();
    unsigned rp = BC();
    unsigned x  = hl + rp;

    F &= (Flag3 | Flag5 | Sign | Zero | Parity);
    if( x > 0xFFFF ) F |= Carry;
    if( ((hl & 0xFFF) + (rp & 0xFFF)) > 0xFFF ) F |= HalfCarry;

    L = x & 0xFF;
    H = (x >> 8) & 0xFF;
}

void I8080::opcode_0a()    // LD   A,(BC)
{
    A = env_.readByte( BC() );
}

void I8080::opcode_0b()    // DEC  BC
{
    if( C-- == 0 ) --B;
}

void I8080::opcode_0c()    // INC  C
{
    C = incByte( C );
}

void I8080::opcode_0d()    // DEC  C
{
    C = decByte( C );
}

void I8080::opcode_0e()    // LD   C,n
{
    C = env_.readByte( PC++ );
}

void I8080::opcode_0f()    // RRCA
{
    A = (A >> 1) | (A << 7);
    F &= ~(AddSub | HalfCarry | Carry);
    if( A & 0x80 ) F |= Carry;
}

void I8080::opcode_11()    // LD   DE,nn
{
    E = env_.readByte( PC++ );
    D = env_.readByte( PC++ );
}

void I8080::opcode_12()    // LD   (DE),A
{
    env_.writeByte( DE(), A );
}

void I8080::opcode_13()    // INC  DE
{
    if( ++E == 0 ) ++D;
}

void I8080::opcode_14()    // INC  D
{
    D = incByte( D );
}

void I8080::opcode_15()    // DEC  D
{
    D = decByte( D );
}

void I8080::opcode_16()    // LD   D,n
{
    D = env_.readByte( PC++ );
}

void I8080::opcode_17()    // RLA
{
    unsigned char   a = A;

    A <<= 1;
    if( F & Carry ) A |= 0x01;
    F &= ~(AddSub | HalfCarry | Carry);
    if( a & 0x80 ) F |= Carry;
}

void I8080::opcode_19()    // ADD  HL,DE
{
    unsigned hl = HL();
    unsigned rp = DE();
    unsigned x  = hl + rp;

    F &= (Flag3 | Flag5 | Sign | Zero | Parity);
    if( x > 0xFFFF ) F |= Carry;
    if( ((hl & 0xFFF) + (rp & 0xFFF)) > 0xFFF ) F |= HalfCarry;

    L = x & 0xFF;
    H = (x >> 8) & 0xFF;
}

void I8080::opcode_1a()    // LD   A,(DE)
{
    A = env_.readByte( DE() );
}

void I8080::opcode_1b()    // DEC  DE
{
    if( E-- == 0 ) --D;
}

void I8080::opcode_1c()    // INC  E
{
    E = incByte( E );
}

void I8080::opcode_1d()    // DEC  E
{
    E = decByte( E );
}

void I8080::opcode_1e()    // LD   E,n
{
    E = env_.readByte( PC++ );
}

void I8080::opcode_1f()    // RRA
{
    unsigned char   a = A;

    A >>= 1;
    if( F & Carry ) A |= 0x80;
    F &= ~(AddSub | HalfCarry | Carry);
    if( a & 0x01 ) F |= Carry;
}

void I8080::opcode_21()    // LD   HL,nn
{
    L = env_.readByte( PC++ );
    H = env_.readByte( PC++ );
}

void I8080::opcode_22()    // LD   (nn),HL
{
    unsigned x = nextWord();

    env_.writeByte( x  , L );
    env_.writeByte( x+1, H );
}

void I8080::opcode_23()    // INC  HL
{
    if( ++L == 0 ) ++H;
}

void I8080::opcode_24()    // INC  H
{
    H = incByte( H );
}

void I8080::opcode_25()    // DEC  H
{
    H = decByte( H );
}

void I8080::opcode_26()    // LD   H,n
{
    H = env_.readByte( PC++ );
}

void I8080::opcode_27()    // DAA
{
    if( ((A & 0x0F) > 9) || (F & HalfCarry) ) {
        A += 0x06;
        F |= HalfCarry;
    }
    else {
        F &= ~HalfCarry;
    }

    if( (A > 0x9F) || (F & Carry) ) {
        A += 0x60;
        F |= Carry;
    }
    else {
        F &= ~Carry;
    }

    setFlagsPSZ();
}

void I8080::opcode_29()    // ADD  HL,HL
{
    unsigned hl = HL();
    unsigned rp = hl;
    unsigned x  = hl + rp;

    F &= (Flag3 | Flag5 | Sign | Zero | Parity);
    if( x > 0xFFFF ) F |= Carry;
    if( ((hl & 0xFFF) + (rp & 0xFFF)) > 0xFFF ) F |= HalfCarry;

    L = x & 0xFF;
    H = (x >> 8) & 0xFF;
}

void I8080::opcode_2a()    // LD   HL,(nn)
{
    unsigned x = nextWord();

    L = env_.readByte( x );
    H = env_.readByte( x+1 );
}

void I8080::opcode_2b()    // DEC  HL
{
    if( L-- == 0 ) --H;
}

void I8080::opcode_2c()    // INC  L
{
    L = incByte( L );
}

void I8080::opcode_2d()    // DEC  L
{
    L = decByte( L );
}

void I8080::opcode_2e()    // LD   L,n
{
    L = env_.readByte( PC++ );
}

void I8080::opcode_2f()    // CPL
{
    A ^= 0xFF;
    F |= AddSub | HalfCarry;
}

void I8080::opcode_31()    // LD   SP,nn
{
    SP = nextWord();
}

void I8080::opcode_32()    // LD   (nn),A
{
    env_.writeByte( nextWord(), A );
}

void I8080::opcode_33()    // INC  SP
{
    SP = (SP + 1) & 0xFFFF;
}

void I8080::opcode_34()    // INC  (HL)
{
    env_.writeByte( HL(), incByte( env_.readByte( HL() ) ) );
}

void I8080::opcode_35()    // DEC  (HL)
{
    env_.writeByte( HL(), decByte( env_.readByte( HL() ) ) );
}

void I8080::opcode_36()    // LD   (HL),n
{
    env_.writeByte( HL(), env_.readByte( PC++ ) );
}

void I8080::opcode_37()    // SCF
{
    F |= Carry;
}

void I8080::opcode_39()    // ADD  HL,SP
{
    unsigned hl = HL();
    unsigned rp = SP;
    unsigned x  = hl + rp;

    F &= (Flag3 | Flag5 | Sign | Zero | Parity);
    if( x > 0xFFFF ) F |= Carry;
    if( ((hl & 0xFFF) + (rp & 0xFFF)) > 0xFFF ) F |= HalfCarry;

    L = x & 0xFF;
    H = (x >> 8) & 0xFF;
}

void I8080::opcode_3a()    // LD   A,(nn)
{
    A = env_.readByte( nextWord() );
}

void I8080::opcode_3b()    // DEC  SP
{
    SP = (SP - 1) & 0xFFFF;
}

void I8080::opcode_3c()    // INC  A
{
    A = incByte( A );
}

void I8080::opcode_3d()    // DEC  A
{
    A = decByte( A );
}

void I8080::opcode_3e()    // LD   A,n
{
    A = env_.readByte( PC++ );
}

void I8080::opcode_3f()    // CCF
{
    F ^= Carry;
}

void I8080::opcode_40()    // LD   B,B
{
}

void I8080::opcode_41()    // LD   B,C
{
    B = C;
}

void I8080::opcode_42()    // LD   B,D
{
    B = D;
}

void I8080::opcode_43()    // LD   B,E
{
    B = E;
}

void I8080::opcode_44()    // LD   B,H
{
    B = H;
}

void I8080::opcode_45()    // LD   B,L
{
    B = L;
}

void I8080::opcode_46()    // LD   B,(HL)
{
    B = env_.readByte( HL() );
}

void I8080::opcode_47()    // LD   B,A
{
    B = A;
}

void I8080::opcode_48()    // LD   C,B
{
    C = B;
}

void I8080::opcode_49()    // LD   C,C
{
}

void I8080::opcode_4a()    // LD   C,D
{
    C = D;
}

void I8080::opcode_4b()    // LD   C,E
{
    C = E;
}

void I8080::opcode_4c()    // LD   C,H
{
    C = H;
}

void I8080::opcode_4d()    // LD   C,L
{
    C = L;
}

void I8080::opcode_4e()    // LD   C,(HL)
{
    C = env_.readByte( HL() );
}

void I8080::opcode_4f()    // LD   C,A
{
    C = A;
}

void I8080::opcode_50()    // LD   D,B
{
    D = B;
}

void I8080::opcode_51()    // LD   D,C
{
    D = C;
}

void I8080::opcode_52()    // LD   D,D
{
}

void I8080::opcode_53()    // LD   D,E
{
    D = E;
}

void I8080::opcode_54()    // LD   D,H
{
    D = H;
}

void I8080::opcode_55()    // LD   D,L
{
    D = L;
}

void I8080::opcode_56()    // LD   D,(HL)
{
    D = env_.readByte( HL() );
}

void I8080::opcode_57()    // LD   D,A
{
    D = A;
}

void I8080::opcode_58()    // LD   E,B
{
    E = B;
}

void I8080::opcode_59()    // LD   E,C
{
    E = C;
}

void I8080::opcode_5a()    // LD   E,D
{
    E = D;
}

void I8080::opcode_5b()    // LD   E,E
{
}

void I8080::opcode_5c()    // LD   E,H
{
    E = H;
}

void I8080::opcode_5d()    // LD   E,L
{
    E = L;
}

void I8080::opcode_5e()    // LD   E,(HL)
{
    E = env_.readByte( HL() );
}

void I8080::opcode_5f()    // LD   E,A
{
    E = A;
}

void I8080::opcode_60()    // LD   H,B
{
    H = B;
}

void I8080::opcode_61()    // LD   H,C
{
    H = C;
}

void I8080::opcode_62()    // LD   H,D
{
    H = D;
}

void I8080::opcode_63()    // LD   H,E
{
    H = E;
}

void I8080::opcode_64()    // LD   H,H
{
}

void I8080::opcode_65()    // LD   H,L
{
    H = L;
}

void I8080::opcode_66()    // LD   H,(HL)
{
    H = env_.readByte( HL() );
}

void I8080::opcode_67()    // LD   H,A
{
    H = A;
}

void I8080::opcode_68()    // LD   L,B
{
    L = B;
}

void I8080::opcode_69()    // LD   L,C
{
    L = C;
}

void I8080::opcode_6a()    // LD   L,D
{
    L = D;
}

void I8080::opcode_6b()    // LD   L,E
{
    L = E;
}

void I8080::opcode_6c()    // LD   L,H
{
    L = H;
}

void I8080::opcode_6d()    // LD   L,L
{
}

void I8080::opcode_6e()    // LD   L,(HL)
{
    L = env_.readByte( HL() );
}

void I8080::opcode_6f()    // LD   L,A
{
    L = A;
}

void I8080::opcode_70()    // LD   (HL),B
{
    env_.writeByte( HL(), B );
}

void I8080::opcode_71()    // LD   (HL),C
{
    env_.writeByte( HL(), C );
}

void I8080::opcode_72()    // LD   (HL),D
{
    env_.writeByte( HL(), D );
}

void I8080::opcode_73()    // LD   (HL),E
{
    env_.writeByte( HL(), E );
}

void I8080::opcode_74()    // LD   (HL),H
{
    env_.writeByte( HL(), H );
}

void I8080::opcode_75()    // LD   (HL),L
{
    env_.writeByte( HL(), L );
}

void I8080::opcode_76()    // HALT
{
    halted_ = 1;
    PC--;
}

void I8080::opcode_77()    // LD   (HL),A
{
    env_.writeByte( HL(), A );
}

void I8080::opcode_78()    // LD   A,B
{
    A = B;
}

void I8080::opcode_79()    // LD   A,C
{
    A = C;
}

void I8080::opcode_7a()    // LD   A,D
{
    A = D;
}

void I8080::opcode_7b()    // LD   A,E
{
    A = E;
}

void I8080::opcode_7c()    // LD   A,H
{
    A = H;
}

void I8080::opcode_7d()    // LD   A,L
{
    A = L;
}

void I8080::opcode_7e()    // LD   A,(HL)
{
    A = env_.readByte( HL() );
}

void I8080::opcode_7f()    // LD   A,A
{
}

void I8080::opcode_80()    // ADD  A,B
{
    addByte( B, 0 );
}

void I8080::opcode_81()    // ADD  A,C
{
    addByte( C, 0 );
}

void I8080::opcode_82()    // ADD  A,D
{
    addByte( D, 0 );
}

void I8080::opcode_83()    // ADD  A,E
{
    addByte( E, 0 );
}

void I8080::opcode_84()    // ADD  A,H
{
    addByte( H, 0 );
}

void I8080::opcode_85()    // ADD  A,L
{
    addByte( L, 0 );
}

void I8080::opcode_86()    // ADD  A,(HL)
{
    addByte( env_.readByte( HL() ), 0 );
}

void I8080::opcode_87()    // ADD  A,A
{
    addByte( A, 0 );
}

void I8080::opcode_88()    // ADC  A,B
{
    addByte( B, F & Carry );
}

void I8080::opcode_89()    // ADC  A,C
{
    addByte( C, F & Carry );
}

void I8080::opcode_8a()    // ADC  A,D
{
    addByte( D, F & Carry );
}

void I8080::opcode_8b()    // ADC  A,E
{
    addByte( E, F & Carry );
}

void I8080::opcode_8c()    // ADC  A,H
{
    addByte( H, F & Carry );
}

void I8080::opcode_8d()    // ADC  A,L
{
    addByte( L, F & Carry );
}

void I8080::opcode_8e()    // ADC  A,(HL)
{
    addByte( env_.readByte( HL() ), F & Carry );
}

void I8080::opcode_8f()    // ADC  A,A
{
    addByte( A, F & Carry );
}

void I8080::opcode_90()    // SUB  B
{
    A = subByte( B, 0 );
}

void I8080::opcode_91()    // SUB  C
{
    A = subByte( C, 0 );
}

void I8080::opcode_92()    // SUB  D
{
    A = subByte( D, 0 );
}

void I8080::opcode_93()    // SUB  E
{
    A = subByte( E, 0 );
}

void I8080::opcode_94()    // SUB  H
{
    A = subByte( H, 0 );
}

void I8080::opcode_95()    // SUB  L
{
    A = subByte( L, 0 );
}

void I8080::opcode_96()    // SUB  (HL)
{
    A = subByte( env_.readByte( HL() ), 0 );
}

void I8080::opcode_97()    // SUB  A
{
    A = subByte( A, 0 );
}

void I8080::opcode_98()    // SBC  A,B
{
    A = subByte( B, F & Carry );
}

void I8080::opcode_99()    // SBC  A,C
{
    A = subByte( C, F & Carry );
}

void I8080::opcode_9a()    // SBC  A,D
{
    A = subByte( D, F & Carry );
}

void I8080::opcode_9b()    // SBC  A,E
{
    A = subByte( E, F & Carry );
}

void I8080::opcode_9c()    // SBC  A,H
{
    A = subByte( H, F & Carry );
}

void I8080::opcode_9d()    // SBC  A,L
{
    A = subByte( L, F & Carry );
}

void I8080::opcode_9e()    // SBC  A,(HL)
{
    A = subByte( env_.readByte( HL() ), F & Carry );
}

void I8080::opcode_9f()    // SBC  A,A
{
    A = subByte( A, F & Carry );
}

void I8080::opcode_a0()    // AND  B
{
    A &= B;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_a1()    // AND  C
{
    A &= C;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_a2()    // AND  D
{
    A &= D;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_a3()    // AND  E
{
    A &= E;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_a4()    // AND  H
{
    A &= H;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_a5()    // AND  L
{
    A &= L;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_a6()    // AND  (HL)
{
    A &= env_.readByte( HL() );
    clearAndSetFlagsPSZ();
}

void I8080::opcode_a7()    // AND  A
{
    clearAndSetFlagsPSZ();
}

void I8080::opcode_a8()    // XOR  B
{
    A ^= B;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_a9()    // XOR  C
{
    A ^= C;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_aa()    // XOR  D
{
    A ^= D;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_ab()    // XOR  E
{
    A ^= E;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_ac()    // XOR  H
{
    A ^= H;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_ad()    // XOR  L
{
    A ^= L;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_ae()    // XOR  (HL)
{
    A ^= env_.readByte( HL() );
    clearAndSetFlagsPSZ();
}

void I8080::opcode_af()    // XOR  A
{
    A = 0;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_b0()    // OR   B
{
    A |= B;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_b1()    // OR   C
{
    A |= C;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_b2()    // OR   D
{
    A |= D;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_b3()    // OR   E
{
    A |= E;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_b4()    // OR   H
{
    A |= H;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_b5()    // OR   L
{
    A |= L;
    clearAndSetFlagsPSZ();
}

void I8080::opcode_b6()    // OR   (HL)
{
    A |= env_.readByte( HL() );
    clearAndSetFlagsPSZ();
}

void I8080::opcode_b7()    // OR   A
{
    clearAndSetFlagsPSZ();
}

void I8080::opcode_b8()    // CP   B
{
    subByte( B, 0 );
}

void I8080::opcode_b9()    // CP   C
{
    subByte( C, 0 );
}

void I8080::opcode_ba()    // CP   D
{
    subByte( D, 0 );
}

void I8080::opcode_bb()    // CP   E
{
    subByte( E, 0 );
}

void I8080::opcode_bc()    // CP   H
{
    subByte( H, 0 );
}

void I8080::opcode_bd()    // CP   L
{
    subByte( L, 0 );
}

void I8080::opcode_be()    // CP   (HL)
{
    subByte( env_.readByte( HL() ), 0 );
}

void I8080::opcode_bf()    // CP   A
{
    subByte( A, 0 );
}

void I8080::opcode_c0()    // RET  NZ
{
    if( ! (F & Zero) ) {
        retFromSub();
        cycles_ += 6;
    }
}

void I8080::opcode_c1()    // POP  BC
{
    C = env_.readByte( SP++ );
    B = env_.readByte( SP++ );
}

void I8080::opcode_c2()    // JP   NZ,nn
{
    unsigned    pc = nextWord();

    if( ! (F & Zero) ) {
        PC = pc;
        cycles_ += 5;
    }
}

void I8080::opcode_c3()    // JP   nn
{
     PC = env_.readWord( PC );
}

void I8080::opcode_c4()    // CALL NZ,nn
{
    unsigned    pc = nextWord();

    if( ! (F & Zero) ) {
        callSub( pc );
        cycles_ += 7;
    }
}

void I8080::opcode_c5()    // PUSH BC
{
    env_.writeByte( --SP, B );
    env_.writeByte( --SP, C );
}

void I8080::opcode_c6()    // ADD  A,n
{
    addByte( env_.readByte( PC++ ), 0 );
}

void I8080::opcode_c7()    // RST  0
{
    callSub( 0x00 );
}

void I8080::opcode_c8()    // RET  Z
{
    if( F & Zero ) {
        retFromSub();
        cycles_ += 6;
    }
}

void I8080::opcode_c9()    // RET
{
     retFromSub();
}

void I8080::opcode_ca()    // JP   Z,nn
{
    unsigned    pc = nextWord();

     if( F & Zero ) {
        PC = pc;
        cycles_ += 5;
    }
}

void I8080::opcode_cc()    // CALL Z,nn
{
    unsigned    pc = nextWord();

    if( F & Zero ) {
        callSub( pc );
        cycles_ += 7;
    }
}

void I8080::opcode_cd()    // CALL nn
{
    callSub( nextWord() );
}

void I8080::opcode_ce()    // ADC  A,n
{
    addByte( env_.readByte( PC++ ), F & Carry );
}

void I8080::opcode_cf()    // RST  8
{
    callSub( 0x08 );
}

void I8080::opcode_d0()    // RET  NC
{
    if( ! (F & Carry) ) {
        retFromSub();
        cycles_ += 6;
    }
}

void I8080::opcode_d1()    // POP  DE
{
    E = env_.readByte( SP++ );
    D = env_.readByte( SP++ );
}

void I8080::opcode_d2()    // JP   NC,nn
{
    unsigned    pc = nextWord();

    if( ! (F & Carry) ) {
        PC = pc;
        cycles_ += 5;
    }
}

void I8080::opcode_d3()    // OUT  (n),A
{
    env_.writePort( env_.readByte( PC++ ), A );
}

void I8080::opcode_d4()    // CALL NC,nn
{
    unsigned    pc = nextWord();

    if( ! (F & Carry) ) {
        callSub( pc );
        cycles_ += 7;
    }
}

void I8080::opcode_d5()    // PUSH DE
{
    env_.writeByte( --SP, D );
    env_.writeByte( --SP, E );
}

void I8080::opcode_d6()    // SUB  n
{
    A = subByte( env_.readByte( PC++ ), 0 );
}

void I8080::opcode_d7()    // RST  10H
{
    callSub( 0x10 );
}

void I8080::opcode_d8()    // RET  C
{
    if( F & Carry ) {
        retFromSub();
        cycles_ += 6;
    }
}

void I8080::opcode_da()    // JP   C,nn
{
    unsigned    pc = nextWord();

     if( F & Carry ) {
        PC = pc;
        cycles_ += 5;
    }
}

void I8080::opcode_db()    // IN   A,(n)
{
    A = env_.readPort( env_.readByte( PC++ ) );
}

void I8080::opcode_dc()    // CALL C,nn
{
//    unsigned    pc = nextWord();

    if( F & Carry ) {
        callSub( nextWord() );
        cycles_ += 7;
    }
}

void I8080::opcode_de()    // SBC  A,n
{
    A = subByte( env_.readByte( PC++ ), F & Carry );
}

void I8080::opcode_df()    // RST  18H
{
    callSub( 0x18 );
}

void I8080::opcode_e0()    // RET  PO
{
    if( ! (F & Parity) ) {
        retFromSub();
        cycles_ += 6;
    }
}

void I8080::opcode_e1()    // POP  HL
{
    L = env_.readByte( SP++ );
    H = env_.readByte( SP++ );
}

void I8080::opcode_e2()    // JP   PO,nn
{
    unsigned    pc = nextWord();

     if( ! (F & Parity) ) {
        PC = pc;
        cycles_ += 5;
    }
}

void I8080::opcode_e3()    // EX   (SP),HL
{
    unsigned char   x;

    x = env_.readByte( SP   ); env_.writeByte( SP,   L ); L = x;
    x = env_.readByte( SP+1 ); env_.writeByte( SP+1, H ); H = x;
}

void I8080::opcode_e4()    // CALL PO,nn
{
    unsigned    pc = nextWord();

    if( ! (F & Parity) ) {
        callSub( pc );
        cycles_ += 7;
    }
}

void I8080::opcode_e5()    // PUSH HL
{
    env_.writeByte( --SP, H );
    env_.writeByte( --SP, L );
}

void I8080::opcode_e6()    // AND  n
{
    A &= env_.readByte( PC++ );
    clearAndSetFlagsPSZ();
}

void I8080::opcode_e7()    // RST  20H
{
    callSub( 0x20 );
}

void I8080::opcode_e8()    // RET  PE
{
    if( F & Parity ) {
        retFromSub();
        cycles_ += 6;
    }
}

void I8080::opcode_e9()    // JP   (HL)
{
    PC = HL();
}

void I8080::opcode_ea()    // JP   PE,nn
{
    unsigned    pc = nextWord();

    if( F & Parity ) {
        PC = pc;
        cycles_ += 5;
    }
}

void I8080::opcode_eb()    // EX   DE,HL
{
    unsigned char x;

    x = D; D = H; H = x;
    x = E; E = L; L = x;
}

void I8080::opcode_ec()    // CALL PE,nn
{
    unsigned    pc = nextWord();

    if( F & Parity ) {
        callSub( pc );
        cycles_ += 7;
    }
}

void I8080::opcode_ee()    // XOR  n
{
    A ^= env_.readByte( PC++ );
    clearAndSetFlagsPSZ();
}

void I8080::opcode_ef()    // RST  28H
{
    callSub( 0x28 );
}

void I8080::opcode_f0()    // RET  P
{
    if( ! (F & Sign) ) {
        retFromSub();
        cycles_ += 6;
    }
}

void I8080::opcode_f1()    // POP  AF
{
    F = env_.readByte( SP++ );
    A = env_.readByte( SP++ );
}

void I8080::opcode_f2()    // JP   P,nn
{
    unsigned    pc = nextWord();

    if( ! (F & Sign) ) {
        PC = pc;
        cycles_ += 5;
    }
}

void I8080::opcode_f3()    // DI
{
    F &= ~Interrupt;
}

void I8080::opcode_f4()    // CALL P,nn
{
    unsigned    pc = nextWord();

    if( ! (F & Sign) ) {
        callSub( pc );
        cycles_ += 7;
    }
}

void I8080::opcode_f5()    // PUSH AF
{
    env_.writeByte( --SP, A );
    env_.writeByte( --SP, F );
}

void I8080::opcode_f6()    // OR   n
{
    A |= env_.readByte( PC++ );
    clearAndSetFlagsPSZ();
}

void I8080::opcode_f7()    // RST  30H
{
    callSub( 0x30 );
}

void I8080::opcode_f8()    // RET  M
{
    if( F & Sign ) {
        retFromSub();
        cycles_ += 6;
    }
}

void I8080::opcode_f9()    // LD   SP,HL
{
    SP = HL();
}

void I8080::opcode_fa()    // JP   M,nn
{
    unsigned    pc = nextWord();

    if( F & Sign ) {
        PC = pc;
        cycles_ += 5;
    }
}

void I8080::opcode_fb()    // EI
{
    // Interrupt should be enabled only when another instruction (after this EI) has
    // been executed. We don't emulate that for now.
    F |= Interrupt;
}

void I8080::opcode_fc()    // CALL M,nn
{
    unsigned    pc = nextWord();

    if( F & Sign ) {
        callSub( pc );
        cycles_ += 7;
    }
}

void I8080::opcode_fe()    // CP   n
{
    subByte( env_.readByte( PC++ ), 0 );
}

void I8080::opcode_ff()    // RST  38H
{
    callSub( 0x38 );
}
