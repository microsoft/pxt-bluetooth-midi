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

#include "MicroBit.h"
#include "pxt.h"
#include "BLEMIDI.h"


    // MIDI characteristic
const uint8_t midiCharacteristicUuid[] = {
        0x77, 0x72, 0xe5, 0xdb, 0x38, 0x68, 0x41, 0x12, 
        0xa1, 0xa9, 0xf2, 0x66, 0x9d, 0x10, 0x6b, 0xf3
};

    // MIDI service
const uint8_t midiServiceUuid[] = {
        0x03, 0xb8, 0x0e, 0x5a, 0xed, 0xe8, 0x4b, 0x33, 
        0xa7, 0x51, 0x6c, 0xe3, 0x4e, 0xc4, 0xc7, 0x00
};

void BLEMIDI::onDataWritten(const GattWriteCallbackParams *params) {
    uBit.serial.send("midi:onDataWritten\n");
    uint16_t length;

    ble.readCharacteristicValue(midiCharacteristicHandle, rxBuffer, &length);
    if (length > 1) {
        // parse BLE message
        uint8_t header = rxBuffer[0];
        for (int i = 1; i < length; i++) {
            uint8_t midiEvent = rxBuffer[i];

            if (midiState == MIDI_STATE_TIMESTAMP) {
                if ((midiEvent & 0x80) == 0) {
                    // running status
                    midiState = MIDI_STATE_WAIT;
                }

                if (midiEvent == 0xf7) {
                    // maybe error
                    midiState = MIDI_STATE_TIMESTAMP;
                    continue;
                }
            }
            if (midiState == MIDI_STATE_TIMESTAMP) {
                timestamp = ((header & 0x3f) << 7) | (midiEvent & 0x7f);
                midiState = MIDI_STATE_WAIT;
            } else if (midiState == MIDI_STATE_WAIT) {
                switch (midiEvent & 0xf0) {
                    case 0xf0: {
                        switch (midiEvent) {
                            case 0xf0:
                                sysExBuffer[sysExBufferPos++] = midiEvent;
                                midiState = MIDI_STATE_SIGNAL_SYSEX;
                                break;

                            case 0xf1:
                            case 0xf3:
                                // 0xf1 MIDI Time Code Quarter Frame. : 2bytes
                                // 0xf3 Song Select. : 2bytes
                                midiEventKind = midiEvent;
                                midiState = MIDI_STATE_SIGNAL_2BYTES_2;
                                break;

                            case 0xf2:
                                // 0xf2 Song Position Pointer. : 3bytes
                                midiEventKind = midiEvent;
                                midiState = MIDI_STATE_SIGNAL_3BYTES_2;
                                break;

                            case 0xf6:
                                // 0xf6 Tune Request : 1byte
                                onTuneRequest();
                                midiState = MIDI_STATE_TIMESTAMP;
                                break;
                            case 0xf8:
                                // 0xf8 Timing Clock : 1byte
                                onTimingClock();
                                midiState = MIDI_STATE_TIMESTAMP;
                                break;
                            case 0xfa:
                                // 0xfa Start : 1byte
                                onStart();
                                midiState = MIDI_STATE_TIMESTAMP;
                                break;
                            case 0xfb:
                                // 0xfb Continue : 1byte
                                onContinue();
                                midiState = MIDI_STATE_TIMESTAMP;
                                break;
                            case 0xfc:
                                // 0xfc Stop : 1byte
                                onStop();
                                midiState = MIDI_STATE_TIMESTAMP;
                                break;
                            case 0xfe:
                                // 0xfe Active Sensing : 1byte
                                onActiveSensing();
                                midiState = MIDI_STATE_TIMESTAMP;
                                break;
                            case 0xff:
                                // 0xff Reset : 1byte
                                onReset();
                                midiState = MIDI_STATE_TIMESTAMP;
                                break;

                            default:
                                break;
                        }
                    }
                    break;
                    case 0x80:
                    case 0x90:
                    case 0xa0:
                    case 0xb0:
                    case 0xe0:
                        // 3bytes pattern
                        midiEventKind = midiEvent;
                        midiState = MIDI_STATE_SIGNAL_3BYTES_2;
                        break;
                    case 0xc0: // program change
                    case 0xd0: // channel after-touch
                        // 2bytes pattern
                        midiEventKind = midiEvent;
                        midiState = MIDI_STATE_SIGNAL_2BYTES_2;
                        break;
                    default:
                        // 0x00 - 0x70: running status
                        if ((midiEventKind & 0xf0) != 0xf0) {
                            // previous event kind is multi-bytes pattern
                            midiEventNote = midiEvent;
                            midiState = MIDI_STATE_SIGNAL_3BYTES_3;
                        }
                        break;
                }
            } else if (midiState == MIDI_STATE_SIGNAL_2BYTES_2) {
                switch (midiEventKind & 0xf0) {
                    // 2bytes pattern
                    case 0xc0: // program change
                        midiEventNote = midiEvent;
                        onProgramChange(midiEventKind & 0xf, midiEventNote);
                        midiState = MIDI_STATE_TIMESTAMP;
                        break;
                    case 0xd0: // channel after-touch
                        midiEventNote = midiEvent;
                        onChannelAftertouch(midiEventKind & 0xf, midiEventNote);
                        midiState = MIDI_STATE_TIMESTAMP;
                        break;
                    case 0xf0: {
                        switch (midiEventKind) {
                            case 0xf1:
                                // 0xf1 MIDI Time Code Quarter Frame. : 2bytes
                                midiEventNote = midiEvent;
                                onTimeCodeQuarterFrame(midiEventNote);
                                midiState = MIDI_STATE_TIMESTAMP;
                                break;
                            case 0xf3:
                                // 0xf3 Song Select. : 2bytes
                                midiEventNote = midiEvent;
                                onSongSelect(midiEventNote);
                                midiState = MIDI_STATE_TIMESTAMP;
                                break;
                            default:
                                // illegal state
                                midiState = MIDI_STATE_TIMESTAMP;
                                break;
                        }
                    }
                        break;
                    default:
                        // illegal state
                        midiState = MIDI_STATE_TIMESTAMP;
                        break;
                }
            } else if (midiState == MIDI_STATE_SIGNAL_3BYTES_2) {
                switch (midiEventKind & 0xf0) {
                    case 0x80:
                    case 0x90:
                    case 0xa0:
                    case 0xb0:
                    case 0xe0:
                    case 0xf0:
                        // 3bytes pattern
                        midiEventNote = midiEvent;
                        midiState = MIDI_STATE_SIGNAL_3BYTES_3;
                        break;
                    default:
                        // illegal state
                        midiState = MIDI_STATE_TIMESTAMP;
                        break;
                }
            } else if (midiState == MIDI_STATE_SIGNAL_3BYTES_3) {
                switch (midiEventKind & 0xf0) {
                    // 3bytes pattern
                    case 0x80: // note off
                        midiEventVelocity = midiEvent;
                        onNoteOff(midiEventKind & 0xf, midiEventNote, midiEventVelocity);
                        midiState = MIDI_STATE_TIMESTAMP;
                        break;
                    case 0x90: // note on
                        midiEventVelocity = midiEvent;
                        if (midiEventVelocity == 0) {
                            onNoteOff(midiEventKind & 0xf, midiEventNote, midiEventVelocity);
                        } else {
                            onNoteOn(midiEventKind & 0xf, midiEventNote, midiEventVelocity);
                        }
                        midiState = MIDI_STATE_TIMESTAMP;
                        break;
                    case 0xa0: // control polyphonic key pressure
                        midiEventVelocity = midiEvent;
                        onPolyphonicAftertouch(midiEventKind & 0xf, midiEventNote, midiEventVelocity);
                        midiState = MIDI_STATE_TIMESTAMP;
                        break;
                    case 0xb0: // control change
                        midiEventVelocity = midiEvent;
                        onControlChange(midiEventKind & 0xf, midiEventNote, midiEventVelocity);
                        midiState = MIDI_STATE_TIMESTAMP;
                        break;
                    case 0xe0: // pitch bend
                        midiEventVelocity = midiEvent;
                        onPitchWheel(midiEventKind & 0xf, (midiEventNote & 0x7f) | ((midiEventVelocity & 0x7f) << 7));
                        midiState = MIDI_STATE_TIMESTAMP;
                        break;
                    case 0xf0: // Song Position Pointer.
                        midiEventVelocity = midiEvent;
                        onSongPositionPointer((midiEventNote & 0x7f) | ((midiEventVelocity & 0x7f) << 7));
                        midiState = MIDI_STATE_TIMESTAMP;
                        break;
                    default:
                        // illegal state
                        midiState = MIDI_STATE_TIMESTAMP;
                        break;
                }
            } else if (midiState == MIDI_STATE_SIGNAL_SYSEX) {
                if (midiEvent == 0xf7) {
                    // the end of message
                    // last written uint8_t is for timestamp
                    if (sysExBufferPos > 0) {
                        sysExBuffer[sysExBufferPos - 1] = midiEvent;
                        onSystemExclusive(sysExBuffer, sysExBufferPos, false);
                    }

                    sysExBufferPos = 0;
                    midiState = MIDI_STATE_TIMESTAMP;
                } else {
                    if (sysExBufferPos == 128) {
                        onSystemExclusive(sysExBuffer, sysExBufferPos, true);
                        sysExBufferPos = 0;
                    }
                    sysExBuffer[sysExBufferPos++] = midiEvent;
                }
            }
        }
    }
}

