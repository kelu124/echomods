
module gray_counter 
#(
  parameter ADDRESS_WIDTH = 4
)
(
  input            i_clk,
  input            i_rst,
  input            i_ce,
  output reg [3:0] o_bin_cnt_out,
  output     [3:0] o_gray_cnt_out
);

reg [3:0] gray_count_i;
reg [3:0] binary_count_i;


// Binary count process
always @ (posedge i_clk or posedge i_rst)
begin
  if(i_rst == 1'b1) begin // Asynchronous reset (active high)
    binary_count_i <= 4'b0001;
  end
  else // Rising clock edge
  begin
    if(i_ce == 1'b1) begin
      binary_count_i <= binary_count_i + 1'b1;
    end
  end
end


// Gray counter
always @ (posedge i_clk or posedge i_rst)
begin
  if(i_rst == 1'b1) begin // Asynchronous reset (active high)
    gray_count_i <= 0;
    o_bin_cnt_out <= 0;
  end
  else begin // Rising clock edge
    if(i_ce == 1'b1) begin
      gray_count_i  <= {binary_count_i[3], (binary_count_i[2:0] ^ binary_count_i[3:1])};
      o_bin_cnt_out <= binary_count_i;
    end
  end
end

assign o_gray_cnt_out = gray_count_i;

endmodule