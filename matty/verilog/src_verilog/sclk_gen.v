
module sclk_gen 
  #(
    parameter DATA_SIZE = 16
  )
  (
    input            i_sys_clk,
    input            i_sys_rst,
    input            i_spi_start,
    input      [7:0] i_clk_period,
    input      [7:0] i_setup_cycles,
    input      [7:0] i_hold_cycles,
    input      [7:0] i_tx2tx_cycles,
    input            i_cpol,
    output reg       o_ss_start,
    output reg       o_sclk
);

wire [7:0] clk_periodby2_i;
    wire [7:0] sclk_period_i;
reg  [7:0] sclk_count_i;
reg        delay_clk_i;
reg        div_clk_i;
wire       clk_falling_i;
wire       clk_rising_i;
reg        delay_count_start_i;
wire       tx2tx_delay_done_i;
wire       hold_delay_done_i;
wire       setup_delay_done_i;
reg  [7:0] delay_count_i;
reg        falling_count_start_i;
reg  [7:0] clk_falling_count_i;
reg        spi_start_i;
reg        sclk_count_start_i;

localparam SPIM_IDLE_STATE       = 5'b00001;
localparam SPIM_SETUP_STATE      = 5'b00010;
localparam SPIM_DATA_TX_STATE    = 5'b00100;
localparam SPIM_HOLD_STATE       = 5'b01000;
localparam SPIM_TX2TX_WAIT_STATE = 5'b10000;
reg [4:0] spim_clk_state_i;


assign clk_periodby2_i = {1'b0, i_clk_period[7:1]};

// SCLK generation - This a clock divider logic, which is enabled only when slave select is LOW.
always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) begin
    sclk_count_i <= 8'b00000001;
    div_clk_i    <= 1'b0;
  end
  else begin
    if(sclk_count_start_i == 1'b1) begin
      if(sclk_count_i < i_clk_period) begin
        sclk_count_i <= sclk_count_i + 'd1;
      end
      else begin
        sclk_count_i <= 8'b00000001;
      end
    end
    else begin
        sclk_count_i <= 8'b00000010;
    end

    if(sclk_count_i > clk_periodby2_i) begin
      div_clk_i <= 1'b0;
    end
    else begin
      div_clk_i <= 1'b1;
    end
  end
end

// Delayed version of divided clock, used to generate falling/rising edge of generated clock

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    delay_clk_i <= 1'b0;
  else
    delay_clk_i <= div_clk_i;
end

// spi start registered...without which the FSM doesn't work!

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    spi_start_i <= 1'b0;
  else
    spi_start_i <= i_spi_start;
end

// SCLK derived based on divide by clock period factor and CPOL.
// Output clock is generated only in data transaction state.

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    o_sclk <= 1'b0;
  else begin
    if(spim_clk_state_i == SPIM_DATA_TX_STATE) begin
      if (i_cpol == 1'b0)
        o_sclk <= div_clk_i;
      else
        o_sclk <= ~div_clk_i;
    end
    else
      o_sclk <= i_cpol;
  end
end

// FSM, which is heart of SPI master
// This enables/disables clock divider, controls output clock, as well as generating chip select
// for SPI Slave, controls setup and hold time before and after SCLK, time interval between
// two transactions.

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) begin
    spim_clk_state_i                  <= SPIM_IDLE_STATE;
    delay_count_start_i               <= 1'b0;
    sclk_count_start_i                <= 1'b0;
    o_ss_start                        <= 1'b1;
    falling_count_start_i             <= 1'b0;
  end
  else begin
    case (spim_clk_state_i)
      SPIM_IDLE_STATE:
        begin
          if (spi_start_i == 1'b1) begin  // registered input
            spim_clk_state_i      <= SPIM_SETUP_STATE;
            delay_count_start_i   <= 1'b1;
            o_ss_start            <= 1'b0;
            sclk_count_start_i    <= 1'b0;
          end
          else begin
            spim_clk_state_i      <= SPIM_IDLE_STATE;
            delay_count_start_i   <= 1'b0;
            o_ss_start            <= 1'b1;
            falling_count_start_i <= 1'b0;
            sclk_count_start_i    <= 1'b0;
          end
        end
      SPIM_SETUP_STATE:
        begin
          if (setup_delay_done_i == 1'b1) begin
            delay_count_start_i   <= 1'b0;
            spim_clk_state_i      <= SPIM_DATA_TX_STATE;
            sclk_count_start_i    <= 1'b1;
            falling_count_start_i <= 1'b1;
          end
          else begin
            spim_clk_state_i      <= SPIM_SETUP_STATE;
            delay_count_start_i   <= 1'b1;
          end
        end
      SPIM_DATA_TX_STATE:
        begin
          if (clk_falling_count_i == DATA_SIZE) begin
              spim_clk_state_i      <= SPIM_HOLD_STATE;
              delay_count_start_i   <= 1'b1;
              falling_count_start_i <= 1'b0;
          end
          else begin
              spim_clk_state_i      <= SPIM_DATA_TX_STATE;
          end
        end
      SPIM_HOLD_STATE:
        begin
          if (hold_delay_done_i == 1'b1) begin
              delay_count_start_i   <= 1'b0;
              spim_clk_state_i      <= SPIM_TX2TX_WAIT_STATE;
              o_ss_start            <= 1'b1;
              sclk_count_start_i    <= 1'b0;
          end
          else begin
              spim_clk_state_i      <= SPIM_HOLD_STATE;
              delay_count_start_i   <= 1'b1;
          end
        end
      SPIM_TX2TX_WAIT_STATE:
        begin
          if (tx2tx_delay_done_i == 1'b1) begin
            delay_count_start_i   <= 1'b0;
            spim_clk_state_i      <= SPIM_IDLE_STATE;
          end
          else begin
            spim_clk_state_i      <= SPIM_TX2TX_WAIT_STATE;
            delay_count_start_i   <= 1'b1;
          end
        end
      default:
        begin
          spim_clk_state_i          <= SPIM_IDLE_STATE;
          delay_count_start_i       <= 1'b0;
          sclk_count_start_i        <= 1'b0;
          o_ss_start                <= 1'b1;
          falling_count_start_i     <= 1'b0;
        end
    endcase;
  end
end

// Delay Counter used for controlling setup, hold and interval between transactions.
// Delay counter enabled only when delay_count_start_i = '1'

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    delay_count_i     <= 8'b00000001;
  else
    if(delay_count_start_i == 1'b0)
      delay_count_i <= 8'b00000001;
    else
      delay_count_i <= delay_count_i + 'd1;
end

assign tx2tx_delay_done_i = delay_count_i == i_tx2tx_cycles ? 1'b1 : 1'b0;
assign hold_delay_done_i  = delay_count_i == i_hold_cycles  ? 1'b1 : 1'b0;
assign setup_delay_done_i = delay_count_i == i_setup_cycles ? 1'b1 : 1'b0;

// SCLK falling edge counter - determines number of bytes transmitted per SPI cycle

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    clk_falling_count_i <= 'd0;
  else begin
    if(falling_count_start_i == 1'b0)
        clk_falling_count_i <= 'd0;
    else if (clk_falling_i == 1'b1)
        clk_falling_count_i <= clk_falling_count_i + 'd1;
  end
end

assign clk_rising_i  = ((div_clk_i == 1'b1) & (delay_clk_i == 1'b0)) ? 1'b1 : 1'b0;
assign clk_falling_i = ((div_clk_i == 1'b0) & (delay_clk_i == 1'b1)) ? 1'b1 : 1'b0;

endmodule