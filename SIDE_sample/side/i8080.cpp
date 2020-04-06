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
#include "i8080.h"

I8080::I8080( I8080Environment & env )
    : env_( env )
{
    reset();
}

I8080::I8080( const I8080 & cpu )
    : env_( cpu.env_ )
{
    operator = ( cpu );
}

I8080 & I8080::operator = ( const I8080 & cpu )
{
    B = cpu.B;
    C = cpu.C;
    D = cpu.D;
    E = cpu.E;
    H = cpu.H;
    L = cpu.L;
    A = cpu.A;
    F = cpu.F;
    PC = cpu.PC;
    SP = cpu.SP;

//    halted_ = halted_;
//    cycles_ = cycles_;

    return *this;
}

void I8080::reset()
{
    B = 0; 
    C = 0;
    D = 0; 
    E = 0;
    H = 0;
    L = 0;
    A = 0;
    F = 0;
    PC = 0;
    SP = 0xF000;

    halted_ = 0;
    cycles_ = 0;
}

void I8080::step()
{
    unsigned op = env_.readByte( PC++ );

    // Execute
    cycles_ += Opcode_[ op ].cycles;
    if( Opcode_[ op ].handler )
        (this->*(Opcode_[ op ].handler))();

    PC &= 0xFFFF;
}

void I8080::interrupt( unsigned address )
{
    if( F & Interrupt ) {
        if( halted_ ) {
            PC++;
            halted_ = 0;
        }
        env_.writeByte( --SP, (PC >> 8) & 0xFF );
        env_.writeByte( --SP, PC & 0xFF );
        PC = address & 0xFFFF;
    }
}
