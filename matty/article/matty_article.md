https://www.iith.ac.in/~raji/Cpapers/LPFB.pdf

# Abstract

Open-source hardware is a key element in the development of science. In the field of ultrasound, little has been achieved so far to grant access to research-grade ultrasound tools. We are presenting the development of a flexible, open architecture for a single element ultrasound imaging platform, operating in pulse-echo mode.

The proposed architecture builds on a transmit-receive channel and on a Field Programmable Gate Array (FPGA), which can be interfaced with a computer. It operates with a high voltage excitation, dynamic gain compensation, fast ADC, with onboard storage capacity for raw acquisitions. Proposed downstream communication operates on a single high speed Serial Peripheral Interface (SPI)

A first experiment is realized to image a wire phantom [@check with PU30], on a B-mode imaging basis.

The results show that this development kit can be used by ultrasound imaging researchers, opening ultrasound as well to different uses.

# 1. Introduction

## Generic to ultrasound

## Open source ultrasound

## Why single element


# 2. System Description

## Objective

## State of the art review

## Proposed design

The proposed design focuses on simplicity at its core. 

### Pulser


A MD0100 then ensures the signal can proceed to the Analog Processing block.

### Analog processing channel
 

Said TGC has a gain that is set-up by an 8-bit DAC, covering the full range of the variage gain of the TGC. Gain can be set up by 5 us intervals.


### Acquisition

Amplified signal is fed to a XX bit high-speed ADC. Acquisition speed can go up to 64 msps.

ACquisitions are managed by the FPGA and stored in the attached RAM for later offloading by the user. The storage [XX Mbytes] enables the user 

###  E. User interface


The platforms offers control over on-board USB or on-board Raspberry Pi connections, connecting to the FPGA using SPI.

This provides the user with the full control over the parameters of the pulse-echo acquisitions.  




# 3. Experimental results

## 3.1 B-Mode imaging

### First results

### Errors using several image reconstruction tools


## 3.2 Chaotic lens



# Conclusion




# s

open source toolchain FPGA 

compressed sensing


integrated hardware


