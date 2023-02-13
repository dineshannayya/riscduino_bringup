

module top ( 
        sys_clk ,	
        reset_n ,

      // Spi I/F
        spi_sck,
        spi_csn  ,
        spi_sio,



        Switch,
        LED  

     );


//---------------------------------
// Global Dec
// ---------------------------------
input        sys_clk ;	
output       reset_n ;

input [3:0]  Switch;
output [7:0] LED   ;

//-------------------------------------
// Spi I/F
//-------------------------------------
input               spi_sck            ; // clock out
input               spi_csn            ; // cs_n
inout  [3:0]        spi_sio            ;
 


wire  [3:0]        spi_si             ; // serial data in
wire  [3:0]        spi_so             ; // serial data out
wire               spi_oen            ; // serial data oen


// WB Master Port
wire         wbm_cyc_o       ;  // strobe/request
wire         wbm_stb_o       ;  // strobe/request
wire  [31:0] wbm_adr_o       ;  // address
wire         wbm_we_o        ;  // write
wire  [31:0] wbm_dat_o       ;  // data output
wire  [3:0]  wbm_sel_o       ;  // byte enable
wire  [31:0] wbm_dat_i       ;  // data input
reg          wbm_ack_i       ;  // acknowlegement
wire         wbm_err_i       ;  // error

assign      spi_sio = (spi_oen == 1'b0) ? spi_so : 4'hz;
assign      spi_si =  (spi_oen == 1'b1) ? spi_sio: 4'b0;


reset_sync u_reset_sync (
    .mclk        (sys_clk),
    .reset_n     (reset_n)
   );




qspis_top u_qspis(

	 .sys_clk         (sys_clk),
	 .rst_n           (reset_n),

         .sclk            (spi_sck),
         .ssn             (spi_csn),
         .sdin            (spi_si),
         .sdout           (spi_so),
         .sdout_oen       (spi_oen),

         // WB Master Port
         .wbm_cyc_o       (wbm_cyc_o ),  // strobe/request
         .wbm_stb_o       (wbm_stb_o ),  // strobe/request
         .wbm_adr_o       (wbm_adr_o ),  // address
         .wbm_we_o        (wbm_we_o  ),  // write
         .wbm_dat_o       (wbm_dat_o ),  // data output
         .wbm_sel_o       (wbm_sel_o ),  // byte enable
         .wbm_dat_i       (wbm_dat_i ),  // data input
         .wbm_ack_i       (wbm_ack_i ),  // acknowlegement
         .wbm_err_i       (wbm_err_i )   // error
    );


wire [3:0] mem_wr = {4{wbm_we_o}};



   BRAM_SINGLE_MACRO #(
      .BRAM_SIZE("18Kb"), // Target BRAM, "9Kb" or "18Kb" 
      .DEVICE("SPARTAN6"), // Target Device: "VIRTEX5", "VIRTEX6", "SPARTAN6" 
      .DO_REG(0), // Optional output register (0 or 1)
      .INIT(36'h000000000), // Initial values on output port
      .INIT_FILE ("NONE"),
      .WRITE_WIDTH(32), // Valid values are 1-36 (19-36 only valid when BRAM_SIZE="18Kb")
      .READ_WIDTH(32),  // Valid values are 1-36 (19-36 only valid when BRAM_SIZE="18Kb")
      .SRVAL(36'h000000000), // Set/Reset value for port output
      .WRITE_MODE("NO_CHANGE") // "WRITE_FIRST", "READ_FIRST", or "NO_CHANGE" 

   ) BRAM_SINGLE_MACRO_inst (
      .DO(wbm_dat_i),       // Output data, width defined by READ_WIDTH parameter
      .ADDR(wbm_adr_o[10:2]),   // Input address, width defined by read/write port depth
      .CLK(sys_clk),     // 1-bit input clock
      .DI(wbm_dat_o),       // Input data port, width defined by WRITE_WIDTH parameter
      .EN(wbm_stb_o),       // 1-bit input RAM enable
      .REGCE('b0), // 1-bit input output register enable
      .RST(!reset_n),     // 1-bit input reset
      .WE(mem_wr)        // Input write enable, width defined by write port depth
   );


initial
begin
   wbm_ack_i <= 1'b0;
end

always @(posedge sys_clk)
begin
   if(wbm_stb_o && !wbm_ack_i) begin
      wbm_ack_i <= 1'b1;
   end else begin
      wbm_ack_i <= 1'b0;
   end
end


led_driver u_led (

    // Assuming 100MHz input clock. May need to adjust the counter below
    // if any other input frequency is used
         .Clk          (sys_clk),
            	 
    // Inputs from the Push Buttons.
         .Switch       (Switch),

   // Reg Interface
         .reg_cs      (1'b0),
         .reg_wr      (1'b0),
         .reg_wdata   (32'b0),
         .reg_rdata   (),
    
    // Output is shown on LED with different functionality.
         .LED         (LED)
);



endmodule
