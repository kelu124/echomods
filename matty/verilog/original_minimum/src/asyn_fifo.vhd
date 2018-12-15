---------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------
-- library declaration
----------------------------------------------------------------------------------------------------
library ieee;

use ieee.std_logic_arith.all;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
----------------------------------------------------------------------------------------------------
-- entity declaration
----------------------------------------------------------------------------------------------------
entity asyn_fifo is

    generic (
        DATA_SIZE    :     integer;
        ADDRESS_WIDTH :     integer
        );
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

end asyn_fifo;
----------------------------------------------------------------------------------------------------
-- architecture declaration
----------------------------------------------------------------------------------------------------
architecture rtl of asyn_fifo is
    constant FIFO_DEPTH  : integer := 2**ADDRESS_WIDTH;
    type ram_type is array (0 to FIFO_DEPTH - 1) of std_logic_vector(DATA_SIZE - 1 downto 0);
    signal   ram_array_i : ram_type;

    signal rd_empty_i           : std_logic_vector(1 downto 0);
    signal wr_full_i            : std_logic_vector(1 downto 0);
    signal fifo_status_i        : std_logic;
    signal rd_ptr_i             : std_logic_vector(ADDRESS_WIDTH - 1 downto 0);
    signal wr_ptr_i             : std_logic_vector(ADDRESS_WIDTH - 1 downto 0);
    signal wr_addr_i            : std_logic_vector(ADDRESS_WIDTH - 1 downto 0);
    signal matchptr_i           : std_logic;
    signal rd_en_int_i          : std_logic;
    signal wr_en_int_i          : std_logic;
    signal set_status_i         : std_logic;
    signal rst_status_i         : std_logic;
    signal detect_full_i        : std_logic;
    signal detect_empty_i       : std_logic;
    signal fifo_status_rd_clk_i : std_logic;
    signal fifo_status_wr_clk_i : std_logic;
    signal fifo_status_reg_i    : std_logic;
    signal wr_ptr_bin_i    :     std_logic_vector(ADDRESS_WIDTH - 1 downto 0);
    signal rd_ptr_bin_i    :     std_logic_vector(ADDRESS_WIDTH - 1 downto 0);
    signal ptr_diff_i      :     std_logic_vector(ADDRESS_WIDTH - 1 downto 0);
    ------------------------------------------------------------------------------------------------
    -- Component declaration of Gray counter
    ------------------------------------------------------------------------------------------------
    component gray_counter
        generic (
            ADDRESS_WIDTH  :     integer);
        port (
            i_clk          : in  std_logic;
            i_rst          : in  std_logic;
            i_ce           : in  std_logic;
            o_bin_cnt_out  : out std_logic_vector(ADDRESS_WIDTH - 1 downto 0);
            o_gray_cnt_out : out std_logic_vector(ADDRESS_WIDTH - 1 downto 0)
            );
    end component;

    
