# bluetooth-midi

A Bluetooth low enery MIDI package for the @boardname@.

### ~hint
![](/static/bluetooth/Bluetooth_SIG.png)

For another device like a smartphone to use any of the Bluetooth "services" which the @boardname@ has, it must first be [paired with the @boardname@](/reference/bluetooth/bluetooth-pairing). Once paired, the other device may connect to the @boardname@ and exchange data relating to many of the @boardname@'s features.

### ~

## Usage

This package allows the @boardname@ to act as a MIDI peripherical, like a piano. It requires to connect to a BLE MIDI device to receive the commands and play them. On iPhone/iPad, try [KORG Module Le](https://itunes.apple.com/us/app/korg-module-le/id1048875111) to play the piano with your @boardname@!

### Example

This program plays all the notes from ``F#-0`` to ``F#-5``.

```
midi.startBluetoothService();
input.onButtonPressed(Button.A, () => {
    // blink the screen
    led.toggle(0, 0);
    // play note
    midi.noteOn(0x90, 400, 0x45);
    //Note on channel 1 (0x90), some note value (note), middle velocity (0x45):
    basic.pause(150);
    //Note on channel 1 (0x90), some note value (note), silent velocity (0x00):
    midi.noteOn(0x90, 400, 0x00);
    basic.pause(150);
})
```

## Supported targets

* for PXT/microbit
* for PXT/calliope

(The metadata above is needed for package search.)

## License

MIT

## Code of Conduct

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.
