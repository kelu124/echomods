//////////////////////////////////////////////////////////////////////////////////
// Company: un0rick
// Engineer: Kelu & David
//
// Create Date:    2018
// Design Name: 	MATTY
// Module Name:    MATTY_MAIN_VHDL
// Project Name:   MATTY
// Target Devices: iCE40-HX4K_TQ144

//

// Revision: 1

//
//////////////////////////////////////////////////////////////////////////////////

module MATTY_MAIN_VHDL
( 	
  input             clk,
  input             reset_alim,
  input             reset_ft,
  input             reset_rpi,
  output            LED_ACQ,
  output            LED_MODE,
  output            LED3,
  input             spi_cs_ft,
  input             spi_sclk_ft,
  input             spi_mosi_ft,
  output            spi_miso_ft,
  input             spi_cs_rpi,
  input             spi_sclk_rpi,
  input             spi_mosi_rpi,
  output            spi_miso_rpi,
  output            spi_cs_flash,
  output            spi_sclk_flash,
  output            spi_mosi_flash,
  input             spi_miso_flash,
  input             cs_rpi2flash,
  input             spi_select,

  output            DAC_cs,
  output            DAC_sclk,
  output            DAC_mosi,
  input             ADC0,
  input             ADC1,
  input             ADC2,
  input             ADC3,
  input             ADC4,
  input             ADC5,
  input             ADC6,
  input             ADC7,
  input             ADC8,
  input             ADC9,
  output            ADC_clk,


  inout      [15:0] RAM_DATA,
  output     [18:0] RAM_ADD,

  output            RAM_nCE,
  output            RAM_nOE,
  output            RAM_nWE,
  output            RAM_nLB,
  output            RAM_nUB,

  input             trig_ext,
  input             trig_rpi,
  input             trig_ft,
  input             button_trig,
  input             button_mode,
  output            pon,
  output            poff,
  input             top_tour1,
  input             top_tour2
);

reg        ram_data_enable;
reg [15:0] RAM_DATA_latched;
assign RAM_DATA = ram_data_enable ? RAM_DATA_latched : 16'hzz;

wire pll_clk128; //simu
wire pll_clk64;//simu

wire reset;

wire trig;

wire spi_cs;
wire spi_mosi;
wire spi_miso;
wire spi_sclk;

reg  [7:0] spi_data_miso          =  'd0;
wire       spi_miso_ready;
reg        spi_miso_valid         = 1'b0;
wire [7:0] spi_data_mosi;
wire       spi_mosi_ready;
reg        spi_mosi_ready_prev    = 1'b0;
reg        spi_mosi_ready_prev2   = 1'b0;
reg        spi_mosi_ready_prev3   = 1'b0;
reg        spi_mosi_ready64_prev  = 1'b0;
reg        spi_mosi_ready64_prev2 = 1'b0;
reg        spi_mosi_ready64_prev3 = 1'b0;
wire       spi_miso_ack;


wire stop_tour1 = 1'b0;
wire stop_tour2 = 1'b0;


wire sSPI_MISO = 1'b0;
wire sPon;
wire sPoff;


wire [3:0] sDAC_CSarray;
wire       sDAC_mosi;
wire       sDAC_sclk;


reg  [18:0]	sRAM_ADD =  'd0;
wire	      sRAM_nWE;


