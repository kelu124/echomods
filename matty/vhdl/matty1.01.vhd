----------------------------------------------------------------------------------
--
-- Create Date:    2018
-- Design Name: 	MATTY
-- Module Name:    MATTY_MAIN_VHDL
-- Project Name:   MATTY
-- Target Devices: iCE40-HX4K_TQ144

--

-- Revision: 1

--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use IEEE.NUMERIC_STD.ALL;


entity MATTY_MAIN_VHDL is
    Port ( 	clk : in  STD_LOGIC;
    		

     		--reset_alim : in  STD_LOGIC; --simu --active low
            reset_alim : in  STD_LOGIC;
            reset_ft : in  STD_LOGIC; --active high 
            reset_rpi : in  STD_LOGIC; --active high
           	LED_ACQ : out  STD_LOGIC;
           	LED_MODE : out  STD_LOGIC;
           	LED3 : out  STD_LOGIC;
        	spi_cs_ft: in  STD_LOGIC;
    		spi_sclk_ft: in  STD_LOGIC;
    		spi_mosi_ft: in  STD_LOGIC;
    		spi_miso_ft : out  STD_LOGIC;
            spi_cs_rpi: in  STD_LOGIC;
            spi_sclk_rpi: in  STD_LOGIC;
            spi_mosi_rpi: in  STD_LOGIC;
            spi_miso_rpi : out  STD_LOGIC;
            spi_cs_flash: out  STD_LOGIC;
            spi_sclk_flash: out  STD_LOGIC;
            spi_mosi_flash: out  STD_LOGIC;
            spi_miso_flash : in  STD_LOGIC;
            cs_rpi2flash: in  STD_LOGIC; --1 to link RPI SPI lines to FLASH lines
            spi_select: in  STD_LOGIC; --  0:FT / 1:RPI

    		DAC_cs: out  STD_LOGIC;
    		DAC_sclk: out  STD_LOGIC;
    		DAC_mosi: out  STD_LOGIC;
    		ADC0: in  STD_LOGIC;
       		ADC1: in  STD_LOGIC;
    		ADC2: in  STD_LOGIC;
    		ADC3: in  STD_LOGIC;
    		ADC4: in  STD_LOGIC;
    		ADC5: in  STD_LOGIC;
    		ADC6: in  STD_LOGIC;
    		ADC7: in  STD_LOGIC;
    		ADC8: in  STD_LOGIC;
    		ADC9: in  STD_LOGIC;
    		ADC_clk: out STD_LOGIC;


			RAM_DATA:inout  std_logic_vector(15 downto 0);
			RAM_ADD:out std_logic_vector(18 downto 0);

 			RAM_nCE: out STD_LOGIC;
 			RAM_nOE: out STD_LOGIC;
 			RAM_nWE: out STD_LOGIC;
 			RAM_nLB: out STD_LOGIC;
 			RAM_nUB: out STD_LOGIC;

        	trig_ext: in  STD_LOGIC;
            trig_rpi: in  STD_LOGIC;
            trig_ft: in  STD_LOGIC;
            button_trig: in  STD_LOGIC;
        	button_mode: in  STD_LOGIC;
    		pon : out  STD_LOGIC;
    		poff : out  STD_LOGIC;
    		top_tour1: in  STD_LOGIC;
    		top_tour2: in  STD_LOGIC
    		);




end MATTY_MAIN_VHDL;




architecture Behavioral of MATTY_MAIN_VHDL is

attribute syn_preserve : boolean;
attribute syn_keep : boolean;
attribute syn_preserve of Behavioral: architecture is true;
attribute syn_keep of Behavioral: architecture is true;

	--signal pll_clk100:std_logic; --sim
	signal pll_clk128:std_logic; --simu
	signal pll_clk64:std_logic; --simu
--signal pll_clk200:std_logic; --simu
	
    signal reset:std_logic; 

    signal trig:std_logic; 

    signal spi_cs:std_logic;
    signal spi_mosi:std_logic;
    signal spi_miso:std_logic;
    signal spi_sclk:std_logic;

	signal spi_data_miso    :  std_logic_vector(7 downto 0) := (others => '0');
	signal spi_miso_ready :  std_logic:= '0';
    signal spi_miso_valid :  std_logic:= '0';
	signal spi_data_mosi :  std_logic_vector(7 downto 0) := (others => '0');
	signal spi_mosi_ready:  std_logic:= '0';
	signal spi_mosi_ready_prev :  std_logic:= '0';
    signal spi_mosi_ready_prev2 :  std_logic:= '0';
    signal spi_mosi_ready_prev3:  std_logic:= '0';
    signal spi_mosi_ready64_prev :  std_logic:= '0';
    signal spi_mosi_ready64_prev2 :  std_logic:= '0';
    signal spi_mosi_ready64_prev3:  std_logic:= '0';
	signal spi_miso_ack:  std_logic:= '0';


	signal stop_tour1 :  std_logic:= '0';
	signal stop_tour2 :  std_logic:= '0';


	signal sSPI_MISO: std_logic:= '0';
	signal sPon: std_logic:= '0';
	signal sPoff: std_logic:= '0';


	signal sDAC_CSarray: std_logic_vector(3 downto 0);
	signal sDAC_mosi: std_logic:= '0';
	signal sDAC_sclk: std_logic:= '0';


	signal 	sRAM_ADD: std_logic_vector(18 downto 0):= (others => '0');
 	signal	sRAM_nWE: std_logic:= '1';


