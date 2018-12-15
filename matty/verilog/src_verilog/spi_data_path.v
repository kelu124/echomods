
module spi_data_path
#(
  parameter DATA_SIZE = 16,
  parameter FIFO_REQ = 0
)
(
  input          i_sys_clk,   // system clock
  input          i_sys_rst,   // system reset
  input          i_csn,       // Master Enable/select
  input  [15:0]  i_data,      // Input data
  input          i_wr,        // Active Low Write, Active High Read
  input          i_rd,        // Active Low Write, Active High Read
  input          i_spi_start,
  output [15:0]  o_data,      // output data
  output         o_tx_ready,  // Transmitter ready, can write another data
 
  output         o_rx_ready,  // Receiver ready, can read data
  output         o_tx_error,  // Transmitter error
  output         o_rx_error,  // Receiver error

  input          i_cpol,      // CPOL value - 0 or 1
  input          i_cpha,      // CPHA value - 0 or 1 
  input          i_lsb_first, // lsb first when '1' /msb first when 

  output reg     o_intr,
  output reg     o_mosi,      // Master output to Slave
  input          i_miso,      // Master input from Slave
  input          i_ssn,       // Slave Slect Active low
  input          i_sclk,      // Clock from SPI Master
  output         mosi_tri_en
);

wire [DATA_SIZE - 1:0] data_in_reg_i;
reg  [DATA_SIZE - 1:0] data_in;
reg  [DATA_SIZE - 1:0] rxdata_reg_i;
reg  [DATA_SIZE - 1:0] txdata_reg_i;
reg  [DATA_SIZE - 1:0] rx_shift_data_pos_sclk_i;
reg  [DATA_SIZE - 1:0] rx_shift_data_neg_sclk_i;
reg  tx_error_i;
reg  rx_error_i;
reg  tx_ready_i;
reg  rx_ready_i;
reg  rx_fifo_rd_en_i;
wire RxFifoEmpty_i;
wire rx_fifo_wr_en_i;
wire ReadHalfFull_i;
wire RxFifoFull_i;
wire tx_fifo_rd_en_i;
wire TxFifoEmpty_i;
reg  tx_fifo_wr_en_i;
wire TxFifoHalfFull_i;
wire TxFifoFull_i;
reg  d1_TxReady_i;
reg  d2_TxReady_i;
reg  d1_RxReady_i;
reg  d2_RxReady_i;
reg  mosi_00_i;
reg  mosi_01_i;
reg  mosi_10_i;
reg  mosi_11_i;
reg  rx_done_pos_sclk_i;
reg  rx_done_neg_sclk_i;
reg  rx_done_reg1_i;
reg  rx_done_reg2_i;
reg  rx_done_reg3_i;
reg  tx_done_pos_sclk_i;
reg  tx_done_neg_sclk_i;
reg  tx_done_reg1_i;
reg  tx_done_reg2_i;
reg  tx_done_reg3_i;
reg  [5:0] rx_data_count_pos_sclk_i;
reg  [5:0] rx_data_count_neg_sclk_i;
reg  [5:0] tx_data_count_pos_sclk_i;
reg  [5:0] tx_data_count_neg_sclk_i;
wire [7:0] dummy_i;
wire [7:0] dummy_rd = 8'h00;


// Read Fifo 
generate if( (FIFO_REQ != 0) & (DATA_SIZE == 8) ) begin
  wire [15:0] u_RxFifo_i_wr_data;

  assign u_RxFifo_i_wr_data[7:0]  = rxdata_reg_i;
  assign u_RxFifo_i_wr_data[15:8] = dummy_rd;

  asyn_fifo 
  #(
    .DATA_SIZE(16),
    .ADDRESS_WIDTH(4)
  )
  u_RxFifo
  (
    .i_rst(i_sys_rst),
    .i_rd_clk(i_sys_clk),
    .i_rd_en(rx_fifo_rd_en_i),
    .o_rd_data(o_data),
    .o_empty(RxFifoEmpty_i),
    .i_wr_clk(i_sys_clk),
    .i_wr_en(rx_fifo_wr_en_i),
    .i_wr_data(u_RxFifo_i_wr_data),
    .o_half_full(ReadHalfFull_i),
    .o_full(RxFifoFull_i)
  );
end
endgenerate

