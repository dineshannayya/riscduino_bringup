module reset_sync (
    input      mclk,
    output wire reset_n
   );


assign reset_n = reset_d3;

reg reset_d1,reset_d2,reset_d3;

reg [7:0] cnt;

initial
begin
   reset_d1 = 0;
   reset_d2 = 0;
   reset_d3 = 0;
	cnt      = 0;
end


always @(posedge mclk)
begin
   reset_d1 <= 1'b1;
   reset_d2 <= reset_d1;
	if(cnt < 8'hFF) cnt <= cnt + 1;
	else begin
      reset_d3 <= reset_d2;
   end
end
   

endmodule

