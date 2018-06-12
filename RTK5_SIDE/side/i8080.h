/*
    I8080 emulator
    Copyright (c) 1997-2002,2003 Alessandro Scotti
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
#ifndef I8080_H_
#define I8080_H_

/**
    Environment for the I8080 CPU emulator.

    This class implements all input/output functions for the I8080 emulator class,
    that is it provides functions to access the system RAM, ROM and I/O ports.

    An object (instance) of this class corresponds to a system that has no RAM, ROM or 
    ports: users of the I8080 emulator should provide the desired behaviour by writing a
    descendant of this class that overrides the required functions.

    @author Alessandro Scotti
*/
class I8080Environment
{
public:
    /** 
        Constructor. 

        The object created by this base class corresponds to a system with no RAM, ROM or 
        ports.
    */
    I8080Environment() {
    }

    /** Destructor. */
    virtual ~I8080Environment() {
    }

    /**
        Reads one byte from memory at the specified address.

        The address parameter may contain any value, including
        values greater than 0xFFFF (64k), so if necessary
        the implementation must check for illegal values and
        handle them according to the implemented system 
        specifications.

        @param  addr    address of memory byte to read

        @return the content of the specified memory address
    */
    virtual unsigned char readByte( unsigned addr ) {
        return 0xFF;
    }

    /**
        Reads a 16 bit word from memory at the specified address.

        The address parameter may contain any value, including
        values greater than 0xFFFF (64k), so if necessary
        the implementation must check for illegal values and
        handle them according to the implemented system 
        specifications.

        The default implementation uses <i>readByte()</i>, so it is not
        strictly necessary to override this method.

        @see #readByte
    */
    virtual unsigned readWord( unsigned addr ) {
        return readByte(addr) | (unsigned)(readByte(addr+1) << 8);
    }

    /**
        Writes one byte to memory at the specified address.

        The address parameter may contain any value, including
        values greater than 0xFFFF (64k), so if necessary
        the implementation must check for illegal values and
        handle them according to the implemented system 
        specifications.

        @param  addr    address of memory byte to write
        @param  value   value to write at specified address
    */
    virtual void writeByte( unsigned addr, unsigned char value ) {
    }

    /**
        Writes a 16 bit word to memory at the specified address.

        The address parameter may contain any value, including
        values greater than 0xFFFF (64k), so if necessary
        the implementation must check for illegal values and
        handle them according to the specifications of the
        emulated system.

        The default implementation uses <i>writeByte()</i>, so it is not
        strictly necessary to override this method.

        <b>Note:</b> the low order byte is placed at the lowest address.

        @param  addr    address of memory word to write
        @param  value   16-bit value to write at specified address

        @see #writeByte
    */
    virtual void writeWord( unsigned addr, unsigned value ) {
        writeByte( addr, value & 0xFF );
        writeByte( addr+1, (value >> 8) & 0xFF );
    }

    /**
        Reads one byte from the specified port.

        <b>Note:</b> the port value is always between 00h and FFh included.

        @param  port    address of port to read

        @return the value of the specified port
    */
    virtual unsigned char readPort( unsigned port ) {
        return 0xFF;
    }

    /**
        Writes one byte from the specified port.

        <b>Note:</b> the port value is always between 00h and FFh included.

        @param  port    address of port to write
        @param  value   value to write to specified port
    */
    virtual void writePort( unsigned port, unsigned char value ) {
    }
};

/**
    I8080 CPU emulator.

    @author Alessandro Scotti
*/
class I8080
{
public:
    /** CPU flags. */
    enum Flags {
        Carry     = 0x01,
        AddSub    = 0x02, Subtraction = AddSub,
        Parity    = 0x04, Overflow = Parity,    // Same bit used for parity and overflow
        Flag3     = 0x08,
        HalfCarry = 0x10, AuxCarry = HalfCarry,
        Flag5     = 0x20, Interrupt = Flag5,
        Zero      = 0x40,
        Sign      = 0x80
    };

public:
    /** 8-bit register B. */
    unsigned char   B;
    /** 8-bit register C. */
    unsigned char   C;
    /** 8-bit register D. */
    unsigned char   D;
    /** 8-bit register E. */
    unsigned char   E;
    /** 8-bit register H. */
    unsigned char   H;
    /** 8-bit register L. */
    unsigned char   L;
    /** 8-bit accumulator register A. */
    unsigned char   A;     
    /** 8-bit flag register F. */
    unsigned char   F;
    /** 16-bit program counter. */
    unsigned        PC;
    /** 16-bit stack pointer. */
    unsigned        SP;

