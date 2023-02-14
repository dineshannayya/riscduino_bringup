`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   07:15:22 02/14/2023
// Design Name:   top
// Module Name:   /home/ise/github/mpw_bringup/mpw-2/numato_mimas_v2/hello_world/tb/tb_top.v
// Project Name:  hello_world
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: top
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_top;

	// Inputs
	reg sys_clk;
	reg SCK;
	reg CSB;
        reg [3:0] SDI;
        wire [3:0] SDO;
        reg spi_oeb;
	reg [3:0] Switch;

        reg [7:0] Rdata;

	// Outputs
	wire reset_n;
	wire [7:0] LED;

	// Bidirs
	tri [3:0] spi_sio;

        assign SDO = spi_sio;
        assign spi_sio = (spi_oeb) ? SDI : 4'bz;

	// Instantiate the Unit Under Test (UUT)
	top uut (
		.sys_clk(sys_clk), 
		.reset_n(reset_n), 
		.spi_sck(SCK), 
		.spi_csn(CSB), 
		.spi_sio(spi_sio), 
		.Switch(Switch), 
		.LED(LED)
	);

   always #12.5 sys_clk <= (sys_clk === 1'b0);
	
	initial begin
		// Initialize Inputs
		sys_clk = 0;
		SCK = 0;
		CSB = 1;
                spi_oeb = 0;
		Switch = 0;

		// Wait 100 ns for global reset to finish
		#100;
		 wait(reset_n == 1);

       start_csb;
       write_byte(8'hEB,2'b0, 4'b1); // CMD
       write_byte(8'h00,2'b10, 4'b100); // ADDR[23:16]
       write_byte(8'h02,2'b10, 4'b100); // ADDR[15:8]
       write_byte(8'h00,2'b10, 4'b100); // ADDR[7:0]
       write_byte(8'h00,2'b10, 4'b100); // DUMMY
       read_byte(Rdata,2'b10, 4'b100); // DUMMY
       read_byte(Rdata,2'b10, 4'b100); // DUMMY
       read_byte(Rdata,2'b10, 4'b100); // DUMMY
       read_byte(Rdata,2'b10, 4'b100); // DUMMY
       read_byte(Rdata,2'b10, 4'b100); // DUMMY
       read_byte(Rdata,2'b10, 4'b100); // DUMMY
       read_byte(Rdata,2'b10, 4'b100); // DUMMY
       read_byte(Rdata,2'b10, 4'b100); // DUMMY
       read_byte(Rdata,2'b10, 4'b100); // DUMMY
       read_byte(Rdata,2'b10, 4'b100); // DUMMY
       end_csb;
        
		#10000;  $finish;
		// Add stimulus here

	end


    // First define tasks for SPI functions

	task start_csb;
	begin
		SCK = 1'b0;
		SDI = 4'b0;
		CSB = 1'b0;
		#50;
	end
	endtask

	task end_csb;
	begin
		SCK = 1'b0;
		SDI = 4'b0;
		CSB = 1'b1;
		#50;
	end
	endtask

	task write_byte;
	input [7:0] odata;
   input [1:0] mode;
   input [3:0] step;
   integer i;
	begin
		SCK = 1'b0;
                spi_oeb = 1;
		for (i=7; i >= 0; i=i-step) begin
		    #50;
                 case(mode)
                 2'b00: begin
		              SDI[0] = odata[i];
                 end
                 2'b01: begin
		              SDI[1] = odata[i];
		              SDI[0] = odata[i-1];
                 end
                 2'b10: begin
		              SDI[3] = odata[i];
		              SDI[2] = odata[i-1];
		              SDI[1] = odata[i-2];
		              SDI[0] = odata[i-3];
                 end
                 endcase
          #50;  SCK = 1'b1;
          #100; SCK = 1'b0;
		end
                spi_oeb = 0;
	    end
	endtask

	task read_byte;
	output [7:0] idata;
   input [1:0] mode;
   input [3:0] step;
   reg [7:0] idata;
   integer i;
	begin
		SCK = 1'b0;
		SDI = 1'b0;
      spi_oeb = 0;
		for (i=7; i >= 0; i=i-step) begin
		    #50;
           case(mode)
           2'b00: begin
		           idata[i] = SDO[0];
              end
           2'b01: begin
		           SDI[i]   = SDO[1];
		           SDI[i-1] = SDO[0];
              end
           2'b10: begin
		           SDI[i]   = SDO[3];
		           SDI[i-1] = SDO[2];
		           SDI[i-2] = SDO[1];
		           SDI[i-3] = SDO[0];
               end
            endcase
            #50;  SCK = 1'b1;
            #100; SCK = 1'b0;
		end
	 end
	endtask      
endmodule

