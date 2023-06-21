module test;

reg [7:0] Mem[0:2047];

reg [7:0] i,j;
reg [7:0] data;



initial begin
   $readmemh("user_uart.hex",Mem);
   for(j = 0; j < 64; j =j + 1)begin
      $write(".INIT_%X (256'h",j);
      for(i = 0; i < 32; i =i + 1)begin
         $write("%2x",Mem[j*32 + (31-i)]);
      end
         $write("),\n");
   end

end


endmodule
