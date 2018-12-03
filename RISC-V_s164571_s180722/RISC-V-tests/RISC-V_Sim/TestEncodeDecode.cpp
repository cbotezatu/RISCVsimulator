#include "TestEncodeDecode.h"
#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <string>
#include "InstructionDecode.h"
#include "InstructionEncode.h"
#include "Register.h"

static void TestEncodeDecodeInstruction(const uint32_t encoded, const std::string& expectedDecoded)
{
	Instruction instruction = DecodeInstruction(encoded);
	std::string actualDecoded = InstructionAsString(instruction);

	if (actualDecoded != expectedDecoded)
	{
		throw std::runtime_error("\nDecoded instruction doesn't match expected decoded instruction.\nExpected: " + expectedDecoded + 
			"\nActual:   " + actualDecoded + "\n");
	}
	else
	{
		std::cout << "Test Success: " << expectedDecoded << std::endl;
	}
}

static void Test_lb()
{
	TestEncodeDecodeInstruction(Create_lb(Regs::a0, Regs::a1,   11), "lb a0 11(a1)");
	TestEncodeDecodeInstruction(Create_lb(Regs::t1, Regs::s3, -123), "lb t1 -123(s3)");
	TestEncodeDecodeInstruction(Create_lb(Regs::s1, Regs::t5, 1342), "lb s1 1342(t5)");
}
static void Test_lh()
{
	TestEncodeDecodeInstruction(Create_lh(Regs::a0, Regs::a1,   11), "lh a0 11(a1)");
	TestEncodeDecodeInstruction(Create_lh(Regs::t1, Regs::s3, -123), "lh t1 -123(s3)");
	TestEncodeDecodeInstruction(Create_lh(Regs::s1, Regs::t5, 1342), "lh s1 1342(t5)");
}
static void Test_lw()
{
	TestEncodeDecodeInstruction(Create_lw(Regs::a0, Regs::a1,   11), "lw a0 11(a1)");
	TestEncodeDecodeInstruction(Create_lw(Regs::t1, Regs::s3, -123), "lw t1 -123(s3)");
	TestEncodeDecodeInstruction(Create_lw(Regs::s1, Regs::t5, 1342), "lw s1 1342(t5)");
}
static void Test_lbu()
{
	TestEncodeDecodeInstruction(Create_lbu(Regs::a0, Regs::a1,   11), "lbu a0 11(a1)");
	TestEncodeDecodeInstruction(Create_lbu(Regs::t1, Regs::s3, -123), "lbu t1 -123(s3)");
	TestEncodeDecodeInstruction(Create_lbu(Regs::s1, Regs::t5, 1342), "lbu s1 1342(t5)");
}
static void Test_lhu()
{
	TestEncodeDecodeInstruction(Create_lhu(Regs::a0, Regs::a1,   11), "lhu a0 11(a1)");
	TestEncodeDecodeInstruction(Create_lhu(Regs::t1, Regs::s3, -123), "lhu t1 -123(s3)");
	TestEncodeDecodeInstruction(Create_lhu(Regs::s1, Regs::t5, 1342), "lhu s1 1342(t5)");
}
static void Test_fence()
{

}
static void Test_fence_i()
{

}
static void Test_addi()
{
	TestEncodeDecodeInstruction(Create_addi(Regs::a3, Regs::a5,   411), "addi a3 a5 411");
	TestEncodeDecodeInstruction(Create_addi(Regs::s6, Regs::x0, -1241), "addi s6 x0 -1241");
	TestEncodeDecodeInstruction(Create_addi(Regs::t3, Regs::gp,     2), "addi t3 gp 2");
}
static void Test_slli()
{
	TestEncodeDecodeInstruction(Create_slli(Regs::a3, Regs::a5,  1), "slli a3 a5 1");
	TestEncodeDecodeInstruction(Create_slli(Regs::s6, Regs::x0, 21), "slli s6 x0 21");
	TestEncodeDecodeInstruction(Create_slli(Regs::t3, Regs::gp,  0), "slli t3 gp 0");
}
static void Test_slti()
{
	TestEncodeDecodeInstruction(Create_slti(Regs::a3, Regs::a5,   411), "slti a3 a5 411");
	TestEncodeDecodeInstruction(Create_slti(Regs::s6, Regs::x0, -1241), "slti s6 x0 -1241");
	TestEncodeDecodeInstruction(Create_slti(Regs::t3, Regs::gp,     2), "slti t3 gp 2");
}
static void Test_sltiu()
{
	TestEncodeDecodeInstruction(Create_sltiu(Regs::a3, Regs::a5,   411), "sltiu a3 a5 411");
	TestEncodeDecodeInstruction(Create_sltiu(Regs::s6, Regs::x0, -1241), "sltiu s6 x0 -1241");
	TestEncodeDecodeInstruction(Create_sltiu(Regs::t3, Regs::gp,     2), "sltiu t3 gp 2");
}
static void Test_xori()
{
	TestEncodeDecodeInstruction(Create_xori(Regs::a3, Regs::a5,   411), "xori a3 a5 411");
	TestEncodeDecodeInstruction(Create_xori(Regs::s6, Regs::x0, -1241), "xori s6 x0 -1241");
	TestEncodeDecodeInstruction(Create_xori(Regs::t3, Regs::gp,     2), "xori t3 gp 2");
}
static void Test_srli()
{
	TestEncodeDecodeInstruction(Create_srli(Regs::a3, Regs::a5,  1), "srli a3 a5 1");
	TestEncodeDecodeInstruction(Create_srli(Regs::s6, Regs::x0, 21), "srli s6 x0 21");
	TestEncodeDecodeInstruction(Create_srli(Regs::t3, Regs::gp,  0), "srli t3 gp 0");
}
static void Test_srai()
{
	TestEncodeDecodeInstruction(Create_srai(Regs::a3, Regs::a5,  1), "srai a3 a5 1");
	TestEncodeDecodeInstruction(Create_srai(Regs::s6, Regs::x0, 21), "srai s6 x0 21");
	TestEncodeDecodeInstruction(Create_srai(Regs::t3, Regs::gp,  0), "srai t3 gp 0");
}
static void Test_ori()
{
	TestEncodeDecodeInstruction(Create_ori(Regs::a3, Regs::a5,   411), "ori a3 a5 411");
	TestEncodeDecodeInstruction(Create_ori(Regs::s6, Regs::x0, -1241), "ori s6 x0 -1241");
	TestEncodeDecodeInstruction(Create_ori(Regs::t3, Regs::gp,     2), "ori t3 gp 2");
}
static void Test_andi()
{
	TestEncodeDecodeInstruction(Create_andi(Regs::a3, Regs::a5,   411), "andi a3 a5 411");
	TestEncodeDecodeInstruction(Create_andi(Regs::s6, Regs::x0, -1241), "andi s6 x0 -1241");
	TestEncodeDecodeInstruction(Create_andi(Regs::t3, Regs::gp,     2), "andi t3 gp 2");
}
static void Test_auipc()
{
	TestEncodeDecodeInstruction(Create_auipc(Regs::t1,  1282), "auipc t1 1282");
	TestEncodeDecodeInstruction(Create_auipc(Regs::s6, 14546), "auipc s6 14546");
	TestEncodeDecodeInstruction(Create_auipc(Regs::s1,     2), "auipc s1 2");
}
static void Test_sb()
{
	TestEncodeDecodeInstruction(Create_sb(Regs::a0, Regs::a1,   11), "sb a1 11(a0)");
	TestEncodeDecodeInstruction(Create_sb(Regs::t1, Regs::s3, -123), "sb s3 -123(t1)");
	TestEncodeDecodeInstruction(Create_sb(Regs::s1, Regs::t5, 1342), "sb t5 1342(s1)");
}
static void Test_sh()
{
	TestEncodeDecodeInstruction(Create_sh(Regs::a0, Regs::a1,   11), "sh a1 11(a0)");
	TestEncodeDecodeInstruction(Create_sh(Regs::t1, Regs::s3, -123), "sh s3 -123(t1)");
	TestEncodeDecodeInstruction(Create_sh(Regs::s1, Regs::t5, 1342), "sh t5 1342(s1)");
}
static void Test_sw()
{
	TestEncodeDecodeInstruction(Create_sw(Regs::a0, Regs::a1,   11), "sw a1 11(a0)");
	TestEncodeDecodeInstruction(Create_sw(Regs::t1, Regs::s3, -123), "sw s3 -123(t1)");
	TestEncodeDecodeInstruction(Create_sw(Regs::s1, Regs::t5, 1342), "sw t5 1342(s1)");
}
static void Test_add()
{
	TestEncodeDecodeInstruction(Create_add(Regs::a3, Regs::a5, Regs::sp), "add a3 a5 sp");
	TestEncodeDecodeInstruction(Create_add(Regs::s6, Regs::x0, Regs::s7), "add s6 x0 s7");
	TestEncodeDecodeInstruction(Create_add(Regs::t3, Regs::gp, Regs::tp), "add t3 gp tp");
}
static void Test_sub()
{
	TestEncodeDecodeInstruction(Create_sub(Regs::a3, Regs::a5, Regs::sp), "sub a3 a5 sp");
	TestEncodeDecodeInstruction(Create_sub(Regs::s6, Regs::x0, Regs::s7), "sub s6 x0 s7");
	TestEncodeDecodeInstruction(Create_sub(Regs::t3, Regs::gp, Regs::tp), "sub t3 gp tp");
}
static void Test_sll()
{
	TestEncodeDecodeInstruction(Create_sll(Regs::a3, Regs::a5, Regs::sp), "sll a3 a5 sp");
	TestEncodeDecodeInstruction(Create_sll(Regs::s6, Regs::x0, Regs::s7), "sll s6 x0 s7");
	TestEncodeDecodeInstruction(Create_sll(Regs::t3, Regs::gp, Regs::tp), "sll t3 gp tp");
}
static void Test_slt()
{
	TestEncodeDecodeInstruction(Create_slt(Regs::a3, Regs::a5, Regs::sp), "slt a3 a5 sp");
	TestEncodeDecodeInstruction(Create_slt(Regs::s6, Regs::x0, Regs::s7), "slt s6 x0 s7");
	TestEncodeDecodeInstruction(Create_slt(Regs::t3, Regs::gp, Regs::tp), "slt t3 gp tp");
}
static void Test_sltu()
{
	TestEncodeDecodeInstruction(Create_sltu(Regs::a3, Regs::a5, Regs::sp), "sltu a3 a5 sp");
	TestEncodeDecodeInstruction(Create_sltu(Regs::s6, Regs::x0, Regs::s7), "sltu s6 x0 s7");
	TestEncodeDecodeInstruction(Create_sltu(Regs::t3, Regs::gp, Regs::tp), "sltu t3 gp tp");
}
static void Test_xor()
{
	TestEncodeDecodeInstruction(Create_xor(Regs::a3, Regs::a5, Regs::sp), "xor a3 a5 sp");
	TestEncodeDecodeInstruction(Create_xor(Regs::s6, Regs::x0, Regs::s7), "xor s6 x0 s7");
	TestEncodeDecodeInstruction(Create_xor(Regs::t3, Regs::gp, Regs::tp), "xor t3 gp tp");
}
static void Test_srl()
{
	TestEncodeDecodeInstruction(Create_srl(Regs::a3, Regs::a5, Regs::sp), "srl a3 a5 sp");
	TestEncodeDecodeInstruction(Create_srl(Regs::s6, Regs::x0, Regs::s7), "srl s6 x0 s7");
	TestEncodeDecodeInstruction(Create_srl(Regs::t3, Regs::gp, Regs::tp), "srl t3 gp tp");
}
static void Test_sra()
{
	TestEncodeDecodeInstruction(Create_sra(Regs::a3, Regs::a5, Regs::sp), "sra a3 a5 sp");
	TestEncodeDecodeInstruction(Create_sra(Regs::s6, Regs::x0, Regs::s7), "sra s6 x0 s7");
	TestEncodeDecodeInstruction(Create_sra(Regs::t3, Regs::gp, Regs::tp), "sra t3 gp tp");
}
static void Test_or()
{
	TestEncodeDecodeInstruction(Create_or(Regs::a3, Regs::a5, Regs::sp), "or a3 a5 sp");
	TestEncodeDecodeInstruction(Create_or(Regs::s6, Regs::x0, Regs::s7), "or s6 x0 s7");
	TestEncodeDecodeInstruction(Create_or(Regs::t3, Regs::gp, Regs::tp), "or t3 gp tp");
}
static void Test_and()
{
	TestEncodeDecodeInstruction(Create_and(Regs::a3, Regs::a5, Regs::sp), "and a3 a5 sp");
	TestEncodeDecodeInstruction(Create_and(Regs::s6, Regs::x0, Regs::s7), "and s6 x0 s7");
	TestEncodeDecodeInstruction(Create_and(Regs::t3, Regs::gp, Regs::tp), "and t3 gp tp");
}
static void Test_lui()
{
	TestEncodeDecodeInstruction(Create_lui(Regs::t1, 122782), "lui t1 122782");
	TestEncodeDecodeInstruction(Create_lui(Regs::s6,   1594), "lui s6 1594");
	TestEncodeDecodeInstruction(Create_lui(Regs::s1,      2), "lui s1 2");
}
static void Test_beq()
{
	TestEncodeDecodeInstruction(Create_beq(Regs::a5, Regs::a1,  -4), "beq a5 a1 -4");
	TestEncodeDecodeInstruction(Create_beq(Regs::s2, Regs::t4, 132), "beq s2 t4 132");
	TestEncodeDecodeInstruction(Create_beq(Regs::t6, Regs::sp,  20), "beq t6 sp 20");
}
static void Test_bne()
{
	TestEncodeDecodeInstruction(Create_bne(Regs::a5, Regs::a1,  -4), "bne a5 a1 -4");
	TestEncodeDecodeInstruction(Create_bne(Regs::s2, Regs::t4, 132), "bne s2 t4 132");
	TestEncodeDecodeInstruction(Create_bne(Regs::t6, Regs::sp,  20), "bne t6 sp 20");
}
static void Test_blt()
{
	TestEncodeDecodeInstruction(Create_blt(Regs::a5, Regs::a1,  -4), "blt a5 a1 -4");
	TestEncodeDecodeInstruction(Create_blt(Regs::s2, Regs::t4, 132), "blt s2 t4 132");
	TestEncodeDecodeInstruction(Create_blt(Regs::t6, Regs::sp,  20), "blt t6 sp 20");
}
static void Test_bge()
{
	TestEncodeDecodeInstruction(Create_bge(Regs::a5, Regs::a1,  -4), "bge a5 a1 -4");
	TestEncodeDecodeInstruction(Create_bge(Regs::s2, Regs::t4, 132), "bge s2 t4 132");
	TestEncodeDecodeInstruction(Create_bge(Regs::t6, Regs::sp,  20), "bge t6 sp 20");
}
static void Test_bltu()
{
	TestEncodeDecodeInstruction(Create_bltu(Regs::a5, Regs::a1,  -4), "bltu a5 a1 -4");
	TestEncodeDecodeInstruction(Create_bltu(Regs::s2, Regs::t4, 132), "bltu s2 t4 132");
	TestEncodeDecodeInstruction(Create_bltu(Regs::t6, Regs::sp,  20), "bltu t6 sp 20");
}
static void Test_bgeu()
{
	TestEncodeDecodeInstruction(Create_bgeu(Regs::a5, Regs::a1,  -4), "bgeu a5 a1 -4");
	TestEncodeDecodeInstruction(Create_bgeu(Regs::s2, Regs::t4, 132), "bgeu s2 t4 132");
	TestEncodeDecodeInstruction(Create_bgeu(Regs::t6, Regs::sp,  20), "bgeu t6 sp 20");
}
static void Test_jalr()
{
	TestEncodeDecodeInstruction(Create_jalr(Regs::a3, Regs::a5,  1), "jalr a3 a5 1");
	TestEncodeDecodeInstruction(Create_jalr(Regs::s6, Regs::x0, 21), "jalr s6 x0 21");
	TestEncodeDecodeInstruction(Create_jalr(Regs::t3, Regs::gp,  0), "jalr t3 gp 0");
}
static void Test_jal()
{
	TestEncodeDecodeInstruction(Create_jal(Regs::s11,-54222), "jal s11 -54222");
	TestEncodeDecodeInstruction(Create_jal(Regs::s6, 12322), "jal s6 12322");
	TestEncodeDecodeInstruction(Create_jal(Regs::t0,    122), "jal t0 122");
}
static void Test_ecall()
{
	TestEncodeDecodeInstruction(Create_ecall(), "ecall");
}
static void Test_ebreak()
{
	TestEncodeDecodeInstruction(Create_ebreak(), "ebreak");
}
static void Test_csrrw()
{

}
static void Test_csrrs()
{

}
static void Test_csrrc()
{

}
static void Test_csrrwi()
{

}
static void Test_csrrsi()
{

}
static void Test_csrrci()
{

}
static void Test_mul()
{
	TestEncodeDecodeInstruction(Create_mul(Regs::a0, Regs::s5, Regs::s10), "mul a0 s5 s10");
	TestEncodeDecodeInstruction(Create_mul(Regs::s2, Regs::t4, Regs::s11), "mul s2 t4 s11");
	TestEncodeDecodeInstruction(Create_mul(Regs::t5, Regs::s10, Regs::t1), "mul t5 s10 t1");
}
static void Test_mulh()
{
	TestEncodeDecodeInstruction(Create_mulh(Regs::a0, Regs::s5, Regs::s10), "mulh a0 s5 s10");
	TestEncodeDecodeInstruction(Create_mulh(Regs::s2, Regs::t4, Regs::s11), "mulh s2 t4 s11");
	TestEncodeDecodeInstruction(Create_mulh(Regs::t5, Regs::s10, Regs::t1), "mulh t5 s10 t1");
}
static void Test_mulhsu()
{
	TestEncodeDecodeInstruction(Create_mulhsu(Regs::a0, Regs::s5, Regs::s10), "mulhsu a0 s5 s10");
	TestEncodeDecodeInstruction(Create_mulhsu(Regs::s2, Regs::t4, Regs::s11), "mulhsu s2 t4 s11");
	TestEncodeDecodeInstruction(Create_mulhsu(Regs::t5, Regs::s10, Regs::t1), "mulhsu t5 s10 t1");
}
static void Test_mulhu()
{
	TestEncodeDecodeInstruction(Create_mulhu(Regs::a0, Regs::s5, Regs::s10), "mulhu a0 s5 s10");
	TestEncodeDecodeInstruction(Create_mulhu(Regs::s2, Regs::t4, Regs::s11), "mulhu s2 t4 s11");
	TestEncodeDecodeInstruction(Create_mulhu(Regs::t5, Regs::s10, Regs::t1), "mulhu t5 s10 t1");
}
static void Test_div()
{
	TestEncodeDecodeInstruction(Create_div(Regs::a0, Regs::s5, Regs::s10), "div a0 s5 s10");
	TestEncodeDecodeInstruction(Create_div(Regs::s2, Regs::t4, Regs::s11), "div s2 t4 s11");
	TestEncodeDecodeInstruction(Create_div(Regs::t5, Regs::s10, Regs::t1), "div t5 s10 t1");
}
static void Test_divu()
{
	TestEncodeDecodeInstruction(Create_divu(Regs::a0, Regs::s5, Regs::s10), "divu a0 s5 s10");
	TestEncodeDecodeInstruction(Create_divu(Regs::s2, Regs::t4, Regs::s11), "divu s2 t4 s11");
	TestEncodeDecodeInstruction(Create_divu(Regs::t5, Regs::s10, Regs::t1), "divu t5 s10 t1");
}
static void Test_rem()
{
	TestEncodeDecodeInstruction(Create_rem(Regs::a0, Regs::s5, Regs::s10), "rem a0 s5 s10");
	TestEncodeDecodeInstruction(Create_rem(Regs::s2, Regs::t4, Regs::s11), "rem s2 t4 s11");
	TestEncodeDecodeInstruction(Create_rem(Regs::t5, Regs::s10, Regs::t1), "rem t5 s10 t1");
}
static void Test_remu()
{
	TestEncodeDecodeInstruction(Create_remu(Regs::a0, Regs::s5, Regs::s10), "remu a0 s5 s10");
	TestEncodeDecodeInstruction(Create_remu(Regs::s2, Regs::t4, Regs::s11), "remu s2 t4 s11");
	TestEncodeDecodeInstruction(Create_remu(Regs::t5, Regs::s10, Regs::t1), "remu t5 s10 t1");
}

