# Concept

## Chaine acquisition US au format pHAT

## Contraintes

* Petite taille (pHAT)
* Acquisition temps réel
* 20Msps au niveau de l'ADC, 10 bits (quicker, and 12bits if possible)
* No external RAM =)
* Blocks DSPs disponibles
* Serie ice40 :) 
* Used only with RPi: fpga can be programmable through RPi / ice40 toolchain

## Nice to have

If there's enough room:
* Test points for logic signals (PPon, PNon, damp, trig, ...)
* Flash
* 2 petits boutons (1 reset, 1 trigger)

## Fonctions requises:

- Pulser, bipolar, en HVPos et HVNeg
- Protect variable gain : path should not exceed +-2V
- Choice between two entries for VGA path (one from pulser, another from raw SMA)
- Variable gain to have
  - DAC to set up the variable gain (as in matty)
  - activate, or not, a fixed gain (eg, the HILO input on AD8331)
- ADC a minima around 20Msps, 12 bits
- Real time
- SPI connection through RPIo connector
- Unused IOs to RPi GPIOs
- Logic trigger to start acquisition
- 500 us d'acquisition

## Fonctions externes

- Generation des hautes tensions + et - (board separée, connecteur à prévoir avec protection polarité )
- Controle RPi 

## Affichage

- LEDs sur HILO, CS du RPi
- 3 LEDs user accessible