    /** 
        Costructor.

        Creates an I8080 emulator associated to the specified <i>environment</i>.
        The <i>environment</i> provides functions to access memory and ports, that is
        it interfaces the emulated CPU with the other (emulated) hardware components.

        @see I8080Environment
    */
    I8080( I8080Environment & env );

    /** Copy constructor. */
    I8080( const I8080 & cpu );

    /** Destructor. */
    virtual ~I8080() {
    }

    /** Resets the CPU to its initial state. */
    virtual void reset();

    /** Executes one CPU instruction. */
    virtual void step();

    /** 
        Informs the CPU that an interrupt has occurred.

        @param  address 16-bit address of the interrupt handler
    */
    virtual void interrupt( unsigned address );

    /** Returns the 16-bit pseudo-register AF. */
    unsigned AF() const {
        return ((unsigned)A << 8) | F; 
    }

    /** Returns the 16-bit pseudo-register BC. */
    unsigned BC() const { 
        return ((unsigned)B << 8) | C; 
    }

    /** Returns the 16-bit pseudo-register DE. */
    unsigned DE() const { 
        return ((unsigned)D << 8) | E; 
    }

    /** Returns the 16-bit pseudo-register HL. */
    unsigned HL() const {
        return ((unsigned)H << 8) | L; 
    }

    /** Returns the number of CPU cycles elapsed from the last reset. */
    unsigned getCycles() const {
        return cycles_;
    }

    /** Sets the CPU cycle counter to the specified value. */
    void setCycles( unsigned value ) {
        cycles_ = value;
    }