//configuration registers
reg 	 [7:0] sEEPon               =  8'h14;		//50ns to 500ns def:200ns	resolution 10ns
reg    [7:0] sEEPonPoff           =  8'h0A;        //0ns to 2550ns def:100ns   resolution 10ns
reg 	[15:0] sEEPoff              = 16'h00C8;  //		//500ns to 3us def:2us
reg	         sTrigInternal        =  1'b0;			// trig when rising
reg	         sEETrigInternal      =  1'b0;			// trig when rising  form SPI
reg	         sEETrigInternal_prev =  1'b0;
reg          sEESingleCont        =  1'b0;			// single if 0
reg          sSingleCont          =  1'b0;			// single if 0
reg	         sACQ                 =  1'b0;	// 1 during acqusition
reg 	[15:0] sEEDelayACQ          = 16'h02BC;	// 0us to 50us def 7us
wire	       sDelayACQ            =  1'b0;
reg 	[15:0] sEEACQ               = 16'h32C8;		//50us to 130us		def 130us	  	 6590
wire	       sACQtime;
reg 	[23:0] sEEPeriod            = 24'h0186A0;	//700us to 10ms def 1ms 	 0186A0
wire	       sPeriod;
wire	       sDACDyn;
reg 	       sPeriod_prev         =  1'b0;
reg 	 [7:0] sEETrigCounter       =  8'h0A; // number of acquisition secquence in continious mode
reg 	 [7:0] sTrigCounter         =  8'h00;
reg  	       sSPI_MSB0LSB1        =  1'b0;

//counters
reg  [23:0] sCounter;

// DAC
reg  [15:0] sDAC_data        = 16'b0011000000000000; // default mask
reg         sDAC_spi_start   = 1'b0;
reg   [7:0] sEEDAC           = 8'h11;
reg   [9:0] sCounterDAC      = 10'b0000000000; // clk for DAC update period 5us X"3E8"
reg   [7:0] sDAC_mem_pointer = 8'h00;

// ADC
reg   [7:0] sCounterADC   = 8'h00; // to set up frequency
reg         sADC_clk      = 1'b0;
reg        sADC_clk_prev  = 1'b0;
reg   [7:0] sEEADC_freq   = 8'h03;
wire [11:0] sADC_data     =  'd0;

wire sADC0 = 1'b0;
wire sADC1 = 1'b0;
wire sADC2 = 1'b0;
wire sADC3 = 1'b0;
wire sADC4 = 1'b0;
wire sADC5 = 1'b0;
wire sADC6 = 1'b0;
wire sADC7 = 1'b0;
wire sADC8 = 1'b0;
wire sADC9 = 1'b0;

//RAM
reg  [18:0] sRAM_pointer_read  =  'd0;
reg  [18:0] sRAM_pointer_write =  'd0;
reg         sEEPointerReset    = 1'b0;
reg  [7:0] sCounterRAM         = 8'h00; // to set up frequency
reg         sRead_data         = 1'b0;

//SPI
reg [1:0] sPointer = 'd0;
reg [7:0] sAddress = 'd0;



// edge
wire        spi_cs_prev             = 1'b0;
wire        button_mode_prev        = 1'b0;
reg  [23:0] button_debounce_counter =  'd0;
reg         trig_prev               = 1'b0;
wire        nrst;
reg         sbuttonModeStatus       = 1'b0;

reg   [7:0] sDAC_mem [1:42];


  
pll128M2 pll128M2_inst7 //simu
(
  .REFERENCECLK(clk),
  .PLLOUTCOREA(pll_clk128),
  .PLLOUTGLOBALA(),
  .PLLOUTCOREB(pll_clk64),
  .PLLOUTGLOBALB(),
  .RESET(reset)
);