--configuration registers
	signal	sEEPon   :  std_logic_vector(7 downto 0):=X"14";		--50ns to 500ns def:200ns	resolution 10ns
    signal  sEEPonPoff   :  std_logic_vector(7 downto 0):=X"0A";        --0ns to 2550ns def:100ns   resolution 10ns
	signal	sEEPoff   : std_logic_vector(15 downto 0):=X"00C8";  --		--500ns to 3us def:2us
	signal	sTrigInternal   :  std_logic:= '0';			-- trig when rising
	signal	sEETrigInternal   :  std_logic:= '0';			-- trig when rising  form SPI
	signal	sEETrigInternal_prev   :  std_logic:= '0';
	Signal  sEESingleCont :  std_logic:= '0';			-- single if 0
	Signal  sSingleCont :  std_logic:= '0';			-- single if 0
	signal	sACQ   :  std_logic:= '0';	-- 1 during acqusition
	signal	sEEDelayACQ   :  std_logic_vector(15 downto 0):=X"02BC";	-- 0us to 50us def 7us
	signal	sDelayACQ   :  std_logic:= '0';
	signal	sEEACQ   :  std_logic_vector(15 downto 0):=X"32C8";		--50us to 130us		def 130us	  	 6590
	signal	sACQtime   :  std_logic:= '0';
	signal	sEEPeriod   :  std_logic_vector(23 downto 0):= X"0186A0";	--700us to 10ms def 1ms 	 0186A0
	signal	sPeriod   :  std_logic:= '0';
	signal	sDACDyn   :  std_logic:= '0';
	signal	sPeriod_prev   :  std_logic:= '0';
	signal	sEETrigCounter   :  std_logic_vector(15 downto 0):=X"000A"; -- number of acquisition secquence in continious mode1
	signal	sTrigCounter   :  std_logic_vector(15 downto 0):=X"0000";
	signal 	sSPI_MSB0LSB1 :  std_logic:= '0';

--counters
	signal sCounter : std_logic_vector(23 downto 0);

-- DAC
	signal sDAC_data : std_logic_vector(15 downto 0) := B"0011000000000000"; -- default mask
	signal sDAC_spi_start :  std_logic:= '0';
	signal sEEDAC   :  std_logic_vector(7 downto 0):= X"11";
	signal sCounterDAC : std_logic_vector(9 downto 0) := B"0000000000"; -- clk for DAC update period 5us X"3E8"
	signal sDAC_mem_pointer: std_logic_vector(7 downto 0):= X"00";

-- ADC
	signal sCounterADC : std_logic_vector(7 downto 0) := X"00"; -- to set up frequency
	signal sADC_clk :  std_logic:= '0';
	signal sADC_clk_prev :  std_logic:= '0';
	signal sEEADC_freq:  std_logic_vector(7 downto 0):= X"03";
	signal sADC_data:  std_logic_vector(11 downto 0):= (others => '0');

    signal sADC0: std_logic:= '0';
    signal sADC1: std_logic:= '0';
    signal sADC2: std_logic:= '0';
    signal sADC3: std_logic:= '0';
    signal sADC4: std_logic:= '0';
    signal sADC5: std_logic:= '0';
    signal sADC6: std_logic:= '0';
    signal sADC7: std_logic:= '0';
    signal sADC8: std_logic:= '0';
    signal sADC9: std_logic:= '0';
--in case of debounce needed
    --signal sADC0_prev: std_logic:= '0';
    --signal sADC1_prev: std_logic:= '0';
    --signal sADC2_prev: std_logic:= '0';
    --signal sADC3_prev: std_logic:= '0';
    --signal sADC4_prev: std_logic:= '0';
    --signal sADC5_prev: std_logic:= '0';
    --signal sADC6_prev: std_logic:= '0';
    --signal sADC7_prev: std_logic:= '0';
    --signal sADC8_prev: std_logic:= '0';
    --signal sADC9_prev: std_logic:= '0';
    --signal sADC0_prev2: std_logic:= '0';
    --signal sADC1_prev2: std_logic:= '0';
    --signal sADC2_prev2: std_logic:= '0';
    --signal sADC3_prev2: std_logic:= '0';
    --signal sADC4_prev2: std_logic:= '0';
    --signal sADC5_prev2: std_logic:= '0';
    --signal sADC6_prev2: std_logic:= '0';
    --signal sADC7_prev2: std_logic:= '0';
    --signal sADC8_prev2: std_logic:= '0';
    --signal sADC9_prev2: std_logic:= '0';



