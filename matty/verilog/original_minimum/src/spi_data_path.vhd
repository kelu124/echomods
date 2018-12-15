
---------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity spi_data_path is
    generic(
        DATA_SIZE   :     integer;
        FIFO_REQ    :     Boolean);
    port (
        i_sys_clk   : in  std_logic;  			  -- system clock
        i_sys_rst   : in  std_logic;  			  -- system reset
        i_csn       : in  std_logic;  			  -- Master Enable/select
        i_data      : in  std_logic_vector(15 downto 0);  -- Input data
        i_wr        : in  std_logic;  			  -- Active Low Write, Active High Read
        i_rd        : in  std_logic;  			  -- Active Low Write, Active High Read
        i_spi_start : in  std_logic;
        o_data      : out std_logic_vector(15 downto 0);  --output data
        o_tx_ready  : out std_logic;  			  -- Transmitter ready, can write another 
  							  -- data
        o_rx_ready  : out std_logic;  			  -- Receiver ready, can read data
        o_tx_error  : out std_logic;  			  -- Transmitter error
        o_rx_error  : out std_logic;  			  -- Receiver error

        i_cpol      : in  std_logic;  	-- CPOL value - 0 or 1
        i_cpha      : in  std_logic;  	-- CPHA value - 0 or 1 
        i_lsb_first : in  std_logic;  	-- lsb first when '1' /msb first when 
  					-- '0'
        o_intr      : out std_logic;
        o_mosi      : out std_logic;  	-- Master output to Slave
        i_miso      : in  std_logic;  	-- Master input from Slave
        i_ssn       : in  std_logic;  	-- Slave Slect Active low
        i_sclk      : in  std_logic;  	-- Clock from SPI Master
        mosi_tri_en : out std_logic
        );

end spi_data_path;

architecture rtl_arch of spi_data_path is

    component asyn_fifo
        generic (
            DATA_SIZE     :     integer;
            ADDRESS_WIDTH :     integer);
        port (
            i_rst         : in  std_logic;
            i_rd_clk      : in  std_logic;
            i_rd_en       : in  std_logic;
            o_rd_data     : out std_logic_vector(15 downto 0);
            o_empty       : out std_logic;
            i_wr_clk      : in  std_logic;
            i_wr_en       : in  std_logic;
            i_wr_data     : in  std_logic_vector(15 downto 0);
            o_half_full   : out std_logic;
            o_full        : out std_logic
            );
    end component;

    signal data_in_reg_i            : std_logic_vector(DATA_SIZE - 1 downto 0);
    signal data_in                  : std_logic_vector(DATA_SIZE - 1 downto 0);
    signal rxdata_reg_i             : std_logic_vector(DATA_SIZE - 1 downto 0);
    signal txdata_reg_i             : std_logic_vector(DATA_SIZE - 1 downto 0);
    signal rx_shift_data_pos_sclk_i : std_logic_vector(DATA_SIZE - 1 downto 0);
    signal rx_shift_data_neg_sclk_i : std_logic_vector(DATA_SIZE - 1 downto 0);
    signal tx_error_i               : std_logic;
    signal rx_error_i               : std_logic;
    signal tx_ready_i               : std_logic;
    signal rx_ready_i               : std_logic;
    signal rx_fifo_rd_en_i          : std_logic;
    signal RxFifoEmpty_i            : std_logic;
    signal rx_fifo_wr_en_i          : std_logic;
    signal ReadHalfFull_i           : std_logic;
    signal RxFifoFull_i             : std_logic;
    signal tx_fifo_rd_en_i          : std_logic;
    signal TxFifoEmpty_i            : std_logic;
    signal tx_fifo_wr_en_i          : std_logic;
    signal TxFifoHalfFull_i         : std_logic;
    signal TxFifoFull_i             : std_logic;
    signal d1_TxReady_i             : std_logic;
    signal d2_TxReady_i             : std_logic;
    signal d1_RxReady_i             : std_logic;
    signal d2_RxReady_i             : std_logic;
    signal mosi_00_i                : std_logic;
    signal mosi_01_i                : std_logic;
    signal mosi_10_i                : std_logic;
    signal mosi_11_i                : std_logic;
    signal rx_done_pos_sclk_i       : std_logic;
    signal rx_done_neg_sclk_i       : std_logic;
    signal rx_done_reg1_i           : std_logic;
    signal rx_done_reg2_i           : std_logic;
    signal rx_done_reg3_i           : std_logic;
    signal tx_done_pos_sclk_i       : std_logic;
    signal tx_done_neg_sclk_i       : std_logic;
    signal tx_done_reg1_i           : std_logic;
    signal tx_done_reg2_i           : std_logic;
    signal tx_done_reg3_i           : std_logic;
    signal rx_data_count_pos_sclk_i : std_logic_vector(5 downto 0);
    signal rx_data_count_neg_sclk_i : std_logic_vector(5 downto 0);
    signal tx_data_count_pos_sclk_i : std_logic_vector(5 downto 0);
    signal tx_data_count_neg_sclk_i : std_logic_vector(5 downto 0);
    signal dummy_i                  : std_logic_vector(7 downto 0);
    signal dummy_rd                 : std_logic_vector(7 downto 0) := (others => '0');

