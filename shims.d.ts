// Auto-generated. Do not edit.


    /**
     * A set of functions to send MIDI commands over Bluetooth
     */

declare namespace midi {

    /**
     * Send a `Note On` event
     * @param channel 0-15
     * @param note 0-127
     * @param velocity 0-127
     */
    //% block
    //% channel.min=0 channel.max=15 note.min=0 note.max=127 velocity.min=0 velocity.max=127 shim=midi::sendNoteOn
    function sendNoteOn(channel: uint8, note: uint8, velocity: uint8): void;

    /**
     * Send a `Note Off` event
     * @param channel 0-15
     * @param note 0-127
     * @param velocity 0-127
     */
    //% block
    //% channel.min=0 channel.max=15 note.min=0 note.max=127 velocity.min=0 velocity.max=127 shim=midi::sendNoteOff
    function sendNoteOff(channel: uint8, note: uint8, velocity: uint8): void;
}

// Auto-generated. Do not edit. Really.