--RAM
	signal sRAM_pointer_read:  std_logic_vector(18 downto 0):= (others => '0');
	signal sRAM_pointer_write:  std_logic_vector(18 downto 0):= (others => '0');
    signal sEEPointerReset:  std_logic:= '0';
	signal sCounterRAM : std_logic_vector(7 downto 0) := X"00"; -- to set up frequency
    signal sRead_data :  std_logic:= '0';

--SPI
	signal sPointer:  std_logic_vector(1 downto 0):= (others => '0');
	signal sAddress:  std_logic_vector(7 downto 0):= (others => '0');



-- edge
	signal spi_cs_prev :  std_logic:= '0';
	signal button_mode_prev :  std_logic:= '0';
    signal button_debounce_counter:  std_logic_vector(23 downto 0):= (others => '0');
	signal trig_prev :  std_logic:= '0';
	signal nrst :  std_logic:= '0';
    signal sbuttonModeStatus :  std_logic:= '0';


TYPE DAC_ARRAY is array (1 to 42) of std_logic_vector(7 downto 0);

    signal sDAC_mem : DAC_ARRAY;



component pll128M2 is
port(
      REFERENCECLK: in std_logic;
      RESET: in std_logic;
      PLLOUTCOREA: out std_logic;
      PLLOUTGLOBALA: out std_logic;
      PLLOUTCOREB: out std_logic;
      PLLOUTGLOBALB: out std_logic
    );
end component pll128M2;


-------------------------


----------------------------------------------SPI--------------------------------------------------------------
 component SPI_SLAVE_ICE is
 Port (
 		i_sys_clk  : in  std_logic;  	-- system clock
         i_sys_rst  : in  std_logic;  	-- system reset
         i_csn      : in  std_logic;  	-- Slave Enable/select
         i_data     : in  std_logic_vector(7 downto 0);  -- Input data
         i_wr       : in  std_logic;  	-- Active Low Write, Active High Read
         i_rd       : in  std_logic;  	-- Active Low Write, Active High Read
         o_data     : out std_logic_vector(7 downto 0);  --output data
         o_tx_ready : out std_logic;  	-- Transmitter ready, can write another
   					-- data
         o_rx_ready : out std_logic;  	-- Receiver ready, can read data
         o_tx_error : out std_logic;  	-- Transmitter error
         o_rx_error : out std_logic;  	-- Receiver error

         i_cpol      : in std_logic;  	-- CPOL value - 0 or 1
         i_cpha      : in std_logic;  	-- CPHA value - 0 or 1
         i_lsb_first : in std_logic;  	-- lsb first when '1' /msb first when
   					-- '0'

         o_miso      : out std_logic;  	-- Slave output to Master
         i_mosi      : in  std_logic;  	-- Slave input from Master
         i_ssn       : in  std_logic;  	-- Slave Slect Active low
         i_sclk      : in  std_logic;  	-- Clock from SPI Master
         miso_tri_en : out std_logic;
 		o_tx_ack    : out std_logic;
 		o_tx_no_ack : out std_logic
     );
 end component SPI_SLAVE_ICE;



component spi_master is
    port(
        i_sys_clk      : in  std_logic;  -- system clock
        i_sys_rst      : in  std_logic;  -- system reset
        i_csn          : in  std_logic;  -- chip select for SPI master
        i_data         : in  std_logic_vector(15 downto 0);  -- Input data
        i_wr           : in  std_logic;  -- Active Low Write, Active High Read
        i_rd           : in  std_logic;  -- Active Low Write, Active High Read
        o_data         : out std_logic_vector(15 downto 0);  --output data
        o_tx_ready     : out std_logic;  -- Transmitter ready, can write another
  					-- data
        o_rx_ready     : out std_logic;  -- Receiver ready, can read data
        o_tx_error     : out std_logic;  -- Transmitter error
        o_rx_error     : out std_logic;  -- Receiver error
        o_intr         : out std_logic;
        i_slave_addr   : in  std_logic_vector(1 downto 0);  -- Slave Address
        i_cpol         : in  std_logic;  -- CPOL value - 0 or 1
        i_cpha         : in  std_logic;  -- CPHA value - 0 or 1
        i_lsb_first    : in  std_logic;  -- lsb first when '1' /msb first when
        i_spi_start    : in  std_logic;  -- START SPI Master Transactions
        i_clk_period   : in  std_logic_vector(7 downto 0);  -- SCL clock period in terms of i_sys_clk
        i_setup_cycles : in  std_logic_vector(7 downto 0);  -- SPIM setup time  in terms of i_sys_clk
        i_hold_cycles  : in  std_logic_vector(7 downto 0);  -- SPIM hold time  in terms of i_sys_clk
        i_tx2tx_cycles : in  std_logic_vector(7 downto 0);  -- SPIM interval between data transactions in terms of i_sys_clk
        o_slave_csn    : out std_logic_vector(3 downto 0);  -- SPI Slave select (chip select) active low
        o_mosi         : out std_logic;  -- Master output to Slave
        i_miso         : in  std_logic;  -- Master input from Slave
        o_sclk         : out std_logic;  -- Master clock
        mosi_tri_en    : out std_logic
        );
