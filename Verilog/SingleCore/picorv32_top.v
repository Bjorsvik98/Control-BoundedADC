
`timescale 1 ns / 1 ps

module picorv32_top (
  input              clk_n, 
  input              reset,
  output wire [31:2] adr,
  output wire [31:0] dat,
  output wire [3:0]  sel,
  output wire        we,
  output wire        cyc,
  input wire [31:0]  rdt_n,
  input wire         ack_n,

  //Look-ahead interface memory
  output wire        mem_la_read,
  output wire        mem_la_write,
  output wire [31:0] mem_la_addr,
  output wire [31:0] mem_la_wdata,
  output wire [3:0] mem_la_wstrb
  );
  wire [31:2]                      adr_n;
  wire [31:0]                      dat_n;
  wire [3:0]                       sel_n;
  wire                             we_n;
  wire                             cyc_n;

  wire                             clk;
  wire                             resetn;
  wire [31:0]                      rdt;
  wire                             ack;
  wire [ 3:0]                      wstrb;
  wire                             we_i;
  wire [1:0]                       dummy;

  assign we_i = wstrb[0] | wstrb[1] | wstrb[2] | wstrb[3];
  assign we = we_i;
  assign sel = we_i ? wstrb : 4'hf;

  parameter [31:0] STACKADDR = 32'h 0001_86A0;
  parameter [31:0] PROGADDR_RESET = 32'h 0000_0000;

  picorv32 #(
    .ENABLE_COUNTERS64(0),
    .ENABLE_REGS_16_31(0),
    .ENABLE_REGS_DUALPORT(0),
    .LATCHED_MEM_RDATA(1),
    .CATCH_MISALIGN(0),
    .CATCH_ILLINSN(0),
    .TWO_STAGE_SHIFT(0),
    .TWO_CYCLE_COMPARE(1),
    .TWO_CYCLE_ALU(1),
    .STACKADDR(STACKADDR),
    .PROGADDR_RESET(PROGADDR_RESET),
    .ENABLE_IRQ(0),
    .ENABLE_MUL(0),
    .ENABLE_FAST_MUL(0)
  ) cpu (
    .clk       (clk),
    .resetn    (resetn),
    .mem_valid (cyc),
    .mem_instr (),
    .mem_ready (ack),
    .mem_addr  ({adr,dummy}),
    .mem_wdata (dat),
    .mem_wstrb (wstrb),
    .mem_rdata (rdt),
    .mem_la_read (mem_la_read ),
		.mem_la_write(mem_la_write),
		.mem_la_addr (mem_la_addr ),
		.mem_la_wdata(mem_la_wdata),
		.mem_la_wstrb(mem_la_wstrb)
  );
  assign clk = ~clk_n;
  assign resetn = ~reset;
  assign adr_n = ~adr;
  assign dat_n = ~dat;
  assign sel_n = ~sel;
  assign we_n = ~we;
  assign cyc_n = ~cyc;
  assign rdt = ~rdt_n;
  assign ack = ~ack_n;

endmodule
