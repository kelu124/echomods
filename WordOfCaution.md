## Some words of caution

* __Disclaimer #0__: __This is not a medical ultrasound scanner__! It's a development kit that can be used for pedagogical and academic purposes - possible immediate use as a non-destructive testing (NDT) tool, for example in metallurgical crack analysis. As in all electronics, be [careful](/WordOfCaution.md).
* __Disclaimer #1__: though an engineer, this project is the first of its sort, I never did something related. It's all but a finalized product.
* __Disclaimer #2__: Ultrasound raises questions. In case you build a scanner, use caution and good sense!

## Safety

Most of the modules can be found on usual open-source hardware procurement websites. However, the two modules specifically developed for this project have to be custom made, as they are not currently sold as kits or assemblies.

One of the modules uses a DC-booster, which can raise the voltage it delivers above 100V, as the R05–100B can deliver up to 134VDC. The design has limited high-voltage to specific points within the module, and to the SMA connector going to the transducer. The other pins of the module have inputs/outputs that range in the [–5V ; 5V] bracket. The full setup, without the motor, did not use more than 170 mA at 9V during the tests. The ATL3 probe, powered at 3.3V, brought the total power envelope to 330mA at 9V. The difference of stimulating the transducer caused a 5 mA at 9V difference.

Other safety issues when applied to humans. There are indeed very strict regulations on ultrasound equipment for use in humans due to both thermal and mechanical effects of ultrasound on tissue such as overheating, and mechanical breaking of tissue structures. We understand that no medical scanners can be sold on the market without having undergone strict measurements and reporting routines (e.g. the FDA in USA and similar institutions elsewhere).

However, the present modules do not aim at providing a medical ultrasound imaging system to a doctor, nor is suitable for tests on living beings, and hence does not need to fulfill the same requirements as a medical device.

## Safety uses of ultrasounds

High power ultrasound can cause deep tissue burns. Limit yourself with a 500mA 5V supply and you should be relatively safe!


