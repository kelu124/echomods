# Some resources USB-UT350



* https://github.com/mmolero/ultratekpy



Some captures from UT350 software



This device comes with a basic oscilloscope software that let's you control pulser and acquisition, but no more

If you want yo measure signal, you have to buy "UT Inspection" software package

Anyway, interesting features are signal type (Full, +Half, +Half, RF), LPF & HPF in software, or averaging

Main control is done using a TI TMS320VC5416 DSP + Xilinx XCR3384XL CPLD

ADC is AD9051, 10-bit 60MSPS

Interestingly, the conversions of the ADC goes to a RAM FIFO chip, IDT 72V251

input path is made out of 2 OpAmps and a VGA (AD605AR)


ADP1109 is probably there to boost 5V to 12V, used by LT IC on HV board

The two big capacitors (C41, C42), D1, L2 and N-channel mosfet T2 are there to invert HV polarity and get a negative pulse 
