# hardware : quelques idées

## NRF

### Carte principale

Carte d'eval BLE (avec un regulateur de tension integre?)
* objective: use the nrf only as the glue between digital/analog IOs and use old phones/RPIs as actual brains.
* check this -> https://www.adafruit.com/product/3406 " _The Bluefruit LE module is an nRF52832 chipset from Nordic, which can be used as both a main microcontroller and a bluetooth low energy interface. For most people, they'll be very happy to use the standard Nordic UART RX/TX connection profile - code is provided! In this profile, the Bluefruit acts as a data pipe, that can 'transparently' transmit back and forth from your iOS or Android device. You can use our iOS App or Android App, or write your own to communicate with the UART service._ "

### Form factor ?

* Revue form factor m5stack
  * 3 form factor standar [large](https://asset.conrad.com/media10/isa/160267/c1/-/fr/001888210PI04/image.jpg?x=600&y=600), [medium but low IOs](https://imgaz2.staticbg.com/thumb/large/oaupload/banggood/images/1A/8E/faadfffe-377f-4ac2-9bd8-42459f74c818.jpg), [small with more IOs](https://images-na.ssl-images-amazon.com/images/I/51%2B1cANK6LL._AC_SX355_.jpg)
  * Format factor m5stack (qui est en version carrée et version stick): ca peut être malin de réutiliser leurs cartes filles (cf section en dessous): pas besoin de réinventer la roue pour des extensions.
  * Du coup, carte mère qui ressemble au m5stack avec un écran, pk pas un oled ?
  * (trip perso) En carte fille type m5stack, un petit up5k serait pas mal aussi :) avec la barrette de connecteurs vers m5stack + accès à la flash, mais aussi des connecteurs pmod (3 ou 4x 8) + rgb pour l'y brancher :)

* Revue formfactor feather
  * standard - check [adafruit specs](https://learn.adafruit.com/adafruit-feather/feather-specification)
  * not so many boards as in 

### Carte fille

* carte de charge / recharge batterie
* carte extension wireless charging
* carte capteur 3x3 axes
* carte neopixel
* carte commande moteur
* GPIO avec choix de tension
* generateur de tensions


## FT boards Ideas

* Dev-board: 
  * déjà peut etre faire un adaptateur FT600 + 2PMOD (en mode BML https://blackmesalabs.wordpress.com/2017/12/19/bml-usb-3-0-fpga-interface-over-pmod/ qui cite une AN  http://www.ftdichip.com/Support/Documents/AppNotes/AN_386%20FTDI%20FT600%20Maximize%20Performance.pdf ) tout son design est là : https://www.dropbox.com/s/i40ia5ljuz0wmnf/bml_usb3_ft600.zip?dl=0
  * (_pas besoin car on a deja des devboards avec suffisament d'IOs) Ft600 +hx4k (au final car up5k pas assez d'ios pour 2x16). Avec un petit ftdi pour flasher (iceprog like matty) et un usb pour le ft ? Caler aussi 2x2x8 PMODs ?
  * Adc 10 bit 10-64msps en double pmod pour les tests ?

* Ca peut valoir le coup de le brancher sur une carte comme le icebreaker, à la limite en envoyant des données préformatées sur le ft600 pour les tests de débit.
  * [ft600] + 80msps clock + 80msps adc tout simplement? ;)
  * [ft600 + up5k] + [AD9201] pour soit 40msps 10bits / à travers un connecteur ?

* Remarques FT600 générales
  * J'aime bien cette idée de séparer [ft600+logique] de l'[adc] ou du système qui doit être capturé (je pense par exemple à la beaglelogic cape qui était un analyseur logique 100Mhz pour beaglebone).
  * Comme le FUSBee5 https://hackaday.io/project/170694-fusbee5 ).
  * Apparament FT601 marche à 1.4Gbps https://twitter.com/fpga_dave/status/1067504684963909632
  * [pas mal de designs avec moult PMODs](https://github.com/kelu124/awesome-latticeFPGAs) pour faire des tests / glue entre ft600/autres et d'autres devices.

* A noter : "_GUSTL BUHEITEL SAYS: Hello, even with the simple FT232H you can achieve up to about 35 MBytes/s when using the FIFO Interface with the 60 MHz Clock from the FTDI. You need ledd than 16 IOs, 8 for the DATA. With the FT600 which is very similiar, you should be able to get a much higher transfer rate. But USB is fastest when transferring large blocks. So use a large dual clock FIFO in the FPGA (I use 128 kBytes), one clock is the FPGA clock and the other is the FTDI clock. And then transfer 64 kByte blocks._"

- Matos existant: [FT600 BML](https://www.dropbox.com/s/i40ia5ljuz0wmnf/bml_usb3_ft600.zip?dl=0) : fichiers prêts à partir en prod.

## FPGA - ideas of with stuff

### References

* https://stackoverflow.com/questions/37136744/fpga-synchronous-bus-timing
* https://github.com/ultraembedded/core_ft60x_axi
* more: https://twitter.com/bml_khubbard/status/946877620746010624 =) 2 cartes: lattice , et ft600 -> design intéressant
* https://stackoverflow.com/questions/37136744/fpga-synchronous-bus-timing

FT600 Xilinx Altera -< : https://www.ftdichip.com/Support/Documents/AppNotes/AN_421_FIFO_Bus_Master_For%20FT60x.pdf ).

### Connectors

Connector types:
* PMOD https://hackaday.io/page/2984-14-bit-80msps-adc-for-sdr-experiments
* autre : https://alchitry.com/products/alchitry-cu-fpga-development-board

## Délires lulu

* 4 chords using esp32 - http://sgreg.fi/projects/4chord-midi -- via esp32 pr MIDI controller via BLE ?
* [SDR](https://pdfs.semanticscholar.org/ff96/f6e985d32c9d89a4c2d4e816831032c1d6bf.pdf) - créateur à contacter ?

## Cartes à faire

### Other 

* With a business case : "[Development of a software-defined radio for the 2.4 GHz band](https://upcommons.upc.edu/handle/2117/90394)"

## Cote USB - debug (debug minimum)

* Optimisation processeur / niveau de debug
* Changer debug/optimisation du projet
  * voir côté linux (module ou pas)
  * module kernel


## Noms et brainstorms

### Concept

- sur le sujet du nom.. et le chocolat
- un nom en chocolat ou chocolate
- des module en ADC2, STEPPER2, OLED2.  le 2 est en carre:) ou square
- une carte mere en chocolate bar ou box
- la suite logiciel en 'chocolate fontain" style matrix

### Reqs

* un nom "unique" qui poppe facilement quand on le googlise  
  * "http://www.chocolateelectronics.com/" existe déjà: pédales de grattes

### Deviations

* "trinitario" (best chocolate beans?)
* "kkow"
* "c0c04"
* "Cocoa (Apple) — Wikipédia" mdr
* "kokoha" ne semble pas trop pris
* "cocoalchemy" ? / "chocoalchemy"
* "chocolatelectronics"




