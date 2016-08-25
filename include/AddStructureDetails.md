### Transducer

A critical component of this system is the ultrasound transducer. A typical ultrasound imaging system uses a wide variety of transducers optimized for specific diagnostic applications, but in our case, we'll limit the costs.
 
### High-Voltage Transmitters ([see the module](/tobo/))

A digital transmit beamformer typically generates the necessary digital transmit signals with the proper timing and phase to produce a focused transmit signal. High-voltage pulsers quickly switch the transducer element to the appropriate programmable high-voltage supplies to generate the transmit waveform. To generate a simple bipolar transmit waveform, a transmit pulser alternately connects the element to a positive and negative transmit supply voltage controlled by the digital beamformer. More complex realizations allow connections to multiple supplies and ground in order to generate more complex multilevel waveforms with better characteristics.


### TGC + LNA = Variable-Gain Amplifier (VGA) ([see the module](/goblin/))

The LNA in the receiver must have excellent noise performance and sufficient gain. In a properly designed receiver the LNA will generally determine the noise performance of the full receiver. 

The VGA, sometimes called a time gain control (TGC) amplifier, provides the receiver with sufficient dynamic range over the full receive cycle. Ultrasound signals propagate in the body at approximately 1540 meters per second and attenuate at a rate of about 1.4dB/cm-MHz roundtrip. Immediately after an acoustic transmit pulse, the received "echo" signal at the LNA's input can be as large as 0.5VP-P. This signal quickly decays to the thermal noise floor of the transducer element. The dynamic range required to receive this signal is approximately 100dB to 110dB, and is well beyond the range of a realistic ADC. As a result, a VGA is used to map this signal into the ADC. A VGA with approximately 30dB to 40dB of gain is necessary to map the received signal into a typical 12-bit ADC used in this application. The gain is ramped as a function of time (i.e., "time gain control") to accomplish this dynamic range mapping.


### Anti-Alias Filter (AAF) and ADC ([see the module](/toadkiller/))

The AAF in the receive chain keeps high-frequency noise and extraneous signals that are beyond the normal maximum imaging frequencies from being aliased back to baseband by the ADC. Many times an adjustable AAF is provided in the design. To avoid aliasing and to preserve the time-domain response of the signal, the filter itself needs to attenuate signals beyond the first Nyquist zone. For this reason Butterworth or higher-order Bessel filters are used.

The ADC used in this application is typically a 12-bit device running from 40Msps to 60Msps. This converter provides the necessary instantaneous dynamic range at acceptable cost and power levels. In a properly designed receiver, this ADC should limit the instantaneous SNR of the receiver. As previously mentioned, however, limitations in the poor-performing VGAs many times limit receiver SNR performance




