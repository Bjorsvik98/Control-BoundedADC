`timescale 1 ns / 1 ps

`define CLOCK_PERIOD_HALF 0.400

`define RESET_PERIOD 200
module tb_picorv32;
   parameter NUM_CORES = 6;
   reg clk;
   wire clk_n;
   reg resetn;
   wire reset;

   wire [NUM_CORES-1:0] [31:2] adr;
   wire [NUM_CORES-1:0] [31:0] dat;
   wire [NUM_CORES-1:0] [3:0]  sel;
   wire [NUM_CORES-1:0]        we;
   wire [NUM_CORES-1:0]        cyc;
   reg  [NUM_CORES-1:0] [31:0] rdt;
   wire [NUM_CORES-1:0] [31:0] rdt_n;
   reg  [NUM_CORES-1:0]        ack;
   wire [NUM_CORES-1:0]        ack_n;

   wire [(32*NUM_CORES)-1:0]   adr_m;
   wire [(32*NUM_CORES)-1:0]   dat_m;
   wire [(4*NUM_CORES)-1:0 ]   sel_m;
   wire [(32*NUM_CORES)-1:0]   rdt_n_m;

//   wire            mem_la_read;
//   wire            mem_la_write;
//   wire [31:0]     mem_la_addr;
//   wire [31:0]     mem_la_wdata;
//   wire [3:0]     mem_la_wstrb;

	reg [31:0]  mem [0:100000];

   reg [31:0] init_mem0 [20];
   reg [31:0] init_mem1 [20];
   reg [31:0] init_mem2 [20];
   reg [31:0] init_mem3 [20];
   reg [31:0] init_mem4 [20];
   reg [31:0] init_mem5 [20];

   // reg [31:0] mem_test [0:255];
   integer     i;

   integer     cyclecounter;

   // initial begin
   //    $readmemh("memimage.hex", mem);
   //    cyclecounter = 0;
   //    clk = 0;
   //    resetn = 0;
   //    #`RESET_PERIOD resetn = 1;
   // end





   integer i_mem_read;
   initial begin
      $readmemh("memimage.hex", mem);
      $readmemh("memimage0.hex", init_mem0);
      $readmemh("memimage1.hex", init_mem1);
      $readmemh("memimage2.hex", init_mem2);
      $readmemh("memimage3.hex", init_mem3);
      $readmemh("memimage4.hex", init_mem4);
      $readmemh("memimage5.hex", init_mem5);
      cyclecounter = 0;
      clk = 0;
      resetn = 0;
      #`RESET_PERIOD resetn = 1;
      $display("Test program starts at time %0t", $time);
   end

   // integer ii;
   // initial begin
   //    for (ii = 0; ii < 256; ii = ii+1) begin
   //       mem_test[ii] = mem[ii];
   //    end
   //    $writememh("mem_test.hex", mem_test);
   //    $writememb("mem_test.bin", mem_test);
   // end
   always #`CLOCK_PERIOD_HALF clk=~clk;

   // stop if timeout
   always @(posedge clk) begin
      cyclecounter = cyclecounter + 1;
      if(cyclecounter >= 2000000) begin
         $display("Error, timeout");

         $writememh("out.hex", mem);

         $finish;
      end
   end

   wire [NUM_CORES-1:0][3:0] mem_we;
   genvar i_mem_we;
   generate
   for(i_mem_we = 0; i_mem_we < NUM_CORES; i_mem_we++) begin
       assign mem_we[i_mem_we] = {4{we[i_mem_we] & cyc[i_mem_we]}} & sel[i_mem_we];
   end
   endgenerate

   integer i_ack;
   always @(negedge clk) begin
      for (i_ack = 0; i_ack < NUM_CORES; i_ack++) begin
         if (!resetn)
            ack[i_ack] <= 1'b0;
         else
            ack[i_ack] <= cyc[i_ack] & !ack[i_ack];
      end
   end

   integer i_mem;
   always @(negedge clk) begin
      for (i_mem = 0; i_mem < NUM_CORES; i_mem++) begin
         if (mem_we[i_mem][0]) mem[adr[i_mem]][7:0]   <= dat[i_mem][7:0];
         if (mem_we[i_mem][1]) mem[adr[i_mem]][15:8]  <= dat[i_mem][15:8];
         if (mem_we[i_mem][2]) mem[adr[i_mem]][23:16] <= dat[i_mem][23:16];
         if (mem_we[i_mem][3]) mem[adr[i_mem]][31:24] <= dat[i_mem][31:24];
         if (mem_we[i_mem][4]) mem[adr[i_mem]][39:32] <= dat[i_mem][39:32];
         if (mem_we[i_mem][5]) mem[adr[i_mem]][47:40] <= dat[i_mem][47:40];

         if(adr[i_mem] > 64) rdt[i_mem] <= mem[adr[i_mem]];
         else if(i_mem == 0) rdt[i_mem] <= init_mem0[adr[i_mem]];
         else if(i_mem == 1) rdt[i_mem] <= init_mem1[adr[i_mem]];
         else if(i_mem == 2) rdt[i_mem] <= init_mem2[adr[i_mem]];
         else if(i_mem == 3) rdt[i_mem] <= init_mem3[adr[i_mem]];
         else if(i_mem == 4) rdt[i_mem] <= init_mem4[adr[i_mem]];
         else if(i_mem == 5) rdt[i_mem] <= init_mem5[adr[i_mem]];
      end

      // if (mem_la_write) begin
		// 	case (mem_la_addr)
		// 		32'h1000_0000: begin

		// 			$display("%h", mem_la_wdata);
		// 			$fflush();
      //       end
      //    endcase
      // end
   end

   // exit when firmware exits
   always @(*) begin
      if(cyc[0] && (adr[0] == 30'h0400_0001) && we[0] && (dat[0] == 32'h0000_00ad)) begin
         $display("Test program ended correctly at time %0t", $time);
         $writememh("out.hex", mem);
         $display("Memory written to out.hex");
         $finish;
      end
   end


   //shall print %t with scaled in ns (-9), with 2 precision digits, and would print the " ns" string
   initial $timeformat(-9, 2, " ns", 20);

   // always @(posedge clk) begin
   //    if(rdt[0] == 32'h0147_d793) $display("Addr is %h: %0t", adr[0], $time);
   // end
   // always @(posedge clk) begin
   //    if(adr > 32'h0001_1cc8 && adr < 32'h0001_1d2c) $display("Adress is %h at t = %0t", adr, $time);
   // end
   genvar i_neg;
   picorv32_top  #(.NUM_CORES(3))
   chip (
                        .clk_n (clk_n), 
                        .reset (reset),
                        .adr (adr_m),
                        .dat (dat_m),
                        .sel (sel_m),
                        .we (we),
                        .cyc (cyc),
                        .rdt_n (rdt_n_m),
                        .ack_n (ack_n)
                        // .mem_la_read(mem_la_read),
                        // .mem_la_write(mem_la_write),
                        // .mem_la_addr(mem_la_addr),
                        // .mem_la_wdata(mem_la_wdata),
                        // .mem_la_wstrb(mem_la_wstrb)
                       );

  assign clk_n = ~clk;
  assign reset = ~resetn;
  // generate
  // for (i_neg = 0; i_neg < NUM_CORES; i_neg++)begin
     assign rdt_n = ~rdt;
     assign ack_n = ~ack;
  // end
  // endgenerate

