#include "pxt.h"
#include "BluetoothMIDIService.h"
using namespace pxt;
/**
* A set of functions to send MIDI commands over Bluetooth
*/
namespace midi {
    BluetoothMIDIService* pMidi;

    BluetoothMIDIService* getMidi() 
    {
        if (NULL == pMidi) 
            pMidi = new BluetoothMIDIService(uBit.ble);
        return pMidi;
    }

    /**
    * Starts the MIDI service
    */
    //% block
    void startBluetoothService() {
        getMidi();
    }

    /**
     * Send a `Note On` event
     * @param channel 0-15
     * @param note 0-127
     * @param velocity 0-127
     */
    //% block
    //% channel.min=0 channel.max=15 note.min=0 note.max=127 velocity.min=0 velocity.max=127
    void noteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
        getMidi()->sendNoteOn(channel, note, velocity);
    }

    /**
     * Send a `Note Off` event
     * @param channel 0-15
     * @param note 0-127
     * @param velocity 0-127
     */
    //% block
    //% channel.min=0 channel.max=15 note.min=0 note.max=127 velocity.min=0 velocity.max=127
    void noteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
        getMidi()->sendNoteOff(channel, note, velocity);
    }
}
