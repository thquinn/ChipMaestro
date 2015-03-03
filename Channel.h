//inclusion guards
#ifndef CHANNEL_H
#define CHANNEL_H

#include "Arduino.h"

//Stores periods of all frequencies. Note that higher-pitched notes have a smaller period.
static int noteTable[128] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x07F1,0x0780,0x0713,0x06AD,0x064D,0x05F3,0x059D,0x054D,0x0500,0x04B8,0x0475,0x0435,0x03F8,0x03BF,0x0389,0x0356,0x0326,0x02F9,0x02CE,0x02A6,0x027F,0x025C,0x023A,0x021A,0x01FB,0x01DF,0x01C4,0x01AB,0x0193,0x017C,0x0167,0x0152,0x013F,0x012D,0x011C,0x010C,0x00FD,0x00EF,0x00E2,0x00D2,0x00C9,0x00BD,0x00B3,0x00A9,0x009F,0x0096,0x008E,0x0086,0x007E,0x0077,0x0070,0x006A,0x0064,0x005E,0x0059,0x0054,0x004F,0x004B,0x0046,0x0042,0x003F,0x003B,0x0038,0x0034,0x0031,0x002F,0x002C,0x0029,0x0027,0x0025,0x0023,0x0021,0x001F,0x001D,0x001B,0x001A,0x0018,0x0017,0x0015,0x0014,0x0013,0x0012,0x0011,0x0010,0x000F,0x000E,0x000D,0x000C,0x000C,0x000B,0x000A,0x0009,0x0008,0x0007,0x0006};
//Indicates whether or not to modify the pulse channels' high bytes during every frequency change. Some classic NES songs may sound more authentic with this enabled.
static boolean dirtyPulse = false;
//Affects the sound of the noise wave.
static boolean tonalNoise = false;
//Sets how fast decaying notes. Lower values make notes decay faster.
static int decayPeriod = 200;
//Sets how fast sweeps occur in solo mode. Lower values make notes sweep faster.
static int sweepPeriod = 200;
//Determines range of pitch bend wheel, in semitones.
static int bendRange = 12;

class Channel
{
  public:
    int note; //The index of the note currently being played by this channel.
    int type; //This channel's type. 0: Triangle wave, 1: Pulse wave, 2: Noise wave. 3: DMC.
    int index; //Used to keep track of both pulse waves.
    byte vol; //The volume of the note currently being played by this channel.
    byte envelope; //The maximum volume of this channel.
    byte lastHigh; //The last high frequency byte sent to the APU for this channel. Bookkeeping for when dirtyPulse is disabled.
    byte dutyCycle; //0: 12.5%, 1: 25%, 2: 50%, 3: 75%
    boolean changed; //Set to true when this channel's data needs to be sent to the APU.
    boolean decaying; //Whether or not this channel's volume should decay.
    int decayTick; //The number of updates since the last volume decay.
    int sweepNote, sweepTarget, sweepFrom, sweepTo; //The period of the tone being played, the target note, and the periods of the start and target notes.;
    int sweepTick; //The number of updates since the sweep began.
    byte pitchBend; //The value of the pitch bend wheel. 64 is normal, 0 is the minimum value, and 127 is the maximum.
    
    byte packet[6]; //Storage for information to be sent to the NES. Even indices hold addresses; the subsequent odd indices hold data.
    
    Channel(int type, int index);
    void update();
    void setPacket();
    int getPeriod(int note);
    void clear();
    
    //static variable accessors/mutators
    boolean getDirtyPulse();
    void setDirtyPulse(boolean val);
    boolean getTonalNoise();
    void setTonalNoise(boolean val);
    int getDecayPeriod();
    void setDecayPeriod(int val);
    int getSweepPeriod();
    void setSweepPeriod(int val);
    int getBendRange();
    void setBendRange(int val);
};

#endif
