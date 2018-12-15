
---------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity sclk_gen is
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
end sclk_gen;

architecture count_arch of sclk_gen is

    signal clk_periodby2_i       : std_logic_vector(7 downto 0);
    signal sclk_period_i         : std_logic_vector(7 downto 0);
    signal sclk_count_i          : std_logic_vector(7 downto 0);
    signal delay_clk_i           : std_logic;
    signal div_clk_i             : std_logic;
    signal clk_falling_i         : std_logic;
    signal clk_rising_i          : std_logic;
    signal delay_count_start_i   : std_logic;
    signal tx2tx_delay_done_i    : std_logic;
    signal hold_delay_done_i     : std_logic;
    signal setup_delay_done_i    : std_logic;
    signal delay_count_i         : std_logic_vector(7 downto 0);
    signal falling_count_start_i : std_logic;
    signal clk_falling_count_i   : std_logic_vector(7 downto 0);
    signal spi_start_i           : std_logic;
    signal sclk_count_start_i    : std_logic;

    type spim_clk_states is (SPIM_IDLE_STATE, SPIM_SETUP_STATE,
                             SPIM_DATA_TX_STATE, SPIM_HOLD_STATE, SPIM_TX2TX_WAIT_STATE);
    signal spim_clk_state_i : spim_clk_states;


begin


    ------------------------------------------------------------------------------------------------
    -- Right shift by 1 to compute divide by 2 of clock period
    ------------------------------------------------------------------------------------------------
    clk_periodby2_i <= '0' & i_clk_period(7 downto 1);

----------------------------------------------------------------------------------------------------
-- SCLK generation - This a clock divider logic, which is enabled only when slave select is LOW.
----------------------------------------------------------------------------------------------------
    process (i_sys_clk, i_sys_rst)
    begin
        if i_sys_rst = '1' then
            sclk_count_i         <= "00000001";
            div_clk_i            <= '0';
        elsif rising_edge(i_sys_clk) then
            if sclk_count_start_i = '1' then
                if sclk_count_i < i_clk_period then
                    sclk_count_i <= sclk_count_i + 1;
                else
                    sclk_count_i <= "00000001";
                end if;
            else
                sclk_count_i     <= "00000010";
            end if;
            if sclk_count_i > clk_periodby2_i then
                div_clk_i        <= '0';
            else
                div_clk_i        <= '1';
            end if;
        end if;
    end process;
----------------------------------------------------------------------------------------------------
-- Delayed version of divided clock, used to generate falling/rising edge of generated clock
----------------------------------------------------------------------------------------------------
    process(i_sys_clk, i_sys_rst)
    begin
        if i_sys_rst = '1' then
            delay_clk_i          <= '0';
        elsif i_sys_clk'event and i_sys_clk = '1' then
            delay_clk_i          <= div_clk_i;
        end if;
    end process;
----------------------------------------------------------------------------------------------------
-- spi start registered...without which the FSM doesn't work!
----------------------------------------------------------------------------------------------------
    process(i_sys_clk, i_sys_rst)
    begin
        if i_sys_rst = '1' then
            spi_start_i          <= '0';
        elsif i_sys_clk'event and i_sys_clk = '1' then
            spi_start_i          <= i_spi_start;
        end if;
    end process;
----------------------------------------------------------------------------------------------------
-- SCLK derived based on divide by clock period factor and CPOL.
-- Output clock is generated only in data transaction state.
----------------------------------------------------------------------------------------------------
    process(i_sys_clk, i_sys_rst)
    begin
        if i_sys_rst = '1' then
            o_sclk               <= '0';
        elsif i_sys_clk'event and i_sys_clk = '1' then
            if spim_clk_state_i = SPIM_DATA_TX_STATE then
                if (i_cpol = '0') then
                    o_sclk       <= div_clk_i;
                else
                    o_sclk       <= not div_clk_i;
                end if;
            else
                o_sclk           <= i_cpol;
            end if;
        end if;
    end process;

