module reset_sync (
    input      mclk,
    output wire reset_n
   );


assign reset_n = reset_d3;

reg reset_d1,reset_d2,reset_d3;

initial
begin
   reset_d1 = 0;
   reset_d2 = 0;
   reset_d3 = 0;
end


always @(posedge mclk)
begin
   reset_d1 <= 1'b1;
   reset_d2 <= reset_d1;
   reset_d3 <= reset_d2;
end
   

endmodule