generate if( (FIFO_REQ != 0) & (DATA_SIZE == 16) ) begin
  asyn_fifo 
  #(
    .DATA_SIZE(16),
    .ADDRESS_WIDTH(4)
  )
  u_RxFifo
  (
    .i_rst(i_sys_rst),
    .i_rd_clk(i_sys_clk),
    .i_rd_en(rx_fifo_rd_en_i),
    .o_rd_data(o_data),
    .o_empty(RxFifoEmpty_i),
    .i_wr_clk(i_sys_clk),
    .i_wr_en(rx_fifo_wr_en_i),
    .i_wr_data(rxdata_reg_i),
    .o_half_full(ReadHalfFull_i),
    .o_full(RxFifoFull_i)
  );
end
endgenerate

// Write Fifo 
generate if( (FIFO_REQ != 0) & (DATA_SIZE == 8) ) begin
  wire [15:0] u_TxFifo_o_rd_data;

  assign data_in_reg_i = u_TxFifo_o_rd_data[7:0];
  assign dummy_i       = u_TxFifo_o_rd_data[15:8];

  asyn_fifo 
  #(
    .DATA_SIZE(16),
    .ADDRESS_WIDTH(4)
  )
  u_TxFifo
  (
    .i_rst(i_sys_rst),
    .i_rd_clk(i_sys_clk),
    .i_rd_en(tx_fifo_rd_en_i),
    .o_rd_data(u_TxFifo_o_rd_data),
.o_empty(TxFifoEmpty_i),
    .i_wr_clk(i_sys_clk),
    .i_wr_en(tx_fifo_wr_en_i),
    .i_wr_data(i_data),
    .o_half_full(TxFifoHalfFull_i),
    .o_full(TxFifoFull_i)
  );
end
endgenerate

generate if( (FIFO_REQ != 0) & (DATA_SIZE == 16) ) begin
  asyn_fifo 
  #(
    .DATA_SIZE(16),
    .ADDRESS_WIDTH(4)
  )
  u_TxFifo
  (
    .i_rst(i_sys_rst),
    .i_rd_clk(i_sys_clk),
    .i_rd_en(tx_fifo_rd_en_i),
    .o_rd_data(data_in_reg_i),
.o_empty(TxFifoEmpty_i),
    .i_wr_clk(i_sys_clk),
    .i_wr_en(tx_fifo_wr_en_i),
    .i_wr_data(i_data),
    .o_half_full(TxFifoHalfFull_i),
    .o_full(TxFifoFull_i)
  );
end
endgenerate

assign o_tx_ready = tx_ready_i;
assign o_rx_ready = rx_ready_i;
assign o_tx_error = tx_error_i;
assign o_rx_error = rx_error_i;

assign mosi_tri_en = i_ssn;

generate if( (FIFO_REQ == 0) & (DATA_SIZE == 16) ) begin
  assign o_data = rxdata_reg_i;
end
endgenerate

generate if( (FIFO_REQ == 0) & (DATA_SIZE == 8) ) begin
  assign o_data[7:0]  = rxdata_reg_i;
  assign o_data[15:8] = 8'h00;
end
endgenerate