begin

    read_fifo_1  : if FIFO_REQ = True and  DATA_SIZE = 8 generate
        u_RxFifo : asyn_fifo
            generic map (
                DATA_SIZE              => 16,
                ADDRESS_WIDTH          => 4)
            port map (
                i_rst                  => i_sys_rst,
                i_rd_clk               => i_sys_clk,
                i_rd_en                => rx_fifo_rd_en_i,
                o_rd_data              => o_data,
                o_empty                => RxFifoEmpty_i,
                i_wr_clk               => i_sys_clk,
                i_wr_en                => rx_fifo_wr_en_i,
                i_wr_data(7 downto 0)  => rxdata_reg_i,
                i_wr_data(15 downto 8) => dummy_rd,
                o_half_full            => ReadHalfFull_i,
                o_full                 => RxFifoFull_i
                );
    end generate read_fifo_1;

    read_fifo_2  : if FIFO_REQ = True and DATA_SIZE = 16 generate
        u_RxFifo : asyn_fifo
            generic map (
                DATA_SIZE     => 16,
                ADDRESS_WIDTH => 4)
            port map (
                i_rst         => i_sys_rst,
                i_rd_clk      => i_sys_clk,
                i_rd_en       => rx_fifo_rd_en_i,
                o_rd_data     => o_data,
                o_empty       => RxFifoEmpty_i,
                i_wr_clk      => i_sys_clk,
                i_wr_en       => rx_fifo_wr_en_i,
                i_wr_data     => rxdata_reg_i,
                o_half_full   => ReadHalfFull_i,
                o_full        => RxFifoFull_i
                );
    end generate read_fifo_2;


    ------------------------------------------------------------------------------------------------
    -- Write Fifo 
    ------------------------------------------------------------------------------------------------
    write_fifo_1 : if FIFO_REQ = True and DATA_SIZE = 8 generate
        u_TxFifo : asyn_fifo
            generic map (
                DATA_SIZE              => 16,
                ADDRESS_WIDTH          => 4)
            port map (
                i_rst                  => i_sys_rst,
                i_rd_clk               => i_sys_clk,
                i_rd_en                => tx_fifo_rd_en_i,
                o_rd_data(7 downto 0)  => data_in_reg_i,
                o_rd_data(15 downto 8) => dummy_i,
                o_empty                => TxFifoEmpty_i,
                i_wr_clk               => i_sys_clk,
                i_wr_en                => tx_fifo_wr_en_i,
                i_wr_data              => i_data,
                o_half_full            => TxFifoHalfFull_i,
                o_full                 => TxFifoFull_i
                );
    end generate write_fifo_1;

    write_fifo_2 : if FIFO_REQ = True and DATA_SIZE = 16 generate
        u_TxFifo : asyn_fifo
            generic map (
                DATA_SIZE     => 16,
                ADDRESS_WIDTH => 4)
            port map (
                i_rst         => i_sys_rst,
                i_rd_clk      => i_sys_clk,
                i_rd_en       => tx_fifo_rd_en_i,
                o_rd_data     => data_in_reg_i,
                o_empty       => TxFifoEmpty_i,
                i_wr_clk      => i_sys_clk,
                i_wr_en       => tx_fifo_wr_en_i,
                i_wr_data     => i_data,
                o_half_full   => TxFifoHalfFull_i,
                o_full        => TxFifoFull_i
                );
    end generate write_fifo_2;

    o_tx_ready <= tx_ready_i;
    o_rx_ready <= rx_ready_i;
    o_tx_error <= tx_error_i;
    o_rx_error <= rx_error_i;

    mosi_tri_en             <= i_ssn;
    
    output_data_16 : if FIFO_REQ = False and DATA_SIZE = 16 generate
        o_data              <= rxdata_reg_i;
    end generate output_data_16;
    
    output_data_8  : if FIFO_REQ = False and DATA_SIZE = 8 generate
        o_data(7 downto 0)  <= rxdata_reg_i;
        o_data(15 downto 8) <= (others => '0');
    end generate output_data_8;
