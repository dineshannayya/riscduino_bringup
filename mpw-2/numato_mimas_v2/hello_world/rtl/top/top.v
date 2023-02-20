

module top ( 
        sys_clk ,	
        reset_n ,

      // Spi I/F
        spi_sck,
        spi_csn  ,
        spi_sio  ,
		  
		  spi_sck_la,
        spi_csn_la,
        spi_sio_la,

        inst_trg,
		  addr_trg,

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

output              spi_sck_la         ; // clock out
output              spi_csn_la         ; // cs_n
output  [3:0]       spi_sio_la         ;
output              inst_trg           ;
output              addr_trg           ;


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


assign      spi_sio = (spi_oen == 1'b0) ? spi_so : 4'hz;
assign      spi_si =  (spi_oen == 1'b1) ? spi_sio: 4'b0;

assign spi_sck_la = spi_sck;
assign spi_csn_la = spi_csn;
assign spi_sio_la = spi_sio;
//assign spi_sio_la[0] = spi_sio[0];
//assign spi_sio_la[3:1] = spi_if_st[2:0];
//assign spi_sio_la[3:1] = bitcnt[2:0];
//assign spi_sio_la[3] =  sck_toggle;


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
      .INIT_0E (256'h000000130000001300000013000000130000001300000013000000131480006f),
      .INIT_0F (256'h0000001300000013000000130000001300000013000000130000001300000013),
      .INIT_10 (256'h0000041300000393000003130000029300000213000001930000011300000093),
      .INIT_11 (256'h0000081300000793000007130000069300000613000005930000051300000493),
      .INIT_12 (256'h00000c1300000b9300000b1300000a9300000a13000009930000091300000893),
      .INIT_13 (256'h300002b700000f9300000f1300000e9300000e1300000d9300000d1300000c93),
      .INIT_14 (256'h242303132f17233701028293300002b70062a02319e303130100033701428293),
      .INIT_15 (256'ha023a021d4c6061320000617d54585932000059755c18193200001970062a023),
      .INIT_16 (256'h8293004902b70062a0234305004902b7d381011320010117fec59de305910005),
      .INIT_17 (256'h458145010062a2230062a023537d01028293004902b70062a023063003130042),
      .INIT_18 (256'hd62ed42ad226d022ce1ecc1aca16c812c60ec40ac206716d13c0006f0c0000ef),
      .INIT_19 (256'hd6eed4ead2e6d0e2cedeccdacad6c8d2c6cec4cac2c6c0c2de3edc3ada36d832),
      .INIT_1A (256'h42d2424241b241224092048000ef860a341025f334202573defedcfadaf6d8f2),
      .INIT_1B (256'h4ad64a4649b649264896480657f2576256d2564255b255225492540243f24362),
      .INIT_1C (256'h0000d5bff06f3020007361515ff65f665ed65e465db65d265c965c064bf64b66),
      .INIT_1D (256'h0000000000000000000000000000000000000000000000000000000000000000),
      .INIT_1E (256'h031302000e1304f0061304c0069304500e9304800f1345b1c398471d300107b7),
      .INIT_1F (256'hcbd4cbd401d7aa2301e7aa23fe55dee301c7a283452904400813052008930570),
      .INIT_20 (256'hfc55d8e301c7a283cbc80107aa23cbd40117aa23cbd00067aa2301c7aa23cbd0),
      .INIT_21 (256'h000000000000000000000000000000000000000000000000000000000000bfd1),
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