end component spi_master;


begin
	
	pll128M2_inst:  pll128M2 --simu
	port map(
          REFERENCECLK => clk,
          PLLOUTCOREA => pll_clk128,
          PLLOUTGLOBALA => open,
          PLLOUTCOREB => pll_clk64,
          PLLOUTGLOBALB => open,
          RESET => reset
        );


 spi_slave_inst : SPI_SLAVE_ICE
 port map (

         i_sys_clk  => pll_clk128 , -- system clock
         i_sys_rst  => nrst,  -- high low synchronous reset --simu
         -- SPI SLAVE INTERFACE
         i_sclk  =>spi_sclk ,
         i_ssn  => spi_cs,
         i_mosi  => spi_mosi,
         o_miso  => spi_miso,
         -- USER INTERFACE
         o_data  => spi_data_mosi ,
         i_wr  => '1',--spi_miso_write_enable, --write enable at low
         i_rd  => '1',--spi_mosi_read_enable, --read enable at high
         o_tx_ready    => spi_miso_ready,
         i_data     => spi_data_miso,
         o_rx_ready => spi_mosi_ready,


         --config
         i_csn =>nrst,--
         miso_tri_en => open,
         i_cpol =>'0',
         i_cpha =>'0',--
         i_lsb_first =>'0',
         o_tx_error => open,
         o_rx_error => open,
         o_tx_ack=> spi_miso_ack,
         o_tx_no_ack => open

 );


spi_master_inst : spi_master
port map (
        i_sys_clk      => pll_clk64 ,  -- system clock
        i_sys_rst      => nrst,  -- system reset --simu
        i_csn          =>'0',  -- chip select for SPI master
        i_data         => sDAC_data,  -- Input data
        i_wr           => '1',  -- Active Low Write, Active High Read
        i_rd           => '1',  -- Active Low Write, Active High Read
        o_data         => open,  --output data
        o_tx_ready     => open,  -- Transmitter ready, can write another data
        o_rx_ready     => open,  -- Receiver ready, can read data
        o_tx_error     => open,  -- Transmitter error
        o_rx_error     => open,  -- Receiver error
        o_intr         => open,
        i_slave_addr   => B"00",  -- Slave Address
        i_cpol         =>'0',  -- CPOL value - 0 or 1
        i_cpha         =>'0', -- CPHA value - 0 or 1
        i_lsb_first    =>'0',  -- lsb first when '1' /msb first when
        i_spi_start    => sDAC_spi_start,  -- START SPI Master Transactions
        i_clk_period   =>X"06",  -- SCL clock period in terms of i_sys_clk
        i_setup_cycles =>X"05",  -- SPIM setup time  in terms of i_sys_clk
        i_hold_cycles  =>X"05",  -- SPIM hold time  in terms of i_sys_clk
        i_tx2tx_cycles =>X"0A",  -- SPIM interval between data transactions in terms of i_sys_clk
        o_slave_csn    =>sDAC_CSarray,  -- SPI Slave select (chip select) active low
        o_mosi         =>sDAC_mosi,  -- Master output to Slave
        i_miso         => '0',  -- Master input from Slave
        o_sclk         => sDAC_sclk,  -- Master clock
        mosi_tri_en    => open
);








-------------------------------trig management-------------------------------------------------

process(pll_clk128,reset)
begin

if reset = '0' then
    sTrigInternal <= '0';
    trig_prev  <= '0';
    sPeriod_prev<= '0';
    sEETrigInternal_prev<= '0';
elsif rising_edge(pll_clk128) then

	if ((trig_prev = '0' and trig ='1') or (sEETrigInternal_prev ='0' and sEETrigInternal ='1') or (sSingleCont ='1' and sPeriod_prev = '1' and sPeriod ='0' and sTrigCounter < (sEETrigCounter-1))) and sCounter /= X"000010" then
		sTrigInternal <= '1';
		sTrigCounter <= sTrigCounter +1;

	elsif sCounter = X"000010" then
		sTrigInternal <= '0';

	end if;


	if (trig_prev = '0' and trig ='1') or (sEETrigInternal_prev ='0' and sEETrigInternal ='1') then
		sTrigCounter <= X"0000";
	end if;

    sEETrigInternal_prev <=sEETrigInternal;
    sPeriod_prev <= sPeriod;
    trig_prev <= trig;