if (NUM_CORES == 3) begin
  assign adr[0] =    {adr_m[31:2] };
  assign adr[1] =    {adr_m[63:34]};
  assign adr[2] =    {adr_m[95:66]};
  assign dat[0] =    dat_m[31:0];
  assign dat[1] =    dat_m[63:32];
  assign dat[2] =    dat_m[95:64];
  assign sel[0] =    sel_m[3:0];
  assign sel[1] =    sel_m[7:4];
  assign sel[2] =    sel_m[11:8];
  assign rdt_n_m =  {rdt_n[2], rdt_n[1], rdt_n[0]};
end

if (NUM_CORES == 4) begin
  assign adr[0] =    {adr_m[31:2] };
  assign adr[1] =    {adr_m[63:34]};
  assign adr[2] =    {adr_m[95:66]};
  assign adr[3] =    {adr_m[127:98]};
  assign dat[0] =    dat_m[31:0];
  assign dat[1] =    dat_m[63:32];
  assign dat[2] =    dat_m[95:64];
  assign dat[3] =    dat_m[127:96];
  assign sel[0] =    sel_m[3:0];
  assign sel[1] =    sel_m[7:4];
  assign sel[2] =    sel_m[11:8];
  assign sel[3] =    sel_m[15:12];
  assign rdt_n_m =  {rdt_n[3], rdt_n[2], rdt_n[1], rdt_n[0]};
