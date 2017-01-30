/*
    Space Invaders arcade machine emulator
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
#include "arcade.h"

unsigned char InvadersMachine::readByte( unsigned addr ) 
{
    return addr < sizeof(ram_) ? ram_[addr] : 0xFF;
}

unsigned char InvadersMachine::readPort( unsigned port ) 
{
    unsigned char   b = 0;

    switch( port ) {
    case 1: 
        b = port1_; 
        port1_ &= 0xFE; 
        break;
    case 2: 
        b = (port2i_ & 0x8F) | (port1_ & 0x70); // Player 1 keys are used for player 2 too
        break;
    case 3: 
        b = (unsigned char)((((port4hi_ << 8) | port4lo_) << port2o_) >> 8);
        break;
    }

    return b;
}

void InvadersMachine::writePort( unsigned addr, unsigned char b )
{
    switch( addr ) {
    case 2:
        port2o_ = b;
        break;
    case 3:
        // Port 3 controls some sounds
        if( ! (b & 0x01) ) sounds_ &= ~SoundUfo;
        if( b & 0x01 ) sounds_ |= SoundUfo;
        if( (b & 0x02) && !(port3o_ & 0x02) ) sounds_ |= SoundShot;
        if( (b & 0x04) && !(port3o_ & 0x04) ) sounds_ |= SoundBaseHit;
        if( (b & 0x08) && !(port3o_ & 0x08) ) sounds_ |= SoundInvaderHit;
        port3o_ = b;
        break;
    case 4:
        port4lo_ = port4hi_;
        port4hi_ = b;
        break;
    case 5:
        // Port 5 controls some sounds
        if( (b & 0x01) && !(port5o_ & 0x01) ) sounds_ |= SoundWalk1;
        if( (b & 0x02) && !(port5o_ & 0x02) ) sounds_ |= SoundWalk2;
        if( (b & 0x04) && !(port5o_ & 0x04) ) sounds_ |= SoundWalk3;
        if( (b & 0x08) && !(port5o_ & 0x08) ) sounds_ |= SoundWalk4;
        if( (b & 0x10) && !(port5o_ & 0x10) ) sounds_ |= SoundUfoHit;
        port5o_ = b;
        break;
    }
}

void InvadersMachine::writeByte( unsigned addr, unsigned char b )
{
    if( addr < 0x2000 || addr >= 0x4000 )
        return;

    ram_[addr] = b;

    if( addr >= 0x2400 ) {
        // This is a write to video memory. Since the video screen is rotated, 
        // consecutive bits correspond to vertically consecutive pixels.
        // This is accounted for in the following code, and an extra buffer
        // is used to store the video memory in a more useable form.
		unsigned k, y;

		addr -= 0x2400;
		y = ((255 - ((addr & 0x1F) * 8) )*224) + (addr / 32);
        for( k=1; k<=128; k<<=1 ) {
            video_[y] = b & k;
			y -= ScreenWidth;
        }
    }
}

void InvadersMachine::reset( int ships, int easy )
{
    // Make sure the number of ships is valid
    if( ships < 3 || ships > 6 ) ships = 3;

    // Reset the CPU and the other machine settings
    cpu_.reset();
    port1_ = 0;
    port2i_ = (ships - 3) & 0x03;   // DIP switches
    port2o_ = 0;
    port3o_ = 0;
    port4lo_ = 0;
    port4hi_ = 0;
    port5o_ = 0;
    sounds_ = 0;

    // Clear the RAM, but avoid the ROM area
    memset( ram_+0x2000, 0, sizeof(ram_)-0x2000 );
    memset( video_, 0, sizeof(video_) );

    // Win a ship at 1000 if easy, otherwise at 1500 (DIP switch)
    if( easy ) port2i_ |= 0x04; 
}

void InvadersMachine::step()
{
    // Resets all sound events but the "permanent" UFO sound,
    // which is turned off by the game
    sounds_ &= SoundUfo;

    // Before a frame is fully rendered, two interrupts have to occur
    for( int i=0; i<2; i++ ) {
        // Go on until an interrupt occurs
        while( cpu_.getCycles() < cycles_per_interrupt_ )
            cpu_.step();

        // Adjust the cycles count
        cpu_.setCycles( cpu_.getCycles() - cycles_per_interrupt_ );
    
        // Call the proper interrupt
        cpu_.interrupt( i ? 0x10 : 0x08 );
    }
}

void InvadersMachine::fireEvent( int event )
{
    switch( event ) 
    {
    case KeyLeftDown:
        port1_ |= 0x20;
        break;
    case KeyLeftUp:
        port1_ &= ~0x20; 
        break;
    case KeyRightDown:
        port1_ |= 0x40; 
        break;
    case KeyRightUp:
        port1_ &= ~0x40; 
        break;
    case KeyFireDown:
        port1_ |= 0x10;
        break;
    case KeyFireUp:
        port1_ &= ~0x10;
        break;
    case KeyOnePlayerDown:
        port1_ |= 0x04;
        break;
    case KeyOnePlayerUp:
        port1_ &= ~0x04;
        break;
    case KeyTwoPlayersDown:
        port1_ |= 0x02;
        break;
    case KeyTwoPlayersUp:
        port1_ &= ~0x02;
        break;
    case CoinInserted:
        port1_ |= 0x01;
        break;
    }
}
