`timescale 1ns / 1ps

// LED Module demo code
// Numato Lab
// http://www.numato.com
// http://www.numato.cc
// License : CC BY-SA (http://creativecommons.org/licenses/by-sa/2.0/)

module led_driver(

    // Assuming 100MHz input clock. May need to adjust the counter below
    // if any other input frequency is used
         input      Clk,
            	 
    // Inputs from the Push Buttons.
         input [3:0]Switch,

   // Reg Interface
         input       reg_cs,
         input       reg_wr,
         input [7:0] reg_wdata,
         output [7:0]reg_rdata,
    
    // Output is shown on LED with different functionality.
         output reg [7:0]LED  
);

// Register used internally	
reg [24:0]count;
reg enable;


assign reg_rdata = LED;

// Provide the initial value
initial 
begin
   LED = 8'h01;
   count = 'h0;
end
        	                             
// Scale down the clock so that output is easily visible.
always @(posedge Clk) begin
   count <= count+1'b1;
   enable <= &count; // enable at roll over case
end  

// On every rising edge of enable check for the Push Button input.
always @(posedge Clk) begin
  if(reg_cs && reg_wr) begin
    LED <= reg_wdata;
  end else if(enable) begin
   LED <= !Switch[0] ? 8'd1   :  
          !Switch[1] ? 8'd2 :
          !Switch[2] ? 8'd4 :
          !Switch[3] ? 8'd8 : {LED[0],LED[7:1]};
	end
end
endmodule
