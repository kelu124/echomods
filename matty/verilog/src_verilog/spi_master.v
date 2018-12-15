module spi_master
  #(
    parameter DATA_SIZE = 16,
    parameter FIFO_REQ  = 1'b0
  )
  (
    input             i_sys_clk,        // system clock
    input             i_sys_rst,        // system reset
    input             i_csn,            // chip select for SPI master
    input      [15:0] i_data,           // Input data
    input             i_wr,             // Active Low Write, Active High Read
    input             i_rd,             // Active Low Write, Active High Read
    output     [15:0] o_data,           //output data
    output            o_tx_ready,       // Transmitter ready, can write another data
    output            o_rx_ready,       // Receiver ready, can read data
    output            o_tx_error,       // Transmitter error
    output            o_rx_error,       // Receiver error
    output            o_intr,         
    input      [1:0]  i_slave_addr,     // Slave Address
    input             i_cpol,           // CPOL value - 0 or 1
    input             i_cpha,           // CPHA value - 0 or 1 
    input             i_lsb_first,      // lsb first when '1' /msb first when 
    input             i_spi_start,      // START SPI Master Transactions
    input      [7:0]  i_clk_period,     // SCL clock period in terms of i_sys_clk
    input      [7:0]  i_setup_cycles,   // SPIM setup time  in terms of i_sys_clk
    input      [7:0]  i_hold_cycles,    // SPIM hold time  in terms of i_sys_clk
    input      [7:0]  i_tx2tx_cycles,   // SPIM interval between data transactions in terms of i_sys_clk
    output reg [3:0]  o_slave_csn,      // SPI Slave select (chip select) active low
    output            o_mosi,           // Master output to Slave
    input             i_miso,           // Master input from Slave
    output            o_sclk,           // Master clock
    output            mosi_tri_en
);

wire sclk_i;
wire ss_start_i;

assign o_sclk = sclk_i;

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    o_slave_csn <= 4'b111;
  else 
    case(i_slave_addr)
      2'b00:
        begin
          o_slave_csn <= {3'b111, ss_start_i};
        end
      2'b01:
        begin
          o_slave_csn <= {2'b11, ss_start_i, 1'b1};
        end
      2'b10:
        begin
          o_slave_csn <= {1'b1, ss_start_i, 2'b11};
        end
      2'b11:
        begin
          o_slave_csn <= {ss_start_i, 3'b111};
        end
      default:
        begin
          o_slave_csn <= 4'b1111;
        end
    endcase
end

sclk_gen
  #(
    .DATA_SIZE(DATA_SIZE)
  )
  sclk_gen_u0
  (
    .i_sys_clk(i_sys_clk),
    .i_sys_rst(i_sys_rst),
    .i_spi_start(i_spi_start),
    .i_clk_period(i_clk_period),
    .i_setup_cycles(i_setup_cycles),
    .i_hold_cycles(i_hold_cycles),
    .i_tx2tx_cycles(i_tx2tx_cycles),
    .i_cpol(i_cpol),
    .o_ss_start(ss_start_i),
    .o_sclk(sclk_i)
  );


spi_data_path
  #(
    .DATA_SIZE(DATA_SIZE),
    .FIFO_REQ(FIFO_REQ)
  )
  spi_data_path_u1
  (
    .i_sys_clk(i_sys_clk),
    .i_sys_rst(i_sys_rst),
    .i_csn(i_csn),
    .i_data(i_data),
    .i_wr(i_wr),
    .i_rd(i_rd),
    .i_spi_start(i_spi_start),
    .o_data(o_data),
    .o_tx_ready(o_tx_ready),
    .o_rx_ready(o_rx_ready),
    .o_tx_error(o_tx_error),
    .o_rx_error(o_rx_error),
    .o_intr(o_intr),
    .i_cpol(i_cpol),
    .i_cpha(i_cpha),
    .i_lsb_first(i_lsb_first),
    .o_mosi(o_mosi),
    .i_miso(i_miso),
    .i_ssn(ss_start_i),
    .i_sclk(sclk_i),
    .mosi_tri_en(mosi_tri_en)
  );


endmodule
