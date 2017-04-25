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
    led.toggle(0, 0);
    midi.playTone(Note.A, music.beat())
    midi.playTone(Note.B, music.beat())
    midi.playTone(Note.C, music.beat())
    midi.playTone(Note.D, music.beat())
    midi.playTone(Note.E, music.beat())
})
input.onButtonPressed(Button.B, () => {
    basic.clearScreen();
    for (let note = 0; note < 127; note++) {
        led.toggle(1, 1);
        midi.playDrum(note);
        basic.pause(100);
    }
})
