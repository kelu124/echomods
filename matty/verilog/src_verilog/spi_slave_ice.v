module SPI_SLAVE_ICE
#(
  parameter DATA_SIZE  = 8
)
(
  input                        i_sys_clk,     	// system clock
  input                        i_sys_rst,     	// system reset
  input                        i_csn,         	// Slave Enable/select
  input      [DATA_SIZE - 1:0] i_data,          // Input data
  input                        i_wr,          	// Active Low Write, Active High Read
  input                        i_rd,          	// Active Low Write, Active High Read
  output     [DATA_SIZE - 1:0] o_data,          //output data
  output                       o_tx_ready,    	// Transmitter ready, can write another data
  output                       o_rx_ready,    	// Receiver ready, can read data
  output                       o_tx_error,    	// Transmitter error
  output                       o_rx_error,    	// Receiver error

  input                        i_cpol,       	  // CPOL value - 0 or 1
  input                        i_cpha,       	  // CPHA value - 0 or 1 
  input                        i_lsb_first,  	  // lsb first when '1' /msb first when '0'

  output reg                   o_miso,        	// Slave output to Master
  input                        i_mosi,        	// Slave input from Master
  input                        i_ssn,         	// Slave Slect Active low
  input                        i_sclk,        	// Clock from SPI Master
  output                       miso_tri_en, 
  output reg                   o_tx_ack,    
  output reg                   o_tx_no_ack 
);


reg [DATA_SIZE - 1:0] data_in_reg_i;
reg [DATA_SIZE - 1:0] rxdata_reg_i;
reg [DATA_SIZE - 1:0] txdata_reg_i;
reg [DATA_SIZE - 1:0] rx_shift_data_pos_sclk_i;
reg [DATA_SIZE - 1:0] rx_shift_data_neg_sclk_i;
reg                   tx_error_i;
reg                   rx_error_i;
reg                   tx_ready_i;
reg                   rx_ready_i;
reg                   miso_00_i, miso_01_i, miso_10_i, miso_11_i;
reg                   rx_done_pos_sclk_i, rx_done_neg_sclk_i, rx_done_reg1_i, rx_done_reg2_i, rx_done_reg3_i;
reg                   tx_done_pos_sclk_i, tx_done_neg_sclk_i, tx_done_reg1_i, tx_done_reg2_i, tx_done_reg3_i;
reg            [5:0]  rx_data_count_pos_sclk_i;
reg            [5:0]  rx_data_count_neg_sclk_i;
reg            [5:0]  tx_data_count_pos_sclk_i;
reg            [5:0]  tx_data_count_neg_sclk_i;
reg                   data_valid_i;
wire                  tx_done_pulse_i;
reg                   tx_error_reg_1_i;
reg                   rx_error_reg_1_i;


assign o_tx_ready = tx_ready_i;
assign o_rx_ready = rx_ready_i;
assign o_tx_error = tx_error_i & (~tx_error_reg_1_i);
assign o_rx_error = rx_error_i & (~rx_error_reg_1_i);



// Data input latch process
// Latched only when slave enabled, Transmitter ready and wr is high.
   