end if;
end process;




process(reset, sTrigInternal, sCounter)
begin

if reset = '0' then
    sACQ <= '0'   ;
--elsif rising_edge(pll_clk100) then

	elsif sTrigInternal = '1'  or (sCounter >1 and sCounter <= sEEPeriod)  then
		sACQ <= '1'	  ; -- signal that indicates you are doing an acquisition
	else
		sACQ <= '0'	  ;

	end if;

--end if;

end process;



-------------------------------end trig management-------------------------------------------------

---------------------------------Counter signal generation---------------------------------------------------------
process(pll_clk128, reset)
begin

if reset = '0' then
sCounter <= X"000000";
elsif rising_edge(pll_clk128) then
	if sACQ = '0' then
		sCounter <= X"000000";	--start counting
	else
		sCounter <= sCounter + 1;
	end if;
end if;
end process;




---------------------------------End Counters-----------------------------------

------------------------------Signal generation-------------------------------------
--PON
sPon <= '1' when sCounter > 0 and sCounter <= sEEPon else '0';

--POFF
sPoff <= '0' when sCounter  > (sEEPonPoff) and sCounter  < (sEEPoff) else '1';




-- ACQUISITION
sACQtime <= '1' when sCounter  > (sEEDelayACQ ) and sCounter  < (sEEACQ) else '0';



--PERIOD GLOBALE for continious mode
sPeriod <= '1' when sCounter > 0 and  sCounter  <= sEEPeriod else '0';


-- DAC DYNAMIC
sDACdyn <= '1' when sCounter  > 0 and sCounter  <= (sEEACQ) else '0';

------------------------------End Signal generation-------------------------------------


------------------------------configuration by spi-------------------------------------

process(pll_clk128, reset, spi_mosi_ready) --pll_clk128
begin


if reset = '0' then
sAddress <= X"00";
sPointer <= B"00";



sEEACQ  <=  X"32C8";
sEEPon  <= X"14";
sEEPonPoff   <=  X"0A";
sEEPoff   <= X"00C8";
sEETrigInternal   <=   '0';
sEESingleCont <=   '0';
sEEDelayACQ   <=  X"02BC";
sEEPeriod  <=   X"0186A0";
sEETrigCounter   <= X"000A";


sDAC_mem(1) <=(others => '0');
sDAC_mem(2) <=(others => '0');
sDAC_mem(3) <=(others => '0');
sDAC_mem(4) <=(others => '0');
sDAC_mem(5) <=(others => '0');
sDAC_mem(6) <=(others => '0');
sDAC_mem(7) <=(others => '0');
sDAC_mem(8) <=(others => '0');
sDAC_mem(9) <=(others => '0');
sDAC_mem(10) <=(others => '0');
sDAC_mem(11) <=(others => '0');
sDAC_mem(12) <=(others => '0');
sDAC_mem(13) <=(others => '0');
sDAC_mem(14) <=(others => '0');
sDAC_mem(15) <=(others => '0');
sDAC_mem(16) <=(others => '0');
sDAC_mem(17) <=(others => '0');
sDAC_mem(18) <=(others => '0');
sDAC_mem(19) <=(others => '0');
sDAC_mem(20) <=(others => '0');
sDAC_mem(21) <=(others => '0');
sDAC_mem(22) <=(others => '0');
sDAC_mem(23) <=(others => '0');
sDAC_mem(24) <=(others => '0');
sDAC_mem(25) <=(others => '0');
sDAC_mem(26) <=(others => '0');
sDAC_mem(27) <=(others => '0');
sDAC_mem(28) <=(others => '0');
sDAC_mem(29) <=(others => '0');
sDAC_mem(30) <=(others => '0');
sDAC_mem(31) <=(others => '0');
sDAC_mem(32) <=(others => '0');
sDAC_mem(33) <=(others => '0');
sDAC_mem(34) <=(others => '0');
sDAC_mem(35) <=(others => '0');
sDAC_mem(36) <=(others => '0');
sDAC_mem(37) <=(others => '0');
sDAC_mem(38) <=(others => '0');
sDAC_mem(39) <=(others => '0');
sDAC_mem(40) <=(others => '0');
sDAC_mem(41) <=(others => '0');
sDAC_mem(42) <=(others => '0');