----------------------------------------------------------------------------------------------------
-- Data input latch process
-- Latched only when slave enabled, Transmitter ready and wr is high.
----------------------------------------------------------------------------------------------------
    process(i_sys_clk, i_sys_rst)
    begin
        if(i_sys_rst = '1') then
            data_in         <= (others => '0');
        elsif rising_edge(i_sys_clk) then
            if FIFO_REQ = False and DATA_SIZE = 8 then
                if (i_wr = '1' and i_csn = '0' and tx_ready_i = '1') then
                    data_in <= i_data(7 downto 0);
                end if;
            elsif FIFO_REQ = False and DATA_SIZE = 16 then
                if (i_wr = '1' and i_csn = '0' and tx_ready_i = '1') then
                    data_in <= i_data;
                end if;
            end if;
        end if;
    end process;

----------------------------------------------------------------------------------------------------
-- Tx FIFO write enable signal generated when write is high and cs is low
----------------------------------------------------------------------------------------------------
    process(i_sys_clk, i_sys_rst)
    begin
        if(i_sys_rst = '1') then
            tx_fifo_wr_en_i         <= '0';
        elsif rising_edge(i_sys_clk) then
            if FIFO_REQ = True then
                if (i_wr = '1' and i_csn = '0') then
                    tx_fifo_wr_en_i <= '1';
                else
                    tx_fifo_wr_en_i <= '0';
                end if;
            end if;
        end if;
    end process;
----------------------------------------------------------------------------------------------------
-- Rx FIFO read enable signal generated when read is high and cs is low
----------------------------------------------------------------------------------------------------
    process(i_sys_clk, i_sys_rst)
    begin
        if(i_sys_rst = '1') then
            rx_fifo_rd_en_i         <= '0';
        elsif rising_edge(i_sys_clk) then
            if FIFO_REQ = True then
                if (i_rd = '1' and i_csn = '0') then
                    rx_fifo_rd_en_i <= '1';
                else
                    rx_fifo_rd_en_i <= '0';
                end if;
            end if;
        end if;
    end process;

    Tx_Ready_Pulse_proc : process (i_sys_clk, i_sys_rst)
    begin  -- process Ready_Pulse_proc
        if i_sys_rst = '1' then  			-- asynchronous reset (active high)
            d1_TxReady_i <= '0';
            d2_TxReady_i <= '0';
        elsif i_sys_clk'event and i_sys_clk = '1' then  -- rising clock edge
            d1_TxReady_i <= tx_ready_i and i_spi_start;
            d2_TxReady_i <= d1_TxReady_i;
        end if;
    end process Tx_Ready_Pulse_proc;

    tx_fifo_rd_en_i <= d1_TxReady_i and (not d2_TxReady_i);

    Rx_Ready_Pulse_proc : process (i_sys_clk, i_sys_rst)
    begin  -- process Ready_Pulse_proc
        if i_sys_rst = '1' then  			-- asynchronous reset (active high)
            d1_RxReady_i <= '0';
            d2_RxReady_i <= '0';
        elsif i_sys_clk'event and i_sys_clk = '1' then  -- rising clock edge
            d1_RxReady_i <= rx_ready_i;
            d2_RxReady_i <= d1_RxReady_i;
        end if;
    end process Rx_Ready_Pulse_proc;

    rx_fifo_wr_en_i <= d1_RxReady_i and (not d2_RxReady_i);

