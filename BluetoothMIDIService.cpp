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
#include "BluetoothMIDIService.h"


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

BluetoothMIDIService::BluetoothMIDIService(BLEDevice *dev): ble(*dev) {
    timestamp = 0;
`    memset(midiBuffer, 0, sizeof(midiBuffer));
    firstRead = true;

    GattCharacteristic midiCharacteristic(midiCharacteristicUuid, midiBuffer, 0, sizeof(midiBuffer), 
          GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ
        | GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY
        );
    GattCharacteristic *midiChars[] = {&midiCharacteristic};

    midiCharacteristic.requireSecurity(SecurityManager::MICROBIT_BLE_SECURITY_LEVEL);

    GattService midiService(midiServiceUuid, midiChars, sizeof(midiChars) / sizeof(GattCharacteristic *));

    ble.addService(midiService);

    midiCharacteristicHandle = midiCharacteristic.getValueHandle();

    ble.gattServer().onDataRead(this, &BluetoothMIDIService::onDataRead);
    ble.onDisconnection(this, &BluetoothMIDIService::onDisconnection);

    tick.start();
}

void BluetoothMIDIService::onDataRead(const GattReadCallbackParams* params) 
{
    if (params->handle == midiCharacteristicHandle) 
    {
        if (firstRead) {
            // send empty payload upon first connect
            ble.gattServer().notify(midiCharacteristicHandle, (uint8_t *)midiBuffer, 0);
            firstRead = false;
        }
    }
}

void BluetoothMIDIService::onDisconnection(const Gap::DisconnectionCallbackParams_t* params) {
    // clear read bit
    firstRead = true;
}

bool BluetoothMIDIService::connected() {
    return ble.getGapState().connected;
}

void BluetoothMIDIService::sendMidiMessage(uint8_t data0) {
    if (connected()) {
        unsigned int ticks = tick.read_ms() & 0x1fff;
        midiBuffer[0] = 0x80 | ((ticks >> 7) & 0x3f);
        midiBuffer[1] = 0x80 | (ticks & 0x7f);
        midiBuffer[2] = data0;
        
        ble.gattServer().notify(midiCharacteristicHandle, (uint8_t *)midiBuffer, 3);
    }
}

void BluetoothMIDIService::sendMidiMessage(uint8_t data0, uint8_t data1) {
    if (connected()) {
        unsigned int ticks = tick.read_ms() & 0x1fff;
        midiBuffer[0] = 0x80 | ((ticks >> 7) & 0x3f);
        midiBuffer[1] = 0x80 | (ticks & 0x7f);
        midiBuffer[2] = data0;
        midiBuffer[3] = data1;
        
        ble.gattServer().notify(midiCharacteristicHandle, (uint8_t *)midiBuffer, 4);
    }
}

void BluetoothMIDIService::sendMidiMessage(uint8_t data0, uint8_t data1, uint8_t data2) {
    if (connected()) {
        unsigned int ticks = tick.read_ms() & 0x1fff;
        midiBuffer[0] = 0x80 | ((ticks >> 7) & 0x3f);
        midiBuffer[1] = 0x80 | (ticks & 0x7f);
        midiBuffer[2] = data0;
        midiBuffer[3] = data1;
        midiBuffer[4] = data2;
        
        ble.gattServer().notify(midiCharacteristicHandle, (uint8_t *)midiBuffer, 5);
    }
}