elsif rising_edge(pll_clk128) then


 if spi_mosi_ready64_prev3 = '0' and spi_mosi_ready64_prev2 = '1' and spi_mosi_ready64_prev = '1' and spi_mosi_ready = '1' then --with debounce as the module gives a two  edges at each transfer


		if sPointer <= B"00" then
			if spi_data_mosi = X"AA" then -- detect configuration
				sPointer <= B"01";
			end if;
            sEETrigInternal <= '0';-- auto reset for SPI trig

		elsif sPointer <= B"01" then  -- get register address
			sAddress <= spi_data_mosi;
			sPointer <= B"10";
            sEEPointerReset <= '0';
		elsif sPointer <= B"10" then  -- get value
			--sData <= spi_data_mosi;
			sPointer <= B"00";

			case sAddress is

                when X"10"=>
                sDAC_mem(1) <=spi_data_mosi;
                when X"11"=>
                sDAC_mem(2) <=spi_data_mosi;
                when X"12"=>
                sDAC_mem(3) <=spi_data_mosi;
                when X"13"=>
                sDAC_mem(4) <=spi_data_mosi;
                when X"14"=>
                sDAC_mem(5) <=spi_data_mosi;
                when X"15"=>
                sDAC_mem(6) <=spi_data_mosi;
                when X"16"=>
                sDAC_mem(7) <=spi_data_mosi;
                when X"17"=>
                sDAC_mem(8) <=spi_data_mosi;
                when X"18"=>
                sDAC_mem(9) <=spi_data_mosi;
                when X"19"=>
                sDAC_mem(10) <=spi_data_mosi;
                when X"1A"=>
                sDAC_mem(11) <=spi_data_mosi;
                when X"1B"=>
                sDAC_mem(12) <=spi_data_mosi;
                when X"1C"=>
                sDAC_mem(13) <=spi_data_mosi;
                when X"1D"=>
                sDAC_mem(14) <=spi_data_mosi;
                when X"1E"=>
                sDAC_mem(15) <=spi_data_mosi;
                when X"1F"=>
                sDAC_mem(16) <=spi_data_mosi;
                when X"20"=>
                sDAC_mem(17) <=spi_data_mosi;
                when X"21"=>
                sDAC_mem(18) <=spi_data_mosi;
                when X"22"=>
                sDAC_mem(19) <=spi_data_mosi;
                when X"23"=>
                sDAC_mem(20) <=spi_data_mosi;
                when X"24"=>
                sDAC_mem(21) <=spi_data_mosi;
                when X"25"=>
                sDAC_mem(22) <=spi_data_mosi;
                when X"26"=>
                sDAC_mem(23) <=spi_data_mosi;
                when X"27"=>
                sDAC_mem(24) <=spi_data_mosi;
                when X"28"=>
                sDAC_mem(25) <=spi_data_mosi;
                when X"29"=>
                sDAC_mem(26) <=spi_data_mosi;
                when X"2A"=>
                sDAC_mem(27) <=spi_data_mosi;
                when X"2B"=>
                sDAC_mem(28) <=spi_data_mosi;
                when X"2C"=>
                sDAC_mem(29) <=spi_data_mosi;
                when X"2D"=>
                sDAC_mem(30) <=spi_data_mosi;
                when X"2E"=>
                sDAC_mem(31) <=spi_data_mosi;
                when X"2F"=>
                sDAC_mem(32) <=spi_data_mosi;
                when X"30"=>
                sDAC_mem(33) <=spi_data_mosi;
                when X"31"=>
                sDAC_mem(34) <=spi_data_mosi;
                when X"32"=>
                sDAC_mem(35) <=spi_data_mosi;
                when X"33"=>
                sDAC_mem(36) <=spi_data_mosi;
                when X"34"=>
                sDAC_mem(37) <=spi_data_mosi;
                when X"35"=>
                sDAC_mem(38) <=spi_data_mosi;
                when X"36"=>
                sDAC_mem(39) <=spi_data_mosi;
                when X"37"=>
                sDAC_mem(40) <=spi_data_mosi;
                when X"38"=>
                sDAC_mem(41) <=spi_data_mosi;
                when X"39"=>
                sDAC_mem(42) <=spi_data_mosi;


                when X"D0"=>
                sEEPonPoff <=spi_data_mosi;


				when X"E0"=>
				sEEPon <=spi_data_mosi;

				when X"E1"=>
				sEEPoff(15 downto 8) <=spi_data_mosi;

				when X"E2"=>
				sEEPoff(7 downto 0) <=spi_data_mosi;

				when X"E3"=>
				sEEDelayACQ(15 downto 8) <=spi_data_mosi;

				when X"E4"=>
				sEEDelayACQ(7 downto 0) <=spi_data_mosi;

				when X"E5"=>
				sEEACQ(15 downto 8) <=spi_data_mosi;

				when X"E6"=>
				sEEACQ(7 downto 0) <=spi_data_mosi;

				when X"E7"=>
				sEEPeriod(23 downto 16) <=spi_data_mosi;

				when X"E8"=>
				sEEPeriod(15 downto 8) <=spi_data_mosi;

				when X"E9"=>
				sEEPeriod(7 downto 0) <=spi_data_mosi;

				when X"EA"=>
				sEETrigInternal <=spi_data_mosi(0);

				when X"EB"=>
				sEESingleCont <=spi_data_mosi(0);

				when X"EC"=>
				sEEDAC <=spi_data_mosi;

				when X"ED"=>
				sEEADC_freq <=spi_data_mosi;

				when X"EE"=>
				sEETrigCounter(7 downto 0) <=spi_data_mosi;

				when X"DE"=>
				sEETrigCounter(15 downto 8) <=spi_data_mosi;


                when X"EF"=>
                sEEPointerReset <=spi_data_mosi(0);

				when others => NULL ;

			end case;
		else
			sAddress <= X"00";
			sPointer <= B"00";
		end if;

	end if;
     spi_mosi_ready64_prev3<= spi_mosi_ready64_prev2;
     spi_mosi_ready64_prev2<= spi_mosi_ready64_prev;
    spi_mosi_ready64_prev<= spi_mosi_ready;