generate if (DATA_SIZE == 8) begin
  assign o_data[7:0] = rxdata_reg_i;

  always @ (posedge i_sys_clk or posedge i_sys_rst)
  begin
    if(i_sys_rst == 1'b1) 
        data_in_reg_i <= 'd0;
    else
      if (i_wr == 1'b1 & i_csn == 1'b0 & tx_ready_i == 1'b1) 
        data_in_reg_i <= i_data[7:0];
  end
end
endgenerate
assign miso_tri_en = i_ssn;

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
  else
    txdata_reg_i <= data_in_reg_i;
end

//// SPI Slave Receiver Section

// MOSI Sampling : Sample at posedge of SCLK for 
//                 1. i_cpol=0 and i_cpha=0 
//                 2. i_cpol=1 and i_cpha=1 

always @ (posedge i_sclk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1)
    rx_shift_data_pos_sclk_i <= 'd0;
  else
    if( (i_ssn == 1'b0) & (( (i_cpol == 1'b0) & (i_cpha == 1'b0) ) | ( (i_cpol == 1'b1) & (i_cpha == 1'b1) ))) begin
      if(i_lsb_first == 1'b1)
        rx_shift_data_pos_sclk_i <= {i_mosi, rx_shift_data_pos_sclk_i[DATA_SIZE-1:1]};
      else
        rx_shift_data_pos_sclk_i <= {rx_shift_data_pos_sclk_i[DATA_SIZE-2:0], i_mosi};
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
        if(rx_data_count_pos_sclk_i == (DATA_SIZE - 1))
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
  else
    if((i_ssn == 1'b0) & (((i_cpol == 1'b1) & (i_cpha == 1'b0)) | ((i_cpol == 1'b0) & (i_cpha == 1'b1)))) begin
      if(i_lsb_first == 1'b1)
        rx_shift_data_neg_sclk_i <= {i_mosi, rx_shift_data_neg_sclk_i[DATA_SIZE-1:1]};
      else
        rx_shift_data_neg_sclk_i <= {rx_shift_data_neg_sclk_i[DATA_SIZE-2:0], i_mosi};
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



// SPI Slave Receiver Receive Done signal generator
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
    if (rx_done_reg2_i == 1'b1 & rx_done_reg3_i == 1'b0)
        rx_ready_i <= 1'b1;
    else if (i_ssn == 1'b1 & i_csn == 1'b0)
        rx_ready_i <= 1'b1;
    else if (i_ssn == 1'b0 & i_csn == 1'b0)
        rx_ready_i <= 1'b0;
  end
end

// Receive error when external interface hasn't read previous data
// A new data received, but last received data hasn't been read yet.

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
    if (i_sys_rst == 1'b1)
      rx_error_i     <= 1'b0;
    else begin
      if(rx_ready_i == 1'b0 & i_rd == 1'b1 & i_csn == 1'b0)
        rx_error_i <= 1'b1;
      else if(i_rd == 1'b1 & i_csn == 1'b0)
        rx_error_i <= 1'b0;
    end
end

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if (i_sys_rst == 1'b1)
    rx_error_reg_1_i <= 1'b0;
  else
    rx_error_reg_1_i <= rx_error_i;
end


//// SPI Slave Transmitter section 

// cpol=0 and cpha=0: data must be placed before rising edge of sclk

always @ (txdata_reg_i or tx_data_count_neg_sclk_i or i_lsb_first)
begin
  if(i_lsb_first == 1'b1)
    miso_00_i <= txdata_reg_i[tx_data_count_neg_sclk_i];
  else
    miso_00_i <= txdata_reg_i[DATA_SIZE - tx_data_count_neg_sclk_i - 'd1];
end

// cpol=1 and cpha=0: data must be placed before falling edge of sclk

always @ (txdata_reg_i or tx_data_count_pos_sclk_i or i_lsb_first)
begin
  if(i_lsb_first == 1'b1)
    miso_10_i <= txdata_reg_i[tx_data_count_pos_sclk_i];
  else
    miso_10_i <= txdata_reg_i[DATA_SIZE - tx_data_count_pos_sclk_i - 'd1];
end

// cpol=0 and cpha=1: data must be placed at rising edge of sclk

always @ (posedge i_sclk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) 
    miso_01_i <= 1'b1;
  else begin
    if(i_lsb_first == 1'b1)
      miso_01_i <= txdata_reg_i[tx_data_count_pos_sclk_i];
    else
      miso_01_i <= txdata_reg_i[DATA_SIZE - tx_data_count_pos_sclk_i - 'd1];
  end
end


// cpol=1 and cpha=1: data must be placed at falling edge of sclk

always @ (negedge i_sclk or posedge i_sys_rst)
begin
  if(i_sys_rst == 1'b1) 
    miso_11_i <= 1'b1;
  else begin
    if(i_lsb_first == 1'b1)
      miso_11_i <= txdata_reg_i[tx_data_count_neg_sclk_i];
    else
      miso_11_i <= txdata_reg_i[DATA_SIZE - tx_data_count_neg_sclk_i - 'd1];
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

always @ (i_ssn or i_cpol or i_cpha or miso_00_i or miso_01_i or miso_10_i or miso_11_i)
begin
  if (i_ssn == 1'b0) begin
      if ((i_cpol == 1'b0) & (i_cpha == 1'b0))
          o_miso <= miso_00_i;
      else if ((i_cpol == 1'b0) & (i_cpha == 1'b1))
          o_miso <= miso_01_i;
      else if ((i_cpol == 1'b1) & (i_cpha == 1'b0))
          o_miso <= miso_10_i;
      else
          o_miso <= miso_11_i;
  end
  else
      o_miso <= 1'b0;
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
// Transmitter ready goes low as soon as ssn goes low


always @ (posedge i_sys_clk or posedge i_sys_rst)
begin  // process tx_ready
	if(i_sys_rst == 1'b1)  	// asynchronous reset (active high)
	    tx_ready_i <= 1'b1;
	else begin  // rising clock edge
	  if (tx_done_reg2_i == 1'b1 & tx_done_reg3_i == 1'b0)
		  tx_ready_i <= 1'b1;
	  else if (i_ssn == 1'b1 & i_csn == 1'b0)
		  tx_ready_i <= 1'b1;
    else if (i_csn == 1'b0 & i_ssn == 1'b0)
      tx_ready_i <= 1'b0;
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


always @ (posedge i_sys_clk or posedge i_sys_rst)
begin
  if (i_sys_rst == 1'b1)
	  tx_error_reg_1_i <= 1'b0;
	else
	  tx_error_reg_1_i <= tx_error_i;
end

//// Tx ACK

// Data Valid in SPI slave interface
always @ (posedge i_sys_clk or posedge i_sys_rst)
begin  // process data_valid_proc
  if(i_sys_rst == 1'b1)  		// asynchronous reset (active high)
      data_valid_i <= 1'b0;
  else begin // rising clock edge
    if (i_wr == 1'b1 & i_ssn == 1'b0)
      data_valid_i <= 1'b1;
    else if (tx_done_pulse_i == 1'b1)
      data_valid_i <= 1'b0;
    else if (i_ssn == 1'b1)
      data_valid_i <= 1'b0;
  end
end

  
always @ (posedge i_sys_clk or posedge i_sys_rst)
begin  // process data_valid_proc
  if(i_sys_rst == 1'b1)  		// asynchronous reset (active high)
    o_tx_ack <= 1'b0;
  else begin  // rising clock edge
    if(i_ssn == 1'b1 & data_valid_i == 1'b1)
      o_tx_ack <= 1'b0;
    else if(tx_done_pulse_i == 1'b1 & data_valid_i == 1'b1)
      o_tx_ack <= 1'b1;
    else
      o_tx_ack <= 1'b0;
  end
end

always @ (posedge i_sys_clk or posedge i_sys_rst)
begin  // process data_valid_proc
  if(i_sys_rst == 1'b1)  		// asynchronous reset (active high)
      o_tx_no_ack <= 1'b0;
  else begin // rising clock edge
    if (i_ssn == 1'b1 & data_valid_i == 1'b1)
      o_tx_no_ack <= 1'b1;
    else if(tx_done_reg3_i == 1'b1 & data_valid_i == 1'b1)
      o_tx_no_ack <= 1'b0;
    else
      o_tx_no_ack <= 1'b0;
  end
end
  
assign tx_done_pulse_i = tx_done_reg2_i & (~tx_done_reg3_i);
  





endmodule