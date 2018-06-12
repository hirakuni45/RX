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

unsigned char I8080::PSZ_[256] = {
    Zero|Parity, 0, 0, Parity, 0, Parity, Parity, 0, 0, Parity, Parity, 0, Parity, 0, 0, Parity, 
    0, Parity, Parity, 0, Parity, 0, 0, Parity, Parity, 0, 0, Parity, 0, Parity, Parity, 0, 
    0, Parity, Parity, 0, Parity, 0, 0, Parity, Parity, 0, 0, Parity, 0, Parity, Parity, 0, 
    Parity, 0, 0, Parity, 0, Parity, Parity, 0, 0, Parity, Parity, 0, Parity, 0, 0, Parity, 
    0, Parity, Parity, 0, Parity, 0, 0, Parity, Parity, 0, 0, Parity, 0, Parity, Parity, 0, 
    Parity, 0, 0, Parity, 0, Parity, Parity, 0, 0, Parity, Parity, 0, Parity, 0, 0, Parity, 
    Parity, 0, 0, Parity, 0, Parity, Parity, 0, 0, Parity, Parity, 0, Parity, 0, 0, Parity, 
    0, Parity, Parity, 0, Parity, 0, 0, Parity, Parity, 0, 0, Parity, 0, Parity, Parity, 0, 
    Sign, Sign|Parity, Sign|Parity, Sign, Sign|Parity, Sign, Sign, Sign|Parity, Sign|Parity, Sign, Sign, Sign|Parity, Sign, Sign|Parity, Sign|Parity, Sign, 
    Sign|Parity, Sign, Sign, Sign|Parity, Sign, Sign|Parity, Sign|Parity, Sign, Sign, Sign|Parity, Sign|Parity, Sign, Sign|Parity, Sign, Sign, Sign|Parity, 
    Sign|Parity, Sign, Sign, Sign|Parity, Sign, Sign|Parity, Sign|Parity, Sign, Sign, Sign|Parity, Sign|Parity, Sign, Sign|Parity, Sign, Sign, Sign|Parity, 
    Sign, Sign|Parity, Sign|Parity, Sign, Sign|Parity, Sign, Sign, Sign|Parity, Sign|Parity, Sign, Sign, Sign|Parity, Sign, Sign|Parity, Sign|Parity, Sign, 
    Sign|Parity, Sign, Sign, Sign|Parity, Sign, Sign|Parity, Sign|Parity, Sign, Sign, Sign|Parity, Sign|Parity, Sign, Sign|Parity, Sign, Sign, Sign|Parity, 
    Sign, Sign|Parity, Sign|Parity, Sign, Sign|Parity, Sign, Sign, Sign|Parity, Sign|Parity, Sign, Sign, Sign|Parity, Sign, Sign|Parity, Sign|Parity, Sign, 
    Sign, Sign|Parity, Sign|Parity, Sign, Sign|Parity, Sign, Sign, Sign|Parity, Sign|Parity, Sign, Sign, Sign|Parity, Sign, Sign|Parity, Sign|Parity, Sign, 
    Sign|Parity, Sign, Sign, Sign|Parity, Sign, Sign|Parity, Sign|Parity, Sign, Sign, Sign|Parity, Sign|Parity, Sign, Sign|Parity, Sign, Sign, Sign|Parity
};


