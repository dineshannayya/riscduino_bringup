

module top ( 
        sys_clk ,	
		  
		  mrn,    
		  tim3_ch2,
 
        mprj_io,


        Switch,
        LED
        //trigger		  

     );


//---------------------------------
// Global Dec
// ---------------------------------
input        sys_clk ;	
output       mrn ;  // Reset Out
output       tim3_ch2; // Clock

input [3:0]  Switch;
output [7:0] LED   ;
wire       trigger;

inout [37:0]  mprj_io;


wire                inst_trg           ;
wire                spi_trig           ;


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

wire [2:0]    spi_if_st      ;
wire          sck_toggle     ;
wire [5:0]    bitcnt         ;
wire          reset_n        ;

reg           clk_1Mhz       ; // 1Mhz clock
reg [7:0]     clk_dcnt       ; // clock div count
wire          addr_trg       ;
wire          spi_st_trans   ;


assign      mprj_io[5:0]   = 6'hz;
assign      mprj_io[27:10] = 18'hz;
assign      mprj_io[37]    = 1'hz;
assign      tim3_ch2       =  trigger; // clk_1Mhz; 

assign      mprj_io[8] = mprj_io[6];
assign      mprj_io[9] = mprj_io[7];
   

//assign      mprj_io[36:28] = 9'hz;

assign      mprj_io[36:33] = (spi_oen == 1'b0) ? spi_so : 4'hz;
assign      spi_si =  (spi_oen == 1'b1) ? mprj_io[36:33]: 4'b0;

assign spi_sck = mprj_io[28];
assign spi_csn = mprj_io[29];
assign mprj_io[32:30] = 3'hz;
assign mrn = reset_n;

assign trigger = spi_trig; // inst_trg;

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
			
			// Debug 
			.spi_if_st        (spi_if_st),
			.sck_toggle       (sck_toggle),
			.bitcnt           (bitcnt),
			.inst_trg         (inst_trg),  
         .addr_trg         (addr_trg),		
         .spi_st_trans     (spi_st_trans),	
         .spi_trig         (spi_trig),			

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


`ifdef RTL_SIM
   bram_bank #(
             .AW(11),
             .filename("user_uart.hex")
               )  u_fifo (
   
                    .CLK (sys_clk),
                    .WREN(mem_wr),
                    .ADDR(wbm_adr_o[10:2]),
                    .WDATA(wbm_dat_o),
                    .RDATA(wbm_dat_i)
          );
`else
   BRAM_SINGLE_MACRO #(
      .BRAM_SIZE("18Kb"), // Target BRAM, "9Kb" or "18Kb" 
      .DEVICE("SPARTAN6"), // Target Device: "VIRTEX5", "VIRTEX6", "SPARTAN6" 
      .DO_REG(0), // Optional output register (0 or 1)
      .INIT(36'h000000000), // Initial values on output port
      .INIT_FILE ("NONE"),
      .WRITE_WIDTH(32), // Valid values are 1-36 (19-36 only valid when BRAM_SIZE="18Kb")
      .READ_WIDTH(32),  // Valid values are 1-36 (19-36 only valid when BRAM_SIZE="18Kb")
      .SRVAL(36'h000000000), // Set/Reset value for port output
      .WRITE_MODE("NO_CHANGE"), // "WRITE_FIRST", "READ_FIRST", or "NO_CHANGE" 

      .INIT_00 (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_01 (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_02 (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_03 (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_04 (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_05 (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_06 (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_07 (256'hffffffff0000006f000000130000000000000000000000000000000000000000),
      .INIT_08 (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_09 (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_0A (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_0B (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_0C (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_0D (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_0E (256'h000000130000001300000013000000130000001300000013000000131200006f),
      .INIT_0F (256'h0000001300000013000000130000001300000013000000130000001300000013),
      .INIT_10 (256'h0000041300000393000003130000029300000213000001930000011300000093),
      .INIT_11 (256'h0000081300000793000007130000069300000613000005930000051300000493),
      .INIT_12 (256'h00000c1300000b9300000b1300000a9300000a13000009930000091300000893),
      .INIT_13 (256'h0800019700000f9300000f1300000e9300000e1300000d9300000d1300000c93),
      .INIT_14 (256'hfec59de305910005a023a021d746061308000617d7c585930800059758418193),
      .INIT_15 (256'ha02306300313004282930c4902b70062a02343050c4902b7560101130c480117),
      .INIT_16 (256'h1640006f0b0000ef458145010062a2230062a023537d010282930c4902b70062),
      .INIT_17 (256'hde3edc3ada36d832d62ed42ad226d022ce1ecc1aca16c812c60ec40ac206716d),
      .INIT_18 (256'hdefedcfadaf6d8f2d6eed4ead2e6d0e2cedeccdacad6c8d2c6cec4cac2c6c0c2),
      .INIT_19 (256'h5492540243f2436242d2424241b241224092048000ef860a341025f334202573),
      .INIT_1A (256'h5c965c064bf64b664ad64a4649b649264896480657f2576256d2564255b25522),
      .INIT_1B (256'h00000000000000000000d83ff06f3020007361515ff65f665ed65e465db65d26),
      .INIT_1C (256'h15934bd40057a22301f762934805f140237343d8100207b77c0510738d5d67c1),
      .INIT_1D (256'h01c7aa2310066e1300b818b34f1d4bd0cbc80013d5130016939310010eb70033),
      .INIT_1E (256'h059304f0061304c00693045003930480029347b110010fb70317ae2301eea023),
      .INIT_1F (256'h007faa23005faa23fee7fee301cfa70345290440081305200893057003130200),
      .INIT_20 (256'h00dfaa23011faa2300cfaa23006faa2300bfaa2300cfaa2300dfaa2300dfaa23),
      .INIT_21 (256'h0000000000000000000000000000b7e1fce7f2e301cfa70300afaa23010faa23),
      .INIT_22 (256'h000100000013000000130000001300000013000000130000001382820f400293),
      .INIT_23 (256'h0000000000000000000000000000000000000000000000000000000000000000)
   ) BRAM_SINGLE_MACRO_inst (
      .DO(wbm_dat_i),       // Output data, width defined by READ_WIDTH parameter
      .ADDR(wbm_adr_o[10:2]),   // Input address, width defined by read/write port depth
      .CLK(sys_clk),     // 1-bit input clock
      .DI(wbm_dat_o),       // Input data port, width defined by WRITE_WIDTH parameter
      .EN(wbm_stb_o),       // 1-bit input RAM enable
      .REGCE(1'b0), // 1-bit input output register enable
      .RST(!reset_n),     // 1-bit input reset
      .WE(mem_wr)        // Input write enable, width defined by write port depth
   );

`endif	
	
// Clock 1Mhz Generation
initial
begin
   clk_1Mhz <= 1'b0;
	clk_dcnt <= 8'h0;
end

always @(posedge sys_clk)
begin
   if(clk_dcnt == 8'd49) begin
	    clk_1Mhz <= ~clk_1Mhz;
		 clk_dcnt <= 0;
	end else begin
		 clk_dcnt <= clk_dcnt +1;
	end	 

end
		 


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

    
    // Output is shown on LED with different functionality.
         .LED         (LED)
);



endmodule
