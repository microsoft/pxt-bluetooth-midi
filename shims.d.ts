// Auto-generated. Do not edit.


    /**
     * A set of functions to send MIDI commands over Bluetooth
     */
    //% color=#0082FB weight=96 icon="\uf294"
declare namespace midi {

    /**
     * Starts the MIDI service
     */
    //% block shim=midi::startBluetoothService
    function startBluetoothService(): void;

    /**
     * Send a `Note On` event
     * @param channel 0-15
     * @param note 0-127
     * @param velocity 0-127
     */
    //% block
    //% channel.min=0 channel.max=15 note.min=0 note.max=127 velocity.min=0 velocity.max=127 shim=midi::noteOn
    function noteOn(channel: uint8, note: uint8, velocity: uint8): void;

    /**
     * Send a `Note Off` event
     * @param channel 0-15
     * @param note 0-127
     * @param velocity 0-127
     */
    //% block
    //% channel.min=0 channel.max=15 note.min=0 note.max=127 velocity.min=0 velocity.max=127 shim=midi::noteOff
    function noteOff(channel: uint8, note: uint8, velocity: uint8): void;

    /**
     * Send a `Tune Request` event
     */
    //% block shim=midi::tuneRequest
    function tuneRequest(): void;

    /**
     * Send a `Timing Clock` event
     */
    //% block shim=midi::timingClock
    function timingClock(): void;

    /**
     * Send a `Start` event
     */
    //% block shim=midi::start
    function start(): void;

    /**
     * Send a `Continue` event
     */
    //% block shim=midi::cont
    function cont(): void;

    /**
     * Send a `Stop` event
     */
    //% block shim=midi::sendStop
    function sendStop(): void;

    /**
     * Send a `Active Sensing` event
     */
    //% block shim=midi::sendActiveSensing
    function sendActiveSensing(): void;

    /**
     * Send a `Reset` event
     */
    //% block shim=midi::sendReset
    function sendReset(): void;

    /**
     * Send a `Program Change` event
     *
     * @param channel 0-15
     * @param program 0-127
     */
    //% block channel.min=0 channel.max=15 program.min=0 program.max=127 shim=midi::programChange
    function programChange(channel: uint8, program: uint8): void;

    /**
     * Send a `Channel Aftertouch` event
     *
     * @param channel 0-15
     * @param pressure 0-127
     */
    //% block channel.min=0 channel.max=15 channel.pressure=0 channel.pressure=127 shim=midi::channelAftertouch
    function channelAftertouch(channel: uint8, pressure: uint8): void;

    /**
     * Send a `Time Code Quarter Frame` event
     *
     * @param timing 0-127
     */
    //% block timing.min=0 timing.max=127 shim=midi::timeCodeQuarterFrame
    function timeCodeQuarterFrame(timing: uint8): void;

    /**
     * Send a `Song Select` event
     *
     * @param song 0-127
     */
    //% block song.min=0 song.max=127 shim=midi::songSelect
    function songSelect(song: uint8): void;

    /**
     * Send a `Polyphonic Aftertouch` event
     *
     * @param channel 0-15
     * @param note 0-127
     * @param pressure 0-127
     */
    //% block channel.min=0 channel.max=15 note.min=0 note.max=127 pressure.min=0 pressure.max=127 shim=midi::polyphonicAftertouch
    function polyphonicAftertouch(channel: uint8, note: uint8, pressure: uint8): void;

    /**
     * Send a `Control Change` event
     *
     * @param channel 0-15
     * @param func 0-127
     * @param value 0-127
     */
    //% block channel.min=0 channel.max=15 func.min=0 func.max=127 value.min=0 value.max=127 shim=midi::controlChange
    function controlChange(channel: uint8, func: uint8, value: uint8): void;

    /**
     * Send a `Pitch Wheel` event
     *
     * @param channel 0-15
     * @param amount 0-8192(center)-16383, eg: 8192
     */
    //% block channel.min=0 channel.max=15 amount.min=0 amount.max=16383 shim=midi::pitchWheel
    function pitchWheel(channel: uint8, amount: uint16): void;

    /**
     * Send a `Song Position Pointer` event
     *
     * @param position 0-16383
     */
    //% block position.min=0 position.max=16383 shim=midi::songPositionPointer
    function songPositionPointer(position: uint16): void;
}

// Auto-generated. Do not edit. Really.
