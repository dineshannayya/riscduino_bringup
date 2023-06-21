// Important!
// This is the recommended coding style to describe no-change synchronized byte-write enable functionality for Virtex-6,
// Spartan-6 and newer device families. This coding style is not supported for older device families. In that case, please refer
// to the corresponding 2-bit and 4-bit write enable templates for device families before Virtex-6 and Spartan-6.
//

module sync_fifo #(
          parameter ADDR_WIDTH  = 12,
          parameter NB_COL	= 4, // Number of write columns
          parameter COL_WIDTH	= 8, // Width of each write column
          parameter PRG_HEX    = "data.hex"
            ) (

                 input 			            clock,
                 input      [NB_COL-1:0]	    write_enable,
                 input      [ADDR_WIDTH-1:0]	    address,
                 input      [NB_COL*COL_WIDTH-1:0]  data_in,
                 output reg [NB_COL*COL_WIDTH-1:0]  data_out
       );
  
   reg	     [NB_COL*COL_WIDTH-1:0]  PrgMem [0:2**ADDR_WIDTH-1];

   //  The forllowing code is only necessary if you wish to initialize the RAM 
   //  contents via an external file (use $readmemb for binary data)
   initial
      $readmemh(PRG_HEX, PrgMem, 'h0, 'hFFF);
  
   always @(posedge clock)
   begin 
      if (~|write_enable)
         data_out <= PrgMem[address];
   end

   generate
   genvar i;
      for (i = 0; i < NB_COL; i = i+1)
      begin
         always @(posedge clock)
         begin  
            if (write_enable[i]) 
               PrgMem[address][(i+1)*COL_WIDTH-1:i*COL_WIDTH]
	              <= data_in[(i+1)*COL_WIDTH-1:i*COL_WIDTH];
         end
      end
   endgenerate
		

endmodule					
