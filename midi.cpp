#include "pxt.h"
#include "BLEMIDI.h"
using namespace pxt;
/**
* A set of functions to send MIDI commands over Bluetooth
*/
namespace midi {
    BLEMIDI* pMidi;

    BLEMIDI* getMidi() 
    {
        if (NULL == pMidi) 
            pMidi = new BLEMIDI(uBit.ble);
        return pMidi;
    }

    /**
     * Send a `Note On` event
     * @param channel 0-15
     * @param note 0-127
     * @param velocity 0-127
     */
    //% block
    //% channel.min=0 channel.max=15 note.min=0 note.max=127 velocity.min=0 velocity.max=127
    void sendNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
        getMidi()->sendNoteOn(channel, note, velocity);
    }
}
