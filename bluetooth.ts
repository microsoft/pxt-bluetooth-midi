namespace bluetooth {
    /**
     * Starts the MIDI service over Bluetooth and registers it as the MIDI transport.
     */
    //% blockId=bluetooth_start_midi block="bluetooth start midi service"
    //% part=bluetooth
    //% blockHidden=1 deprecated=true
    export function startMidiService() {
        function send(buffer: Buffer) {
            bluetooth.midiSendMessage(buffer);
        }
        midi.setTransport(send);
        bluetooth.midiSendMessage(pins.createBuffer(0)); // does nothing but starts service lazily
    }

    /**
     * Sends a MIDI message
     */
    //% shim=bluetooth::midiSendMessage
    //% advanced=true
    export function midiSendMessage(data: Buffer) {
        return;
    }

}
// automatically start midi service
bluetooth.startMidiService();