end

if (NUM_CORES == 5) begin
  assign adr[0] =    {adr_m[31:2] };
  assign adr[1] =    {adr_m[63:34]};
  assign adr[2] =    {adr_m[95:66]};
  assign adr[3] =    {adr_m[127:98]};
  assign adr[4] =    {adr_m[159:130]};
  assign dat[0] =    dat_m[31:0];
  assign dat[1] =    dat_m[63:32];
  assign dat[2] =    dat_m[95:64];
  assign dat[3] =    dat_m[127:96];
  assign dat[4] =    dat_m[159:128];
  assign sel[0] =    sel_m[3:0];
  assign sel[1] =    sel_m[7:4];
  assign sel[2] =    sel_m[11:8];
  assign sel[3] =    sel_m[15:12];
  assign sel[4] =    sel_m[19:16];
  assign rdt_n_m =  {rdt_n[4], rdt_n[3], rdt_n[2], rdt_n[1], rdt_n[0]};
end

if (NUM_CORES == 6) begin
  assign adr[0] =    {adr_m[31:2] };
  assign adr[1] =    {adr_m[63:34]};
  assign adr[2] =    {adr_m[95:66]};
  assign adr[3] =    {adr_m[127:98]};
  assign adr[4] =    {adr_m[159:130]};
  assign adr[5] =    {adr_m[191:162]};
  assign dat[0] =    dat_m[31:0];
  assign dat[1] =    dat_m[63:32];
  assign dat[2] =    dat_m[95:64];
  assign dat[3] =    dat_m[127:96];
  assign dat[4] =    dat_m[159:128];
  assign dat[5] =    dat_m[191:160];
  assign sel[0] =    sel_m[3:0];
  assign sel[1] =    sel_m[7:4];
  assign sel[2] =    sel_m[11:8];
  assign sel[3] =    sel_m[15:12];
  assign sel[4] =    sel_m[19:16];
  assign sel[5] =    sel_m[23:20];
  assign rdt_n_m =  {rdt_n[5], rdt_n[4], rdt_n[3], rdt_n[2], rdt_n[1], rdt_n[0]};

end
  
endmodule




// `timescale 1 ns / 1 ps

// `define CLOCK_PERIOD_HALF 0.375

// `define RESET_PERIOD 800
// module tb_picorv32;
//    parameter NUM_CORES = 3;
//    reg clk;
//    wire clk_n;
//    reg resetn;
//    wire reset;

//    wire [NUM_CORES-1:0] [31:2] adr;
//    wire [NUM_CORES-1:0] [31:0] dat;
//    wire [NUM_CORES-1:0] [3:0]  sel;
//    wire [NUM_CORES-1:0]        we;
//    wire [NUM_CORES-1:0]        cyc;
//    reg  [NUM_CORES-1:0] [31:0] rdt;
//    wire [NUM_CORES-1:0] [31:0] rdt_n;
//    reg  [NUM_CORES-1:0]        ack;
//    wire [NUM_CORES-1:0]        ack_n;

// //   wire            mem_la_read;
// //   wire            mem_la_write;
// //   wire [31:0]     mem_la_addr;
// //   wire [31:0]     mem_la_wdata;
// //   wire [3:0]     mem_la_wstrb;

// 	reg [31:0]  mem [0:100000];

//    reg [31:0] init_mem0 [20];
//    reg [31:0] init_mem1 [20];
//    reg [31:0] init_mem2 [20];

//    // reg [31:0] mem_test [0:255];
//    integer     i;

//    integer     cyclecounter;

//    // initial begin
//    //    $readmemh("memimage.hex", mem);
//    //    cyclecounter = 0;
//    //    clk = 0;
//    //    resetn = 0;
//    //    #`RESET_PERIOD resetn = 1;
//    // end
//    integer i_mem_read;
//    initial begin
//       $readmemh("memimage.hex", mem);
//       $readmemh("memimage0.hex", init_mem0);
//       $readmemh("memimage1.hex", init_mem1);
//       $readmemh("memimage2.hex", init_mem2);
//       cyclecounter = 0;
//       clk = 0;
//       resetn = 0;
//       #`RESET_PERIOD resetn = 1;
//    end