void TestAllEncodeDecode()
{
	try
	{
		Test_lb();
		Test_lh();
		Test_lw();
		Test_lbu();
		Test_lhu();
		Test_fence();
		Test_fence_i();
		Test_addi();
		Test_slli();
		Test_slti();
		Test_sltiu();
		Test_xori();
		Test_srli();
		Test_srai();
		Test_ori();
		Test_andi();
		Test_auipc();
		Test_sb();
		Test_sh();
		Test_sw();
		Test_add();
		Test_sub();
		Test_sll();
		Test_slt();
		Test_sltu();
		Test_xor();
		Test_srl();
		Test_sra();
		Test_or();
		Test_and();
		Test_lui();
		Test_beq();
		Test_bne();
		Test_blt();
		Test_bge();
		Test_bltu();
		Test_bgeu();
		Test_jalr();
		Test_jal();
		Test_ecall();
		Test_ebreak();
		Test_csrrw();
		Test_csrrs();
		Test_csrrc();
		Test_csrrwi();
		Test_csrrsi();
		Test_csrrci();
		Test_mul();
		Test_mulh();
		Test_mulhsu();
		Test_mulhu();
		Test_div();
		Test_divu();
		Test_rem();
		Test_remu();
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Failed to finish all encode decode tests" << std::endl;
		std::cout << e.what() << std::endl;
		return;
	}

	std::cout << "Successfully finished all encode decode tests\n" << std::endl;
}