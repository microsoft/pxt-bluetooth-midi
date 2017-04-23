bluetooth.onBluetoothConnected(() => {
    basic.showString("C")
})
bluetooth.onBluetoothDisconnected(() => {
    basic.showString("D")
})
bluetooth.startMidiService();
basic.showString("S")
let channel = 1;
input.onButtonPressed(Button.A, () => {
    basic.clearScreen();
    let piano = midi.inputChannel(channel);
    for (let note = 0x0; note < 0x5A; note++) {
        led.toggle(0, 0);
        piano.noteOn(note);
        basic.pause(100);
        piano.noteOff(note);
        basic.pause(100);
    }
})
input.onButtonPressed(Button.B, () => {
    channel += 1;
    basic.showNumber(channel);
})
input.onButtonPressed(Button.AB, () => {
    basic.clearScreen();
    for (let note = 0; note < 127; note++) {
        led.toggle(1, 1);
        midi.playDrum(note);
    }
})
