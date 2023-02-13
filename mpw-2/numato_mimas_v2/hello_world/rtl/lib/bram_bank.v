module bram_bank #(
// --------------------------------------------------------------------------
// Parameter Declarations
// --------------------------------------------------------------------------
  parameter AW = 6,
  parameter filename = "data.hex"
)
 (
  // Inputs
  input  wire          CLK,
  input  wire [AW-1:2] ADDR,
  input  wire [31:0]   WDATA,
  input  wire [3:0]    WREN,

  // Outputs
  output wire [31:0]   RDATA);

// -----------------------------------------------------------------------------
// Constant Declarations
// -----------------------------------------------------------------------------
localparam AWT = (1<<(AW-2));

  // Memory Array
  reg     [7:0]   BRAM0 [0:AWT-1];
  reg     [7:0]   BRAM1 [0:AWT-1];
  reg     [7:0]   BRAM2 [0:AWT-1];
  reg     [7:0]   BRAM3 [0:AWT-1];

  // Infer Block RAM - syntax is very specific.
  always @ (posedge CLK)
    begin
      if (WREN[0])
        BRAM0[ADDR] <= WDATA[7:0];
      if (WREN[1])
        BRAM1[ADDR] <= WDATA[15:8];
      if (WREN[2])
        BRAM2[ADDR] <= WDATA[23:16];
      if (WREN[3])
        BRAM3[ADDR] <= WDATA[31:24];
    end

  integer i;
  reg [7:0] fileimage [0:((1<<AW)-1)];

  initial begin
    $readmemh(filename, fileimage);
    // Copy from single array to splitted array
    for (i=0;i<AWT; i= i+1)
      begin
      BRAM0[i] = fileimage[ 4*i];
      BRAM1[i] = fileimage[(4*i)+1];
      BRAM2[i] = fileimage[(4*i)+2];
      BRAM3[i] = fileimage[(4*i)+3];
      end

  end


endmodule
