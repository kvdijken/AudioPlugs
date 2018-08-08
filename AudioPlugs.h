/*
 * AudioInputPlugs for switching one of the inputs through to the single output. Also
 * all inputs can be disabled.
 * 
 * AudioOutputPlugs for switching the single input through to the active outputs,
 * which may be more than one.
 * 
 * Developed 2018 by Koen van Dijken
 */


#ifndef _audioplugs_h_
#define _audioplugs_h_

#include "Arduino.h"
#include "AudioStream.h"


/**
 * AudioInputPlugs
 */
class AudioInputPlugs : public AudioStream
{
  public:
    AudioInputPlugs(void) : AudioStream(4, inputQueueArray) {
      // No channel active yet.
      activeChannel = -1;
    }
    
    virtual void update( void );

    /**
     * plug( 2 ) to plug in channel two and unplug all other inputs
     * plug( -1 ) to unplug all inputs
     */
    void plug( int channel ) {
      if( channel > 3 )
        // not allowed
        return;
      if( channel < -1 )
        // not allowed
        return;
      activeChannel = channel;
    }
  private:
    int activeChannel;
    audio_block_t *inputQueueArray[4];
};


/**
 * AudioOutputPlugs
 */
class AudioOutputPlugs: public AudioStream
{
  public:
    AudioOutputPlugs() : AudioStream(1, inputQueueArray) {
      activemask = 0;
    }

    /**
     * plug to enable the selected output channel
     */
    void plug( uint8_t channel ) {
      if (channel > 3)
        return;
      // enable this channel
      activemask |= (1 << channel);
    }

    /*
     * unplug to disable the selected output channel
     */
    void unplug(uint8_t channel) {
      if (channel > 3) 
        return;
      // disable this channel
      activemask &= ~(1 << channel);
    }

    virtual void update(void);
  private:
    uint8_t activemask;
    audio_block_t *inputQueueArray[1];
};

#endif
