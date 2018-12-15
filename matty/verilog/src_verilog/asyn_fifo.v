
module asyn_fifo 
#(
  parameter DATA_SIZE = 16,
  parameter ADDRESS_WIDTH = 4
)
(
  input             i_rst,
  input             i_rd_clk,
  input             i_rd_en,
  output reg [15:0] o_rd_data,
  output            o_empty,
  input             i_wr_clk,
  input             i_wr_en,
  input      [15:0] i_wr_data,
  output            o_half_full,
  output            o_full
);

parameter FIFO_DEPTH = 2**ADDRESS_WIDTH;
reg [FIFO_DEPTH - 1:0] ram_array_i [DATA_SIZE - 1:0];



reg  [1:0]                 rd_empty_i;
reg  [1:0]                 wr_full_i;
reg                        fifo_status_i;
wire [ADDRESS_WIDTH - 1:0] rd_ptr_i;
wire [ADDRESS_WIDTH - 1:0] wr_ptr_i;
// wire [ADDRESS_WIDTH - 1:0] wr_addr_i; // Not present
wire                       matchptr_i;
wire                       rd_en_int_i;
wire                       wr_en_int_i;
wire                       set_status_i;
wire                       rst_status_i;
wire                       detect_full_i;
wire                       detect_empty_i;
reg                        fifo_status_rd_clk_i;
reg                        fifo_status_wr_clk_i;
wire                       fifo_status_reg_i;
wire [ADDRESS_WIDTH - 1:0] wr_ptr_bin_i;
wire [ADDRESS_WIDTH - 1:0] rd_ptr_bin_i;
reg  [ADDRESS_WIDTH - 1:0] ptr_diff_i;

gray_counter
#(
  .ADDRESS_WIDTH(ADDRESS_WIDTH)
)
u0_gray_counter
(
  .i_clk(i_wr_clk),
  .i_rst(i_rst),
  .i_ce(wr_en_int_i),
  .o_bin_cnt_out(wr_ptr_bin_i),
  .o_gray_cnt_out(wr_ptr_i)
);

gray_counter
#(
  .ADDRESS_WIDTH(ADDRESS_WIDTH)
)
u1_gray_counter
(
  .i_clk(i_rd_clk),
  .i_rst(i_rst),
  .i_ce(rd_en_int_i),
  .o_bin_cnt_out(rd_ptr_bin_i),
  .o_gray_cnt_out(rd_ptr_i)
);

// Read data from Memory
always @ (posedge i_rd_clk)
begin
  if( (i_rd_en == 1'b1) & (rd_empty_i[1] == 1'b0) )
    o_rd_data <= ram_array_i[rd_ptr_i];
end

// Write data into Memory
always @ (posedge i_wr_clk)
begin
  if( (i_wr_en == 1'b1) & (wr_full_i[1] == 1'b0) )
    ram_array_i[wr_ptr_i] <= i_wr_data;
end

// Binary pointer difference
always @ (wr_ptr_bin_i or rd_ptr_bin_i) begin
  if (wr_ptr_bin_i > rd_ptr_bin_i)
    ptr_diff_i <= wr_ptr_bin_i - rd_ptr_bin_i;
  else if(rd_ptr_bin_i > wr_ptr_bin_i)
    ptr_diff_i <= ((FIFO_DEPTH - rd_ptr_bin_i) + wr_ptr_bin_i);
  else
    ptr_diff_i <= {ADDRESS_WIDTH{1'b0}};
end

assign o_half_full = ptr_diff_i[ADDRESS_WIDTH - 1];

// Internal Fifo write and read enable
assign wr_en_int_i = i_wr_en & (~wr_full_i[1]);
assign rd_en_int_i = i_rd_en & (~rd_empty_i[1]);

// Check if write and read pointer match
assign matchptr_i = wr_ptr_i == rd_ptr_i ? 1'b1 : 1'b0;

// Set fifo status by comparing write and read pointer
assign set_status_i = (wr_ptr_i[ADDRESS_WIDTH-2] ~^ rd_ptr_i[ADDRESS_WIDTH-1]) &
                      (wr_ptr_i[ADDRESS_WIDTH-1] ^ rd_ptr_i[ADDRESS_WIDTH-2]);
assign rst_status_i = (wr_ptr_i[ADDRESS_WIDTH-2] ^ rd_ptr_i[ADDRESS_WIDTH-1]) &
                      (wr_ptr_i[ADDRESS_WIDTH-1] ~^ rd_ptr_i[ADDRESS_WIDTH-2]);

// Fifo status read clock register
always @ (posedge i_rd_clk or posedge i_rst) 
begin
  if(i_rst == 1'b1)
    fifo_status_rd_clk_i <= 1'b0;
  else
    fifo_status_rd_clk_i <= fifo_status_i;
end

// Fifo status write clock register
always @ (posedge i_wr_clk or posedge i_rst) 
begin
  if(i_rst == 1'b1)
    fifo_status_wr_clk_i <= 1'b0;
  else
    fifo_status_wr_clk_i <= fifo_status_i;
end

assign fifo_status_reg_i = fifo_status_rd_clk_i | fifo_status_wr_clk_i;

// Staus
always @ (rst_status_i or fifo_status_reg_i or i_rst or set_status_i)
begin
  if( (rst_status_i == 1'b1) | (i_rst == 1'b1) )
      fifo_status_i <= 1'b0;
  else if (set_status_i == 1'b1)
      fifo_status_i <= 1'b1;
  else
      fifo_status_i <= fifo_status_reg_i;
end

// Full Detection
assign detect_full_i = fifo_status_i & matchptr_i;


// Register full
always @ (posedge i_wr_clk or posedge detect_full_i)
begin
  if(detect_full_i == 1'b1)
    wr_full_i <= 2'b11;
  else 
    wr_full_i <= {wr_full_i[0], detect_full_i};
end

// Empty Detection
assign detect_empty_i = (~fifo_status_i) & matchptr_i;

// Register Empty
always @ (posedge i_rd_clk or posedge detect_empty_i)
begin
  if(detect_empty_i == 1'b1)
    rd_empty_i <= 2'b11;
  else
    rd_empty_i <= {rd_empty_i[0], detect_empty_i};
end

assign o_full = wr_full_i[1];
assign o_empty = rd_empty_i[1];

endmodule