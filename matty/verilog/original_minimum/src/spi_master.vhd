
---------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity spi_master is
    generic(
        DATA_SIZE      :     integer := 16;
	FIFO_REQ       :     Boolean := False);
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
end spi_master;

architecture spi_master_rtl of spi_master is

    component sclk_gen
        generic(
            DATA_SIZE      :     integer);
        port(
            i_sys_clk      : in  std_logic;
            i_sys_rst      : in  std_logic;
            i_spi_start    : in  std_logic;
            i_clk_period   : in  std_logic_vector(7 downto 0);
            i_setup_cycles : in  std_logic_vector(7 downto 0);
            i_hold_cycles  : in  std_logic_vector(7 downto 0);
            i_tx2tx_cycles : in  std_logic_vector(7 downto 0);
            i_cpol         : in  std_logic;
            o_ss_start     : out std_logic;
            o_sclk         : out std_logic
            );
    end component;

    component spi_data_path
        generic(
            DATA_SIZE   :     integer;
	    FIFO_REQ    :     Boolean);
        port (
            i_sys_clk   : in  std_logic;  -- system clock
            i_sys_rst   : in  std_logic;  -- system reset
            i_csn       : in  std_logic;  -- Master Enable/select
            i_data      : in  std_logic_vector(16 - 1 downto 0);  -- Input data
            i_wr        : in  std_logic;  -- Active Low Write, Active High Read
            i_rd        : in  std_logic;  -- Active Low Write, Active High Read
            i_spi_start : in  std_logic;
            o_data      : out std_logic_vector(16 - 1 downto 0);  --output data
            o_tx_ready  : out std_logic;  -- Transmitter ready, can write another 
  					-- data
            o_rx_ready  : out std_logic;  -- Receiver ready, can read data
            o_tx_error  : out std_logic;  -- Transmitter error
            o_rx_error  : out std_logic;  -- Receiver error

            i_cpol      : in  std_logic;  -- CPOL value - 0 or 1
            i_cpha      : in  std_logic;  -- CPHA value - 0 or 1 
            i_lsb_first : in  std_logic;  -- lsb first when '1' /msb first when 
  					  -- '0'
            o_intr      : out std_logic;
            o_mosi      : out std_logic;  -- Master output to Slave
            i_miso      : in  std_logic;  -- Master input from Slave
            i_ssn       : in  std_logic;  -- Slave Slect Active low
            i_sclk      : in  std_logic;  -- Clock from SPI Master
            mosi_tri_en : out std_logic
            );

    end component;

    signal sclk_i     : std_logic;
    signal ss_start_i : std_logic;


begin

    o_sclk <= sclk_i;

    process (i_sys_clk, i_sys_rst)
    begin
        if i_sys_rst = '1' then
            o_slave_csn         <= (others => '1');
        elsif rising_edge(i_sys_clk) then
            case (i_slave_addr) is
                when "00"                  =>
                    o_slave_csn <= "111" & ss_start_i;
                when "01"                  =>
                    o_slave_csn <= "11" & ss_start_i & '1';
                when "10"                  =>
                    o_slave_csn <= '1' & ss_start_i & "11";
                when "11"                  =>
                    o_slave_csn <= ss_start_i & "111";
                when others                =>
                    o_slave_csn <= "1111";
            end case;
        end if;
    end process;

    sclk_gen_u0 : sclk_gen
        generic map(
            DATA_SIZE      => DATA_SIZE)
        port map(
            i_sys_clk      => i_sys_clk,
            i_sys_rst      => i_sys_rst,
            i_spi_start    => i_spi_start,
            i_clk_period   => i_clk_period,
            i_setup_cycles => i_setup_cycles,
            i_hold_cycles  => i_hold_cycles,
            i_tx2tx_cycles => i_tx2tx_cycles,
            i_cpol         => i_cpol,
            o_ss_start     => ss_start_i,
            o_sclk         => sclk_i
            );

    spi_data_path_u1 : spi_data_path
        generic map(
            DATA_SIZE   => DATA_SIZE,
	    FIFO_REQ    => FIFO_REQ)
        port map(
            i_sys_clk   => i_sys_clk,
            i_sys_rst   => i_sys_rst,
            i_csn       => i_csn,
            i_data      => i_data,
            i_wr        => i_wr,
            i_rd        => i_rd,
            i_spi_start => i_spi_start,
            o_data      => o_data,
            o_tx_ready  => o_tx_ready,
            o_rx_ready  => o_rx_ready,
            o_tx_error  => o_tx_error,
            o_rx_error  => o_rx_error,
            o_intr      => o_intr,
            i_cpol      => i_cpol,
            i_cpha      => i_cpha,
            i_lsb_first => i_lsb_first,
            o_mosi      => o_mosi,
            i_miso      => i_miso,
            i_ssn       => ss_start_i,
            i_sclk      => sclk_i,
            mosi_tri_en => mosi_tri_en
            );

end spi_master_rtl;