----------------------------------------------------------------------------------------------------
-- Receive Data Register, mux it based on sampling
-- Data latched based on Rx Done signal
----------------------------------------------------------------------------------------------------
    process(i_sys_clk, i_sys_rst)
    begin
        if(i_sys_rst = '1') then
            rxdata_reg_i         <= (others => '0');
        elsif rising_edge(i_sys_clk) then
            if (rx_done_reg1_i = '1' and rx_done_reg2_i = '0') then
                if ((i_cpol = '0' and i_cpha = '0') or (i_cpol = '1' and i_cpha = '1')) then
                    rxdata_reg_i <= rx_shift_data_pos_sclk_i;
                else
                    rxdata_reg_i <= rx_shift_data_neg_sclk_i;
                end if;
            end if;
        end if;
    end process;

---------------------------------------------------------------------------------------------------
-- Re-register data to be transmitted
----------------------------------------------------------------------------------------------------
    process(i_sys_clk, i_sys_rst)
    begin
        if(i_sys_rst = '1') then
            txdata_reg_i     <= (others => '0');
        elsif rising_edge(i_sys_clk) then
            if FIFO_REQ = True then
                txdata_reg_i <= data_in_reg_i;
            else
                txdata_reg_i <= data_in;
            end if;

        end if;
    end process;

----------------------------------------------------------------------------
-- SPI Slave Receiver Section  		---------------------------------------------
----------------------------------------------------------------------------
----------------------------------------------------------------------------
--- MOSI Sampling : Sample at posedge of SCLK for 
--                  1. i_cpol=0 and i_cpha=0 
--                  2. i_cpol=1 and i_cpha=1 
----------------------------------------------------------------------------
    process(i_sclk, i_sys_rst)
    begin
        if (i_sys_rst = '1') then
            rx_shift_data_pos_sclk_i         <= (others => '0');
        elsif rising_edge(i_sclk) then
            if (i_ssn = '0' and ((i_cpol = '0' and i_cpha = '0') or (i_cpol = '1' and i_cpha = '1'))) then
                if (i_lsb_first = '1') then
                    rx_shift_data_pos_sclk_i <= i_miso & rx_shift_data_pos_sclk_i(DATA_SIZE-1 downto 1);
                else
                    rx_shift_data_pos_sclk_i <= rx_shift_data_pos_sclk_i(DATA_SIZE-2 downto 0) & i_miso;
                end if;
            end if;
        end if;
    end process;

    process(i_sclk, i_sys_rst)
    begin
        if (i_sys_rst = '1') then
            rx_data_count_pos_sclk_i         <= (others => '0');
            rx_done_pos_sclk_i               <= '0';
        elsif rising_edge(i_sclk) then
            if (i_ssn = '0' and ((i_cpol = '0' and i_cpha = '0') or (i_cpol = '1' and i_cpha = '1'))) then
                if (rx_data_count_pos_sclk_i = DATA_SIZE - 1) then
                    rx_data_count_pos_sclk_i <= (others => '0');
                    rx_done_pos_sclk_i       <= '1';
                elsif (i_ssn = '0') then
                    rx_data_count_pos_sclk_i <= rx_data_count_pos_sclk_i + 1;
                    rx_done_pos_sclk_i       <= '0';
                end if;
            end if;
        end if;
    end process;