end if;
end process;



----------------------DAC---------------------MCP4811 - clock max 20Mhz in use 20Mhz - transmit data every 5us

process(pll_clk64, reset)


begin
if reset = '0' then
    sCounterDAC <= (others => '0');
    sDAC_spi_start <= '0';

    sDAC_data <= (others => '0');
    sDAC_mem_pointer<= (others => '0');

elsif rising_edge(pll_clk64) then
	sCounterDAC <= sCounterDAC + 1;
	if  sCounterDAC =  319 then
		sCounterDAC <= (others => '0');
		sDAC_spi_start <= '1';


	elsif sCounterDAC =  5 then
		sDAC_spi_start <= '0';
	elsif sCounterDAC =  300 then
        if sDACdyn = '1'  and sDAC_mem_pointer<=42 then
            sDAC_data <= B"00110" & sDAC_mem(to_integer(unsigned(sDAC_mem_pointer))) & B"000";
            --sDAC_data <= B"00110" & sEEDAC & B"000"; -- for no dynamic use
            sDAC_mem_pointer <= sDAC_mem_pointer+1;
        else
	        sDAC_data <= B"00110" & sEEDAC & B"000";
            sDAC_mem_pointer <=1;
        end if;
	end if;
end if;
end process;




----------------------end DAC--------------------

----------------------ADC-------------------- ADC10065  - CLK max 65MHz
process(pll_clk128, reset) -- ADC CLK generation during Acquisition time
begin

if reset = '0' then
    sADC_clk <= '0';
    sCounterADC <= (others => '0');

elsif rising_edge(pll_clk128) then

	if sACQtime = '1' then
		sCounterADC <= sCounterADC + 1;
		if  sCounterADC =  sEEADC_freq then
			sCounterADC <= (others => '0');
			sADC_clk <= not sADC_clk;
		end if;
	else
		sADC_clk <= '0';
	end if;
end if;
end process;




----------------------end ADC--------------------


----------------------RAM&ADC--------------------



process(reset, pll_clk128)-- ADC CLK generation during Acquisition time
begin

if reset  = '0' then
    spi_data_miso <= X"36";
    sCounterRAM<= (others => '0');
    sRAM_pointer_write<= (others => '0');
    sRAM_pointer_read<= (others => '0');
    sSPI_MSB0LSB1<='0';
    spi_mosi_ready_prev<='0';
    spi_mosi_ready_prev2<='0';
    spi_mosi_ready_prev3<='0';
    sRead_data<='0';
    RAM_DATA <= (others=>'Z');
    spi_miso_valid<='0';

