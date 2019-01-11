# That was the todo for going to v1.0 to v1.01

(proto to prod)

* Footprints
  * Check clock footprint (quelle raison pour plantage par Macrofab?)
  * Correct HV Module footprint (reversed)
* Simplification
  * Remove i2c components / lines
    * Seul i2c: RPi's line
  * REMOVE U118, U131, U134
* Checks
  * Vérifier U143 et U160 (seemed to bug when using IO4 as CS)
* Headers (2x6 as PMODs, exposing) ( J9 and J19 split ):
  * PMOD 1 (close to SMA)
    * TopTurn 1, 2, 3
    * Out 1, 2, 3
    * Pon
    * Poff
    * 5V, 3.3V and GND
  * PMOD 2 (somewhere else)
    * IO 1 to 4
    * In 1, 2, 3, Trig
    * 5V, 3.3V and GND
* Reorga
  * RPi header reversed + OLED reversed (écran loin)
    * Mounting holes for RPi0
    * Décaler / splitter J10
* Interfaces
  * RESET button for FPGA ? 
  * LED for chip enable on SPI FLASH
    * LED on flash/fpga CS
    * LED on RPi / USB select