----------------------------------------------------------------------------
--- MOSI Sampling : Sample at negedge of SCLK for
-- 1. i_cpol=1 and i_cpha=0
-- 2. i_cpol=0 and i_cpha=1
----------------------------------------------------------------------------
    process(i_sclk, i_sys_rst)
    begin
        if (i_sys_rst = '1') then
            rx_shift_data_neg_sclk_i         <= (others => '0');
        elsif falling_edge(i_sclk) then
            if (i_ssn = '0' and ((i_cpol = '1' and i_cpha = '0') or (i_cpol = '0' and i_cpha = '1'))) then
                if (i_lsb_first = '1') then
                    rx_shift_data_neg_sclk_i <= i_miso & rx_shift_data_neg_sclk_i(DATA_SIZE-1 downto 1);
                else
                    rx_shift_data_neg_sclk_i <= rx_shift_data_neg_sclk_i(DATA_SIZE-2 downto 0) & i_miso;
                end if;
            end if;
        end if;
    end process;

    process(i_sclk, i_sys_rst)
    begin
        if (i_sys_rst = '1') then
            rx_data_count_neg_sclk_i     <= (others => '0');
            rx_done_neg_sclk_i           <= '0';
        elsif falling_edge(i_sclk) then
            if (rx_data_count_neg_sclk_i = DATA_SIZE - 1) then
                rx_data_count_neg_sclk_i <= (others => '0');
                rx_done_neg_sclk_i       <= '1';
            elsif (i_ssn = '0') then
                rx_data_count_neg_sclk_i <= rx_data_count_neg_sclk_i + 1;
                rx_done_neg_sclk_i       <= '0';
            end if;
        end if;
    end process;


----------------------------------------------------------------------------
-- SPI Master Receiver Receive Done signal generator
-- This is based on CPOL and CPHA
----------------------------------------------------------------------------
    process(i_sys_clk, i_sys_rst)
    begin
        if (i_sys_rst = '1') then
            rx_done_reg1_i     <= '0';
            rx_done_reg2_i     <= '0';
            rx_done_reg3_i     <= '0';
        elsif rising_edge(i_sys_clk) then
            if (i_ssn = '0' and ((i_cpol = '0' and i_cpha = '0') or (i_cpol = '1' and i_cpha = '1'))) then
                rx_done_reg1_i <= rx_done_pos_sclk_i;
            else
                rx_done_reg1_i <= rx_done_neg_sclk_i;
            end if;
            rx_done_reg2_i     <= rx_done_reg1_i;
            rx_done_reg3_i     <= rx_done_reg2_i;
        end if;
    end process;
----------------------------------------------------------------------------------------------------
-- Receiver ready at the end of reception.
-- A valid receive data available at this time
----------------------------------------------------------------------------------------------------

    process(i_sys_clk, i_sys_rst)
    begin
        if (i_sys_rst = '1') then
            rx_ready_i     <= '0';
        elsif rising_edge(i_sys_clk) then
            if (rx_done_reg2_i = '1' and rx_done_reg3_i = '0') then
                rx_ready_i <= '1';
            elsif (i_rd = '1' and i_csn = '0') then
                rx_ready_i <= '0';
            end if;
        end if;
    end process;
----------------------------------------------------------------------------------------------------
-- Receive error when external interface hasn't read previous data
-- A new data received, but last received data hasn't been read yet.
----------------------------------------------------------------------------------------------------
    process(i_sys_clk, i_sys_rst)
    begin
        if (i_sys_rst = '1') then
            rx_error_i     <= '0';
        elsif rising_edge(i_sys_clk) then
            if (rx_done_reg2_i = '1' and rx_done_reg3_i = '0' and rx_ready_i = '1') then
                rx_error_i <= '1';
            elsif (i_rd = '1' and i_csn = '0') then
                rx_error_i <= '0';
            end if;
        end if;
    end process;
