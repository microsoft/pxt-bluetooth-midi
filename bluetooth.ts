namespace bluetooth {
    /**
     * Starts the MIDI service over Bluetooth and registers it as the MIDI transport.
     */
    //% blockId=bluetooth_start_midi block="bluetooth start midi service"
    //% part=bluetooth
    export function startMidiService() {
        function send(buffer: Buffer) {
            bluetooth.midiSendMessage(buffer);
        }
        midi.setInputTransport(send);
        bluetooth.midiSendMessage(pins.createBuffer(0));
    }
}