# ##############################################################################

# iCEcube SDC

# Version:            2017.08.27940

# File Generated:     Jan 16 2018 20:20:02

# ##############################################################################

####---- CreateClock list ----1
define_clock   {p:CLK}  -freq 12 -clockgroup default_clkgroup_0
#define_clock   {p:spi_sclk}  -freq 150 -clockgroup default_clkgroup_1
#create_clock  -period 20.00 -name {spi_sclk} [get_ports {spi_sclk}] 