    /** Assignment operator. Note that the environment is <b>not</b> copied. */
    I8080 & operator = ( const I8080 & );

protected:
    /* 
        Implementation of opcodes 0x00 to 0xFF.

        For each function both the Z80 and 8080 mnemonics are specified,
        with also a short explanation of the latter.
    */
    void opcode_00();   // NOP              / NOP       (no operation)
    void opcode_01();   // LD   BC,nn       / LXI  B,nn (load immediate register pair B & C)
    void opcode_02();   // LD   (BC),A      / STAX B    (store A indirect to B & C)
    void opcode_03();   // INC  BC          / INX  B
    void opcode_04();   // INC  B           / INR  B    (increment register)
    void opcode_05();   // DEC  B           / DCR  B    (decrement register)
    void opcode_06();   // LD   B,n         / MVI  B,n  (move immediate register)         
    void opcode_07();   // RLCA             / RLC       (rotate A left)
    // 0x08
    void opcode_09();   // ADD  HL,BC       / DAD  B    (add B & C to H & L)
    void opcode_0a();   // LD   A,(BC)      / LDAX B    (load A indirect from B & C)
    void opcode_0b();   // DEC  BC          / DEX  B
    void opcode_0c();   // INC  C           / INR  C    (increment register)
    void opcode_0d();   // DEC  C           / DCR  C    (decrement register)
    void opcode_0e();   // LD   C,n         / MVI  C,n  (move immediate register)
    void opcode_0f();   // RRCA             / RRC       (rotate A right)
    // 0x10
    void opcode_11();   // LD   DE,nn       / LXI  D,nn (load immediate register pair D & E)
    void opcode_12();   // LD   (DE),A      / STAX D    (store A indirect to D & E)
    void opcode_13();   // INC  DE          / INX  D
    void opcode_14();   // INC  D           / INR  D    (increment register)
    void opcode_15();   // DEC  D           / DCR  D    (decrement register)
    void opcode_16();   // LD   D,n         / MVI  D,n  (move immediate register)
    void opcode_17();   // RLA              / RAL       (rotate A left thru carry)
    // 0x18
    void opcode_19();   // ADD  HL,DE       / DAD  D    (add D & E to H & L)
    void opcode_1a();   // LD   A,(DE)      / LDAX D    (load A indirect from D & E)
    void opcode_1b();   // DEC  DE          / DEX  D
    void opcode_1c();   // INC  E           / INR  E    (increment register)
    void opcode_1d();   // DEC  E           / DCR  E    (decrement register)
    void opcode_1e();   // LD   E,n         / MVI  E,n  (move immediate register)
    void opcode_1f();   // RRA              / RAR       (rotate A right thru carry)
    // 0x20
    void opcode_21();   // LD   HL,nn       / LXI  H,nn (load immediate register pair H & L)
    void opcode_22();   // LD   (nn),HL     / SHLD      (store H & L direct)
    void opcode_23();   // INC  HL          / INX  H
    void opcode_24();   // INC  H           / INR  H    (increment register)
    void opcode_25();   // DEC  H           / DCR  H    (decrement register)
    void opcode_26();   // LD   H,n         / MVI  H,n  (move immediate register)
    void opcode_27();   // DAA              / DAA       (decimal adjust A)
    // 0x28
    void opcode_29();   // ADD  HL,HL       / DAD  H    (add H & L to H & L)    
    void opcode_2a();   // LD   HL,(nn)     / LHLD      (load H & L direct)
    void opcode_2b();   // DEC  HL          / DEX  H
    void opcode_2c();   // INC  L           / INR  L    (increment register)
    void opcode_2d();   // DEC  L           / DCR  L    (decrement register)
    void opcode_2e();   // LD   L,n         / MVI  L,n  (move immediate register)
    void opcode_2f();   // CPL              / CMA       (complement A)
    // 0x30
    void opcode_31();   // LD   SP,nn       / LXI  SP   (load immediate stack pointer)
    void opcode_32();   // LD   (nn),A      / STA  nn   (store A direct)
    void opcode_33();   // INC  SP          / INX  SP
    void opcode_34();   // INC  (HL)        / INR  M    (increment memory)
    void opcode_35();   // DEC  (HL)
    void opcode_36();   // LD   (HL),n      / MVI  M,n  (move immediate memory)
    void opcode_37();   // SCF              / STC       (set carry)    
    // 0x38
    void opcode_39();   // ADD  HL,SP       / DAD  SP   (add stack pointer to H & L)
    void opcode_3a();   // LD   A,(nn)      / LDA       (load A direct)
    void opcode_3b();   // DEC  SP          / DEX  SP
    void opcode_3c();   // INC  A           / INR  A    (increment register)
    void opcode_3d();   // DEC  A           / DCR  A    (decrement register)
    void opcode_3e();   // LD   A,n         / MVI  A,n  (move immediate register)
    void opcode_3f();   // CCF              / CMC       (complement carry)
    void opcode_40();   // LD   B,B         / MOV  B,B  (move register to register)
    void opcode_41();   // LD   B,C         / MOV  B,C
    void opcode_42();   // LD   B,D         / MOV  B,D
    void opcode_43();   // LD   B,E         / MOV  B,E
    void opcode_44();   // LD   B,H         / MOV  B,H
    void opcode_45();   // LD   B,L         / MOV  B,L
    void opcode_46();   // LD   B,(HL)      / MOV  B,M  (move memory to register)
    void opcode_47();   // LD   B,A         / MOV  B,A
    void opcode_48();   // LD   C,B         / MOV  C,B
    void opcode_49();   // LD   C,C         / MOV  C,C
    void opcode_4a();   // LD   C,D         / MOV  C,D
    void opcode_4b();   // LD   C,E         / MOV  C,E
    void opcode_4c();   // LD   C,H         / MOV  C,H
    void opcode_4d();   // LD   C,L         / MOV  C,L
    void opcode_4e();   // LD   C,(HL)      / MOV  C,M
    void opcode_4f();   // LD   C,A         / MOV  C,A
    void opcode_50();   // LD   D,B         / MOV  D,B
    void opcode_51();   // LD   D,C         / MOV  D,C
    void opcode_52();   // LD   D,D         / MOV  D,D
    void opcode_53();   // LD   D,E         / MOV  D,E
    void opcode_54();   // LD   D,H         / MOV  D,H
    void opcode_55();   // LD   D,L         / MOV  D,L
    void opcode_56();   // LD   D,(HL)      / MOV  D,M
    void opcode_57();   // LD   D,A         / MOV  D,A
    void opcode_58();   // LD   E,B         / MOV  E,B
    void opcode_59();   // LD   E,C         / MOV  E,C
    void opcode_5a();   // LD   E,D         / MOV  E,D
    void opcode_5b();   // LD   E,E         / MOV  E,E
    void opcode_5c();   // LD   E,H         / MOV  E,H
    void opcode_5d();   // LD   E,L         / MOV  E,L
    void opcode_5e();   // LD   E,(HL)      / MOV  E,M
    void opcode_5f();   // LD   E,A         / MOV  E,A
    void opcode_60();   // LD   H,B         / MOV  H,B
    void opcode_61();   // LD   H,C         / MOV  H,C
    void opcode_62();   // LD   H,D         / MOV  H,D
    void opcode_63();   // LD   H,E         / MOV  H,E
    void opcode_64();   // LD   H,H         / MOV  H,H
    void opcode_65();   // LD   H,L         / MOV  H,L
    void opcode_66();   // LD   H,(HL)      / MOV  H,M
    void opcode_67();   // LD   H,A         / MOV  H,A
    void opcode_68();   // LD   L,B         / MOV  L,B
    void opcode_69();   // LD   L,C         / MOV  L,C
    void opcode_6a();   // LD   L,D         / MOV  L,D
    void opcode_6b();   // LD   L,E         / MOV  L,E
    void opcode_6c();   // LD   L,H         / MOV  L,H
    void opcode_6d();   // LD   L,L         / MOV  L,L
    void opcode_6e();   // LD   L,(HL)      / MOV  L,M
    void opcode_6f();   // LD   L,A         / MOV  L,A
    void opcode_70();   // LD   (HL),B      / MOV  M,B  (move register to memory)
    void opcode_71();   // LD   (HL),C      / MOV  M,C
    void opcode_72();   // LD   (HL),D      / MOV  M,D
    void opcode_73();   // LD   (HL),E      / MOV  M,E
    void opcode_74();   // LD   (HL),H      / MOV  M,H
    void opcode_75();   // LD   (HL),L      / MOV  M,L
    void opcode_76();   // HALT             / HLT       (halt)
    void opcode_77();   // LD   (HL),A      / MOV  M,A
    void opcode_78();   // LD   A,B         / MOV  A,B
    void opcode_79();   // LD   A,C         / MOV  A,C
    void opcode_7a();   // LD   A,D         / MOV  A,D
    void opcode_7b();   // LD   A,E         / MOV  A,E
    void opcode_7c();   // LD   A,H         / MOV  A,H
    void opcode_7d();   // LD   A,L         / MOV  A,L
    void opcode_7e();   // LD   A,(HL)      / MOV  A,M
    void opcode_7f();   // LD   A,A         / MOV  A,A
    void opcode_80();   // ADD  A,B         / ADD B     (add register to A)
    void opcode_81();   // ADD  A,C         / ADD C
    void opcode_82();   // ADD  A,D         / ADD D
    void opcode_83();   // ADD  A,E         / ADD E
    void opcode_84();   // ADD  A,H         / ADD H
    void opcode_85();   // ADD  A,L         / ADD L
    void opcode_86();   // ADD  A,(HL)      / ADD M     (add register to memory)
    void opcode_87();   // ADD  A,A         / ADD A
    void opcode_88();   // ADC  A,B         / ADC B     (add register to A with carry)
    void opcode_89();   // ADC  A,C         / ADC C
    void opcode_8a();   // ADC  A,D         / ADC D
    void opcode_8b();   // ADC  A,E         / ADC E
    void opcode_8c();   // ADC  A,H         / ADC H
    void opcode_8d();   // ADC  A,L         / ADC L
    void opcode_8e();   // ADC  A,(HL)      / ADC M     (add memory to A with carry)
    void opcode_8f();   // ADC  A,A         / ADC A
    void opcode_90();   // SUB  B           / SUB B     (subtract register from A)
    void opcode_91();   // SUB  C           / SUB C
    void opcode_92();   // SUB  D           / SUB D
    void opcode_93();   // SUB  E           / SUB E
    void opcode_94();   // SUB  H           / SUB H
    void opcode_95();   // SUB  L           / SUB L
    void opcode_96();   // SUB  (HL)        / SUB M     (subtract memory from A)
    void opcode_97();   // SUB  A           / SUB A
    void opcode_98();   // SBC  A,B         / SBB B     (subtract register from A with borrow)
    void opcode_99();   // SBC  A,C         / SBB C
    void opcode_9a();   // SBC  A,D         / SBB D
    void opcode_9b();   // SBC  A,E         / SBB E
    void opcode_9c();   // SBC  A,H         / SBB H
    void opcode_9d();   // SBC  A,L         / SBB L
    void opcode_9e();   // SBC  A,(HL)      / SBB M     (subtract memory from A with borrow)
    void opcode_9f();   // SBC  A,A         / SBB A
    void opcode_a0();   // AND  B           / ANA B     (and register with A)
    void opcode_a1();   // AND  C           / ANA C
    void opcode_a2();   // AND  D           / ANA D
    void opcode_a3();   // AND  E           / ANA E
    void opcode_a4();   // AND  H           / ANA H
    void opcode_a5();   // AND  L           / ANA L
    void opcode_a6();   // AND  (HL)        / ANA M     (and memory with A)
    void opcode_a7();   // AND  A           / ANA A
    void opcode_a8();   // XOR  B           / XRA B     (exclusive or register with A)
    void opcode_a9();   // XOR  C           / XRA C
    void opcode_aa();   // XOR  D           / XRA D
    void opcode_ab();   // XOR  E           / XRA E
    void opcode_ac();   // XOR  H           / XRA H
    void opcode_ad();   // XOR  L           / XRA L
    void opcode_ae();   // XOR  (HL)        / XRA M     (exclusive or memory with A)
    void opcode_af();   // XOR  A           / XRA A
    void opcode_b0();   // OR   B           / ORA B     (or register with A)
    void opcode_b1();   // OR   C           / ORA C
    void opcode_b2();   // OR   D           / ORA D
    void opcode_b3();   // OR   E           / ORA E
    void opcode_b4();   // OR   H           / ORA H
    void opcode_b5();   // OR   L           / ORA L
    void opcode_b6();   // OR   (HL)        / ORA M     (or memory with A)
    void opcode_b7();   // OR   A           / ORA A
    void opcode_b8();   // CP   B           / CMP B     (compare register with A)
    void opcode_b9();   // CP   C           / CMP C 
    void opcode_ba();   // CP   D           / CMP D
    void opcode_bb();   // CP   E           / CMP E
    void opcode_bc();   // CP   H           / CMP H
    void opcode_bd();   // CP   L           / CMP L
    void opcode_be();   // CP   (HL)        / CMP M     (compare memory with A)
    void opcode_bf();   // CP   A           / CMP A
    void opcode_c0();   // RET  NZ          / RNZ
    void opcode_c1();   // POP  BC          / POP B     (pop register pair B & C off stack)
    void opcode_c2();   // JP   NZ,nn       / JNZ nn
    void opcode_c3();   // JP   nn          / JMP nn    (jump unconditional)
    void opcode_c4();   // CALL NZ,nn       / CNZ nn
    void opcode_c5();   // PUSH BC          / PUSH B    (push register pair B & C on stack)
    void opcode_c6();   // ADD  A,n         / ADI n     (add immediate to A)
    void opcode_c7();   // RST  00H         / RST 00h   (restart from 0000h)
    void opcode_c8();   // RET  Z           / RZ
    void opcode_c9();   // RET              / RET       (return)
    void opcode_ca();   // JP   Z,nn        / JZ  nn
    // 0xCB
    void opcode_cc();   // CALL Z,nn        / CZ  nn
    void opcode_cd();   // CALL nn          / CALL nn   (call unconditional)
    void opcode_ce();   // ADC  A,n         / ACI n     (add immediate to A with carry)
    void opcode_cf();   // RST  08H         / RST 08h
    void opcode_d0();   // RET  NC          / RNC
    void opcode_d1();   // POP  DE          / POP D     (pop register pair D & E off stack)
    void opcode_d2();   // JP   NC,nn       / JNC nn
    void opcode_d3();   // OUT  (n),A       / OUT n     (output)
    void opcode_d4();   // CALL NC,nn       / CNC nn
    void opcode_d5();   // PUSH DE          / PUSH D    (push register pair D & E on stack)
    void opcode_d6();   // SUB  n           / SUI n     (subtract immediate from A)
    void opcode_d7();   // RST  10H         / RST 10h
    void opcode_d8();   // RET  C           / RC
    // 0xD9
    void opcode_da();   // JP   C,nn        / JC  nn
    void opcode_db();   // IN   A,(n)       / IN  n     (input)
    void opcode_dc();   // CALL C,nn        / CC  nn
    // 0xDD
    void opcode_de();   // SBC  A,n         / SBI n     (subtract immediate from a with borrow)
    void opcode_df();   // RST  18H         / RST 18h
    void opcode_e0();   // RET  PO          / RPO
    void opcode_e1();   // POP  HL          / POP H     (pop register pair H & L off stack)
    void opcode_e2();   // JP   PO,nn       / JPO nn
    void opcode_e3();   // EX   (SP),HL     / XTHL      (exchange top of stack, H & L)
    void opcode_e4();   // CALL PO,nn       / CPO nn
    void opcode_e5();   // PUSH HL          / PUSH H    (push register pair H & L on stack)
    void opcode_e6();   // AND  n           / ANI n     (and immediate with A)
    void opcode_e7();   // RST  20H         / RST 20h
    void opcode_e8();   // RET  PE          / RPE
    void opcode_e9();   // JP   (HL)        / PCHL      (H & L to program counter)
    void opcode_ea();   // JP   PE,nn       / JPE n
    void opcode_eb();   // EX   DE,HL       / XCHG      (exchange D & E, H & L registers)
    void opcode_ec();   // CALL PE,nn       / CPE nn
    // 0xED
    void opcode_ee();   // XOR  n           / XRI n     (exclusive or immediate with A)
    void opcode_ef();   // RST  28H         / RST 28h
    void opcode_f0();   // RET  P           / RP        (return on positive)
    void opcode_f1();   // POP  AF          / POP PSW   (pop A and Flags off stack)
    void opcode_f2();   // JP   P,nn        / JP  nn    (jump on positive)
    void opcode_f3();   // DI               / DI        (disable interrupts)
    void opcode_f4();   // CALL P,nn        / CP  nn    (call on positive)
    void opcode_f5();   // PUSH AF          / PUSH PSW  (push A and Flags on stack)
    void opcode_f6();   // OR   n           / ORI n     (or immediate with A)
    void opcode_f7();   // RST  30H         / RST 30h
    void opcode_f8();   // RET  M           / RM        (return on minus)
    void opcode_f9();   // LD   SP,HL       / SPHL      (H & L to stack pointer)
    void opcode_fa();   // JP   M,nn        / JM  nn    (jump on minus)
    void opcode_fb();   // EI               / EI        (enable interrupts)
    void opcode_fc();   // CALL M,nn        / CM  nn    (call on minus)
    // 0xFD
    void opcode_fe();   // CP   n           / CPI n     (compare immediate with A)  
    void opcode_ff();   // RST  38H         / RST 38h

