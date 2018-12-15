library IEEE;
use IEEE.std_logic_1164.all;

entity pll128M2 is
port(
      REFERENCECLK: in std_logic;
      RESET: in std_logic;
      PLLOUTCOREA: out std_logic;
      PLLOUTCOREB: out std_logic;
      PLLOUTGLOBALA: out std_logic;
      PLLOUTGLOBALB: out std_logic
    );
end entity pll128M2;

architecture BEHAVIOR of pll128M2 is
signal openwire : std_logic;
signal openwirebus : std_logic_vector (7 downto 0);
component SB_PLL40_2F_CORE
  generic (
       		--- Feedback
		FEEDBACK_PATH	 		 : string := "SIMPLE"; -- String (simple, delay, phase_and_delay, external)
		DELAY_ADJUSTMENT_MODE_FEEDBACK 	 : string := "FIXED"; 
		DELAY_ADJUSTMENT_MODE_RELATIVE 	 : string := "FIXED"; 
		SHIFTREG_DIV_MODE 		: bit_vector(1 downto 0)	:= "00"; 	 --  0-->Divide by 4, 1-->Divide by 7, 3 -->Divide by 5	
	  	FDA_FEEDBACK 			: bit_vector(3 downto 0) 	:= "0000"; 	 --  Integer (0-15). 
		FDA_RELATIVE 			: bit_vector(3 downto 0)	:= "0000"; 	 --  Integer (0-15).
		PLLOUT_SELECT_PORTA		 : string := "GENCLK";
		PLLOUT_SELECT_PORTB		 : string := "GENCLK";

  		--- Use the spread sheet to populate the values below
		DIVF				: bit_vector(6 downto 0);  -- Determine a good default value
		DIVR				: bit_vector(3 downto 0);  -- Determine a good default value
		DIVQ				: bit_vector(2 downto 0);  -- Determine a good default value
		FILTER_RANGE			: bit_vector(2 downto 0);  -- Determine a good default value

  		--- Additional C-Bits
  		ENABLE_ICEGATE_PORTA		: bit				:= '0';
  		ENABLE_ICEGATE_PORTB		: bit				:= '0';

  		--- Test Mode Parameter 
		TEST_MODE			: bit := '0';
		EXTERNAL_DIVIDE_FACTOR		: integer := 1 -- Not Used by model, Added for PLL config GUI
       );
  port (
        REFERENCECLK		: in std_logic;			    -- Driven by core logic
        PLLOUTCOREA			: out std_logic;		    -- PLL output to core logic
        PLLOUTGLOBALA		: out std_logic;		    -- PLL output to global network
        PLLOUTCOREB			: out std_logic;		    -- PLL output to core logic
        PLLOUTGLOBALB		: out std_logic;		    -- PLL output to global network
        EXTFEEDBACK		: in std_logic;			    -- Driven by core logic
        DYNAMICDELAY		: in std_logic_vector (7 downto 0); -- Driven by core logic
        LOCK				: out std_logic;	 	    -- Output of PLL
        BYPASS			: in std_logic;			    -- Driven by core logic
        RESETB			: in std_logic;			    -- Driven by core logic
        LATCHINPUTVALUE		: in std_logic;			    -- iCEGate Signal
        -- Test Pins
        SDO			: out std_logic;				-- Output of PLL
        SDI			: in std_logic;					-- Driven by core logic
        SCLK			: in std_logic					-- Driven by core logic
       );
end component;
begin
pll128M2_inst: SB_PLL40_2F_CORE
-- Fin=12, Fout=128
generic map(
             DIVR => "0000",
             DIVF => "1010100",
             DIVQ => "011",
             FILTER_RANGE => "001",
             FEEDBACK_PATH => "SIMPLE",
             DELAY_ADJUSTMENT_MODE_FEEDBACK => "FIXED",
             FDA_FEEDBACK => "0000",
             DELAY_ADJUSTMENT_MODE_RELATIVE => "FIXED",
             FDA_RELATIVE => "0000",
             SHIFTREG_DIV_MODE => "00",
             PLLOUT_SELECT_PORTA => "GENCLK",
             PLLOUT_SELECT_PORTB => "GENCLK_HALF",
             ENABLE_ICEGATE_PORTA => '0',
             ENABLE_ICEGATE_PORTB => '0'
           )
port map(
          REFERENCECLK => REFERENCECLK,
          PLLOUTCOREA => PLLOUTCOREA,
          PLLOUTCOREB => PLLOUTCOREB,
          PLLOUTGLOBALA => PLLOUTGLOBALA,
          PLLOUTGLOBALB => PLLOUTGLOBALB,
          EXTFEEDBACK => openwire,
          DYNAMICDELAY => openwirebus,
          RESETB => RESET,
          BYPASS => '0',
          LATCHINPUTVALUE => openwire,
          LOCK => open,
          SDI => openwire,
          SDO => open,
          SCLK => openwire
        );

end BEHAVIOR;

--uiPll40ModuleData
--PllType: SB_PLL40_2F_CORE
--PllModuleName: pll128M2
--PllInstanceName: pll128M2_inst
--DIVR: 0000
--DIVF: 1010100
--DIVQ: 011
--FILTER_RANGE: 001
--FEEDBACK_PATH: SIMPLE
--EXTERNAL_DIVIDE_FACTOR: 1
--DELAY_ADJUSTMENT_MODE_FEEDBACK: 
--DELAY_ADJUSTMENT_MODE_RELATIVE: FIXED
--FIXED_DELAY_ADJUSTMENT_FEEDBACK: 0
--FIXED_DELAY_ADJUSTMENT_RELATIVE: 0
--SHIFTREG_DIV_MODE: 00
--PLLOUT_SELECT: GENCLK
--PLLOUT_SELECT_PORTA: GENCLK
--PLLOUT_SELECT_PORTB: GENCLK_HALF
--ENABLE_ICEGATE: false
--ENABLE_ICEGATE_PORTA: false
--ENABLE_ICEGATE_PORTB: false
--TEST_MODE: 
--RESET: true
--BYPASS: false
--LATCHINPUTVALUE: false
--LOCK: false
--InputFrequency: 12
--OutputFrequency: 128
