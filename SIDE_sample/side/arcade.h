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
#ifndef ARCADE_H_
#define ARCADE_H_

#include <string.h>

#include "i8080.h"

/**
    Space Invaders arcade machine emulator.

    This class emulates in software the original Space Invaders arcade machine. It uses
    the I8080 emulator to emulate the CPU and extends the I8080Environment to provide
    the required functions to the CPU emulation.

    For portability, this class does not make direct use of functions that may depend
    on a specific system, such as sound and video. However, it does provide access to
    all necessary information in a form that makes it much easier for a system-dependent
    layer to implement the required functionality.

    For example, sound samples are not directly played but the <i>getSounds()</i> function
    provides information about what sounds the game is playing.

    @author Alessandro Scotti

    @see I8080
    @see I8080Environment
*/
class InvadersMachine : public I8080Environment
{
public:
    /** Machine-related definitions. */
    enum Constants {
        ScreenWidth     = 224,
        ScreenHeight    = 256
    };

    /** Sounds played by the machine. */
    enum Sounds {
        SoundUfo        = 1,
        SoundShot       = 2,
        SoundBaseHit    = 4,
        SoundInvaderHit = 8,
        SoundUfoHit     = 16,
        SoundWalk1      = 32,
        SoundWalk2      = 64,
        SoundWalk3      = 128,
        SoundWalk4      = 256
    };

    /** Events accepted by the machine. */
    enum Events {
        KeyLeftDown     = 0,
        KeyLeftUp,
        KeyRightDown,
        KeyRightUp,
        KeyFireDown,
        KeyFireUp,
        KeyOnePlayerDown,
        KeyOnePlayerUp,
        KeyTwoPlayersDown,
        KeyTwoPlayersUp,
        CoinInserted
    };

public:
    /** Constructor. */
    InvadersMachine();

    /** Destructor. */
    virtual ~InvadersMachine();

    /**
        Resets the machine.

        @param  ships   number of ships per game (3 to 6)
        @param  easy    enable easy play if non zero
    */
    void reset( int ships = 3, int easy = 0 );

    /**
        Executes the program until the next frame is ready.
    */
    void step();

    /**
        Informs the machine that an event has occurred.

        This function is used mainly to fire events related to the coin slots or
        the arcade input devices, such as joysticks and buttons.

        @param  event   event to fire (see the Events enumeration for a list of recognized events)
    */
    void fireEvent( int event );

    /** 
        Returns a pointer to the game video memory in normalized form
        (224x256, one byte per pixel).

        The original machine uses a one bit per pixel monochrome video adapter, where
        a byte contains eight <i>vertically aligned</i> pixels. Since this format is not 
        in use anymore, the emulator reorganizes video memory so that there is one <i>byte</i>
        per pixel, with scanlines arranged <i>as usual</i>: the first scanline starts at offset
        <b>0</b>, the second at offset <b>224</b> and so on. This "wastes" some memory,
        but makes it much easier to render the video on current cards.

        @return a pointer to a 224x256 byte array, where each byte corresponds to a screen pixel
    */
    const unsigned char * getVideo() const {
        return video_;
    }

    /**
        Returns a bit array which describes what sounds the game has played during
        the last frame.

        The original machine used custom analogic devices for sounds, controlled by
        a couple of I/O ports. Once activated each sound device would go on automatically
        and generate its own sound effect without requiring further control by the CPU.
        Because of that, the easiest and probably best approach for emulation is to sample
        the original sounds and then simply play them back when required. This is the
        approach that this class supports with the <i>getSounds()</i> function.

        To simplify implementations, the emulator adopts an <i>event based</i> approach that 
        keeps track of <i>changes</i> in the sound status. In fact, it is only useful to
        know when a sound is activated, because then it will play automatically and then go
        off all by itself. 
        In fact, when <i>step()</i> is called, one of the first things it does is to reset
        the sound status. As the game runs, it may activate one or more sounds, which the
        emulator keeps track of. Eventually, on exit from the <i>step()</i> function, the
        updated sound status can be retrieved by calling <i>getSounds()</i>.

        The value returned by <i>getSounds()</i> is an array of bits where each bit corresponds
        to a sound. If a bit is set, it means that during the last step (or <i>frame</i>) the
        game has played the corresponding sound. Note that if a bit is not set that does not mean
        that the corresponding sound is turned off, but rather that it keeps it current status. 
        A sound should be only turned off when the corresponding sample has been entirely played.

        The only exception is represented by the UFO sound (the <i>SoundUfo</i> bit), which
        goes into a continuous loop when played. In this case the game explicitly turns on and
        off the sound, and so the corresponding bit by <i>getSounds()</i> actually reflects the
        sound status, playing when set and not playing when reset.

        Assuming that the function <i>PlaySound</i> plays a sound once, and that <i>PlayLoopedSound</i>
        plays a sound that automatically loops, sounds could be handled like in the following
        code snippet.

        <pre>
        @@ ...
        @@ machine.step();
        @@ 
        @@ if( machine.getSounds() & InvadersMachine::SoundShot )
        @@     PlaySound( "SoundShot sample" );
        @@ ...
        @@ 
        @@ if( machine.getSounds() & InvadersMachine::SoundUfo )
        @@     PlayLoopedSound( "SoundUfo sample" );
        @@ else
        @@     StopLoopedSound( "SoundUfo sample" );
        @@ ...
        </pre>

        @see #Sounds                
    */
    unsigned getSounds() const {
        return sounds_;
    }

    /**
        Sets the video frame rate.

        @param  fps     frames per second
    */
    void setFrameRate( unsigned fps ) {
        // Cycles per interrupt are given by the formula:
        // "CPU clock" / ("interrupts per frame" * "frames per second")
        cycles_per_interrupt_ = (2000000 / (2*fps));    // 2Mhz processor, 2 interrupts per frame
        fps_ = fps;
    }

    /**
        Returns the current frame rate.
    */
    unsigned getFrameRate() const {
        return fps_;
    }

    /**
        Sets the machine ROM.

        For this machine, the ROM is an 8K area that starts at address 0x0000.

        <b>Note:</b> the ROM is copied to internal storage and the specified pointer
        is no longer used after this function returns.

        @param  rom pointer to the ROM buffer
    */
    void setROM( const char * rom ) {
        memcpy( ram_, rom, 0x2000 );
    }

protected:
    // Implementation of the CpuEnvironment interface
    unsigned char readByte( unsigned addr );

    void writeByte( unsigned, unsigned char );

    unsigned char readPort( unsigned port );

    void writePort( unsigned, unsigned char );

private:
    unsigned char   port1_;
    unsigned char   port2i_;    // Port 2 in
    unsigned char   port2o_;    // Port 2 out
    unsigned char   port3o_;    // Port 3 out
    unsigned char   port4lo_;   // Port 4 out (lo)
    unsigned char   port4hi_;   // Port 4 out (hi)
    unsigned char   port5o_;    // Port 5 out
    unsigned char   ram_[0x4000];
    unsigned char   video_[ScreenWidth*ScreenHeight];
    unsigned        sounds_;
    unsigned        fps_;
    unsigned        cycles_per_interrupt_;
    I8080 *         cpu_;
};

#endif // ARCADE_H_
