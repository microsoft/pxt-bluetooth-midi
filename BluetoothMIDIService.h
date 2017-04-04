/* Copyright (c) 2014 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __BLEMIDI_H__
#define __BLEMIDI_H__

#include "ble/BLE.h"

/** 
 * A class to communicate a BLE MIDI device
 */
class BluetoothMIDIService {
public:
    /**
     * Constructor
     */
    BluetoothMIDIService(BLEDevice *device);

    /**
     * Check if a BLE MIDI device is connected
     *
     * @returns true if a midi device is connected
     */
    bool connected();

    /**
     * Attach a callback called when the `Tune Request` event is received
     *
     * @param ptr function pointer
     *   prototype: void onTuneRequest();
     */
    inline void attachTuneRequest(void (*fn)()) {
        onTuneRequest = fn;
    }

    /**
     * Attach a callback called when the `Timing Clock` event is received
     *
     * @param ptr function pointer
     *   prototype: void onTimingClock();
     */
    inline void attachTimingClock(void (*fn)()) {
        onTimingClock = fn;
    }

    /**
     * Attach a callback called when the `Start` event is received
     *
     * @param ptr function pointer
     *   prototype: void onStart();
     */
    inline void attachStart(void (*fn)()) {
        onStart = fn;
    }

    /**
     * Attach a callback called when the `Continue` event is received
     *
     * @param ptr function pointer
     *   prototype: void onContinue();
     */
    inline void attachContinue(void (*fn)()) {
        onContinue = fn;
    }

    /**
     * Attach a callback called when the `Stop` event is received
     *
     * @param ptr function pointer
     *   prototype: void onStop();
     */
    inline void attachStop(void (*fn)()) {
        onStop = fn;
    }

    /**
     * Attach a callback called when the `Active Sensing` event is received
     *
     * @param ptr function pointer
     *   prototype: void onActiveSensing();
     */
    inline void attachActiveSensing(void (*fn)()) {
        onActiveSensing = fn;
    }

    /**
     * Attach a callback called when the `Reset` event is received
     *
     * @param ptr function pointer
     *   prototype: void onReset();
     */
    inline void attachReset(void (*fn)()) {
        onReset = fn;
    }

    /**
     * Attach a callback called when the `Program Change` event is received
     *
     * @param ptr function pointer
     *   prototype: void onProgramChange(uint8_t channel, uint8_t program);
     */
    inline void attachnProgramChange(void (*fn)(uint8_t, uint8_t)) {
        onProgramChange = fn;
    }

    /**
     * Attach a callback called when the `Channel Aftertouch` event is received
     *
     * @param ptr function pointer
     *   prototype: void onChannelAftertouch(uint8_t channel, uint8_t pressure);
     */
    inline void attachChannelAftertouch(void (*fn)(uint8_t, uint8_t)) {
        onChannelAftertouch = fn;
    }

    /**
     * Attach a callback called when the `Time Code Quarter Frame` event is received
     *
     * @param ptr function pointer
     *   prototype: void onTimeCodeQuarterFrame(uint8_t timing);
     */
    inline void attachTimeCodeQuarterFrame(void (*fn)(uint8_t)) {
        onTimeCodeQuarterFrame = fn;
    }

    /**
     * Attach a callback called when the `Song Select` event is received
     *
     * @param ptr function pointer
     *   prototype: void onSongSelect(uint8_t song);
     */
    inline void attachSongSelect(void (*fn)(uint8_t)) {
        onSongSelect = fn;
    }

    /**
     * Attach a callback called when the `Note Off` event is received
     *
     * @param ptr function pointer
     *   prototype: void onNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
     */
    inline void attachNoteOff(void (*fn)(uint8_t, uint8_t, uint8_t)) {
        onNoteOff = fn;
    }

    /**
     * Attach a callback called when the `Note On` event is received
     *
     * @param ptr function pointer
     *   prototype: void onNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
     */
    inline void attachNoteOn(void (*fn)(uint8_t, uint8_t, uint8_t)) {
        onNoteOn = fn;
    }

    /**
     * Attach a callback called when the `Polyphonic Aftertouch` event is received
     *
     * @param ptr function pointer
     *   prototype: void onPolyphonicAftertouch(uint8_t channel, uint8_t note, uint8_t pressure);
     */
    inline void attachPolyphonicAftertouch(void (*fn)(uint8_t, uint8_t, uint8_t)) {
        onPolyphonicAftertouch = fn;
    }

    /**
     * Attach a callback called when the `Control Change` event is received
     *
     * @param ptr function pointer
     *   prototype: void onControlChange(uint8_t channel, uint8_t function, uint8_t value);
     */
    inline void attachControlChange(void (*fn)(uint8_t, uint8_t, uint8_t)) {
        onControlChange = fn;
    }

    /**
     * Attach a callback called when the `Pitch Wheel` event is received
     *
     * @param ptr function pointer
     *   prototype: void onPitchWheel(uint8_t channel, uint16_t amount);
     */
    inline void attachPitchWheel(void (*fn)(uint8_t, uint16_t)) {
        onPitchWheel = fn;
    }

    /**
     * Attach a callback called when the `Song Position Pointer` event is received
     *
     * @param ptr function pointer
     *   prototype: void onSongPositionPointer(uint16_t position);
     */
    inline void attachSongPositionPointer(void (*fn)(uint16_t)) {
        onSongPositionPointer = fn;
    }