    /** Adds byte OP to accumulator, with carry CF. Flags are updated. */
    void addByte( unsigned char OP, unsigned char CF );

    /** Calls subroutine at specified address. */
    void callSub( unsigned addr );

    /** Clears all the flags and sets parity, zero and sign according to accumulator value. */
    void clearAndSetFlagsPSZ();

    /** Decrements and returns the specified byte. Flags are updated. */
    unsigned char decByte( unsigned char b );

    /** Increments and returns the specified byte. Flags are updated. */
    unsigned char incByte( unsigned char b );

    /** Fetches the next 16-bit value at the program counter address. */
    unsigned nextWord();

    /** Returns from the current subroutine. */
    void retFromSub();

    /** Sets parity, zero and sign according to accumulator value. */
    void setFlagsPSZ();

    /** Subtracts byte OP from accumulator, with borrow CF. Flags are updated. */
    unsigned char subByte( unsigned char OP, unsigned char CF );

private:
    typedef void (I8080::* OpcodeHandler)();

    typedef struct {
        OpcodeHandler   handler;
        unsigned        cycles;
    } OpcodeInfo;

    static OpcodeInfo   Opcode_[256];   // Opcode table

    static unsigned char    PSZ_[256];  // Parity, sign, zero table

    unsigned            halted_;
    unsigned            cycles_;
    I8080Environment &  env_;
};

#endif // I8080_H_
