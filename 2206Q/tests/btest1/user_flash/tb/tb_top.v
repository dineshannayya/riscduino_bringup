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
	tri [37:0] mprj_io;

    reg        err_flag;

  assign SDO = mprj_io[36:33];
  assign mprj_io[28] = SCK;
  assign mprj_io[29] = CSB;
  assign mprj_io[36:33] = (spi_oeb) ? SDI : 4'bz;

	`ifdef WFDUMP
	   initial begin
	   	  $dumpfile("simx.vcd");
	   	  $dumpvars(0, tb_top);
       end
     `endif
  
	// Instantiate the Unit Under Test (UUT)
	top uut (
		.sys_clk(sys_clk), 
		.mrn(reset_n), 
		.mprj_io(mprj_io),
		//.spi_sck(SCK), 
		//.spi_csn(CSB), 
		//.spi_sio(spi_sio), 
		.Switch(Switch), 
		.LED(LED)
	);

   always #5.0 sys_clk <= (sys_clk === 1'b0);
	
	initial begin
		// Initialize Inputs
		sys_clk = 0;
		SCK = 0;
		CSB = 1;
      spi_oeb = 0;
		Switch = 0;
        err_flag = 0;

		// Wait 100 ns for global reset to finish
		#100;
		 wait(reset_n == 1);

        
         $display("Testing: Fast Read Quad I/O (EBh)");
         spi_read_cmd(8'hEB,24'h200,2'b00,2'b10,1'b1,4'b0010);

         $display("Testing: Fast Read (0Bh)");
         spi_read_cmd(8'h0B,24'h200,2'b00,2'b00,1'b0,4'b0001);

		#10000;  $finish;
		// Add stimulus here

	end

task spi_read_cmd;

input [7:0] cmd;
input [23:0] addr;
input [1:0] iMode; // Init Mode
input [1:0] fMode; // Final Mode
input       mode;
input [3:0] dbyte;

integer i;
begin
       start_csb;
       write_byte(cmd,iMode); // CMD
       write_byte(addr[23:16],fMode); // ADDR[23:16]
       write_byte(addr[15:8],fMode); // ADDR[15:8]
       write_byte(addr[7:0],fMode); // ADDR[7:0]
       if(mode)
            write_byte(8'h00,fMode); // MODE
       for(i =0; i < dbyte ; i = i+1) begin
           read_byte(Rdata,fMode); // Dummy
       end
       read_cmp_byte(8'h93,fMode); // Data
       read_cmp_byte(8'h00,fMode); // Data
       read_cmp_byte(8'h00,fMode); // Data
       read_cmp_byte(8'h00,fMode); // Data
       read_cmp_byte(8'h13,fMode); // Data
       read_cmp_byte(8'h01,fMode); // Data
       read_cmp_byte(8'h00,fMode); // Data
       read_cmp_byte(8'h00,fMode); // Data
       read_cmp_byte(8'h93,fMode); // Data
       read_cmp_byte(8'h01,fMode); // Data
       read_cmp_byte(8'h00,fMode); // Data
       read_cmp_byte(8'h00,fMode); // Data
       end_csb;
end
endtask

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
   reg [3:0] step;
   integer i;
	begin
		SCK = 1'b0;
        spi_oeb = 1;
        step  = 1;
        case(mode)
           2'b00: step = 4'b0001;
           2'b01: step = 4'b0010;
           2'b10: step = 4'b0100;
         endcase


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
   reg [3:0] step;
   reg [7:0] idata;
   integer i;
	begin
		SCK = 1'b0;
		SDI = 1'b0;
      spi_oeb = 0;
        case(mode)
           2'b00: step = 4'b0001;
           2'b01: step = 4'b0010;
           2'b10: step = 4'b0100;
         endcase
		for (i=7; i >= 0; i=i-step) begin
		    #50;
           case(mode)
           2'b00: begin
		           idata[i] = SDO[0];
              end
           2'b01: begin
		           idata[i]   = SDO[1];
		           idata[i-1] = SDO[0];
              end
           2'b10: begin
		           idata[i]   = SDO[3];
		           idata[i-1] = SDO[2];
		           idata[i-2] = SDO[1];
		           idata[i-3] = SDO[0];
               end
            endcase
            #50;  SCK = 1'b1;
            #100; SCK = 1'b0;
		end
	 end
	endtask      

	task read_cmp_byte;
	input [7:0] cdata;
    input [1:0] mode;
    reg [3:0] step;
    reg [7:0] idata;
   integer i;
	begin
		SCK = 1'b0;
		SDI = 1'b0;
      spi_oeb = 0;
        case(mode)
           2'b00: step = 4'b0001;
           2'b01: step = 4'b0010;
           2'b10: step = 4'b0100;
         endcase
		for (i=7; i >= 0; i=i-step) begin
		    #50;
           case(mode)
           2'b00: begin
		           idata[i] = SDO[0];
              end
           2'b01: begin
		           idata[i]   = SDO[1];
		           idata[i-1] = SDO[0];
              end
           2'b10: begin
		           idata[i]   = SDO[3];
		           idata[i-1] = SDO[2];
		           idata[i-2] = SDO[1];
		           idata[i-3] = SDO[0];
               end
            endcase
            #50;  SCK = 1'b1;
            #100; SCK = 1'b0;
		end
        if(cdata == idata)
           $display("SPI READ DATA : 0x%x => MATCHED",idata);
        else begin
           $display("SPI READ DATA : Exp: 0x%x Rxd: 0x%x => FAILED",cdata,idata);
           err_flag = 1;
        end
	 end
	endtask      
endmodule

