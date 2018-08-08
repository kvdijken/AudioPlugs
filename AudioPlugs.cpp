/*
 * AudioInputPlugs for switching one of the inputs through to the single output. Also
 * all inputs can be disabled.
 * 
 * AudioOutputPlugs for switching the single input through to the active outputs,
 * which may be more than one.
 * 
 * Developed 2018 by Koen van Dijken
 */


#include <Arduino.h>
#include "audioplugs.h"


/**

*/
void AudioInputPlugs::update(void)
{
  if ( activeChannel != -1 ) {
    audio_block_t *in = receiveReadOnly( activeChannel );
    if ( in ) {
      transmit( in );
      release( in );
    }
  }
}



/**

*/
void AudioOutputPlugs::update( void )
{
  audio_block_t *block = NULL;
  // Copy the input stream to all active output streams.
  for ( int channel = 0; channel < 4; channel++ ) {
    if (!(activemask & (1 << channel)))
      continue;
    if ( block == NULL ) {
      // Ask for the input stream
      block = receiveReadOnly( 0 );
      if ( !block )
        return;
    }
    transmit( block, channel );
  }
  if ( block )
    release( block );
}

