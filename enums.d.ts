// Auto-generated. Do not edit.


    /**
     * Attach a callback called when the `System Exclusive` event is received
     *
     * @param ptr function pointer
     *   prototype: void onSystemExclusive(uint8_t *sysex, uint16_t length, bool hasNextData);
     */

    declare enum MIDI_STATE {
    MIDI_STATE_TIMESTAMP = 0,
    MIDI_STATE_WAIT = 1,
    MIDI_STATE_SIGNAL_2BYTES_2 = 2,
    MIDI_STATE_SIGNAL_3BYTES_2 = 3,
    MIDI_STATE_SIGNAL_3BYTES_3 = 4,
    MIDI_STATE_SIGNAL_SYSEX = 5,
    }
declare namespace bluetooth {
}

// Auto-generated. Do not edit. Really.