BLEMIDI::BLEMIDI(BLEDevice *dev): ble(*dev) {
    sysExBufferPos = 0;

    timestamp = 0;    
    midiEventKind = 0;
    midiEventNote = 0;
    midiEventVelocity = 0;

    memset(midi, 0, sizeof(midi));
    memset(sysExBuffer, 0, sizeof(sysExBuffer));
    memset(rxBuffer, 0, sizeof(rxBuffer));

    GattCharacteristic midiCharacteristic(midiCharacteristicUuid, midi, 0, sizeof(midi), 
        GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE 
        | GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE_WITHOUT_RESPONSE 
        | GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ 
        | GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY
        );
    GattCharacteristic *midiChars[] = {&midiCharacteristic};

    midiCharacteristic.requireSecurity(SecurityManager::MICROBIT_BLE_SECURITY_LEVEL);

    GattService midiService(midiServiceUuid, midiChars, sizeof(midiChars) / sizeof(GattCharacteristic *));

    ble.addService(midiService);

    midiCharacteristicHandle = midiCharacteristic.getValueHandle();

    ble.onDataWritten(this, &BLEMIDI::onDataWritten);
    tick.start();
}

bool BLEMIDI::connected() {
    return ble.getGapState().connected;
}

void BLEMIDI::sendMidiMessage(uint8_t data0) {
    if (connected()) {
        unsigned int ticks = tick.read_ms() & 0x1fff;
        midi[0] = 0x80 | ((ticks >> 7) & 0x3f);
        midi[1] = 0x80 | (ticks & 0x7f);
        midi[2] = data0;
        
        ble.updateCharacteristicValue(midiCharacteristicHandle, midi, 3);
    }
}

