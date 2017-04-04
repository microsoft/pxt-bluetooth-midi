// https://www.arduino.cc/en/tutorial/midi
// play notes from F#-0 (0x1E) to F#-5 (0x5A):
for (let note = 0x1E; note < 0x5A; note++) {
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    midi.noteOn(0x90, note, 0x45);
    basic.pause(100);
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    midi.noteOn(0x90, note, 0x00);
    basic.pause(100);
}