// Data input latch process
// Latched only when slave enabled, Transmitter ready and wr is high.
always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    data_in <= 'd0;
  else 
    if( (FIFO_REQ == 0) & (DATA_SIZE == 8) ) begin
      if( (i_wr == 1'b1) & (i_csn == 1'b0) & (tx_ready_i == 1'b1) )
        data_in <= i_data[7:0];
    end
    else if( (FIFO_REQ == 0) & (DATA_SIZE == 16) ) begin
      if( (i_wr == 1'b1) & (i_csn == 1'b0) & (tx_ready_i == 1'b1) )
        data_in <= i_data;
    end
end

// Tx FIFO write enable signal generated when write is high and cs is low
always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    tx_fifo_wr_en_i <= 1'b0;
  else
    if(FIFO_REQ != 0) begin
      if( (i_wr == 1'b1) & (i_csn == 1'b0) )
        tx_fifo_wr_en_i <= 1'b1;
      else 
        tx_fifo_wr_en_i <= 1'b0;
    end
end

// Rx FIFO read enable signal generated when read is high and cs is low
always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    rx_fifo_rd_en_i <= 1'b0;
  else
    if(FIFO_REQ != 0) begin
      if ( (i_rd == 1'b1) & (i_csn == 1'b0) )
        rx_fifo_rd_en_i <= 1'b1;
      else
        rx_fifo_rd_en_i <= 1'b0;
    end
end

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin //process Ready_Pulse_proc
  if(i_sys_rst == 1'b1)
  begin
    d1_TxReady_i <= 1'b0;
    d2_TxReady_i <= 1'b0;
  end
  else
  begin
    d1_TxReady_i <= tx_ready_i & i_spi_start;
    d2_TxReady_i <= d1_TxReady_i;
  end
end

assign tx_fifo_rd_en_i = d1_TxReady_i & (~d2_TxReady_i);

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin //process Ready_Pulse_proc
  if(i_sys_rst == 1'b1)
  begin
    d1_RxReady_i <= 1'b0;
    d2_RxReady_i <= 1'b0;
  end
  else
  begin
    d1_RxReady_i <= rx_ready_i;
    d2_RxReady_i <= d1_RxReady_i;
  end
end

assign rx_fifo_wr_en_i = d1_RxReady_i & (~d2_RxReady_i);

// Receive Data Register, mux it based on sampling
// Data latched based on Rx Done signal
always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    rxdata_reg_i <= 'd0;
  else
    if( (rx_done_reg1_i == 1'b1) & (rx_done_reg2_i == 1'b0) ) begin
      if(( (i_cpol == 1'b0) & (i_cpha == 1'b0) ) | ( (i_cpol == 1'b1) & (i_cpha == 1'b1) ))
        rxdata_reg_i <= rx_shift_data_pos_sclk_i;
      else
        rxdata_reg_i <= rx_shift_data_neg_sclk_i;
    end
end

// Re-register data to be transmitted
always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    txdata_reg_i     <= 'd0;
  else begin
    if(FIFO_REQ != 0)
      txdata_reg_i <= data_in_reg_i;
    else
      txdata_reg_i <= data_in;
  end
end

//// SPI Slave Receiver Section

// MOSI Sampling : Sample at posedge of SCLK for 
//                 1. i_cpol=0 and i_cpha=0 
//                 2. i_cpol=1 and i_cpha=1 

always @ (posedge i_sclk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    rx_shift_data_pos_sclk_i <= 'd0;
  else begin
    if( (i_ssn == 1'b0) & (( (i_cpol == 1'b0) & (i_cpha == 1'b0) ) | ( (i_cpol == 1'b1) & (i_cpha == 1'b1) ))) begin
      if(i_lsb_first == 1'b1)
        rx_shift_data_pos_sclk_i <= {i_miso, rx_shift_data_pos_sclk_i[DATA_SIZE-1:1]};
      else
        rx_shift_data_pos_sclk_i <= {rx_shift_data_pos_sclk_i[DATA_SIZE-2:0], i_miso};
    end
  end
end

always @ (posedge i_sclk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) 
  begin
    rx_data_count_pos_sclk_i <= 'd0;
    rx_done_pos_sclk_i       <= 1'b0;
  end
  else 
  begin
      if( (i_ssn == 1'b0) & (( (i_cpol == 1'b0) & (i_cpha == 1'b0) ) | ( (i_cpol == 1'b1) & (i_cpha == 1'b1) )))
      begin
        if(rx_data_count_pos_sclk_i == DATA_SIZE - 'd1) 
        begin
          rx_data_count_pos_sclk_i <= 'd0;
          rx_done_pos_sclk_i       <= 1'b1;
        end
        else if(i_ssn == 1'b0)
        begin
          rx_data_count_pos_sclk_i <= rx_data_count_pos_sclk_i + 'd1;
          rx_done_pos_sclk_i       <= 1'b0;
        end
      end
  end
end

// - MOSI Sampling : Sample at negedge of SCLK for
//  1. i_cpol=1 and i_cpha=0
//  2. i_cpol=0 and i_cpha=1
always @ (negedge i_sclk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) 
    rx_shift_data_neg_sclk_i <= 'd0;
  else begin
    if((i_ssn == 1'b0) & (((i_cpol == 1'b1) & (i_cpha == 1'b0)) | ((i_cpol == 1'b0) & (i_cpha == 1'b1)))) begin
      if(i_lsb_first == 1'b1)
        rx_shift_data_neg_sclk_i <= {i_miso, rx_shift_data_neg_sclk_i[DATA_SIZE-1:1]};
      else
        rx_shift_data_neg_sclk_i <= {rx_shift_data_neg_sclk_i[DATA_SIZE-2:0], i_miso};
    end
  end
end

always @ (negedge i_sclk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) 
  begin
    rx_data_count_neg_sclk_i     <= 'd0;
    rx_done_neg_sclk_i           <= 1'b0;
  end
  else
  begin
    if(rx_data_count_neg_sclk_i == DATA_SIZE - 'd1)
    begin
      rx_data_count_neg_sclk_i <= 'd0;
      rx_done_neg_sclk_i       <= 'b1;
    end
    else if(i_ssn == 1'b0)
    begin
      rx_data_count_neg_sclk_i <= rx_data_count_neg_sclk_i + 'd1;
      rx_done_neg_sclk_i       <= 1'b0;
    end
  end
end


// SPI Master Receiver Receive Done signal generator
// This is based on CPOL and CPHA
always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) 
  begin
    rx_done_reg1_i     <= 'd0;
    rx_done_reg2_i     <= 'd0;
    rx_done_reg3_i     <= 'd0;
  end
  else
  begin
    if( (i_ssn == 1'b0) & (((i_cpol == 1'b0) & (i_cpha == 1'b0)) | ((i_cpol == 1'b1) & (i_cpha == 1'b1))) )
    begin
      rx_done_reg1_i <= rx_done_pos_sclk_i;
    end
    else
    begin
      rx_done_reg1_i <= rx_done_neg_sclk_i;
    end

    rx_done_reg2_i     <= rx_done_reg1_i;
    rx_done_reg3_i     <= rx_done_reg2_i;
  end
end

// Receiver ready at the end of reception.
// A valid receive data available at this time

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) 
    rx_ready_i     <= 1'b0;
  else begin
    if((rx_done_reg2_i == 1'b1) & (rx_done_reg3_i == 1'b0))
      rx_ready_i <= 1'b1;
    else if ((i_rd == 1'b1) & (i_csn == 1'b0))
      rx_ready_i <= 1'b0;
  end
end

// Receive error when external interface hasn't read previous data
// A new data received, but last received data hasn't been read yet.
always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) 
    rx_error_i <= 1'b0;
  else begin
    if((rx_done_reg2_i == 1'b1) & (rx_done_reg3_i == 1'b0) & (rx_ready_i == 1'b1))
      rx_error_i <= 1'b1;
    else if ((i_rd == 1'b1) & (i_csn == 1'b0))
      rx_error_i <= 1'b0;
  end
end

//// SPI Master Transmitter section 

// cpol=0 and cpha=0: data must be placed before rising edge of sclk

always @ (txdata_reg_i or tx_data_count_neg_sclk_i or i_lsb_first)
begin
  if(i_lsb_first == 1'b1)
    mosi_00_i <= txdata_reg_i[tx_data_count_neg_sclk_i];
  else
    mosi_00_i <= txdata_reg_i[DATA_SIZE - tx_data_count_neg_sclk_i - 'd1];
end


// cpol=1 and cpha=0: data must be placed before falling edge of sclk

always @ (txdata_reg_i or tx_data_count_pos_sclk_i or i_lsb_first)
begin
  if(i_lsb_first == 1'b1)
    mosi_10_i <= txdata_reg_i[tx_data_count_pos_sclk_i];
  else
    mosi_10_i <= txdata_reg_i[DATA_SIZE - tx_data_count_pos_sclk_i - 'd1];
end

// cpol=0 and cpha=1: data must be placed at rising edge of sclk

always @ (posedge i_sclk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) 
    mosi_01_i <= 1'b1;
  else begin
    if(i_lsb_first == 1'b1)
      mosi_01_i <= txdata_reg_i[tx_data_count_pos_sclk_i];
    else
      mosi_01_i <= txdata_reg_i[DATA_SIZE - tx_data_count_pos_sclk_i - 'd1];
  end
end

// cpol=1 and cpha=1: data must be placed at falling edge of sclk

always @ (negedge i_sclk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) 
    mosi_11_i <= 1'b1;
  else begin
    if(i_lsb_first == 1'b1)
      mosi_11_i <= txdata_reg_i[tx_data_count_neg_sclk_i];
    else
      mosi_11_i <= txdata_reg_i[DATA_SIZE - tx_data_count_neg_sclk_i - 'd1];
  end
end

// Tx count on falling edge of sclk for cpol=0 and cpha=0
// and cpol=1 and cpha=1

always @ (negedge i_sclk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) 
  begin
    tx_data_count_neg_sclk_i <= 'd0;
    tx_done_neg_sclk_i       <= 1'b0;
  end
  else
  begin
    if(tx_data_count_neg_sclk_i == DATA_SIZE - 'd1)
    begin
      tx_data_count_neg_sclk_i <= 'd0;
      tx_done_neg_sclk_i       <= 1'b1;
    end
    else if(i_ssn == 1'b0)
    begin
      tx_data_count_neg_sclk_i <= tx_data_count_neg_sclk_i + 'd1;
      tx_done_neg_sclk_i       <= 1'b0;
    end
  end
end


// Tx count on rising edge of sclk for cpol=1 and cpha=0
// and cpol=0 and cpha=1

always @ (posedge i_sclk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) 
  begin
    tx_data_count_pos_sclk_i <= 'd0;
    tx_done_pos_sclk_i       <= 1'b0;
  end
  else
  begin
    if(tx_data_count_pos_sclk_i == DATA_SIZE - 'd1) 
    begin
      tx_data_count_pos_sclk_i <= 'd0;
      tx_done_pos_sclk_i       <= 1'b1;
    end
    else if(i_ssn == 1'b0)
    begin
      tx_data_count_pos_sclk_i <= tx_data_count_pos_sclk_i + 'd1;
      tx_done_pos_sclk_i       <= 1'b0;
    end
  end
end

always @ (i_ssn or i_cpol or i_cpha or mosi_00_i or mosi_01_i or mosi_10_i or mosi_11_i)
begin
  if (i_ssn == 1'b0) begin
      if ((i_cpol == 1'b0) & (i_cpha == 1'b0))
          o_mosi <= mosi_00_i;
      else if ((i_cpol == 1'b0) & (i_cpha == 1'b1))
          o_mosi <= mosi_01_i;
      else if ((i_cpol == 1'b1) & (i_cpha == 1'b0))
          o_mosi <= mosi_10_i;
      else
          o_mosi <= mosi_11_i;
  end
  else
      o_mosi <= 1'b0;
end

// Transmit done generation
// Muxed based on CPOL and CPHA

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
  begin
    tx_done_reg1_i     <= 1'b0;
    tx_done_reg2_i     <= 1'b0;
    tx_done_reg3_i     <= 1'b0;
  end
  else
  begin
    if(((i_cpol == 1'b0) & (i_cpha == 1'b0)) | ((i_cpol == 1'b1) & (i_cpha == 1'b1)))
    begin
      tx_done_reg1_i <= tx_done_neg_sclk_i;
    end
    else
    begin
      tx_done_reg1_i <= tx_done_pos_sclk_i;
    end
    tx_done_reg2_i     <= tx_done_reg1_i;
    tx_done_reg3_i     <= tx_done_reg2_i;
  end
end

// Transmitter is ready at the end of Transmission
// Transmitter ready goes low as soon as it gets a data byte/word

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    tx_ready_i <= 1'b1;
  else begin
    if (i_spi_start == 1'b1)
        tx_ready_i <= 1'b0;
    else if ((tx_done_reg2_i == 1'b1) & (tx_done_reg3_i == 1'b0))
        tx_ready_i <= 1'b1;
  end
end

// Transmitter error when a data is written while transmitter busy transmitting data
// (busy when Tx Ready = 0)

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    tx_error_i <= 1'b0;
  else begin
    if((tx_ready_i == 1'b0) & (i_wr == 1'b1) & (i_csn == 1'b0))
      tx_error_i <= 1'b1;
    else if((i_wr == 1'b1) & (i_csn == 1'b0))
      tx_error_i <= 1'b0;
  end
end

// Interrupt generation logic

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
   o_intr     <= 1'b0;
  else
    if(   (tx_error_i   == 1'b1) 
        | (rx_error_i   == 1'b1) 
        | (tx_ready_i   == 1'b1) 
        | (rx_ready_i   == 1'b1) 
        | (RxFifoFull_i == 1'b1) 
        | (TxFifoFull_i == 1'b1))
      o_intr <= 1'b1;
end


endmodule