    /**
     * Attach a callback called when the `System Exclusive` event is received
     *
     * @param ptr function pointer
     *   prototype: void onSystemExclusive(uint8_t *sysex, uint16_t length, bool hasNextData);
     */
    inline void attachSystemExclusive(void (*fn)(uint8_t *, uint16_t, bool)) {
        onSystemExclusive = fn;
    }

    /**
     * Send a `Tune Request` event
     */
    void sendTuneRequest();

    /**
     * Send a `Timing Clock` event
     */
    void sendTimingClock();

    /**
     * Send a `Start` event
     */
    void sendStart();

    /**
     * Send a `Continue` event
     */
    void sendContinue();

    /**
     * Send a `Stop` event
     */
    void sendStop();

    /**
     * Send a `Active Sensing` event
     */
    void sendActiveSensing();

    /**
     * Send a `Reset` event
     */
    void sendReset();

    /**
     * Send a `Program Change` event
     *
     * @param channel 0-15
     * @param program 0-127
     */
    void sendProgramChange(uint8_t channel, uint8_t program);

    /**
     * Send a `Channel Aftertouch` event
     *
     * @param channel 0-15
     * @param pressure 0-127
     */
    void sendChannelAftertouch(uint8_t channel, uint8_t pressure);

    /**
     * Send a `Time Code Quarter Frame` event
     *
     * @param timing 0-127
     */
    void sendTimeCodeQuarterFrame(uint8_t timing);

    /**
     * Send a `Song Select` event
     *
     * @param song 0-127
     */
    void sendSongSelect(uint8_t song);

    /**
     * Send a `Note Off` event
     *
     * @param channel 0-15
     * @param note 0-127
     * @param velocity 0-127
     */
    void sendNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);

    /**
     * Send a `Note On` event
     *
     * @param channel 0-15
     * @param note 0-127
     * @param velocity 0-127
     */
    void sendNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);

    /**
     * Send a `Polyphonic Aftertouch` event
     *
     * @param channel 0-15
     * @param note 0-127
     * @param pressure 0-127
     */
    void sendPolyphonicAftertouch(uint8_t channel, uint8_t note, uint8_t pressure);

    /**
     * Send a `Control Change` event
     *
     * @param channel 0-15
     * @param function 0-127
     * @param value 0-127
     */
    void sendControlChange(uint8_t channel, uint8_t function, uint8_t value);

    /**
     * Send a `Pitch Wheel` event
     *
     * @param channel 0-15
     * @param amount 0-8192(center)-16383
     */
    void sendPitchWheel(uint8_t channel, uint16_t amount);

    /**
     * Send a `Song Position Pointer` event
     *
     * @param position 0-16383
     */
    void sendSongPositionPointer(uint16_t position);

    /**
     * Send a `System Exclusive` event
     *
     * @param sysex the data starts with `0xf0` and ends with `0xf7`
     * @param length
     */
    void sendSystemExclusive(uint8_t * sysex, uint16_t length);

private:
    uint16_t sysExBufferPos;
    uint8_t sysExBuffer[128];
    
    uint16_t timestamp;

    uint8_t midiEventKind;
    uint8_t midiEventNote;
    uint8_t midiEventVelocity;
    uint8_t midi[20];
    uint8_t rxBuffer[20];

    BLEDevice &ble;
    GattAttribute::Handle_t midiCharacteristicHandle;    
    Timer tick;

    enum MIDI_STATE {
        MIDI_STATE_TIMESTAMP = 0,
        MIDI_STATE_WAIT,
        MIDI_STATE_SIGNAL_2BYTES_2,
        MIDI_STATE_SIGNAL_3BYTES_2,
        MIDI_STATE_SIGNAL_3BYTES_3,
        MIDI_STATE_SIGNAL_SYSEX
    };

    MIDI_STATE midiState;

    void (*onTuneRequest)();
    void (*onTimingClock)();
    void (*onStart)();
    void (*onContinue)();
    void (*onStop)();
    void (*onActiveSensing)();
    void (*onReset)();
    void (*onProgramChange)(uint8_t, uint8_t);
    void (*onChannelAftertouch)(uint8_t, uint8_t);
    void (*onTimeCodeQuarterFrame)(uint8_t);
    void (*onSongSelect)(uint8_t);
    void (*onNoteOff)(uint8_t, uint8_t, uint8_t);
    void (*onNoteOn)(uint8_t, uint8_t, uint8_t);
    void (*onPolyphonicAftertouch)(uint8_t, uint8_t, uint8_t);
    void (*onControlChange)(uint8_t, uint8_t, uint8_t);
    void (*onPitchWheel)(uint8_t, uint16_t);
    void (*onSongPositionPointer)(uint16_t);
    void (*onSystemExclusive)(uint8_t *, uint16_t, bool);

    void sendMidiMessage(uint8_t data0);
    void sendMidiMessage(uint8_t data0, uint8_t data1);
    void sendMidiMessage(uint8_t data0, uint8_t data1, uint8_t data2);

    void onDataWritten(const GattWriteCallbackParams *params);
};

#endif /* __BLEMIDI_H__ */
