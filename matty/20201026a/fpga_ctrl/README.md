# FPGA control scripts

## csr_map.py

This file contains CSR map class with some CSR-related constants and access methods.

## csr_map.md

Table with CSR map structure being described.

## ftdi_dev.py

Wrapper classes over PyFtdi library API to provide methods for SPI transaction generation and GPIO toggling.

## fpga_ctrl.py

Main control script "to run them all". Contains class to perform FPGA high-level manipulations: reset, write or read CSR and etc.

## test_csr_rw.py

Test of read/write registers.

## test_csr_ro.py

Test of read only registers.

## test_ram.py

Test of external RAM.