void I8080::addByte( unsigned char op, unsigned char cf )
{
    unsigned    x = A + op;

    if( cf ) x++;

    F &= (Flag3 | Flag5);
    if( ! (x & 0xFF) ) F |= Zero;
    if( x & 0x80 ) F |= Sign;
    if( x >= 0x100 ) F |= Carry;

    /*
        Halfcarry (or auxiliary carry for the 8080) is set on carry from the low order 
        four bits.

        To see how to compute it, let's take a look at the following table, which
        shows the binary addition of two binary numbers:

        A   B   A+B
        -----------
        0   0   0
        0   1   1
        1   0   1
        1   1   0

        Note that if only the lowest bit is used, then A+B, A-B and A^B yield the same 
        value. If we know A, B and the sum A+B+C, then C is easily derived:
            C = A+B+C - A - B,  that is
            C = A+B+C ^ A ^ B.

        For the halfcarry, A and B above are the fifth bit of a byte, which corresponds
        to the value 0x10. So:

            Halfcarry = ((accumulator+operand+halfcarry) ^ accumulator ^ operand) & 0x10

        Note that masking off all bits but one is important because we have worked all
        the math by using one bit only.
    */
    if( (A ^ op ^ x) & 0x10 ) F |= HalfCarry;

    /*
        The overflow bit is useful when dealing with signed numbers. It is set when the 
        (signed) result is too large to fit into the destination register, causing a 
        change in the sign bit. 

        For a sum, we can only have overflow when adding two numbers that are both positive
        or both negative. For example 0x5E + 0x4B (94 + 75) yields 0xA9 (169), which fits
        into an 8-bit register only if it is interpreted as an unsigned number. If we 
        consider the result as a signed integer, then 0xA9 corresponds to decimal -87 and
        we have overflow.
        Note that if we add two signed numbers of opposite sign then we cannot overflow
        the destination register, because the absolute value of the result will always fit
        in 7 bits, leaving the most significant bit free for use as a sign bit.

        We can code all the above concisely by noting that:

            ~(A ^ op) & 0x80

        is true if and only if A and op have the same sign. Also:

            (x ^ op) & 0x80

        is true if and only if the sum of A and op has taken a sign opposite to that
        of its operands.

        Thus the expression:

            ~(A ^ op) & (x ^ op) & 0x80

        reads "A has the same sign as op, and the opposite as x", where x is the sum of
        A and op (and an optional carry).
    */
    if( ~(A ^ op) & (x ^ op) & 0x80 ) F |= Overflow;

    A = x;
}

void I8080::callSub( unsigned addr )
{
    SP -= 2;
    env_.writeWord( SP, PC );
    PC = addr & 0xFFFF;
}

void I8080::clearAndSetFlagsPSZ()
{
    F = (F & (Flag3 | Flag5)) | PSZ_[A];
}

unsigned char I8080::decByte( unsigned char b )
{
    F = (F & ~(Zero | Sign | HalfCarry | Overflow)) | AddSub;
    if( (b & 0x0F) == 0 ) F |= HalfCarry;
    --b;
    if( b == 0x7F ) F |= Overflow;
    if( b & 0x80 ) F |= Sign;
    if( b == 0 ) F |= Zero;

    return b;
}

unsigned char I8080::incByte( unsigned char b )
{
    ++b;
    F &= ~(AddSub | Zero | Sign | HalfCarry | Overflow);
    if( ! (b & 0x0F) ) F |= HalfCarry;
    if( b == 0x80 ) F |= Overflow;
    if( b & 0x80 ) F |= Sign;
    if( b == 0 ) F |= Zero;

    return b;
}

unsigned I8080::nextWord()
{
    unsigned x = env_.readWord( PC );
    PC += 2;
    return x;
}

void I8080::retFromSub()
{
    PC = env_.readWord( SP );
    SP += 2;
}

void I8080::setFlagsPSZ()
{
    F = (F & ~(Parity | Sign | Zero)) | PSZ_[A];
}

unsigned char I8080::subByte( unsigned char op, unsigned char cf )
{
    unsigned char   x = A - op;

    if( cf ) x--;

    F = Subtraction | (F & (Flag3 | Flag5));
    if( x == 0 ) F |= Zero;
    if( x & 0x80 ) F |= Sign;
    if( (x >= A) && (op | cf)) F |= Carry;

    // See addByte() for an explanation of the halfcarry bit.
    if( (A ^ op ^ x) & 0x10 ) F |= HalfCarry;

    // See addByte() for an explanation of the overflow bit. The only difference here
    // is that for a subtraction we must check that the two operands have different
    // sign, because in fact A-B is A+(-B). Note however that since subtraction is not
    // symmetric, we have to use (x ^ A) to get the correct result, whereas for the
    // addition (x ^ A) is equivalent to (x ^ op).
    if( (A ^ op) & (x ^ A) & 0x80 ) F |= Overflow;

    return x;
}