void BLEMIDI::sendMidiMessage(uint8_t data0, uint8_t data1) {
    if (connected()) {
        unsigned int ticks = tick.read_ms() & 0x1fff;
        midi[0] = 0x80 | ((ticks >> 7) & 0x3f);
        midi[1] = 0x80 | (ticks & 0x7f);
        midi[2] = data0;
        midi[3] = data1;
        
        ble.updateCharacteristicValue(midiCharacteristicHandle, midi, 4);
    }
}

void BLEMIDI::sendMidiMessage(uint8_t data0, uint8_t data1, uint8_t data2) {
    if (connected()) {
        uBit.serial.send("midi:sendmsg\n");
        unsigned int ticks = tick.read_ms() & 0x1fff;
        midi[0] = 0x80 | ((ticks >> 7) & 0x3f);
        midi[1] = 0x80 | (ticks & 0x7f);
        midi[2] = data0;
        midi[3] = data1;
        midi[4] = data2;
        
        ble.updateCharacteristicValue(midiCharacteristicHandle, midi, 5);
    }
}

void BLEMIDI::sendTuneRequest() {
    sendMidiMessage(0xf6);
}
void BLEMIDI::sendTimingClock() {
    sendMidiMessage(0xf8);
}
void BLEMIDI::sendStart() {
    sendMidiMessage(0xfa);
}
void BLEMIDI::sendContinue() {
    sendMidiMessage(0xfb);
}
void BLEMIDI::sendStop() {
    sendMidiMessage(0xfc);
}
void BLEMIDI::sendActiveSensing() {
    sendMidiMessage(0xfe);
}
void BLEMIDI::sendReset() {
    sendMidiMessage(0xff);
}
void BLEMIDI::sendProgramChange(uint8_t channel, uint8_t program) {
    sendMidiMessage(0xc0 | (channel & 0xf), program);
}
void BLEMIDI::sendChannelAftertouch(uint8_t channel, uint8_t pressure) {
    sendMidiMessage(0xd0 | (channel & 0xf), pressure);
}
void BLEMIDI::sendTimeCodeQuarterFrame(uint8_t timing) {
    sendMidiMessage(0xf1, timing & 0x7f);
}
void BLEMIDI::sendSongSelect(uint8_t song) {
    sendMidiMessage(0xf3, song & 0x7f);
}
void BLEMIDI::sendNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
    sendMidiMessage(0x80 | (channel & 0xf), note, velocity);
}
void BLEMIDI::sendNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
    sendMidiMessage(0x90 | (channel & 0xf), note, velocity);
}
void BLEMIDI::sendPolyphonicAftertouch(uint8_t channel, uint8_t note, uint8_t pressure) {
    sendMidiMessage(0xa0 | (channel & 0xf), note, pressure);
}
void BLEMIDI::sendControlChange(uint8_t channel, uint8_t function, uint8_t value) {
    sendMidiMessage(0xb0 | (channel & 0xf), function, value);
}
void BLEMIDI::sendPitchWheel(uint8_t channel, uint16_t amount) {
    sendMidiMessage(0xe0 | (channel & 0xf), amount & 0x7f, (amount >> 7) & 0x7f);
}
void BLEMIDI::sendSongPositionPointer(uint16_t position) {
    sendMidiMessage(0xf2, position & 0x7f, (position >> 7) & 0x7f);
}
void BLEMIDI::sendSystemExclusive(uint8_t * sysex, uint16_t length) {
    uBit.serial.send("midi:sendsystem\n");
    if (connected()) {
        uint8_t position = 0;

        // header
        uint16_t ticks = tick.read_ms() & 0x1fff;
        midi[position++] = 0x80 | ((ticks >> 7) & 0x3f);
        midi[position++] = 0x80 | (ticks & 0x7f);

        for (int i = 0; i < length; i++) {
            if (i == length - 1) {
                // modify last byte
                midi[position++] = 0x80 | (ticks & 0x7f);

                if (position == 20) {
                    ble.updateCharacteristicValue(midiCharacteristicHandle, midi, 20);

                    position = 0;
                    // header
                    midi[position++] = 0x80 | (ticks >> 7) & 0x3f;
                }
            }
            midi[position++] = sysex[i];
            if (position == 20) {
                ble.updateCharacteristicValue(midiCharacteristicHandle, midi, 20);

                position = 0;
                // header
                midi[position++] = 0x80 | (ticks >> 7) & 0x3f;
            }

            ticks = tick.read_ms() & 0x1fff;
        }

        if (position > 0) {
            // send remains
            ble.updateCharacteristicValue(midiCharacteristicHandle, midi, position);
        }
    }
}
