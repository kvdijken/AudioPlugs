# AudioPlugs

This library lets the user create switches in the audio path. These switches can be switched on and off at runtime.

It includes two classes: AudioInputPlugs and AudioOutputPlugs.

AudioInputPlugs contains four inputs and one output. One input can be switched through to the output. Or neither input can be used, and hence there will be no output. The switching can be done with the plug() method.

AudioOutputPlugs contains one input and four outputs. Any of the four outputs can receive the data from the input, also simultaneously. The switching can be done with the plug() and unplug() methods. Plug for switching on, and unplug for switching off.