elsif rising_edge(pll_clk128) then

    sCounterRAM <= sCounterRAM + 1;

	if sACQtime = '1' then
        if sADC_clk_prev = '0' and sADC_clk ='1' then -- save in RAM the current ADC value
			sRAM_ADD <= sRAM_pointer_write;
			sRAM_pointer_write <= sRAM_pointer_write+1;
            --RAM_DATA <= '1'&sTrigCounter(1 downto 0) & top_tour2&top_tour1&sADC9&sADC8&sADC7&'0'&sADC6&sADC5&sADC4&sADC3&sADC2&sADC1&sADC0; -- in case of debounce needed
            RAM_DATA <= '1'&sTrigCounter(1 downto 0) & top_tour2&top_tour1&ADC9&ADC8&ADC7&'0'&ADC6&ADC5&ADC4&ADC3&ADC2&ADC1&ADC0;
			sCounterRAM<= (others => '0');
		end if;

        sADC_clk_prev <= sADC_clk;
		spi_data_miso <= X"81";  -- during acq the SPI return 0x81 value
        spi_miso_valid <= '1';

	elsif sACQtime = '0' then

		RAM_DATA <= (others=>'Z');		-- free Ram BUS

	-- SPI data send when there is no acq


         if spi_mosi_ready_prev3 = '0' and spi_mosi_ready_prev2 = '1' and spi_mosi_ready_prev = '1' and spi_mosi_ready = '1' then
            sRAM_ADD <= sRAM_pointer_read;---new address pointer on the RAM address bus
            --Mechanism to alternated MSB and LSB word
            if sSPI_MSB0LSB1 = '0' then                     -- send on SPI MSB of data
                sCounterRAM<= (others => '0');-----
                sRead_data <='1';
                sSPI_MSB0LSB1 <= not sSPI_MSB0LSB1;
            else                                             -- send on SPI LSB of data 
                spi_data_miso <= RAM_DATA(7 downto 0);
                sRAM_pointer_read <= sRAM_pointer_read +1;
                sSPI_MSB0LSB1 <= not sSPI_MSB0LSB1;
                spi_miso_valid <= '1';

            end if;
        end if;


        --Mechanism to read the data on the bus only once per 2 SPI transfers with delay to be sure the data in ready on the bus
        if sRead_data = '1' then
           if sCounterRAM = 8 then
                spi_data_miso <= RAM_DATA(15 downto 8);
                sRead_data <='0';
            elsif sCounterRAM = 9 then
                spi_miso_valid <= '1';
            end if;

        end if;


           
    end if;

    if sEEPointerReset = '1' then    -- reset pointer from SPI order
        sRAM_pointer_write<= (others => '0');
        sRAM_pointer_read<= (others => '0');
	end if;
    
    spi_mosi_ready_prev3<= spi_mosi_ready_prev2;
    spi_mosi_ready_prev2<= spi_mosi_ready_prev;
    spi_mosi_ready_prev<= spi_mosi_ready;




end if;
end process;


sRAM_nWE<= sADC_clk when sACQtime = '1' else '1';



----------------------end RAM--------------------

----------------------Buttons toggle mode--------------------

process(pll_clk64, reset)
begin
if reset = '0' then

        sSingleCont <= '0';
elsif rising_edge(pll_clk64) then


    if button_mode = '1' then
        button_debounce_counter <= button_debounce_counter + 1;
    else
        button_debounce_counter <= X"000000";
    end if;


    if button_debounce_counter = X"FFFFFF" then
        sbuttonModeStatus <= not sbuttonModeStatus;
    end if;

    sSingleCont <= sbuttonModeStatus xor sEESingleCont;


end if;
end process;


----------------------end Button--------------------



----------------------Logic--------------------

--reset
--reset <= '0' when (reset_alim = '0' or reset_ft = '1' or reset_rpi = '1') else '1'; -- normal behavior
reset <= '0' when (reset_rpi = '0') else '1'; -- to do not take into account the power supply Master reset component

--communication spi
spi_sclk <= spi_sclk_rpi when spi_select = '1' else spi_sclk_ft;
spi_mosi <= spi_mosi_rpi when spi_select = '1' else spi_mosi_ft;
spi_miso_rpi <= spi_miso when (spi_select = '1' and cs_rpi2flash = '0') else
                spi_miso_flash when (spi_select = '1' and cs_rpi2flash = '1') else
                '0';
spi_miso_ft <= spi_miso when spi_select = '0' else '0';
spi_cs <= spi_cs_rpi when spi_select = '1' else spi_cs_ft;


-- Rpi Flash link
spi_sclk_flash <= spi_sclk_rpi when cs_rpi2flash = '1' else '0';
spi_mosi_flash <= spi_mosi_rpi when cs_rpi2flash = '1' else '0';
spi_cs_flash <= spi_cs_rpi when cs_rpi2flash = '1' else '0';

--trig
trig <= '1' when (trig_ext = '1' or trig_rpi = '1' or trig_ft = '1') else '0';



----------------------End Logic--------------------


----------------------outputs---------------------


nrst <= not reset;
pon <= sPon;
poff <= sPoff;
DAC_sclk <= sDAC_sclk;
DAC_cs <= sDAC_CSarray(0);
DAC_mosi <= sDAC_mosi;
ADC_clk <= sADC_clk;
RAM_nUB  <= '0';--sRAM_nUB;
RAM_nLB  <= '0';--sRAM_nLB;
RAM_nWE  <= sRAM_nWE;
RAM_nOE  <= '0';--sRAM_nOE;
RAM_nCE  <= '0';--sRAM_nCE;
RAM_ADD <= sRAM_ADD;
LED_ACQ <= sACQ;
LED_MODE <=sSingleCont;
LED3 <= '1' when reset='1' else '0';




end Behavioral;
