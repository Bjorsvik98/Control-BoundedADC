	.section .text
	.global _start
	.global main


_start:
	/* print "START\n" */
	# lui a0,0x10000000>>12
	# addi a1,zero,'S'
	# addi a2,zero,'T'
	# addi a3,zero,'A'
	# addi a4,zero,'R'
	# addi a5,zero,'\n'
	# sw a1,0(a0)
	# sw a2,0(a0)
	# sw a3,0(a0)
	# sw a4,0(a0)
	# sw a2,0(a0)
	# sw a5,0(a0)

	# # /* execute some insns for "make timing" */
	# lui a0,0
	# auipc a0,0
	# slli a0,a0,0
	# slli a0,a0,31
	# addi a1,zero,0
	# sll a0,a0,a1
	# addi a1,zero,31
	# sll a0,a0,a1

	/* set stack pointer for core 1 */
	/* lui sp,(64*1024)>>12 */
	/* ff9c = 1111111110011100 */
	/* efcc = 1110111111001100 */
	/*0x17000=10111000000000000 */
	/*0x10000=10000000000000000*/
	/*  */
	
	/* jump to main C code */
	# lui sp,0xf /* EF9C */
	# jal ra,main

	/* set stack pointer for core 2*/
	# li a1,2
	# lui sp,0xe 
	# jal ra,main2
	
	# /* set stack pointer for core 3*/
	# # li a1,3
	# li sp,0x4650
	# jal ra,main3

	# lui sp,0xf
	# # li a0,1
	# jal ra,parallel

	# lui sp,0xe
	# li a0,2
	# jal ra,parallel

	# lui sp,0xd
	# li a0,3
	# jal ra,parallel


	/* print "DONE\n" */
	lui a0,0x10000000>>12
	addi a1,zero,'D'
	addi a2,zero,'O'
	addi a3,zero,'N'
	addi a4,zero,'E'
	addi a5,zero,'\n'
	sw a1,0(a0)
	sw a2,0(a0)
	sw a3,0(a0)
	sw a4,0(a0)
	sw a5,0(a0)

	/* exit testbench */
	addi a0, a0, 0x4
	addi a1, zero, 0xad
	sw a1, 0(a0)

	/* trap */
	ebreak
