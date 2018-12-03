#include "TestInstructions.h"
#include <stdexcept>
#include <iostream>
#include "InstructionEncode.h"
#include "Register.h"
#include "Processor.h"
#include "InstructionDecode.h"
#include <string>
#include <memory>
#include "Instruction.h"
#include "ReadProgram.h"
#include "RISCV_Program.h"

static void Success(const std::string& testName)
{
    std::cout << "Test Success: " << testName << std::endl;
}

static void TestProgram(RISCV_Program& program, const std::string& filepath)
{
	program.Save(filepath);
	std::unique_ptr<RISCV_Program> loadedProgram = LoadProgram(filepath);

	program.Test();
	loadedProgram->Test();

	CompareRISCVPrograms(program, loadedProgram);
}

static void Test_lb()
{
	RISCV_Program program("Test_lb");

	program.SetRegister(Regs::s0, 102);
	program.AddInstruction(Create_sb(Regs::x0, Regs::s0, 100));
	program.AddInstruction(Create_lb(Regs::t0, Regs::x0, 100));
	program.ExpectRegisterValue(Regs::t0, 102);

	program.SetRegister(Regs::s1, 0x80'80'80'80);
	program.SetRegister(Regs::s2, 39);
	program.AddInstruction(Create_sb(Regs::s2, Regs::s1, 24));
	program.AddInstruction(Create_lb(Regs::t1, Regs::s2, 24));
	program.ExpectRegisterValue(Regs::t1, 0xff'ff'ff'80);

	program.SetRegister(Regs::s3, 0x4f'4f'4f4f);
	program.SetRegister(Regs::s4, 103);
	program.AddInstruction(Create_sb(Regs::s4, Regs::s3, 291));
	program.AddInstruction(Create_lb(Regs::t2, Regs::s4, 291));
	program.ExpectRegisterValue(Regs::t2, 0x4f);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_lb");

	Success("test_lb");
}
static void Test_lh()
{
	RISCV_Program program("Test_lh");

	program.SetRegister(Regs::s0, 13302);
	program.AddInstruction(Create_sh(Regs::x0, Regs::s0, 100));
	program.AddInstruction(Create_lh(Regs::t0, Regs::x0, 100));
	program.ExpectRegisterValue(Regs::t0, 13302);

	program.SetRegister(Regs::s1, 0x80'80'80'80);
	program.SetRegister(Regs::s2, 39);
	program.AddInstruction(Create_sh(Regs::s2, Regs::s1, 24));
	program.AddInstruction(Create_lh(Regs::t1, Regs::s2, 24));
	program.ExpectRegisterValue(Regs::t1, 0xff'ff'80'80);

	program.SetRegister(Regs::s3, 0x4f'4f'4f4f);
	program.SetRegister(Regs::s4, 103);
	program.AddInstruction(Create_sh(Regs::s4, Regs::s3, 291));
	program.AddInstruction(Create_lh(Regs::t2, Regs::s4, 291));
	program.ExpectRegisterValue(Regs::t2, 0x4f'4f);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_lh");

	Success("test_lh");
}
static void Test_lw()
{
	RISCV_Program program("Test_lw");

	program.SetRegister(Regs::s0, 1338802);
	program.AddInstruction(Create_sw(Regs::x0, Regs::s0, 100));
	program.AddInstruction(Create_lw(Regs::t0, Regs::x0, 100));
	program.ExpectRegisterValue(Regs::t0, 1338802);

	program.SetRegister(Regs::s1, 0x80'80'80'80);
	program.SetRegister(Regs::s2, 39);
	program.AddInstruction(Create_sw(Regs::s2, Regs::s1, 24));
	program.AddInstruction(Create_lw(Regs::t1, Regs::s2, 24));
	program.ExpectRegisterValue(Regs::t1, 0x80'80'80'80);

	program.SetRegister(Regs::s3, 0x4f'4f'4f4f);
	program.SetRegister(Regs::s4, 103);
	program.AddInstruction(Create_sw(Regs::s4, Regs::s3, 291));
	program.AddInstruction(Create_lw(Regs::t2, Regs::s4, 291));
	program.ExpectRegisterValue(Regs::t2, 0x4f'4f'4f'4f);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_lw");

	Success("test_lw");
}
static void Test_lbu()
{
	RISCV_Program program("Test_lbu");

	program.SetRegister(Regs::s0, 102);
	program.AddInstruction(Create_sb(Regs::x0, Regs::s0, 100));
	program.AddInstruction(Create_lbu(Regs::t0, Regs::x0, 100));
	program.ExpectRegisterValue(Regs::t0, 102);

	program.SetRegister(Regs::s1, 0x80'80'80'80);
	program.SetRegister(Regs::s2, 39);
	program.AddInstruction(Create_sb(Regs::s2, Regs::s1, 24));
	program.AddInstruction(Create_lbu(Regs::t1, Regs::s2, 24));
	program.ExpectRegisterValue(Regs::t1, 0x00'00'0080);

	program.SetRegister(Regs::s3, 0x4f'4f'4f4f);
	program.SetRegister(Regs::s4, 103);
	program.AddInstruction(Create_sb(Regs::s4, Regs::s3, 291));
	program.AddInstruction(Create_lbu(Regs::t2, Regs::s4, 291));
	program.ExpectRegisterValue(Regs::t2, 0x4f);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_lbu");

	Success("test_lbu");
}
static void Test_lhu()
{
	RISCV_Program program("Test_lhu");

	program.SetRegister(Regs::s0, 13302);
	program.AddInstruction(Create_sh(Regs::x0, Regs::s0, 100));
	program.AddInstruction(Create_lhu(Regs::t0, Regs::x0, 100));
	program.ExpectRegisterValue(Regs::t0, 13302);

	program.SetRegister(Regs::s1, 0x80'80'80'80);
	program.SetRegister(Regs::s2, 39);
	program.AddInstruction(Create_sh(Regs::s2, Regs::s1, 24));
	program.AddInstruction(Create_lhu(Regs::t1, Regs::s2, 24));
	program.ExpectRegisterValue(Regs::t1, 0x00'00'80'80);

	program.SetRegister(Regs::s3, 0x4f'4f'4f4f);
	program.SetRegister(Regs::s4, 103);
	program.AddInstruction(Create_sh(Regs::s4, Regs::s3, 291));
	program.AddInstruction(Create_lhu(Regs::t2, Regs::s4, 291));
	program.ExpectRegisterValue(Regs::t2, 0x4f'4f);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_lhu");

	Success("test_lhu");
}
static void Test_fence()
{

}
static void Test_fence_i()
{

}
static void Test_addi()
{
    RISCV_Program program("Test_addi");

    program.AddInstruction(Create_addi(Regs::t1, Regs::x0, 125));
    program.ExpectRegisterValue(Regs::t1, 125);

    program.AddInstruction(Create_addi(Regs::t2, Regs::t1, 35));
    program.ExpectRegisterValue(Regs::t2, 160);

    program.AddInstruction(Create_addi(Regs::t3, Regs::t2, -100));
    program.ExpectRegisterValue(Regs::t3, 60);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_addi");

	Success("test_addi");
}
static void Test_slli()
{
	RISCV_Program program("Test_slli");

	program.SetRegister(Regs::t0, 0x0f'00'ff'00);
	program.AddInstruction(Create_slli(Regs::t1, Regs::t0, 4));
	program.ExpectRegisterValue(Regs::t1, 0xf0'0f'f0'00);

	program.AddInstruction(Create_slli(Regs::t2, Regs::t0, 16));
	program.ExpectRegisterValue(Regs::t2, 0xff'00'00'00);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_slli");

	Success("test_slli");
}
static void Test_slti()
{
	RISCV_Program program("Test_slti");

	program.SetRegister(Regs::t0, 20);
	program.AddInstruction(Create_slti(Regs::t1, Regs::t0, 21));
	program.ExpectRegisterValue(Regs::t1, 1);

	program.AddInstruction(Create_slti(Regs::t2, Regs::t0, 20));
	program.ExpectRegisterValue(Regs::t2, 0);

	program.AddInstruction(Create_slti(Regs::t3, Regs::t0, 19));
	program.ExpectRegisterValue(Regs::t3, 0);

	program.AddInstruction(Create_slti(Regs::t4, Regs::t0, -19));
	program.ExpectRegisterValue(Regs::t4, 0);

	program.SetRegister(Regs::t0, -20);
	program.AddInstruction(Create_slti(Regs::t5, Regs::t0, -19));
	program.ExpectRegisterValue(Regs::t5, 1);

	program.AddInstruction(Create_slti(Regs::t6, Regs::t0, -20));
	program.ExpectRegisterValue(Regs::t6, 0);

	program.AddInstruction(Create_slti(Regs::s1, Regs::t0, -21));
	program.ExpectRegisterValue(Regs::s1, 0);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_slti");

	Success("test_slti");
}
static void Test_sltiu()
{
	RISCV_Program program("Test_sltiu");

	program.SetRegister(Regs::t0, 20);
	program.AddInstruction(Create_sltiu(Regs::t1, Regs::t0, 21));
	program.ExpectRegisterValue(Regs::t1, 1);

	program.AddInstruction(Create_sltiu(Regs::t2, Regs::t0, 20));
	program.ExpectRegisterValue(Regs::t2, 0);

	program.AddInstruction(Create_sltiu(Regs::t3, Regs::t0, 19));
	program.ExpectRegisterValue(Regs::t3, 0);

	program.AddInstruction(Create_sltiu(Regs::t4, Regs::t0, -19));
	program.ExpectRegisterValue(Regs::t4, 1);

	program.SetRegister(Regs::t0, -20);
	program.AddInstruction(Create_sltiu(Regs::t5, Regs::t0, -19));
	program.ExpectRegisterValue(Regs::t5, 1);

	program.AddInstruction(Create_sltiu(Regs::t6, Regs::t0, -20));
	program.ExpectRegisterValue(Regs::t6, 0);

	program.AddInstruction(Create_sltiu(Regs::s1, Regs::t0, -21));
	program.ExpectRegisterValue(Regs::s1, 0);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_sltiu");

	Success("test_sltiu");
}
static void Test_xori()
{
	RISCV_Program program("Test_xori");

	program.SetRegister(Regs::t0, 0x0f'00'ff'f0);
	program.AddInstruction(Create_xori(Regs::t1, Regs::t0, 0x00'00'07'0f));
	program.ExpectRegisterValue(Regs::t1, 0x0f'00'f8'ff);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_xori");

	Success("test_xori");
}
static void Test_srli()
{
	RISCV_Program program("Test_srli");

	program.SetRegister(Regs::t0, 0xf0'ff'00'f0);
	program.AddInstruction(Create_srli(Regs::t1, Regs::t0, 4));
	program.ExpectRegisterValue(Regs::t1, 0x0f'0f'f0'0f);

	program.AddInstruction(Create_srli(Regs::t2, Regs::t0, 12));
	program.ExpectRegisterValue(Regs::t2, 0x00'0f'0f'f0);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_srli");

	Success("test_srli");
}
static void Test_srai()
{
	RISCV_Program program("Test_srai");

	program.SetRegister(Regs::t0, 0xf0'ff'00'f0);
	program.AddInstruction(Create_srai(Regs::t1, Regs::t0, 4));
	program.ExpectRegisterValue(Regs::t1, 0xff'0f'f0'0f);

	program.AddInstruction(Create_srai(Regs::t2, Regs::t0, 12));
	program.ExpectRegisterValue(Regs::t2, 0xff'ff'0f'f0);

	program.SetRegister(Regs::t0, 0x00'f0'ff'f0);
	program.AddInstruction(Create_srai(Regs::t3, Regs::t0, 4));
	program.ExpectRegisterValue(Regs::t3, 0x00'0f'0f'ff);

	program.AddInstruction(Create_srai(Regs::t4, Regs::t0, 12));
	program.ExpectRegisterValue(Regs::t4, 0x00'00'0f'0f);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_srai");

	Success("test_srai");
}
static void Test_ori()
{
	RISCV_Program program("Test_ori");

	program.SetRegister(Regs::t0, 0x8f'00'ff'f1);
	program.AddInstruction(Create_ori(Regs::t1, Regs::t0, 0x00'00'07'00));
	program.ExpectRegisterValue(Regs::t1, 0x8f'00'ff'f1);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_ori");

	Success("test_ori");
}
static void Test_andi()
{
	RISCV_Program program("Test_andi");

	program.SetRegister(Regs::t0, 0x0f'00'ff'f1);
	program.AddInstruction(Create_andi(Regs::t1, Regs::t0, 0x00'00'07'01));
	program.ExpectRegisterValue(Regs::t1, 0x00'00'07'01);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_andi");

	Success("test_andi");
}
static void Test_auipc()
{
	RISCV_Program program("Test_auipc");

	program.AddInstruction(Create_auipc(Regs::t0, 0x00'00'04'00));
	program.ExpectRegisterValue(Regs::t0, (0x00'00'04'00 << 12) + 0);

	program.AddInstruction(Create_auipc(Regs::t1, 0x00'00'04'00));
	program.ExpectRegisterValue(Regs::t1, (0x00'00'04'00 << 12) + 4);

	program.AddInstruction(Create_auipc(Regs::t2, 0x00'07'04'00));
	program.ExpectRegisterValue(Regs::t2, (0x00'07'04'00 << 12) + 8);

	program.AddInstruction(Create_auipc(Regs::t3, 0));
	program.ExpectRegisterValue(Regs::t3, 12);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_auipc");

	Success("test_auipc");
}
static void Test_sb()
{
	//has already been tested in the lb tests
	RISCV_Program program("Test_sb");

	program.SetRegister(Regs::s0, 102);
	program.AddInstruction(Create_sb(Regs::x0, Regs::s0, 100));
	program.AddInstruction(Create_lb(Regs::t0, Regs::x0, 100));
	program.ExpectRegisterValue(Regs::t0, 102);

	program.SetRegister(Regs::s2, 102);
	program.SetRegister(Regs::s1, 60);
	program.AddInstruction(Create_sb(Regs::s1, Regs::s2, -23));
	program.AddInstruction(Create_lb(Regs::t1, Regs::s1, -23));
	program.ExpectRegisterValue(Regs::t1, 102);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_sb");

	Success("test_sb");
}
static void Test_sh()
{
	RISCV_Program program("Test_sh");

	program.SetRegister(Regs::s0, 0xce'2d);
	program.AddInstruction(Create_sh(Regs::x0, Regs::s0, 100));

	program.AddInstruction(Create_lb(Regs::t0, Regs::x0, 100));
	program.AddInstruction(Create_lb(Regs::t1, Regs::x0, 101));
	program.ExpectRegisterValue(Regs::t0, 0x2d);
	program.ExpectRegisterValue(Regs::t1, 0xff'ff'ff'ce);

	program.SetRegister(Regs::s2, 10232);
	program.SetRegister(Regs::s1, 50);
	program.AddInstruction(Create_sh(Regs::s1, Regs::s2, -23));
	program.AddInstruction(Create_lh(Regs::t1, Regs::s1, -23));
	program.ExpectRegisterValue(Regs::t1, 10232);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_sh");

	Success("test_sh");
}
static void Test_sw()
{
	RISCV_Program program("Test_sw");

	program.SetRegister(Regs::s0, 0x3a'74'ce'2d);
	program.AddInstruction(Create_sw(Regs::x0, Regs::s0, 100));

	program.AddInstruction(Create_lb(Regs::t0, Regs::x0, 100));
	program.AddInstruction(Create_lb(Regs::t1, Regs::x0, 101));
	program.AddInstruction(Create_lb(Regs::t2, Regs::x0, 102));
	program.AddInstruction(Create_lb(Regs::t3, Regs::x0, 103));
	program.ExpectRegisterValue(Regs::t0, 0x2d);
	program.ExpectRegisterValue(Regs::t1, 0xff'ff'ff'ce);
	program.ExpectRegisterValue(Regs::t2, 0x74);
	program.ExpectRegisterValue(Regs::t3, 0x3a);

	program.AddInstruction(Create_lh(Regs::t4, Regs::x0, 100));
	program.AddInstruction(Create_lh(Regs::t5, Regs::x0, 102));
	program.ExpectRegisterValue(Regs::t4, 0xff'ff'ce'2d);
	program.ExpectRegisterValue(Regs::t5, 0x3a'74);

	program.AddInstruction(Create_lh(Regs::t6, Regs::x0, 101));
	program.ExpectRegisterValue(Regs::t6, 0x74'ce);

	program.SetRegister(Regs::s2, 10232);
	program.SetRegister(Regs::s1, 50);
	program.AddInstruction(Create_sw(Regs::s1, Regs::s2, -23));
	program.AddInstruction(Create_lw(Regs::s3, Regs::s1, -23));
	program.ExpectRegisterValue(Regs::s3, 10232);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_sw");

	Success("test_sw");
}
static void Test_add()
{
	RISCV_Program program("Test_add");

	program.SetRegister(Regs::t0, 125);
	program.AddInstruction(Create_add(Regs::t1, Regs::x0, Regs::t0));
	program.ExpectRegisterValue(Regs::t1, 125);

	program.SetRegister(Regs::t0, 35);
	program.AddInstruction(Create_add(Regs::t2, Regs::t1, Regs::t0));
	program.ExpectRegisterValue(Regs::t2, 160);

	program.SetRegister(Regs::t0, -100);
	program.AddInstruction(Create_add(Regs::t3, Regs::t2, Regs::t0));
	program.ExpectRegisterValue(Regs::t3, 60);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_add");

	Success("test_add");
}
static void Test_sub()
{
	RISCV_Program program("Test_sub");

	program.SetRegister(Regs::t0, 125);
	program.AddInstruction(Create_sub(Regs::t1, Regs::x0, Regs::t0));
	program.ExpectRegisterValue(Regs::t1, -125);

	program.SetRegister(Regs::t0, 35);
	program.AddInstruction(Create_sub(Regs::t2, Regs::t1, Regs::t0));
	program.ExpectRegisterValue(Regs::t2, -160);

	program.SetRegister(Regs::t0, -100);
	program.AddInstruction(Create_sub(Regs::t3, Regs::t2, Regs::t0));
	program.ExpectRegisterValue(Regs::t3, -60);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_sub");

	Success("test_sub");
}
static void Test_sll()
{
	RISCV_Program program("Test_sll");

	program.SetRegister(Regs::t0, 0x0f'00'ff'00);
	program.SetRegister(Regs::s0, 4);
	program.AddInstruction(Create_sll(Regs::t1, Regs::t0, Regs::s0));
	program.ExpectRegisterValue(Regs::t1, 0xf0'0f'f0'00);

	program.SetRegister(Regs::s0, 16);
	program.AddInstruction(Create_sll(Regs::t2, Regs::t0, Regs::s0));
	program.ExpectRegisterValue(Regs::t2, 0xff'00'00'00);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_sll");

	Success("test_sll");
}
static void Test_slt()
{
	RISCV_Program program("Test_slt");

	program.SetRegister(Regs::t0, 20);
	program.SetRegister(Regs::a0, 21);
	program.AddInstruction(Create_slt(Regs::t1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t1, 1);

	program.SetRegister(Regs::a0, 20);
	program.AddInstruction(Create_slt(Regs::t2, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t2, 0);

	program.SetRegister(Regs::a0, 19);
	program.AddInstruction(Create_slt(Regs::t3, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t3, 0);

	program.SetRegister(Regs::a0, -19);
	program.AddInstruction(Create_slt(Regs::t4, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t4, 0);

	program.SetRegister(Regs::t0, -20);
	program.SetRegister(Regs::a0, -19);
	program.AddInstruction(Create_slt(Regs::t5, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t5, 1);

	program.SetRegister(Regs::a0, -20);
	program.AddInstruction(Create_slt(Regs::t6, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t6, 0);

	program.SetRegister(Regs::a0, -21);
	program.AddInstruction(Create_slt(Regs::s1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::s1, 0);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_slt");

	Success("test_slt");
}
static void Test_sltu()
{
	RISCV_Program program("Test_sltu");

	program.SetRegister(Regs::t0, 20);
	program.SetRegister(Regs::a0, 21);
	program.AddInstruction(Create_sltu(Regs::t1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t1, 1);

	program.SetRegister(Regs::a0, 20);
	program.AddInstruction(Create_sltu(Regs::t2, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t2, 0);

	program.SetRegister(Regs::a0, 19);
	program.AddInstruction(Create_sltu(Regs::t3, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t3, 0);

	program.SetRegister(Regs::a0, -19);
	program.AddInstruction(Create_sltu(Regs::t4, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t4, 1);

	program.SetRegister(Regs::t0, -20);
	program.SetRegister(Regs::a0, -19);
	program.AddInstruction(Create_sltu(Regs::t5, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t5, 1);

	program.SetRegister(Regs::a0, -20);
	program.AddInstruction(Create_sltu(Regs::t6, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t6, 0);

	program.SetRegister(Regs::a0, -21);
	program.AddInstruction(Create_sltu(Regs::s1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::s1, 0);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_sltu");

	Success("test_sltu");
}
static void Test_xor()
{
	RISCV_Program program("Test_xor");

	program.SetRegister(Regs::t0, 0x0f'00'ff'f0);
	program.SetRegister(Regs::t1, 0x00'00'07'0f);
	program.AddInstruction(Create_xor(Regs::t2, Regs::t0, Regs::t1));
	program.ExpectRegisterValue(Regs::t2, 0x0f'00'f8'ff);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_xor");

	Success("test_xor");
}
static void Test_srl()
{
	RISCV_Program program("Test_srl");

	program.SetRegister(Regs::t0, 0xf0'ff'00'f0);
	program.SetRegister(Regs::a0, 4);
	program.AddInstruction(Create_srl(Regs::t1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t1, 0x0f'0f'f0'0f);

	program.SetRegister(Regs::a0, 12);
	program.AddInstruction(Create_srl(Regs::t2, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t2, 0x00'0f'0f'f0);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_srl");

	Success("test_srl");
}
static void Test_sra()
{
	RISCV_Program program("Test_sra");

	program.SetRegister(Regs::t0, 0xf0'ff'00'f0);
	program.SetRegister(Regs::a0, 4);
	program.AddInstruction(Create_sra(Regs::t1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t1, 0xff'0f'f0'0f);

	program.SetRegister(Regs::a0, 12);
	program.AddInstruction(Create_sra(Regs::t2, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t2, 0xff'ff'0f'f0);

	program.SetRegister(Regs::t0, 0x00'f0'ff'f0);
	program.SetRegister(Regs::a0, 4);
	program.AddInstruction(Create_sra(Regs::t3, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t3, 0x00'0f'0f'ff);

	program.SetRegister(Regs::a0, 12);
	program.AddInstruction(Create_sra(Regs::t4, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t4, 0x00'00'0f'0f);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_sra");

	Success("test_sra");
}
static void Test_or()
{
	RISCV_Program program("Test_or");

	program.SetRegister(Regs::t0, 0x8f'00'ff'f1);
	program.SetRegister(Regs::a0, 0x00'00'07'00);
	program.AddInstruction(Create_or(Regs::t1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t1, 0x8f'00'ff'f1);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_or");

	Success("test_or");
}
static void Test_and()
{
	RISCV_Program program("Test_and");

	program.SetRegister(Regs::t0, 0x0f'00'ff'f1);
	program.SetRegister(Regs::a0, 0x00'00'07'01);
	program.AddInstruction(Create_and(Regs::t1, Regs::t0, Regs::a0));
	program.ExpectRegisterValue(Regs::t1, 0x00'00'07'01);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_and");

	Success("test_and");
}
static void Test_lui()
{
	RISCV_Program program("Test_lui");

	program.AddInstruction(Create_lui(Regs::t0, 0x00'00'04'00));
	program.ExpectRegisterValue(Regs::t0, 0x00'00'04'00 << 12);

	program.AddInstruction(Create_lui(Regs::t1, 63322));
	program.ExpectRegisterValue(Regs::t1, 63322 << 12);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_lui");

	Success("test_lui");
}
static void Test_beq()
{
	RISCV_Program program("Test_beq");

	program.SetRegister(Regs::s0, 1);
	program.SetRegister(Regs::s1, 1);
	program.SetRegister(Regs::s2, 1);
	program.SetRegister(Regs::s3, 1);
	program.SetRegister(Regs::s4, 1);
	program.ExpectRegisterValue(Regs::s0, 0);
	program.ExpectRegisterValue(Regs::s1, 1);
	program.ExpectRegisterValue(Regs::s2, 0);
	program.ExpectRegisterValue(Regs::s3, 0);
	program.ExpectRegisterValue(Regs::s4, 0);

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_beq(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s0, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_beq(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s1, 0));

	program.SetRegister(Regs::t0, 10);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_beq(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s2, 0));

	program.SetRegister(Regs::t0, -5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_beq(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s3, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, -10);
	program.AddInstruction(Create_beq(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s4, 0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_beq");

	Success("test_beq");
}
static void Test_bne()
{
	RISCV_Program program("Test_bne");

	program.SetRegister(Regs::s0, 1);
	program.SetRegister(Regs::s1, 1);
	program.SetRegister(Regs::s2, 1);
	program.SetRegister(Regs::s3, 1);
	program.SetRegister(Regs::s4, 1);
	program.ExpectRegisterValue(Regs::s0, 1);
	program.ExpectRegisterValue(Regs::s1, 0);
	program.ExpectRegisterValue(Regs::s2, 1);
	program.ExpectRegisterValue(Regs::s3, 1);
	program.ExpectRegisterValue(Regs::s4, 1);

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bne(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s0, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bne(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s1, 0));

	program.SetRegister(Regs::t0, 10);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bne(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s2, 0));

	program.SetRegister(Regs::t0, -5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bne(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s3, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, -10);
	program.AddInstruction(Create_bne(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s4, 0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_bne");

	Success("test_bne");
}
static void Test_blt()
{
	RISCV_Program program("Test_blt");

	program.SetRegister(Regs::s0, 1);
	program.SetRegister(Regs::s1, 1);
	program.SetRegister(Regs::s2, 1);
	program.SetRegister(Regs::s3, 1);
	program.SetRegister(Regs::s4, 1);
	program.ExpectRegisterValue(Regs::s0, 1);
	program.ExpectRegisterValue(Regs::s1, 0);
	program.ExpectRegisterValue(Regs::s2, 0);
	program.ExpectRegisterValue(Regs::s3, 1);
	program.ExpectRegisterValue(Regs::s4, 0);

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_blt(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s0, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_blt(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s1, 0));

	program.SetRegister(Regs::t0, 10);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_blt(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s2, 0));

	program.SetRegister(Regs::t0, -5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_blt(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s3, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, -10);
	program.AddInstruction(Create_blt(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s4, 0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_blt");

	Success("test_blt");
}
static void Test_bge()
{
	RISCV_Program program("Test_bge");

	program.SetRegister(Regs::s0, 1);
	program.SetRegister(Regs::s1, 1);
	program.SetRegister(Regs::s2, 1);
	program.SetRegister(Regs::s3, 1);
	program.SetRegister(Regs::s4, 1);
	program.ExpectRegisterValue(Regs::s0, 0);
	program.ExpectRegisterValue(Regs::s1, 1);
	program.ExpectRegisterValue(Regs::s2, 1);
	program.ExpectRegisterValue(Regs::s3, 0);
	program.ExpectRegisterValue(Regs::s4, 1);

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bge(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s0, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bge(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s1, 0));

	program.SetRegister(Regs::t0, 10);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bge(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s2, 0));

	program.SetRegister(Regs::t0, -5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bge(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s3, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, -10);
	program.AddInstruction(Create_bge(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s4, 0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_bge");

	Success("test_bge");
}
static void Test_bltu()
{
	RISCV_Program program("Test_bltu");

	program.SetRegister(Regs::s0, 1);
	program.SetRegister(Regs::s1, 1);
	program.SetRegister(Regs::s2, 1);
	program.SetRegister(Regs::s3, 1);
	program.SetRegister(Regs::s4, 1);
	program.ExpectRegisterValue(Regs::s0, 1);
	program.ExpectRegisterValue(Regs::s1, 0);
	program.ExpectRegisterValue(Regs::s2, 0);
	program.ExpectRegisterValue(Regs::s3, 0);
	program.ExpectRegisterValue(Regs::s4, 1);

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bltu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s0, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bltu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s1, 0));

	program.SetRegister(Regs::t0, 10);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bltu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s2, 0));

	program.SetRegister(Regs::t0, -5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bltu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s3, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, -10);
	program.AddInstruction(Create_bltu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s4, 0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_bltu");

	Success("test_bltu");
}
static void Test_bgeu()
{
	RISCV_Program program("Test_bgeu");

	program.SetRegister(Regs::s0, 1);
	program.SetRegister(Regs::s1, 1);
	program.SetRegister(Regs::s2, 1);
	program.SetRegister(Regs::s3, 1);
	program.SetRegister(Regs::s4, 1);
	program.ExpectRegisterValue(Regs::s0, 0);
	program.ExpectRegisterValue(Regs::s1, 1);
	program.ExpectRegisterValue(Regs::s2, 1);
	program.ExpectRegisterValue(Regs::s3, 1);
	program.ExpectRegisterValue(Regs::s4, 0);

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bgeu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s0, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bgeu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s1, 0));

	program.SetRegister(Regs::t0, 10);
	program.SetRegister(Regs::t1, 5);
	program.AddInstruction(Create_bgeu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s2, 0));

	program.SetRegister(Regs::t0, -5);
	program.SetRegister(Regs::t1, 10);
	program.AddInstruction(Create_bgeu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s3, 0));

	program.SetRegister(Regs::t0, 5);
	program.SetRegister(Regs::t1, -10);
	program.AddInstruction(Create_bgeu(Regs::t0, Regs::t1, 8));
	program.AddInstruction(Create_li(Regs::s4, 0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_bgeu");

	Success("test_bgeu");
}
static void Test_jalr()
{
	RISCV_Program program("Test_jalr");

	program.AddInstruction(Create_jalr(Regs::t0, Regs::x0, 8));
	program.ExpectRegisterValue(Regs::t0, 4);
	program.AddInstruction(Create_li(Regs::s0, -1));
	program.SetRegister(Regs::s0, 1);
	program.ExpectRegisterValue(Regs::s0, 1);

	program.SetRegister(Regs::a0, -4);
	program.AddInstruction(Create_jalr(Regs::t1, Regs::a0, 28));
	program.ExpectRegisterValue(Regs::t1, 20);
	program.AddInstruction(Create_li(Regs::s0, -1));
	program.SetRegister(Regs::s1, 1);
	program.ExpectRegisterValue(Regs::s1, 1);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_jalr");

	Success("test_jalr");
}
static void Test_jal()
{
	RISCV_Program program("Test_jal");

	program.AddInstruction(Create_jal(Regs::t0, 8));
	program.ExpectRegisterValue(Regs::t0, 4);
	program.AddInstruction(Create_li(Regs::s0, -1));
	program.SetRegister(Regs::s0, 1);
	program.ExpectRegisterValue(Regs::s0, 1);

	program.AddInstruction(Create_jal(Regs::t1, 8));
	program.ExpectRegisterValue(Regs::t1, 16);
	program.AddInstruction(Create_li(Regs::s0, -1));
	program.SetRegister(Regs::s1, 1);
	program.ExpectRegisterValue(Regs::s1, 1);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_jal");

	Success("test_jal");
}
static void Test_ecall()
{
	RISCV_Program program("Test_ecall");

	program.SetRegister(Regs::a1, 10);
	program.AddInstruction(Create_ecall());
	program.SetRegister(Regs::s0, 1);
	program.ExpectRegisterValue(Regs::s0, 1);

	program.SetRegister(Regs::a0, 9);
	program.AddInstruction(Create_ecall());
	program.SetRegister(Regs::s1, 1);
	program.ExpectRegisterValue(Regs::s1, 1);

	program.SetRegister(Regs::a0, 11);
	program.AddInstruction(Create_ecall());
	program.SetRegister(Regs::s2, 1);
	program.ExpectRegisterValue(Regs::s2, 1);

	program.SetRegister(Regs::a0, 10);
	program.SetRegister(Regs::s3, -1);
	program.AddInstruction(Create_ecall());
	program.SetRegister(Regs::s3, 1);
	program.ExpectRegisterValue(Regs::s3, -1);

	TestProgram(program, "InstructionTests/test_ecall");

	Success("test_ecall");
}
static void Test_ebreak()
{

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
	RISCV_Program program("Test_mul");

	program.SetRegister(Regs::a0, 12);
	program.SetRegister(Regs::a1, 27);
	program.ExpectRegisterValue(Regs::s0, 12 * 27);
	program.ExpectRegisterValue(Regs::s1, 12 * 27);
	program.AddInstruction(Create_mul(Regs::s0, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mul(Regs::s1, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, 756);
	program.ExpectRegisterValue(Regs::s2, -31 * 756);
	program.ExpectRegisterValue(Regs::s3, -31 * 756);
	program.AddInstruction(Create_mul(Regs::s2, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mul(Regs::s3, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, -756);
	program.ExpectRegisterValue(Regs::s4, -31 * -756);
	program.ExpectRegisterValue(Regs::s5, -31 * -756);
	program.AddInstruction(Create_mul(Regs::s4, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mul(Regs::s5, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -32331);
	program.SetRegister(Regs::a1, -712356);
	program.ExpectRegisterValue(Regs::s6, -32331 * -712356);
	program.ExpectRegisterValue(Regs::s7, -32331 * -712356);
	program.AddInstruction(Create_mul(Regs::s6, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mul(Regs::s7, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, 21351321);
	program.SetRegister(Regs::a1, -92364243);
	program.ExpectRegisterValue(Regs::s8, 21351321 * -92364243);
	program.ExpectRegisterValue(Regs::s9, 21351321 * -92364243);
	program.AddInstruction(Create_mul(Regs::s8, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mul(Regs::s9, Regs::a1, Regs::a0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_mul");

	Success("test_mul");
}
static void Test_mulh()
{
	RISCV_Program program("Test_mulh");

	program.SetRegister(Regs::a0, 12);
	program.SetRegister(Regs::a1, 27);
	program.ExpectRegisterValue(Regs::s0, 0);
	program.ExpectRegisterValue(Regs::s1, 0);
	program.AddInstruction(Create_mulh(Regs::s0, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulh(Regs::s1, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, 756);
	program.ExpectRegisterValue(Regs::s2, -1);
	program.ExpectRegisterValue(Regs::s3, -1);
	program.AddInstruction(Create_mulh(Regs::s2, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulh(Regs::s3, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, -756);
	program.ExpectRegisterValue(Regs::s4, 0);
	program.ExpectRegisterValue(Regs::s5, 0);
	program.AddInstruction(Create_mulh(Regs::s4, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulh(Regs::s5, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -32331);
	program.SetRegister(Regs::a1, -712356);
	program.ExpectRegisterValue(Regs::s6, 5);
	program.ExpectRegisterValue(Regs::s7, 5);
	program.AddInstruction(Create_mulh(Regs::s6, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulh(Regs::s7, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, 21351321);
	program.SetRegister(Regs::a1, -92364243);
	program.ExpectRegisterValue(Regs::s8, -459165);
	program.ExpectRegisterValue(Regs::s9, -459165);
	program.AddInstruction(Create_mulh(Regs::s8, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulh(Regs::s9, Regs::a1, Regs::a0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_mulh");

	Success("test_mulh");
}
static void Test_mulhsu()
{
	RISCV_Program program("Test_mulhsu");

	program.SetRegister(Regs::a0, 12);
	program.SetRegister(Regs::a1, 27);
	program.ExpectRegisterValue(Regs::s0, 0);
	program.ExpectRegisterValue(Regs::s1, 0);
	program.AddInstruction(Create_mulhsu(Regs::s0, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulhsu(Regs::s1, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, 756);
	program.ExpectRegisterValue(Regs::s2, -1);
	program.ExpectRegisterValue(Regs::s3, 755);
	program.AddInstruction(Create_mulhsu(Regs::s2, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulhsu(Regs::s3, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, -756);
	program.ExpectRegisterValue(Regs::s4, -31);
	program.ExpectRegisterValue(Regs::s5, -756);
	program.AddInstruction(Create_mulhsu(Regs::s4, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulhsu(Regs::s5, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -32331);
	program.SetRegister(Regs::a1, -712356);
	program.ExpectRegisterValue(Regs::s6, -32326);
	program.ExpectRegisterValue(Regs::s7, -712351);
	program.AddInstruction(Create_mulhsu(Regs::s6, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulhsu(Regs::s7, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, 21351321);
	program.SetRegister(Regs::a1, -92364243);
	program.ExpectRegisterValue(Regs::s8, 20892156);
	program.ExpectRegisterValue(Regs::s9, -459165);
	program.AddInstruction(Create_mulhsu(Regs::s8, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulhsu(Regs::s9, Regs::a1, Regs::a0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_mulhsu");

	Success("test_mulhsu");
}
static void Test_mulhu()
{
	RISCV_Program program("Test_mulhu");

	program.SetRegister(Regs::a0, 12);
	program.SetRegister(Regs::a1, 27);
	program.ExpectRegisterValue(Regs::s0, 0);
	program.ExpectRegisterValue(Regs::s1, 0);
	program.AddInstruction(Create_mulhu(Regs::s0, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulhu(Regs::s1, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, 756);
	program.ExpectRegisterValue(Regs::s2, 755);
	program.ExpectRegisterValue(Regs::s3, 755);
	program.AddInstruction(Create_mulhu(Regs::s2, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulhu(Regs::s3, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, -756);
	program.ExpectRegisterValue(Regs::s4, -787);
	program.ExpectRegisterValue(Regs::s5, -787);
	program.AddInstruction(Create_mulhu(Regs::s4, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulhu(Regs::s5, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -32331);
	program.SetRegister(Regs::a1, -712356);
	program.ExpectRegisterValue(Regs::s6, -744682);
	program.ExpectRegisterValue(Regs::s7, -744682);
	program.AddInstruction(Create_mulhu(Regs::s6, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulhu(Regs::s7, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, 21351321);
	program.SetRegister(Regs::a1, -92364243);
	program.ExpectRegisterValue(Regs::s8, 20892156);
	program.ExpectRegisterValue(Regs::s9, 20892156);
	program.AddInstruction(Create_mulhu(Regs::s8, Regs::a0, Regs::a1));
	program.AddInstruction(Create_mulhu(Regs::s9, Regs::a1, Regs::a0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_mulhu");

	Success("test_mulhu");
}
static void Test_div()
{
	RISCV_Program program("Test_div");

	program.SetRegister(Regs::a0, 12);
	program.SetRegister(Regs::a1, 27);
	program.ExpectRegisterValue(Regs::s0, 0);
	program.ExpectRegisterValue(Regs::s1, 2);
	program.AddInstruction(Create_div(Regs::s0, Regs::a0, Regs::a1));
	program.AddInstruction(Create_div(Regs::s1, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, 756);
	program.ExpectRegisterValue(Regs::s2, 0);
	program.ExpectRegisterValue(Regs::s3, -24);
	program.AddInstruction(Create_div(Regs::s2, Regs::a0, Regs::a1));
	program.AddInstruction(Create_div(Regs::s3, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, -756);
	program.ExpectRegisterValue(Regs::s4, 0);
	program.ExpectRegisterValue(Regs::s5, 24);
	program.AddInstruction(Create_div(Regs::s4, Regs::a0, Regs::a1));
	program.AddInstruction(Create_div(Regs::s5, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -32331);
	program.SetRegister(Regs::a1, -712356);
	program.ExpectRegisterValue(Regs::s6, 0);
	program.ExpectRegisterValue(Regs::s7, 22);
	program.AddInstruction(Create_div(Regs::s6, Regs::a0, Regs::a1));
	program.AddInstruction(Create_div(Regs::s7, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, 21351321);
	program.SetRegister(Regs::a1, -92364243);
	program.ExpectRegisterValue(Regs::s8, 0);
	program.ExpectRegisterValue(Regs::s9, -4);
	program.AddInstruction(Create_div(Regs::s8, Regs::a0, Regs::a1));
	program.AddInstruction(Create_div(Regs::s9, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, 10);
	program.SetRegister(Regs::a1, 0);
	program.ExpectRegisterValue(Regs::s10, -1);
	program.ExpectRegisterValue(Regs::s11, 0);
	program.AddInstruction(Create_div(Regs::s10, Regs::a0, Regs::a1));
	program.AddInstruction(Create_div(Regs::s11, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, INT32_MIN);
	program.SetRegister(Regs::a1, -1);
	program.ExpectRegisterValue(Regs::a2, INT32_MIN);
	program.ExpectRegisterValue(Regs::a3, 0);
	program.AddInstruction(Create_div(Regs::a2, Regs::a0, Regs::a1));
	program.AddInstruction(Create_div(Regs::a3, Regs::a1, Regs::a0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_div");

	Success("test_div");
}
static void Test_divu()
{
	RISCV_Program program("Test_divu");

	program.SetRegister(Regs::a0, 12);
	program.SetRegister(Regs::a1, 27);
	program.ExpectRegisterValue(Regs::s0, 0);
	program.ExpectRegisterValue(Regs::s1, 2);
	program.AddInstruction(Create_divu(Regs::s0, Regs::a0, Regs::a1));
	program.AddInstruction(Create_divu(Regs::s1, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, 756);
	program.ExpectRegisterValue(Regs::s2, 5681173);
	program.ExpectRegisterValue(Regs::s3, 0);
	program.AddInstruction(Create_divu(Regs::s2, Regs::a0, Regs::a1));
	program.AddInstruction(Create_divu(Regs::s3, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, -756);
	program.ExpectRegisterValue(Regs::s4, 1);
	program.ExpectRegisterValue(Regs::s5, 0);
	program.AddInstruction(Create_divu(Regs::s4, Regs::a0, Regs::a1));
	program.AddInstruction(Create_divu(Regs::s5, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -32331);
	program.SetRegister(Regs::a1, -712356);
	program.ExpectRegisterValue(Regs::s6, 1);
	program.ExpectRegisterValue(Regs::s7, 0);
	program.AddInstruction(Create_divu(Regs::s6, Regs::a0, Regs::a1));
	program.AddInstruction(Create_divu(Regs::s7, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, 21351321);
	program.SetRegister(Regs::a1, -92364243);
	program.ExpectRegisterValue(Regs::s8, 0);
	program.ExpectRegisterValue(Regs::s9, 196);
	program.AddInstruction(Create_divu(Regs::s8, Regs::a0, Regs::a1));
	program.AddInstruction(Create_divu(Regs::s9, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, 10);
	program.SetRegister(Regs::a1, 0);
	program.ExpectRegisterValue(Regs::s10, 10);
	program.ExpectRegisterValue(Regs::s11, 0);
	program.AddInstruction(Create_divu(Regs::s10, Regs::a0, Regs::a1));
	program.AddInstruction(Create_divu(Regs::s11, Regs::a1, Regs::a0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_divu");

	Success("test_divu");
}
static void Test_rem()
{
	RISCV_Program program("Test_rem");

	program.SetRegister(Regs::a0, 12);
	program.SetRegister(Regs::a1, 27);
	program.ExpectRegisterValue(Regs::s0, 12);
	program.ExpectRegisterValue(Regs::s1, 3);
	program.AddInstruction(Create_rem(Regs::s0, Regs::a0, Regs::a1));
	program.AddInstruction(Create_rem(Regs::s1, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, 756);
	program.ExpectRegisterValue(Regs::s2, -31);
	program.ExpectRegisterValue(Regs::s3, 12);
	program.AddInstruction(Create_rem(Regs::s2, Regs::a0, Regs::a1));
	program.AddInstruction(Create_rem(Regs::s3, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, -756);
	program.ExpectRegisterValue(Regs::s4, -31);
	program.ExpectRegisterValue(Regs::s5, -12);
	program.AddInstruction(Create_rem(Regs::s4, Regs::a0, Regs::a1));
	program.AddInstruction(Create_rem(Regs::s5, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -32331);
	program.SetRegister(Regs::a1, -712356);
	program.ExpectRegisterValue(Regs::s6, -32331);
	program.ExpectRegisterValue(Regs::s7, -1074);
	program.AddInstruction(Create_rem(Regs::s6, Regs::a0, Regs::a1));
	program.AddInstruction(Create_rem(Regs::s7, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, 21351321);
	program.SetRegister(Regs::a1, -92364243);
	program.ExpectRegisterValue(Regs::s8, 21351321);
	program.ExpectRegisterValue(Regs::s9, -6958959);
	program.AddInstruction(Create_rem(Regs::s8, Regs::a0, Regs::a1));
	program.AddInstruction(Create_rem(Regs::s9, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, 10);
	program.SetRegister(Regs::a1, 0);
	program.ExpectRegisterValue(Regs::s10, 10);
	program.ExpectRegisterValue(Regs::s11, 0);
	program.AddInstruction(Create_rem(Regs::s10, Regs::a0, Regs::a1));
	program.AddInstruction(Create_rem(Regs::s11, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, INT32_MIN);
	program.SetRegister(Regs::a1, -1);
	program.ExpectRegisterValue(Regs::a2, 0);
	program.ExpectRegisterValue(Regs::a3, -1);
	program.AddInstruction(Create_rem(Regs::a2, Regs::a0, Regs::a1));
	program.AddInstruction(Create_rem(Regs::a3, Regs::a1, Regs::a0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_rem");

	Success("test_rem");
}
static void Test_remu()
{
	RISCV_Program program("Test_remu");

	program.SetRegister(Regs::a0, 12);
	program.SetRegister(Regs::a1, 27);
	program.ExpectRegisterValue(Regs::s0, 12);
	program.ExpectRegisterValue(Regs::s1, 3);
	program.AddInstruction(Create_remu(Regs::s0, Regs::a0, Regs::a1));
	program.AddInstruction(Create_remu(Regs::s1, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, 756);
	program.ExpectRegisterValue(Regs::s2, 477);
	program.ExpectRegisterValue(Regs::s3, 756);
	program.AddInstruction(Create_remu(Regs::s2, Regs::a0, Regs::a1));
	program.AddInstruction(Create_remu(Regs::s3, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -31);
	program.SetRegister(Regs::a1, -756);
	program.ExpectRegisterValue(Regs::s4, 725);
	program.ExpectRegisterValue(Regs::s5, -756);
	program.AddInstruction(Create_remu(Regs::s4, Regs::a0, Regs::a1));
	program.AddInstruction(Create_remu(Regs::s5, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, -32331);
	program.SetRegister(Regs::a1, -712356);
	program.ExpectRegisterValue(Regs::s6, 680025);
	program.ExpectRegisterValue(Regs::s7, -712356);
	program.AddInstruction(Create_remu(Regs::s6, Regs::a0, Regs::a1));
	program.AddInstruction(Create_remu(Regs::s7, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, 21351321);
	program.SetRegister(Regs::a1, -92364243);
	program.ExpectRegisterValue(Regs::s8, 21351321);
	program.ExpectRegisterValue(Regs::s9, 17744137);
	program.AddInstruction(Create_remu(Regs::s8, Regs::a0, Regs::a1));
	program.AddInstruction(Create_remu(Regs::s9, Regs::a1, Regs::a0));

	program.SetRegister(Regs::a0, 10);
	program.SetRegister(Regs::a1, 0);
	program.ExpectRegisterValue(Regs::s10, 10);
	program.ExpectRegisterValue(Regs::s11, 0);
	program.AddInstruction(Create_remu(Regs::s10, Regs::a0, Regs::a1));
	program.AddInstruction(Create_remu(Regs::s11, Regs::a1, Regs::a0));

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_remu");

	Success("test_remu");
}
static void Test_li()
{
	RISCV_Program program("Test_li");

	program.AddInstruction(Create_li(Regs::s0, 0xff'ff'ff'ff));
	program.ExpectRegisterValue(     Regs::s0, 0xff'ff'ff'ff);

	program.AddInstruction(Create_li(Regs::s1, 29'154'821));
	program.ExpectRegisterValue(     Regs::s1, 29'154'821);

	program.AddInstruction(Create_li(Regs::s2, 2'993'781'092));
	program.ExpectRegisterValue(     Regs::s2, 2'993'781'092);

	program.AddInstruction(Create_li(Regs::s3, -12));
	program.ExpectRegisterValue(     Regs::s3, -12);

	program.AddInstruction(Create_li(Regs::s4, -1'125'213'234));
	program.ExpectRegisterValue(     Regs::s4, -1'125'213'234);

	program.AddInstruction(Create_li(Regs::s5, 0xff'00'00'00));
	program.ExpectRegisterValue(     Regs::s5, 0xff'00'00'00);

	program.SetRegister(Regs::s6, 10);
	program.AddInstruction(Create_li(Regs::s6, 0));
	program.ExpectRegisterValue(     Regs::s6, 0);

	program.EndProgram();
	TestProgram(program, "InstructionTests/test_li");

	Success("test_li");
}

void TestAllInstructions()
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
		Test_li();
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Failed to finish all instruction tests" << std::endl;
		std::cout << e.what() << std::endl;
		return;
	}

	std::cout << "Successfully finished all instruction tests\n" << std::endl;
}