begin  -- rtl
    
    ------------------------------------------------------------------------------------------------
    -- Component Instance of Gray counter
    ------------------------------------------------------------------------------------------------
    u0_gray_counter : gray_counter
        generic map (
            ADDRESS_WIDTH  => ADDRESS_WIDTH)
        port map (
            i_clk          => i_wr_clk,
            i_rst          => i_rst,
            i_ce           => wr_en_int_i,
            o_bin_cnt_out  => wr_ptr_bin_i,
            o_gray_cnt_out => wr_ptr_i
            );

    u1_gray_counter : gray_counter
        generic map (
            ADDRESS_WIDTH  => ADDRESS_WIDTH)
        port map (
            i_clk          => i_rd_clk,
            i_rst          => i_rst,
            i_ce           => rd_en_int_i,
            o_bin_cnt_out  => rd_ptr_bin_i,
            o_gray_cnt_out => rd_ptr_i
            );

    ------------------------------------------------------------------------------------------------
    -- Read data from Memory
    ------------------------------------------------------------------------------------------------
     rd_data_proc      : process (i_rd_clk)
     begin  -- process rd_data_proc
         if i_rd_clk'event and i_rd_clk = '1' then  -- rising clock edge
             if i_rd_en = '1' and rd_empty_i(1) = '0' then
                 o_rd_data <= ram_array_i(conv_integer(rd_ptr_i));
             end if;
         end if;
     end process rd_data_proc;

        ------------------------------------------------------------------------------------------------
    -- write data into Memory
    ------------------------------------------------------------------------------------------------
    wr_data_proc : process (i_wr_clk)
    begin  -- process wr_data_proc
        if i_wr_clk'event and i_wr_clk = '1' then  -- rising clock edge
            if (i_wr_en = '1' and wr_full_i(1) = '0') then
                ram_array_i (conv_integer(wr_ptr_i)) <= i_wr_data;
            end if;
        end if;
    end process wr_data_proc;

    ------------------------------------------------------------------------------------------------
    -- Binary pointer differene
    ------------------------------------------------------------------------------------------------
    ptr_diff_proc : process (wr_ptr_bin_i, rd_ptr_bin_i)
    begin  -- process ptr_diff_proc
        if (wr_ptr_bin_i > rd_ptr_bin_i) then
            ptr_diff_i <= wr_ptr_bin_i - rd_ptr_bin_i;
        elsif (rd_ptr_bin_i > wr_ptr_bin_i) then
            ptr_diff_i <= ((FIFO_DEPTH - rd_ptr_bin_i) + wr_ptr_bin_i);
        else
            ptr_diff_i <= (others => '0');
        end if;
    end process ptr_diff_proc;

    o_half_full <= ptr_diff_i(ADDRESS_WIDTH - 1) ;

    ------------------------------------------------------------------------------------------------
    -- Internal Fifo write and read enable
    ------------------------------------------------------------------------------------------------
    wr_en_int_i <= i_wr_en and (not wr_full_i(1));
    rd_en_int_i <= i_rd_en and (not rd_empty_i(1));

    ------------------------------------------------------------------------------------------------
    -- check if write and read pointer match
    ------------------------------------------------------------------------------------------------
    matchptr_i <= '1' when wr_ptr_i = rd_ptr_i else '0';

    ------------------------------------------------------------------------------------------------
    -- Set fifo status by comparing write and read pointer
    ------------------------------------------------------------------------------------------------
    set_status_i <= (wr_ptr_i(ADDRESS_WIDTH-2) xnor rd_ptr_i(ADDRESS_WIDTH-1)) and
                    (wr_ptr_i(ADDRESS_WIDTH-1) xor rd_ptr_i(ADDRESS_WIDTH-2));

    rst_status_i <= (wr_ptr_i(ADDRESS_WIDTH-2) xor rd_ptr_i(ADDRESS_WIDTH-1)) and
                    (wr_ptr_i(ADDRESS_WIDTH-1) xnor rd_ptr_i(ADDRESS_WIDTH-2));

    

    ------------------------------------------------------------------------------------------------
    -- Fifo status read clock register
    ------------------------------------------------------------------------------------------------
    fifo_status_rd_clk_proc : process (i_rd_clk, i_rst)
    begin  -- process fifo_status_rd_clk_proc
        if i_rst = '1' then                           -- asynchronous reset (active high)
            fifo_status_rd_clk_i <= '0';
        elsif i_rd_clk'event and i_rd_clk = '1' then  -- rising clock edge
            fifo_status_rd_clk_i <= fifo_status_i;
        end if;
    end process fifo_status_rd_clk_proc;

    ------------------------------------------------------------------------------------------------
    -- Fifo status write clock register
    ------------------------------------------------------------------------------------------------
    fifo_status_wr_clk_proc : process (i_wr_clk, i_rst)
    begin  -- process fifo_status_wr_clk_proc
        if i_rst = '1' then                           -- asynchronous reset (active high)
            fifo_status_wr_clk_i <= '0';
        elsif i_wr_clk'event and i_wr_clk = '1' then  -- rising clock edge
            fifo_status_wr_clk_i <= fifo_status_i;
        end if;
    end process fifo_status_wr_clk_proc;

    fifo_status_reg_i <= fifo_status_rd_clk_i or fifo_status_wr_clk_i;

    ------------------------------------------------------------------------------------------------
    -- Staus
    ------------------------------------------------------------------------------------------------
    fifo_status : process (rst_status_i, fifo_status_reg_i, i_rst, set_status_i)
    begin  -- process fifo_status
        if rst_status_i = '1' or i_rst = '1' then
            fifo_status_i <= '0';
        elsif (set_status_i = '1') then
            fifo_status_i <= '1';
        else
            fifo_status_i <= fifo_status_reg_i;
        end if;
    end process fifo_status;

    ------------------------------------------------------------------------------------------------
    -- Full Detection
    ------------------------------------------------------------------------------------------------
    detect_full_i <= fifo_status_i and matchptr_i;

    ------------------------------------------------------------------------------------------------
    -- Register full
    ------------------------------------------------------------------------------------------------
    register_full_proc : process (i_wr_clk, detect_full_i)
    begin  -- process register_full_proc
        if detect_full_i = '1' then                   -- asynchronous reset (active high)
            wr_full_i <= "11";
        elsif i_wr_clk'event and i_wr_clk = '1' then  -- rising clock edge
            wr_full_i <= wr_full_i(0) & detect_full_i;
        end if;
    end process register_full_proc;

    ------------------------------------------------------------------------------------------------
    --  Empty Detection
    ------------------------------------------------------------------------------------------------
    detect_empty_i <= not fifo_status_i and matchptr_i;

    ------------------------------------------------------------------------------------------------
    -- Register Empty
    ------------------------------------------------------------------------------------------------
    register_empty_proc : process (i_rd_clk, detect_empty_i)
    begin  -- process register_empty_proc
        if detect_empty_i = '1' then                  -- asynchronous reset (active high)
            rd_empty_i <= "11";
        elsif i_rd_clk'event and i_rd_clk = '1' then  -- rising clock edge
            rd_empty_i <= rd_empty_i(0) & detect_empty_i;
        end if;
    end process register_empty_proc;

    o_full <= wr_full_i(1);

    o_empty <= rd_empty_i(1);

end rtl;