----------------------------------------------------------------------------------------------------
-- FSM, which is heart of SPI master
-- This enables/disables clock divider, controls output clock, as well as generating chip select
-- for SPI Slave, controls setup and hold time before and after SCLK, time interval between
-- two transactions.
----------------------------------------------------------------------------------------------------
    process (i_sys_clk, i_sys_rst)
    begin
        if i_sys_rst = '1' then
            spim_clk_state_i                  <= SPIM_IDLE_STATE;
            delay_count_start_i               <= '0';
            sclk_count_start_i                <= '0';
            o_ss_start                        <= '1';
            falling_count_start_i             <= '0';
        elsif (rising_edge(i_sys_clk)) then
            case (spim_clk_state_i) is
                when SPIM_IDLE_STATE       =>
                    if (spi_start_i = '1') then  -- registered input
                        spim_clk_state_i      <= SPIM_SETUP_STATE;
                        delay_count_start_i   <= '1';
                        o_ss_start            <= '0';
                        sclk_count_start_i    <= '0';
                    else
                        spim_clk_state_i      <= SPIM_IDLE_STATE;
                        delay_count_start_i   <= '0';
                        o_ss_start            <= '1';
                        falling_count_start_i <= '0';
                        sclk_count_start_i    <= '0';
                    end if;
                when SPIM_SETUP_STATE      =>
                    if (setup_delay_done_i = '1') then
                        delay_count_start_i   <= '0';
                        spim_clk_state_i      <= SPIM_DATA_TX_STATE;
                        sclk_count_start_i    <= '1';
                        falling_count_start_i <= '1';
                    else
                        spim_clk_state_i      <= SPIM_SETUP_STATE;
                        delay_count_start_i   <= '1';
                    end if;
                when SPIM_DATA_TX_STATE    =>
                    if (clk_falling_count_i = DATA_SIZE) then
                        spim_clk_state_i      <= SPIM_HOLD_STATE;
                        delay_count_start_i   <= '1';
                        falling_count_start_i <= '0';
                    else
                        spim_clk_state_i      <= SPIM_DATA_TX_STATE;
                    end if;
                when SPIM_HOLD_STATE       =>
                    if (hold_delay_done_i = '1') then
                        delay_count_start_i   <= '0';
                        spim_clk_state_i      <= SPIM_TX2TX_WAIT_STATE;
                        o_ss_start            <= '1';
                        sclk_count_start_i    <= '0';
                    else
                        spim_clk_state_i      <= SPIM_HOLD_STATE;
                        delay_count_start_i   <= '1';
                    end if;
                when SPIM_TX2TX_WAIT_STATE =>
                    if (tx2tx_delay_done_i = '1') then
                        delay_count_start_i   <= '0';
                        spim_clk_state_i      <= SPIM_IDLE_STATE;
                    else
                        spim_clk_state_i      <= SPIM_TX2TX_WAIT_STATE;
                        delay_count_start_i   <= '1';
                    end if;
                when others                =>
                    spim_clk_state_i          <= SPIM_IDLE_STATE;
                    delay_count_start_i       <= '0';
                    sclk_count_start_i        <= '0';
                    o_ss_start                <= '1';
                    falling_count_start_i     <= '0';
            end case;
        end if;
    end process;

    ------------------------------------------------------------------------------------------------
    -- Delay Counter used for controlling setup, hold and interval between transactions.
    -- Delay counter enabled only when delay_count_start_i = '1'
    ------------------------------------------------------------------------------------------------
    process (i_sys_clk, i_sys_rst)
    begin
        if i_sys_rst = '1' then
            delay_count_i     <= "00000001";
        elsif rising_edge(i_sys_clk) then
            if delay_count_start_i = '0' then
                delay_count_i <= "00000001";
            else
                delay_count_i <= delay_count_i + 1;
            end if;
        end if;
    end process;
    tx2tx_delay_done_i        <= '1' when delay_count_i = i_tx2tx_cycles else '0';
    hold_delay_done_i         <= '1' when delay_count_i = i_hold_cycles  else '0';
    setup_delay_done_i        <= '1' when delay_count_i = i_setup_cycles else '0';

    ------------------------------------------------------------------------------------------------
    -- SCLK falling edge counter - determines number of bytes transmitted per SPI cycle
    ------------------------------------------------------------------------------------------------
    process (i_sys_clk, i_sys_rst)
    begin
        if i_sys_rst = '1' then
            clk_falling_count_i     <= (others => '0');
        elsif rising_edge(i_sys_clk) then
            if falling_count_start_i = '0' then
                clk_falling_count_i <= (others => '0');
            elsif (clk_falling_i = '1') then
                clk_falling_count_i <= clk_falling_count_i + 1;
            end if;
        end if;
    end process;
    clk_rising_i                    <= '1' when div_clk_i = '1' and delay_clk_i = '0' else '0';
    clk_falling_i                   <= '1' when div_clk_i = '0' and delay_clk_i = '1' else '0';

end count_arch;
