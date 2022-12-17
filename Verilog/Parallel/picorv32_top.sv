
`timescale 1 ns / 1 ps
// parameter NUM_CORES = 4;
module picorv32_top  #(parameter NUM_CORES = 6)
  (
  input                               clk_n, 
  input                               reset,
  // output wire [NUM_CORES-1:0] [31:2]  adr,
  output wire [(32*NUM_CORES)-1:0]  adr,
  // output wire [NUM_CORES-1:0] [31:0]  dat,
  output wire [(32*NUM_CORES)-1:0]  dat,
  // output wire [NUM_CORES-1:0] [3:0]   sel,
  output wire [(4*NUM_CORES)-1:0]   sel,
  output wire [NUM_CORES-1:0]         we,
  output wire [NUM_CORES-1:0]         cyc,
  // input wire  [NUM_CORES-1:0] [31:0]  rdt_n,
  input wire  [(32*NUM_CORES)-1:0]  rdt_n,
  input wire  [NUM_CORES-1:0]         ack_n

  //Look-ahead interface memory
  // output wire        mem_la_read,
  // output wire        mem_la_write,
  // output wire [31:0] mem_la_addr,
  // output wire [31:0] mem_la_wdata,
  // output wire [3:0] mem_la_wstrb
  );
  wire [NUM_CORES-1:0][31:2]          adr_n;
  wire [NUM_CORES-1:0][31:0]          dat_n;
  wire [NUM_CORES-1:0][3:0]           sel_n;
  wire [NUM_CORES-1:0]                we_n;
  wire [NUM_CORES-1:0]                cyc_n;

  wire                                clk;
  wire                                resetn;
  wire [NUM_CORES-1:0][31:0]          rdt;
  wire [NUM_CORES-1:0]                ack;
  wire [NUM_CORES-1:0][ 3:0]          wstrb;
  wire [NUM_CORES-1:0]                we_i;
  wire [NUM_CORES-1:0][1:0]           dummy;

  genvar i_we;
  generate
    for (i_we = 0; i_we < NUM_CORES; i_we++) begin
      assign we_i[i_we] = wstrb[i_we][0] | wstrb[i_we][1] | wstrb[i_we][2] | wstrb[i_we][3];
      assign we[i_we] = we_i[i_we];
      assign sel[(4*i_we)+3:4*i_we] = we_i[i_we] ? wstrb[i_we] : 4'hf;
    end
  endgenerate

  parameter [31:0] STACKADDR = 32'h 0001_86A0;
  parameter [31:0] PROGADDR_RESET = 32'h 0000_0000;

  genvar i_core;
  generate
    for(i_core = 0; i_core < NUM_CORES; i_core=i_core+1)begin

      picorv32 #(
        .ENABLE_COUNTERS64(0),
        .ENABLE_REGS_16_31(1),
        .ENABLE_REGS_DUALPORT(0),
        .LATCHED_MEM_RDATA(1),
        .CATCH_MISALIGN(0),
        .CATCH_ILLINSN(0),
        .TWO_STAGE_SHIFT(1),
        .TWO_CYCLE_COMPARE(1),//
        .TWO_CYCLE_ALU(1),//
        .STACKADDR(STACKADDR),
        .PROGADDR_RESET(PROGADDR_RESET),
        .ENABLE_IRQ(0),
        .ENABLE_MUL(1),
        .ENABLE_FAST_MUL(0)
        )
      cpu (
        .clk       ( clk          ),
        .resetn    ( resetn       ),
        .mem_valid ( cyc[i_core]  ),
        .mem_instr (              ),
        .mem_ready ( ack[i_core]  ),
        .mem_addr  ( adr[(32*(i_core+1))-1:(32*i_core)]),
        .mem_wdata ( dat[(32*(i_core+1))-1:32*(i_core)]  ),
        .mem_wstrb ( wstrb[i_core]),
        .mem_rdata ( rdt[i_core]  )
        // .mem_la_read (mem_la_read ),
        // .mem_la_write(mem_la_write),
        // .mem_la_addr (mem_la_addr ),
        // .mem_la_wdata(mem_la_wdata),
        // .mem_la_wstrb(mem_la_wstrb)
      );

    
      assign adr_n[i_core] = ~adr[(32*(i_core+1))-1:32*(i_core)];
      assign dat_n[i_core] = ~dat[(32*(i_core+1))-1:32*(i_core)];
      
      assign sel_n[i_core] = ~sel[(4*(i_core+1))-1:4*(i_core)];
      assign we_n[i_core] = ~we[i_core];
      assign cyc_n[i_core] = ~cyc[i_core];
      assign rdt[i_core] = ~rdt_n[(32*(i_core+1))-1:32*(i_core)];
      assign ack[i_core] = ~ack_n[i_core];
    end
  endgenerate
  
  assign clk = ~clk_n;
  assign resetn = ~reset;
 

endmodule



// `timescale 1 ns / 1 ps

