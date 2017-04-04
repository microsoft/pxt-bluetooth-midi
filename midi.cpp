#include "pxt.h"
#include "BluetoothMIDIService.h"
using namespace pxt;
/**
* A set of functions to send MIDI commands over Bluetooth
*/
//% color=#0082FB weight=96 icon="\uf294"
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

    /**
     * Send a `Tune Request` event
     */
     //% block
    void tuneRequest() {
        getMidi()->sendTuneRequest();   
    }

    /**
     * Send a `Timing Clock` event
     */
     //% block
    void timingClock() {
        getMidi()->sendTimingClock();        
    }

    /**
     * Send a `Start` event
     */
     //% block
    void start() {
        getMidi()->sendStart();
    }

    /**
     * Send a `Continue` event
     */
     //% block
    void cont() {
        getMidi()->sendContinue();        
    }

    /**
     * Send a `Stop` event
     */
     //% block
    void sendStop() {
        getMidi()->sendReset();        
    }

    /**
     * Send a `Active Sensing` event
     */
     //% block
    void sendActiveSensing() {
        getMidi()->sendReset();
    }

    /**
     * Send a `Reset` event
     */
     //% block
    void sendReset() {
        getMidi()->sendReset();
    }

    /**
     * Send a `Program Change` event
     *
     * @param channel 0-15
     * @param program 0-127
     */
     //% block channel.min=0 channel.max=15 program.min=0 program.max=127
    void programChange(uint8_t channel, uint8_t program) {
        getMidi()->sendProgramChange(channel, program);
    }

    /**
     * Send a `Channel Aftertouch` event
     *
     * @param channel 0-15
     * @param pressure 0-127
     */
    //% block channel.min=0 channel.max=15 channel.pressure=0 channel.pressure=127
    void channelAftertouch(uint8_t channel, uint8_t pressure) {
        getMidi()->sendChannelAftertouch(channel, pressure);
    }

    /**
     * Send a `Time Code Quarter Frame` event
     *
     * @param timing 0-127
     */
     //% block timing.min=0 timing.max=127
    void timeCodeQuarterFrame(uint8_t timing) {
        getMidi()->sendTimeCodeQuarterFrame(timing);
    }

    /**
     * Send a `Song Select` event
     *
     * @param song 0-127
     */
    //% block song.min=0 song.max=127
    void songSelect(uint8_t song) {
        getMidi()->sendSongSelect(song);
    }

    /**
     * Send a `Polyphonic Aftertouch` event
     *
     * @param channel 0-15
     * @param note 0-127
     * @param pressure 0-127
     */
     //% block channel.min=0 channel.max=15 note.min=0 note.max=127 pressure.min=0 pressure.max=127
    void polyphonicAftertouch(uint8_t channel, uint8_t note, uint8_t pressure) {
        getMidi()->sendPolyphonicAftertouch(channel, note, pressure);
    }

    /**
     * Send a `Control Change` event
     *
     * @param channel 0-15
     * @param func 0-127
     * @param value 0-127
     */
    //% block channel.min=0 channel.max=15 func.min=0 func.max=127 value.min=0 value.max=127
    void controlChange(uint8_t channel, uint8_t func, uint8_t value) {
        getMidi()->sendControlChange(channel, func, value);
    }

    /**
     * Send a `Pitch Wheel` event
     *
     * @param channel 0-15
     * @param amount 0-8192(center)-16383, eg: 8192
     */
     //% block channel.min=0 channel.max=15 amount.min=0 amount.max=16383
    void pitchWheel(uint8_t channel, uint16_t amount) {
        getMidi()->sendPitchWheel(channel, amount);
    }

    /**
     * Send a `Song Position Pointer` event
     *
     * @param position 0-16383
     */
     //% block position.min=0 position.max=16383
    void songPositionPointer(uint16_t position) {
        getMidi()->sendSongPositionPointer(position);
    }
}
