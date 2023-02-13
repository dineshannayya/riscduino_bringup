

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
output              spi_sck            ; // clock out
output              spi_csn            ; // cs_n
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

 bram_bank #(
          .AW(12),
          .filename    ("data.hex")
            ) u_ram (

             .CLK      (sys_clk),
             .WREN     (mem_wr),
             .ADDR     (wbm_adr_o[11:2]),
             .WDATA    (wbm_dat_o),
             .RDATA    (wbm_dat_i)
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
         .reg_cs      ('b0),
         .reg_wr      ('b0),
         .reg_wdata   ('b0),
         .reg_rdata   (),
    
    // Output is shown on LED with different functionality.
         .LED         (LED)
);



endmodule