// module picorv32_top #(NUM_CORES = 3)
//   (
//   input                               clk_n, 
//   input                               reset,
//   output wire [NUM_CORES-1:0] [31:2]  adr,
//   output wire [NUM_CORES-1:0] [31:0]  dat,
//   output wire [NUM_CORES-1:0] [3:0]   sel,
//   output wire [NUM_CORES-1:0]         we,
//   output wire [NUM_CORES-1:0]         cyc,
//   input wire  [NUM_CORES-1:0] [31:0]  rdt_n,
//   input wire  [NUM_CORES-1:0]         ack_n

//   //Look-ahead interface memory
//   // output wire        mem_la_read,
//   // output wire        mem_la_write,
//   // output wire [31:0] mem_la_addr,
//   // output wire [31:0] mem_la_wdata,
//   // output wire [3:0] mem_la_wstrb
//   );
//   wire [NUM_CORES-1:0][31:2]          adr_n;
//   wire [NUM_CORES-1:0][31:0]          dat_n;
//   wire [NUM_CORES-1:0][3:0]           sel_n;
//   wire [NUM_CORES-1:0]                we_n;
//   wire [NUM_CORES-1:0]                cyc_n;

//   wire                                clk;
//   wire                                resetn;
//   wire [NUM_CORES-1:0][31:0]          rdt;
//   wire [NUM_CORES-1:0]                ack;
//   wire [NUM_CORES-1:0][ 3:0]          wstrb;
//   wire [NUM_CORES-1:0]                we_i;
//   wire [NUM_CORES-1:0][1:0]           dummy;

//   genvar i_we;
//   generate
//     for (i_we = 0; i_we < NUM_CORES; i_we++) begin
//       assign we_i[i_we] = wstrb[i_we][0] | wstrb[i_we][1] | wstrb[i_we][2] | wstrb[i_we][3];
//       assign we[i_we] = we_i[i_we];
//       assign sel[i_we] = we_i[i_we] ? wstrb[i_we] : 4'hf;
//     end
//   endgenerate

//   parameter [31:0] STACKADDR = 32'h 0001_86A0;
//   parameter [31:0] PROGADDR_RESET = 32'h 0000_0000;

//   genvar i_core;
//   generate
//     for(i_core = 0; i_core < NUM_CORES; i_core=i_core+1)begin

//       picorv32 #(
//         .ENABLE_COUNTERS64(0),
//         .ENABLE_REGS_16_31(1),
//         .ENABLE_REGS_DUALPORT(0),
//         .LATCHED_MEM_RDATA(1),
//         .CATCH_MISALIGN(0),
//         .CATCH_ILLINSN(0),
//         .TWO_STAGE_SHIFT(0),
//         .TWO_CYCLE_COMPARE(1),
//         .TWO_CYCLE_ALU(1),
//         .STACKADDR(STACKADDR),
//         .PROGADDR_RESET(PROGADDR_RESET),
//         .ENABLE_IRQ(0),
//         .ENABLE_MUL(1))
//       cpu (
//         .clk       ( clk          ),
//         .resetn    ( resetn       ),
//         .mem_valid ( cyc[i_core]  ),
//         .mem_instr (              ),
//         .mem_ready ( ack[i_core]  ),
//         .mem_addr  ( {adr[i_core],dummy[i_core]}  ),
//         .mem_wdata ( dat[i_core]  ),
//         .mem_wstrb ( wstrb[i_core]),
//         .mem_rdata ( rdt[i_core]  )
//         // .mem_la_read (mem_la_read ),
//         // .mem_la_write(mem_la_write),
//         // .mem_la_addr (mem_la_addr ),
//         // .mem_la_wdata(mem_la_wdata),
//         // .mem_la_wstrb(mem_la_wstrb)
//       );

    
//       assign adr_n[i_core] = ~adr[i_core];
//       assign dat_n[i_core] = ~dat[i_core];
//       assign sel_n[i_core] = ~sel[i_core];
//       assign we_n[i_core] = ~we[i_core];
//       assign cyc_n[i_core] = ~cyc[i_core];
//       assign rdt[i_core] = ~rdt_n[i_core];
//       assign ack[i_core] = ~ack_n[i_core];
//     end
//   endgenerate
  
//   assign clk = ~clk_n;
//   assign resetn = ~reset;
 

// endmodule