SPI_SLAVE_ICE spi_slave_inst
(
  .i_sys_clk(pll_clk128), // system clock
  .i_sys_rst(nrst),  // high low synchronous reset //simu
  // SPI SLAVE INTERFACE
  .i_sclk(spi_sclk ),
  .i_ssn(spi_cs),
  .i_mosi(spi_mosi),
  .o_miso(spi_miso),
  // USER INTERFACE
  .o_data(spi_data_mosi),
  .i_wr(1'b1),//spi_miso_write_enable, //write enable at low
  .i_rd(1'b1),//spi_mosi_read_enable, //read enable at high
  .o_tx_ready(spi_miso_ready),
  .i_data(spi_data_miso),
  .o_rx_ready(spi_mosi_ready),

  //config
  .i_csn(nrst),//
  .miso_tri_en(),
  .i_cpol(1'b0),
  .i_cpha(1'b0),//
  .i_lsb_first(1'b0),
  .o_tx_error(),
  .o_rx_error(),
  .o_tx_ack(spi_miso_ack),
  .o_tx_no_ack()
);


spi_master spi_master_inst
(
  .i_sys_clk(pll_clk64),  // system clock
  .i_sys_rst(nrst),  // system reset //simu
  .i_csn(1'b0),  // chip select for SPI master
  .i_data(sDAC_data),  // Input data
  .i_wr(1'b1),  // Active Low Write, Active High Read
  .i_rd(1'b1),  // Active Low Write, Active High Read
  .o_data(),  //output data
  .o_tx_ready(),  // Transmitter ready, can write another data
  .o_rx_ready(),  // Receiver ready, can read data
  .o_tx_error(),  // Transmitter error
  .o_rx_error(),  // Receiver error
  .o_intr(),
  .i_slave_addr(2'b00),  // Slave Address
  .i_cpol(1'b0),  // CPOL value - 0 or 1
  .i_cpha(1'b0), // CPHA value - 0 or 1
  .i_lsb_first(1'b0),  // lsb first when '1' /msb first when
  .i_spi_start(sDAC_spi_start),  // START SPI Master Transactions
  .i_clk_period(8'h06),  // SCL clock period in terms of i_sys_clk
  .i_setup_cycles(8'h05),  // SPIM setup time  in terms of i_sys_clk
  .i_hold_cycles(8'h05),  // SPIM hold time  in terms of i_sys_clk
  .i_tx2tx_cycles(8'h0A),  // SPIM interval between data transactions in terms of i_sys_clk
  .o_slave_csn(sDAC_CSarray),  // SPI Slave select (chip select) active low
  .o_mosi(sDAC_mosi),  // Master output to Slave
  .i_miso(1'b0),  // Master input from Slave
  .o_sclk(sDAC_sclk),  // Master clock
  .mosi_tri_en()
);


///////////////////////////////trig management/////////////////////////////////////////////////

always @ (posedge pll_clk128 or negedge reset)
begin
  if(reset == 1'b0) begin
      sTrigInternal        <= 1'b0;
      trig_prev            <= 1'b0;
      sPeriod_prev         <= 1'b0;
      sEETrigInternal_prev <= 1'b0;
  end
  else begin
    if( (  (trig_prev == 1'b0 & trig == 1'b1) | (sEETrigInternal_prev == 1'b0 & sEETrigInternal == 1'b1) | (sSingleCont == 1'b1 & sPeriod_prev == 1'b1 & sPeriod == 1'b0 & sTrigCounter < (sEETrigCounter - 'd1)) ) & sCounter != 24'h000010)
    begin
      sTrigInternal <= 1'b1;
      sTrigCounter  <= sTrigCounter + 'd1;
    end
    else if(sCounter == 24'h000010)
    begin
      sTrigInternal <= 1'b0;
    end


    if((trig_prev == 1'b0 & trig == 1'b1) | (sEETrigInternal_prev == 1'b0 & sEETrigInternal == 1'b1))
    begin
      sTrigCounter <= 8'h00;
    end

    sEETrigInternal_prev <=sEETrigInternal;
    sPeriod_prev <= sPeriod;
    trig_prev <= trig;
  end
end


always @ (reset or sTrigInternal or sCounter)
begin
  if(reset == 1'b0)
      sACQ <= 1'b0;
  else if(sTrigInternal == 1'b1 | (sCounter > 1 & sCounter <= sEEPeriod))
      sACQ <= 1'b1; // signal that indicates you are doing an acquisition
  else
      sACQ <= 1'b0;
end


///////////////////////////////end trig management/////////////////////////////////////////////////

/////////////////////////////////Counter signal generation/////////////////////////////////////////////////////////
always @ (posedge pll_clk128 or negedge reset)
begin
  if(reset == 1'b0)
    sCounter <= 24'h000000;
  else
    if(sACQ == 1'b0)
      sCounter <= 24'h000000;	//start counting
    else
      sCounter <= sCounter + 'd1;
end

/////////////////////////////////End Counters///////////////////////////////////

//////////////////////////////Signal generation/////////////////////////////////////
//PON
assign sPon = sCounter > 0 & sCounter <= sEEPon;

//POFF
assign sPoff = sCounter  > (sEEPonPoff) & sCounter  < (sEEPoff) ? 1'b0 : 1'b1;

// ACQUISITION
assign sACQtime = sCounter  > (sEEDelayACQ ) & sCounter  < (sEEACQ);

//PERIOD GLOBALE for continious mode
assign sPeriod = sCounter > 0 &  sCounter  <= sEEPeriod;

// DAC DYNAMIC
assign sDACDyn = sCounter  > 0 & sCounter  <= (sEEACQ);

//////////////////////////////End Signal generation/////////////////////////////////////

integer i;
always @ (posedge pll_clk128 or negedge reset) //pll_clk128
begin


  if(reset == 1'b0)
  begin
    sAddress <= 8'h00;
    sPointer <= 2'b00;



    sEEACQ            <=  16'h32C8;
    sEEPon            <=  8'h14;
    sEEPonPoff        <=  8'h0A;
    sEEPoff           <=  16'h00C8;
    sEETrigInternal   <=  1'b0;
    sEESingleCont     <=  1'b0;
    sEEDelayACQ       <=  16'h02BC;
    sEEPeriod         <=  24'h0186A0;
    sEETrigCounter    <=  8'h0A;


    for(i = 1; i <= 42; i=i+1) sDAC_mem[i] <= 8'h00;
  end
  else begin
    if(spi_mosi_ready64_prev3 == 1'b0 & spi_mosi_ready64_prev2 == 1'b1 & spi_mosi_ready64_prev == 1'b1 & spi_mosi_ready == 1'b1) begin //with debounce as the module gives a two  edges at each transfer
        if(sPointer <= 2'b00) begin
          if(spi_data_mosi == 8'hAA) begin // detect configuration
            sPointer <= 2'b01;
          end
          sEETrigInternal <= 1'b0; // auto reset for SPI trig
        end
        else if(sPointer <= 2'b01) begin  // get register address
          sAddress <= spi_data_mosi;
          sPointer <= 2'b10;
          sEEPointerReset <= 1'b0;
        end
        else if(sPointer <= 2'b10) begin  // get value
          sPointer <= 2'b00;

          case(sAddress)
            8'h10:
              sDAC_mem[1]  <= spi_data_mosi;
            8'h11:
              sDAC_mem[2]  <= spi_data_mosi;
            8'h12:
              sDAC_mem[3]  <= spi_data_mosi;
            8'h13:
              sDAC_mem[4]  <= spi_data_mosi;
            8'h14:
              sDAC_mem[5]  <= spi_data_mosi;
            8'h15:
              sDAC_mem[6]  <= spi_data_mosi;
            8'h16:
              sDAC_mem[7]  <= spi_data_mosi;
            8'h17:
              sDAC_mem[8]  <= spi_data_mosi;
            8'h18:
              sDAC_mem[9]  <= spi_data_mosi;
            8'h19:
              sDAC_mem[10] <= spi_data_mosi;
            8'h1A:
              sDAC_mem[11] <= spi_data_mosi;
            8'h1B:
              sDAC_mem[12] <= spi_data_mosi;
            8'h1C:
              sDAC_mem[13] <= spi_data_mosi;
            8'h1D:
              sDAC_mem[14] <= spi_data_mosi;
            8'h1E:
              sDAC_mem[15] <= spi_data_mosi;
            8'h1F:
              sDAC_mem[16] <= spi_data_mosi;
            8'h20:
              sDAC_mem[17] <= spi_data_mosi;
            8'h21:
              sDAC_mem[18] <= spi_data_mosi;
            8'h22:
              sDAC_mem[19] <= spi_data_mosi;
            8'h23:
              sDAC_mem[20] <= spi_data_mosi;
            8'h24:
              sDAC_mem[21] <= spi_data_mosi;
            8'h25:
              sDAC_mem[22] <= spi_data_mosi;
            8'h26:
              sDAC_mem[23] <= spi_data_mosi;
            8'h27:
              sDAC_mem[24] <= spi_data_mosi;
            8'h28:
              sDAC_mem[25] <= spi_data_mosi;
            8'h29:
              sDAC_mem[26] <= spi_data_mosi;
            8'h2A:
              sDAC_mem[27] <= spi_data_mosi;
            8'h2B:
              sDAC_mem[28] <= spi_data_mosi;
            8'h2C:
              sDAC_mem[29] <= spi_data_mosi;
            8'h2D:
              sDAC_mem[30] <= spi_data_mosi;
            8'h2E:
              sDAC_mem[31] <= spi_data_mosi;
            8'h2F:
              sDAC_mem[32] <= spi_data_mosi;
            8'h30:
              sDAC_mem[33] <= spi_data_mosi;
            8'h31:
              sDAC_mem[34] <= spi_data_mosi;
            8'h32:
              sDAC_mem[35] <= spi_data_mosi;
            8'h33:
              sDAC_mem[36] <= spi_data_mosi;
            8'h34:
              sDAC_mem[37] <= spi_data_mosi;
            8'h35:
              sDAC_mem[38] <= spi_data_mosi;
            8'h36:
              sDAC_mem[39] <= spi_data_mosi;
            8'h37:
              sDAC_mem[40] <= spi_data_mosi;
            8'h38:
              sDAC_mem[41] <= spi_data_mosi;
            8'h39:
              sDAC_mem[42] <= spi_data_mosi;
            8'hD0:
              sEEPonPoff <= spi_data_mosi;
            8'hE0:
              sEEPon <= spi_data_mosi;
            8'hE1:
              sEEPoff[15:8] <=spi_data_mosi;
            8'hE2:
              sEEPoff[7:0]  <=spi_data_mosi;
            8'hE3:
              sEEDelayACQ[15:8] <= spi_data_mosi;
            8'hE4:
              sEEDelayACQ[7:0]  <= spi_data_mosi;
            8'hE5:
              sEEACQ[15:8] <= spi_data_mosi;
            8'hE6:
              sEEACQ[7:0] <= spi_data_mosi;
            8'hE7:
              sEEPeriod[23:16] <= spi_data_mosi;
            8'hE8:
              sEEPeriod[15:8] <= spi_data_mosi;
            8'hE9:
              sEEPeriod[7:0] <= spi_data_mosi;
            8'hEA:
              sEETrigInternal <= spi_data_mosi[0];
            8'hEB:
              sEESingleCont <= spi_data_mosi[0];
            8'hEC:
              sEEDAC <= spi_data_mosi;
            8'hED:
              sEEADC_freq <= spi_data_mosi;
            8'hEE:
              sEETrigCounter <= spi_data_mosi;
            8'hEF:
              sEEPointerReset <= spi_data_mosi[0];
            default:
              ;
          endcase
        end
        else begin
          sAddress <= 8'h00;
          sPointer <= 2'b00;
        end
        
    end
        spi_mosi_ready64_prev3<= spi_mosi_ready64_prev2;
        spi_mosi_ready64_prev2<= spi_mosi_ready64_prev;
        spi_mosi_ready64_prev<= spi_mosi_ready;
  end
end


//////////////////////DAC////////////////////-MCP4811 - clock max 20Mhz in use 20Mhz - transmit data every 5us

always @ (posedge pll_clk64 or negedge reset)
begin
  if(reset == 1'b0) begin
      sCounterDAC <= 'd0;
      sDAC_spi_start <= 1'b0;

      sDAC_data <= 'd0;
      sDAC_mem_pointer <= 'd0;
  end
  else begin
    sCounterDAC <= sCounterDAC + 'd1;
    if(sCounterDAC ==  'd319) begin
      sCounterDAC <= 'd0;
      sDAC_spi_start <= 1'b1;
    end
    else if(sCounterDAC == 'd5) begin
      sDAC_spi_start <= 1'b0;
    end
    else if(sCounterDAC == 'd300) begin
          if(sDACDyn == 1'b1 & sDAC_mem_pointer <= 'd42) begin
            sDAC_data <= {5'b00110, sDAC_mem[sDAC_mem_pointer], 3'b000};
            //sDAC_data <= B"00110" & sEEDAC & B"000"; // for no dynamic use
            sDAC_mem_pointer <= sDAC_mem_pointer + 'd1;
          end
          else
          begin
            sDAC_data <= {5'b00110, sEEDAC & 3'b000};
            sDAC_mem_pointer <= 8'd1;
          end
    end
  end
end

//////////////////////end DAC////////////////////

//////////////////////ADC//////////////////// ADC10065  - CLK max 65MHz
always @ (posedge pll_clk128 or negedge reset) // ADC CLK generation during Acquisition time
begin
  if(reset == 1'b0) begin
    sADC_clk <= 1'b0;
    sCounterADC <= 'd0;
  end
  else begin
    if(sACQtime == 1'b1) begin
      sCounterADC <= sCounterADC + 'd1;
      if(sCounterADC ==  sEEADC_freq) begin
        sCounterADC <= 'd0;
        sADC_clk <= ~sADC_clk;
      end
    end
    else begin
      sADC_clk <= 1'b0;
    end
  end
end

//////////////////////end ADC////////////////////



// //////////////////////RAM&ADC////////////////////



always @ (posedge pll_clk128 or negedge reset)// ADC CLK generation during Acquisition time
begin
  if(reset  == 1'b0) begin
      spi_data_miso        <=  8'h36;
      sCounterRAM          <=   'd0;
      sRAM_pointer_write   <=   'd0;
      sRAM_pointer_read    <=   'd0;
      sSPI_MSB0LSB1        <=  1'b0;
      spi_mosi_ready_prev  <=  1'b0;
      spi_mosi_ready_prev2 <=  1'b0;
      spi_mosi_ready_prev3 <=  1'b0;
      sRead_data           <=  1'b0;
      RAM_DATA_latched     <= 16'hxxxx;
      ram_data_enable      <=  1'b0;
      spi_miso_valid       <=  1'b0;
  end
  else begin

    sCounterRAM <= sCounterRAM + 'd1;

    if(sACQtime == 1'b1) begin
      if(sADC_clk_prev == 1'b0 & sADC_clk == 1'b1) begin // save in RAM the current ADC value
        sRAM_ADD <= sRAM_pointer_write;
        sRAM_pointer_write <= sRAM_pointer_write+1;
        RAM_DATA_latched <= {1'b1, sTrigCounter[1:0], top_tour2, top_tour1, ADC9, ADC8, ADC7, 1'b0, ADC6, ADC5, ADC4, ADC3, ADC2, ADC1, ADC0};
        ram_data_enable  <= 1'b1;
        sCounterRAM<= 'd0;
      end

      sADC_clk_prev  <= sADC_clk;
      spi_data_miso  <= 8'h81;  // during acq the SPI return 0x81 value
      spi_miso_valid <= 1'b1;
    end
    else if(sACQtime == 1'b0) begin
      RAM_DATA_latched <= 16'hxxxx;		// free Ram BUS
      ram_data_enable <= 1'b0;

      // SPI data send when there is no acq

      if(spi_mosi_ready_prev3 == 1'b0 & spi_mosi_ready_prev2 == 1'b1 & spi_mosi_ready_prev == 1'b1 & spi_mosi_ready == 1'b1) begin
        sRAM_ADD <= sRAM_pointer_read; //-new address pointer on the RAM address bus
        //Mechanism to alternated MSB and LSB word
        if(sSPI_MSB0LSB1 == 1'b0) begin                     // send on SPI MSB of data
          sCounterRAM<= 'd0;////-
          sRead_data <= 1'b1;
          sSPI_MSB0LSB1 <= ~sSPI_MSB0LSB1;
        end
        else begin                                        // send on SPI LSB of data 
          spi_data_miso <= RAM_DATA_latched[7:0];
          sRAM_pointer_read <= sRAM_pointer_read + 'd1;
          sSPI_MSB0LSB1 <= ~sSPI_MSB0LSB1;
          spi_miso_valid <= 1'b1;
        end
      end


      //Mechanism to read the data on the bus only once per 2 SPI transfers with delay to be sure the data in ready on the bus
      if(sRead_data == 1'b1) begin
        if(sCounterRAM == 'd8) begin
          spi_data_miso <= RAM_DATA_latched[15:8];
          sRead_data <= 1'b0;
        end
        else if(sCounterRAM == 'd9) begin
            spi_miso_valid <= 1'b1;
        end
      end
      
    end

    if(sEEPointerReset == 1'b1) begin    // reset pointer from SPI order
        sRAM_pointer_write<= 'd0;
        sRAM_pointer_read<= 'd0;
    end
      
    spi_mosi_ready_prev3 <= spi_mosi_ready_prev2;
    spi_mosi_ready_prev2 <= spi_mosi_ready_prev;
    spi_mosi_ready_prev  <= spi_mosi_ready;
  end
end


assign sRAM_nWE = sACQtime == 1'b1 ? sADC_clk : 1'b1;



// //////////////////////end RAM////////////////////


//////////////////////Buttons toggle mode////////////////////

always @ (posedge pll_clk64 or negedge reset)
begin
  if(reset == 1'b0) begin
    sSingleCont <= 1'b0;
  end
  else begin


    if(button_mode == 1'b1) begin
        button_debounce_counter <= button_debounce_counter + 1;
    end
    else begin
        button_debounce_counter <= 24'h000000;
    end

    if(button_debounce_counter == 24'hFFFFFF) begin
        sbuttonModeStatus <= ~sbuttonModeStatus;
    end

    sSingleCont <= sbuttonModeStatus ^ sEESingleCont;
  end
end

//////////////////////end Button////////////////////


//////////////////////Logic////////////////////

//reset
assign reset = reset_rpi; // to do not take into account the power supply Master reset component

//communication spi
assign spi_sclk     = spi_select == 1'b1 ? spi_sclk_rpi : spi_sclk_ft;
assign spi_mosi     = spi_select == 1'b1 ? spi_mosi_rpi : spi_mosi_ft;
assign spi_miso_rpi = (spi_select == 1'b1 & cs_rpi2flash == 1'b0) ? spi_miso :
                      (spi_select == 1'b1 & cs_rpi2flash == 1'b1) ? spi_miso_flash : 1'b0;

assign spi_miso_ft = spi_select == 1'b0 ? spi_miso   : 1'b0;
assign spi_cs      = spi_select == 1'b1 ? spi_cs_rpi : spi_cs_ft;


// Rpi Flash link
assign spi_sclk_flash = cs_rpi2flash == 1'b1 ? spi_sclk_rpi : 1'b0;
assign spi_mosi_flash = cs_rpi2flash == 1'b1 ? spi_mosi_rpi : 1'b0;
assign spi_cs_flash   = cs_rpi2flash == 1'b1 ? spi_cs_rpi   : 1'b0;

//trig
assign trig = trig_ext == 1'b1 | trig_rpi == 1'b1 | trig_ft == 1'b1;



// //////////////////////End Logic////////////////////

//////////////////////outputs////////////////////


assign nrst     = ~reset;
assign pon      = sPon;
assign poff     = sPoff;
assign DAC_sclk = sDAC_sclk;
assign DAC_cs   = sDAC_CSarray[0];
assign DAC_mosi = sDAC_mosi;
assign ADC_clk  = sADC_clk;
assign RAM_nUB  = 1'b0; //sRAM_nUB;
assign RAM_nLB  = 1'b0; //sRAM_nLB;
assign RAM_nWE  = sRAM_nWE;
assign RAM_nOE  = 1'b0; //sRAM_nOE;
assign RAM_nCE  = 1'b0; //sRAM_nCE;
assign RAM_ADD  = sRAM_ADD;
assign LED_ACQ  = sACQ;
assign LED_MODE = sSingleCont;
assign LED3     = reset;

endmodule