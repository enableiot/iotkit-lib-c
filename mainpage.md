To start working with the iotkik library, you will need to:

1. Install it.
2. Run a sample program (optional).
3. Learn more (optional).

<B> Install it </B>

No installation is required on the device (support for other platforms coming soon).

<B> Run a sample program </B>

On the device, iotkit-comm sample programs can be found in /usr/share/iotkit-comm/examples/c. Here is how you run the
distributed thermostat sample application included in the iotkit-comm sources:

$ cd /usr/share/iotkit-comm/examples/c <BR>
$ ./sensor <BR>
Then, in another terminal:

$ cd /usr/share/iotkit-comm/examples/c <BR>
$ ./thermostat <BR>
In the thermostat terminal, you will see output

You can run multiple instances of './sensor'; the thermostat will find those sensors and include their temperature data in the mean.
