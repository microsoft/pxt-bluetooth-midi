# bluetooth-midi

A [Bluetooth low enery MIDI](https://www.midi.org/specifications/item/bluetooth-le-midi) package for the @boardname@.

### ~hint
![](/static/bluetooth/Bluetooth_SIG.png)

For another device like a smartphone to use any of the Bluetooth "services" which the @boardname@ has, it must first be [paired with the @boardname@](/reference/bluetooth/bluetooth-pairing). Once paired, the other device may connect to the @boardname@ and exchange data relating to many of the @boardname@'s features.

### ~

## Usage

This package allows the @boardname@ to act as a MIDI peripherical, like a piano. It requires to connect to a BLE MIDI device to receive the commands and play them.

Place a ``||bluetooth start midi service||`` block in your program to enable MDI over Bluetooth low energy.

```blocks
bluetooth.startMidiService();
```

This library uses the [MIDI package](/pkg/microsoft/pxt-midi). 
Please refer to that project documentation for further details.

## Apps

Any app that supports a MIDI keyboard or instrument should work.

* iPhone/iPad: [Apple GarageBand](https://itunes.apple.com/us/app/garageband/id408709785?mt=8)

## Supported targets

* for PXT/microbit

(The metadata above is needed for package search.)

## License

MIT

## Code of Conduct

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

```package
midi=microsoft/pxt-midi
bluetooth-midi=microsoft/pxt-bluetooth-midi
```