----------------------------------------------------------------------------
-- SPI Master Transmitter section  				      ----
----------------------------------------------------------------------------
----------------------------------------------------------------------------
-- cpol=0 and cpha=0: data must be placed before rising edge of sclk  -------
----------------------------------------------------------------------------

    process(txdata_reg_i, tx_data_count_neg_sclk_i, i_lsb_first)
    begin
        if(i_lsb_first = '1') then
            mosi_00_i <= txdata_reg_i(conv_integer(tx_data_count_neg_sclk_i));
        else
            mosi_00_i <= txdata_reg_i(conv_integer(DATA_SIZE-tx_data_count_neg_sclk_i-1));
        end if;
    end process;


----------------------------------------------------------------------------
-- cpol=1 and cpha=0: data must be placed before falling edge of sclk  -------
----------------------------------------------------------------------------

    process(txdata_reg_i, tx_data_count_pos_sclk_i, i_lsb_first)
    begin
        if(i_lsb_first = '1') then
            mosi_10_i <= txdata_reg_i(conv_integer(tx_data_count_pos_sclk_i));
        else
            mosi_10_i <= txdata_reg_i(conv_integer(DATA_SIZE-tx_data_count_pos_sclk_i-1));
        end if;
    end process;

----------------------------------------------------------------------------
-- cpol=0 and cpha=1: data must be placed at rising edge of sclk  -------
----------------------------------------------------------------------------
    process (i_sclk, i_sys_rst)
    begin
        if i_sys_rst = '1' then
            mosi_01_i     <= '1';
        elsif rising_edge(i_sclk) then
            if(i_lsb_first = '1') then
                mosi_01_i <= txdata_reg_i(conv_integer(tx_data_count_pos_sclk_i));
            else
                mosi_01_i <= txdata_reg_i(conv_integer(DATA_SIZE-tx_data_count_pos_sclk_i-1));
            end if;
        end if;
    end process;

----------------------------------------------------------------------------
-- cpol=1 and cpha=1: data must be placed at falling edge of sclk  -------
----------------------------------------------------------------------------

    process (i_sclk, i_sys_rst)
    begin
        if i_sys_rst = '1' then
            mosi_11_i     <= '1';
        elsif falling_edge(i_sclk) then
            if(i_lsb_first = '1') then
                mosi_11_i <= txdata_reg_i(conv_integer(tx_data_count_neg_sclk_i));
            else
                mosi_11_i <= txdata_reg_i(conv_integer(DATA_SIZE-tx_data_count_neg_sclk_i-1));
            end if;
        end if;
    end process;

----------------------------------------------------------------------------
-- Tx count on falling edge of sclk for cpol=0 and cpha=0  -------
-- and cpol=1 and cpha=1  				   -------
----------------------------------------------------------------------------
    process(i_sclk, i_sys_rst)
    begin
        if (i_sys_rst = '1') then
            tx_data_count_neg_sclk_i     <= (others => '0');
            tx_done_neg_sclk_i           <= '0';
        elsif falling_edge(i_sclk) then
            if (tx_data_count_neg_sclk_i = DATA_SIZE - 1) then
                tx_data_count_neg_sclk_i <= (others => '0');
                tx_done_neg_sclk_i       <= '1';
            elsif (i_ssn = '0') then
                tx_data_count_neg_sclk_i <= tx_data_count_neg_sclk_i + 1;
                tx_done_neg_sclk_i       <= '0';
            end if;
        end if;
    end process;


