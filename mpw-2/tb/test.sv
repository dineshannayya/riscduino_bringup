
/************************************************************
  Author: Dinesh Annayya <dinesh.annayya.gmail.com>

  This test bench to emulate the hold issue in the mpw-2 caravel
  gpio chain.

  Standard apporach used, when there hold violation in specific chain, then
  one cycle will be dropped for the chain, so that rest of the chain are intact.
  This test bench can able to create hold violation in multiple location.

  How to cross-check: In waveform check the 13 bit shift register of each chain.
  1. When no hold violation, all the chain shift register will be 0x1800 at end of chain shift.
  2. All the Hold violation chain will be at 0x1001 and good chain will be 0x1800



*****************************************************/
`timescale 1 ns/1 ps


module tb_top;


parameter PAD_CTRL_BITS = 13;
parameter NO_PAD = 38;
parameter real CLK1_PERIOD  = 20; // 50Mhz
reg   serial_clock,resetn,test_start;
wire  serial_data;
reg  [PAD_CTRL_BITS-1:0] shift_reg;
wire [NO_PAD-1:0] serial_clock_in;
wire [NO_PAD-1:0] serial_data_in;
wire [NO_PAD-1:0] serial_data_out;
wire [NO_PAD-1:0] serial_clock_out;



always #(CLK1_PERIOD/2) serial_clock  <= (serial_clock === 1'b0);



assign serial_data = shift_reg[PAD_CTRL_BITS-1];

//assign serial_clock_in  = {serial_clock_out[NO_PAD-2:0],serial_clock};
assign serial_data_in   = {serial_data_out[NO_PAD-2:0],serial_data};


assign serial_clock_in[0]           = serial_clock;
assign #1 serial_clock_in[1]        = serial_clock_out[0]; // Hold Violation is Chain 36
assign    serial_clock_in[2]        = serial_clock_out[1];
assign    serial_clock_in[3]        = serial_clock_out[2];
assign #1 serial_clock_in[4]        = serial_clock_out[3]; // Hold Violation at Chain 33
assign    serial_clock_in[5]        = serial_clock_out[4];
assign    serial_clock_in[6]        = serial_clock_out[5];
assign    serial_clock_in[7]        = serial_clock_out[6];
assign    serial_clock_in[8]        = serial_clock_out[7];
assign #1 serial_clock_in[9]        = serial_clock_out[8];
assign    serial_clock_in[10]       = serial_clock_out[9];
assign    serial_clock_in[11]       = serial_clock_out[10];
assign    serial_clock_in[12]       = serial_clock_out[11];
assign serial_clock_in[NO_PAD-1:13]  = serial_clock_out[NO_PAD-2:12];



reg [3:0] shift_cnt;
reg       skip_shift;
reg [7:0] chain_no;
wire [37:0] skip = 38'b01_0010_0001_0000_0000_0000_0000_0000_0000_0000;
parameter   TOTAL_SKIP = 3; // Indicate total Hold Violation skip needed
integer i;


initial
begin
   resetn = 0;
   serial_clock = 0;
   test_start = 0;
   #100 resetn = 1;
   repeat (1) @(posedge serial_clock);
   test_start = 1;

   // Wait for all the Shift block to get same data
   repeat ((38*13-TOTAL_SKIP)) @(posedge serial_clock);
   test_start = 0;
   
   repeat (1000) @(posedge serial_clock);
   $finish;


end

always @(posedge serial_clock or negedge resetn)
begin
   if(resetn == 1'b0) begin
      shift_reg    <= 13'h1800;
      shift_cnt    <= 'h0;
      shift_cnt    <= 'h0;
      chain_no     <= 'h0;
      skip_shift   <= 'h0; // Skip a chain shift
   end else begin
       if(test_start) begin
          if(skip[chain_no+1] && shift_cnt == 12) begin
             shift_reg  <= 13'h1000;
             shift_cnt  <= 1;
             chain_no   <= chain_no+1;
             skip_shift <= 1'b1;
          end else begin
             skip_shift <= 1'b0;
             if(shift_cnt == 12) begin
                shift_reg <= 13'h1800;
                chain_no   <= chain_no+1;
                shift_cnt  <= 0;
             end else begin
                shift_reg <= {shift_reg[PAD_CTRL_BITS-2:0],shift_reg[PAD_CTRL_BITS-1]};
                shift_cnt = shift_cnt+1;
             end
         end
      end
   end
end
 

initial begin
    $dumpfile("simx.vcd");
    $dumpvars(0, tb_top);
end      


generate 
genvar tcnt;
   for (tcnt = 0; $unsigned(tcnt) < NO_PAD; tcnt=tcnt+1) begin : ch_

    shift_data u_shift (
                    .resetn          (resetn                    ),
                    .shift_enb       (test_start                ),
                    .serial_clock    (serial_clock_in[tcnt]     ),
                    .serial_data_in  (serial_data_in[tcnt]      ),
                    .serial_data_out (serial_data_out[tcnt]     ),
                    .serial_clock_out(serial_clock_out[tcnt]    )
               );
  end

 endgenerate




endmodule

module shift_data #( parameter PAD_CTRL_BITS = 13)(
           input  logic resetn,
           input  logic shift_enb,
           input  logic serial_clock,
           input  logic serial_data_in,
           output logic serial_data_out,
           output logic serial_clock_out
      );


    /* Serial shift for the above (latched) values */
    reg [PAD_CTRL_BITS-1:0] shift_register;

    assign serial_clock_out = serial_clock;
	assign serial_data_out = shift_register[PAD_CTRL_BITS-1];




    always @(posedge serial_clock or negedge resetn) begin
	if (resetn == 1'b0) begin
	    /* Clear shift register */
	    shift_register <= 'd0;
	end else begin
	    /* Shift data in */
        if(shift_enb)
	       shift_register <= {shift_register[PAD_CTRL_BITS-2:0], serial_data_in};
	end
    end


endmodule


