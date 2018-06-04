#include "pxt.h"
#include "BluetoothMIDIService.h"
using namespace pxt;
/**
* A set of functions to send MIDI commands over Bluetooth
*/
namespace bluetooth {
    BluetoothMIDIService* pMidi = NULL;
    BluetoothMIDIService* getMidi() 
    {
        if (NULL == pMidi)
            pMidi = new BluetoothMIDIService(uBit.ble);
        return pMidi;
    }

    //%
    void midiSendMessage(Buffer data) {
        BluetoothMIDIService* pMidi = getMidi();            
        auto buf = data->payload;
        switch(data->length) {
            case 1: 
                pMidi->sendMidiMessage(buf[0]);
                break;
            case 2:
                pMidi->sendMidiMessage(buf[0], buf[1]);
                break;
            case 3:
                pMidi->sendMidiMessage(buf[0], buf[1], buf[2]);
                break;
        }
    }
}