----------------------------------------------------------------------------
-- Tx count on rising edge of sclk for cpol=1 and cpha=0  -------
-- and cpol=0 and cpha=1  				  -------
----------------------------------------------------------------------------
    process(i_sclk, i_sys_rst)
    begin
        if (i_sys_rst = '1') then
            tx_data_count_pos_sclk_i     <= (others => '0');
            tx_done_pos_sclk_i           <= '0';
        elsif rising_edge(i_sclk) then
            if (tx_data_count_pos_sclk_i = DATA_SIZE - 1) then
                tx_data_count_pos_sclk_i <= (others => '0');
                tx_done_pos_sclk_i       <= '1';
            elsif (i_ssn = '0') then
                tx_data_count_pos_sclk_i <= tx_data_count_pos_sclk_i + 1;
                tx_done_pos_sclk_i       <= '0';
            end if;
        end if;
    end process;

    process(i_ssn, i_cpol, i_cpha, mosi_00_i, mosi_01_i, mosi_10_i, mosi_11_i)
    begin
        if (i_ssn = '0') then
            if (i_cpol = '0' and i_cpha = '0') then
                o_mosi <= mosi_00_i;
            elsif (i_cpol = '0' and i_cpha = '1') then
                o_mosi <= mosi_01_i;
            elsif (i_cpol = '1' and i_cpha = '0') then
                o_mosi <= mosi_10_i;
            else
                o_mosi <= mosi_11_i;
            end if;
        else
            o_mosi     <= '0';
        end if;
    end process;

----------------------------------------------------------------------------------------------------
-- Transmit done generation
-- Muxed based on CPOL and CPHA
----------------------------------------------------------------------------------------------------
    process(i_sys_clk, i_sys_rst)
    begin
        if (i_sys_rst = '1') then
            tx_done_reg1_i     <= '0';
            tx_done_reg2_i     <= '0';
            tx_done_reg3_i     <= '0';
        elsif rising_edge(i_sys_clk) then
            if (i_cpol = '0' and i_cpha = '0') or (i_cpol = '1' and i_cpha = '1') then
                tx_done_reg1_i <= tx_done_neg_sclk_i;
            else
                tx_done_reg1_i <= tx_done_pos_sclk_i;
            end if;
            tx_done_reg2_i     <= tx_done_reg1_i;
            tx_done_reg3_i     <= tx_done_reg2_i;
        end if;
    end process;

------------------------------------------------------------------------------------------------
-- Transmitter is ready at the end of Transmission
-- Transmitter ready goes low as soon as it gets a data byte/word
------------------------------------------------------------------------------------------------

    process(i_sys_clk, i_sys_rst)
    begin
        if (i_sys_rst = '1') then
            tx_ready_i     <= '1';
        elsif rising_edge(i_sys_clk) then
            if (i_spi_start = '1') then
                tx_ready_i <= '0';
            elsif (tx_done_reg2_i = '1' and tx_done_reg3_i = '0') then
                tx_ready_i <= '1';
            end if;
        end if;
    end process;

----------------------------------------------------------------------------------------------------
-- Transmitter error when a data is written while transmitter busy transmitting data
-- (busy when Tx Ready = 0)
----------------------------------------------------------------------------------------------------
    process(i_sys_clk, i_sys_rst)
    begin
        if (i_sys_rst = '1') then
            tx_error_i     <= '0';
        elsif rising_edge(i_sys_clk) then
            if(tx_ready_i = '0' and i_wr = '1' and i_csn = '0') then
                tx_error_i <= '1';
            elsif(i_wr = '1' and i_csn = '0') then
                tx_error_i <= '0';
            end if;
        end if;
    end process;

    ------------------------------------------------------------------------------------------------
    -- Interrupt generation logic
    ------------------------------------------------------------------------------------------------
    intr_gen_proc : process (i_sys_clk, i_sys_rst)
    begin  -- process intr_gen_proc
        if i_sys_rst = '1' then  			-- asynchronous reset (active high)
            o_intr     <= '0';
        elsif i_sys_clk'event and i_sys_clk = '1' then  -- rising clock edge
            if(tx_error_i = '1' or rx_error_i = '1' or tx_ready_i = '1' or rx_ready_i = '1'
               or RxFifoFull_i = '1' or TxFifoFull_i = '1')then
                o_intr <= '1';
            end if;
        end if;
    end process intr_gen_proc;

end rtl_arch;