//    // integer ii;
//    // initial begin
//    //    for (ii = 0; ii < 256; ii = ii+1) begin
//    //       mem_test[ii] = mem[ii];
//    //    end
//    //    $writememh("mem_test.hex", mem_test);
//    //    $writememb("mem_test.bin", mem_test);
//    // end
//    always #`CLOCK_PERIOD_HALF clk=~clk;

//    // stop if timeout
//    always @(posedge clk) begin
//       cyclecounter = cyclecounter + 1;
//       if(cyclecounter >= 10000000) begin
//          $display("Error, timeout");

//          $writememh("out.hex", mem);

//          $finish;
//       end
//    end

//    wire [NUM_CORES-1:0][3:0] mem_we;
//    genvar i_mem_we;
//    generate
//    for(i_mem_we = 0; i_mem_we < NUM_CORES; i_mem_we++) begin
//        assign mem_we[i_mem_we] = {4{we[i_mem_we] & cyc[i_mem_we]}} & sel[i_mem_we];
//    end
//    endgenerate

//    integer i_ack;
//    always @(negedge clk) begin
//       for (i_ack = 0; i_ack < NUM_CORES; i_ack++) begin
//          if (!resetn)
//             ack[i_ack] <= 1'b0;
//          else
//             ack[i_ack] <= cyc[i_ack] & !ack[i_ack];
//       end
//    end

//    integer i_mem;
//    always @(negedge clk) begin
//       for (i_mem = 0; i_mem < NUM_CORES; i_mem++) begin
//          if (mem_we[i_mem][0]) mem[adr[i_mem]][7:0]   <= dat[i_mem][7:0];
//          if (mem_we[i_mem][1]) mem[adr[i_mem]][15:8]  <= dat[i_mem][15:8];
//          if (mem_we[i_mem][2]) mem[adr[i_mem]][23:16] <= dat[i_mem][23:16];
//          if (mem_we[i_mem][3]) mem[adr[i_mem]][31:24] <= dat[i_mem][31:24];

//          if(adr[i_mem] > 64) rdt[i_mem] <= mem[adr[i_mem]];
//          else if(i_mem == 0) rdt[i_mem] <= init_mem0[adr[i_mem]];
//          else if(i_mem == 1) rdt[i_mem] <= init_mem1[adr[i_mem]];
//          else if(i_mem == 2) rdt[i_mem] <= init_mem2[adr[i_mem]];
//       end

//       // if (mem_la_write) begin
// 		// 	case (mem_la_addr)
// 		// 		32'h1000_0000: begin

// 		// 			$display("%h", mem_la_wdata);
// 		// 			$fflush();
//       //       end
//       //    endcase
//       // end
//    end

//    // exit when firmware exits
//    always @(*) begin
//       if(cyc[0] && (adr[0] == 30'h0400_0001) && we[0] && (dat[0] == 32'h0000_00ad)) begin
//          $display("Test program ended correctly");
//          $writememh("out.hex", mem);
//          $finish;
//       end
//    end


//    //shall print %t with scaled in ns (-9), with 2 precision digits, and would print the " ns" string
//    initial $timeformat(-9, 2, " ns", 20);

//    // always @(posedge clk) begin
//    //    if(rdt[0] == 32'h0147_d793) $display("Addr is %h: %0t", adr[0], $time);
//    // end
//    // always @(posedge clk) begin
//    //    if(adr > 32'h0001_1cc8 && adr < 32'h0001_1d2c) $display("Adress is %h at t = %0t", adr, $time);
//    // end
//    genvar i_neg;
//    picorv32_top #(.NUM_CORES(NUM_CORES))
//    chip (
//                         .clk_n (clk_n), 
//                         .reset (reset),
//                         .adr (adr),
//                         .dat (dat),
//                         .sel (sel),
//                         .we (we),
//                         .cyc (cyc),
//                         .rdt_n (rdt_n),
//                         .ack_n (ack_n)
//                         // .mem_la_read(mem_la_read),
//                         // .mem_la_write(mem_la_write),
//                         // .mem_la_addr(mem_la_addr),
//                         // .mem_la_wdata(mem_la_wdata),
//                         // .mem_la_wstrb(mem_la_wstrb)
//                        );

//    assign clk_n = ~clk;
//    assign reset = ~resetn;
//    generate
//    for (i_neg = 0; i_neg < NUM_CORES; i_neg++)begin
//       assign rdt_n = ~rdt;
//       assign ack_n = ~ack;
//    end
//    endgenerate
// endmodule

