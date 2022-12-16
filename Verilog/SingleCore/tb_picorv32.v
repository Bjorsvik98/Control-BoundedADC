`timescale 1 ns / 1 ps

`define CLOCK_PERIOD_HALF 0.2

`define RESET_PERIOD 400

module tb_picorv32;
   reg clk;
   wire clk_n;
   reg resetn;
   wire reset;

   wire [31:2] adr;
   wire [31:0] dat;
   wire [3:0]  sel;
   wire        we;
   wire        cyc;
   reg [31:0]  rdt;
   wire [31:0] rdt_n;
   reg         ack;
   wire        ack_n;

	 reg [31:0]  mem [0:100000];

   integer     i;

   integer     cyclecounter;

   initial begin
      $readmemh("memimage.hex", mem);
      cyclecounter = 0;
      clk = 0;
      resetn = 0;
      #`RESET_PERIOD resetn = 1;
      $display("Test program starts at time %0t", $time);
   end

   always #`CLOCK_PERIOD_HALF clk=~clk;

   // stop if timeout
   always @(posedge clk) begin
      cyclecounter = cyclecounter + 1;
      if(cyclecounter >= 100000000) begin
         $display("Error, timeout");

         $writememh("out.hex", mem);

         $finish;
      end
   end

   wire [3:0] mem_we = {4{we & cyc}} & sel;

   always @(negedge clk)
     if (!resetn)
       ack <= 1'b0;
     else
       ack <= cyc & !ack;

   always @(negedge clk) begin
      if (mem_we[0]) mem[adr][7:0]   <= dat[7:0];
      if (mem_we[1]) mem[adr][15:8]  <= dat[15:8];
      if (mem_we[2]) mem[adr][23:16] <= dat[23:16];
      if (mem_we[3]) mem[adr][31:24] <= dat[31:24];
      rdt <= mem[adr];
   end

   // exit when firmware exits
   always @(*) begin
      if(cyc && (adr == 30'h0400_0001) && we && (dat == 32'h0000_00ad)) begin
         $display("Test program ended correctly at time %0t", $time);

         $writememh("out.hex", mem);
         
         $finish;
      end
   end
    
   initial $timeformat(-9, 2, " ns", 20);


   picorv32_top chip (
                       .clk_n (clk_n), 
                       .reset (reset),
                       .adr (adr),
                       .dat (dat),
                       .sel (sel),
                       .we (we),
                       .cyc (cyc),
                       .rdt_n (rdt_n),
                       .ack_n (ack_n)
                       );

   assign clk_n = ~clk;
   assign reset = ~resetn;
   assign rdt_n = ~rdt;
   assign ack_n = ~ack;

endmodule

