bluetooth.onBluetoothConnected(() => {
    basic.showString("C")
})
bluetooth.onBluetoothDisconnected(() => {
    basic.showString("D")
})
bluetooth.startMidiService();
basic.showString("S")
input.onButtonPressed(Button.A, () => {
    basic.clearScreen();
    let piano = midi.inputChannel(0);
    for (let note = 0x0; note < 0x5A; note++) {
        led.toggle(0, 0);
        piano.noteOn(note);
        basic.pause(100);
        piano.noteOff(note);
        basic.pause(100);
    }
})