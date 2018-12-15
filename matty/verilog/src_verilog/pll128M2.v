module pll128M2(REFERENCECLK,
                           RESET,
                           PLLOUTCOREA,
                           PLLOUTCOREB,
                           PLLOUTGLOBALA,
                           PLLOUTGLOBALB);

input REFERENCECLK;
input RESET;    /* To initialize the simulation properly, the RESET signal (Active Low) must be asserted at the beginning of the simulation */ 
output PLLOUTCOREA;
output PLLOUTCOREB;
output PLLOUTGLOBALA;
output PLLOUTGLOBALB;

SB_PLL40_2F_CORE pll128M2_inst(.REFERENCECLK(REFERENCECLK),
                                          .PLLOUTCOREA(PLLOUTCOREA),
                                          .PLLOUTCOREB(PLLOUTCOREB),
                                          .PLLOUTGLOBALA(PLLOUTGLOBALA),
                                          .PLLOUTGLOBALB(PLLOUTGLOBALB),
                                          .EXTFEEDBACK(),
                                          .DYNAMICDELAY(),
                                          .RESETB(RESET),
                                          .BYPASS(1'b0),
                                          .LATCHINPUTVALUE(),
                                          .LOCK(),
                                          .SDI(),
                                          .SDO(),
                                          .SCLK());

//\\ Fin=12, Fout=128;
defparam pll128M2_inst.DIVR = 4'b0000;
defparam pll128M2_inst.DIVF = 7'b1010100;
defparam pll128M2_inst.DIVQ = 3'b011;
defparam pll128M2_inst.FILTER_RANGE = 3'b001;
defparam pll128M2_inst.FEEDBACK_PATH = "SIMPLE";
defparam pll128M2_inst.DELAY_ADJUSTMENT_MODE_FEEDBACK = "FIXED";
defparam pll128M2_inst.FDA_FEEDBACK = 4'b0000;
defparam pll128M2_inst.DELAY_ADJUSTMENT_MODE_RELATIVE = "FIXED";
defparam pll128M2_inst.FDA_RELATIVE = 4'b0000;
defparam pll128M2_inst.SHIFTREG_DIV_MODE = 2'b00;
defparam pll128M2_inst.PLLOUT_SELECT_PORTA = "GENCLK";
defparam pll128M2_inst.PLLOUT_SELECT_PORTB = "GENCLK_HALF";
defparam pll128M2_inst.ENABLE_ICEGATE_PORTA = 1'b0;
defparam pll128M2_inst.ENABLE_ICEGATE_PORTB = 1'b0;

endmodule
