#include "TestRandomInstructions.h"
#include <cstdint>
#include <array>
#include <memory>
#include <string>
#include "InstructionType.h"
#include "Register.h"
#include "TSrandom.h"
#include "InstructionEncode.h"
#include "RISCV_Program.h"

static const std::array<InstructionType, 29> ArithmeticInstructions = 
{
	InstructionType::addi,
	InstructionType::slli,
	InstructionType::slti,
	InstructionType::sltiu,
	InstructionType::xori,
	InstructionType::srli,
	InstructionType::srai,
	InstructionType::ori,
	InstructionType::andi,
	InstructionType::auipc,
	InstructionType::add,
	InstructionType::sub,
	InstructionType::sll,
	InstructionType::slt,
	InstructionType::sltu,
	InstructionType::xor_,
	InstructionType::srl,
	InstructionType::sra,
	InstructionType::or_,
	InstructionType::and_,
	InstructionType::lui,
	InstructionType::mul,
	InstructionType::mulh,
	InstructionType::mulhsu,
	InstructionType::mulhu,
	InstructionType::div,
	InstructionType::divu,
	InstructionType::rem,
	InstructionType::remu
};

static Regs GetRandomRegister(FRandom::TCRandom& random)
{
	int32_t randomNumber;
	do
	{
		randomNumber = FRandom::RandomRange(random, 0, 32);
	} while (randomNumber == static_cast<int32_t>(Regs::sp));

	return static_cast<Regs>(randomNumber);
}

static uint32_t RandomizeInstruction(const InstructionType type, FRandom::TCRandom& random)
{
	const Regs rs1 = GetRandomRegister(random);
	const Regs rs2 = GetRandomRegister(random);
	const Regs rs3 = GetRandomRegister(random);
	const uint32_t immediate5Bits  = FRandom::RandomRange(random, 0, 31);
	const uint32_t immediate12Bits = FRandom::RandomRange(random, -2048, 4095);
	const uint32_t immediate20Bits = FRandom::RandomRange(random, 0, 1048575);

	switch (type)
	{
		case InstructionType::lb:
			return Create_lb(rs1, rs2, immediate12Bits);
		case InstructionType::lh:
			return Create_lh(rs1, rs2, immediate12Bits);
		case InstructionType::lw:
			return Create_lw(rs1, rs2, immediate12Bits);
		case InstructionType::lbu:
			return Create_lbu(rs1, rs2, immediate12Bits);
		case InstructionType::lhu:
			return Create_lhu(rs1, rs2, immediate12Bits);
		case InstructionType::fence:
			return Create_fence();
		case InstructionType::fence_i:
			return Create_fence_i();
		case InstructionType::addi:
			return Create_addi(rs1, rs2, immediate12Bits);
		case InstructionType::slli:
			return Create_slli(rs1, rs2, immediate5Bits);
		case InstructionType::slti:
			return Create_slti(rs1, rs2, immediate12Bits);
		case InstructionType::sltiu:
			return Create_sltiu(rs1, rs2, immediate12Bits);
		case InstructionType::xori:
			return Create_xori(rs1, rs2, immediate12Bits);
		case InstructionType::srli:
			return Create_srli(rs1, rs2, immediate5Bits);
		case InstructionType::srai:
			return Create_srai(rs1, rs2, immediate5Bits);
		case InstructionType::ori:
			return Create_ori(rs1, rs2, immediate12Bits);
		case InstructionType::andi:
			return Create_andi(rs1, rs2, immediate12Bits);
		case InstructionType::auipc:
			return Create_auipc(rs1, immediate20Bits);
		case InstructionType::sb:
			return Create_sb(rs1, rs2, immediate12Bits);
		case InstructionType::sh:
			return Create_sh(rs1, rs2, immediate12Bits);
		case InstructionType::sw:
			return Create_sw(rs1, rs2, immediate12Bits);
		case InstructionType::add:
			return Create_add(rs1, rs2, rs3);
		case InstructionType::sub:
			return Create_sub(rs1, rs2, rs3);
		case InstructionType::sll:
			return Create_sll(rs1, rs2, rs3);
		case InstructionType::slt:
			return Create_slt(rs1, rs2, rs3);
		case InstructionType::sltu:
			return Create_sltu(rs1, rs2, rs3);
		case InstructionType::xor_:
			return Create_xor(rs1, rs2, rs3);
		case InstructionType::srl:
			return Create_srl(rs1, rs2, rs3);
		case InstructionType::sra:
			return Create_sra(rs1, rs2, rs3);
		case InstructionType::or_:
			return Create_or(rs1, rs2, rs3);
		case InstructionType::and_:
			return Create_and(rs1, rs2, rs3);
		case InstructionType::lui:
			return Create_lui(rs1, immediate20Bits);
		case InstructionType::beq:
			return Create_beq(rs1, rs2, immediate12Bits);
		case InstructionType::bne:
			return Create_bne(rs1, rs2, immediate12Bits);
		case InstructionType::blt:
			return Create_blt(rs1, rs2, immediate12Bits);
		case InstructionType::bge:
			return Create_bge(rs1, rs2, immediate12Bits);
		case InstructionType::bltu:
			return Create_bltu(rs1, rs2, immediate12Bits);
		case InstructionType::bgeu:
			return Create_bgeu(rs1, rs2, immediate12Bits);
		case InstructionType::jalr:
			return Create_jalr(rs1, rs2, immediate12Bits);
		case InstructionType::jal:
			return Create_jal(rs1, immediate20Bits);
		case InstructionType::ecall:
			return Create_ecall();
		case InstructionType::ebreak:
			return Create_ebreak();
		case InstructionType::csrrw:
			return Create_csrrw();
		case InstructionType::csrrs:
			return Create_csrrs();
		case InstructionType::csrrc:
			return Create_csrrc();
		case InstructionType::csrrwi:
			return Create_csrrwi();
		case InstructionType::csrrsi:
			return Create_csrrsi();
		case InstructionType::csrrci:
			return Create_csrrci();
		case InstructionType::mul:
			return Create_mul(rs1, rs2, rs3);
		case InstructionType::mulh:
			return Create_mulh(rs1, rs2, rs3);
		case InstructionType::mulhsu:
			return Create_mulhsu(rs1, rs2, rs3);
		case InstructionType::mulhu:
			return Create_mulhu(rs1, rs2, rs3);
		case InstructionType::div:
			return Create_div(rs1, rs2, rs3);
		case InstructionType::divu:
			return Create_divu(rs1, rs2, rs3);
		case InstructionType::rem:
			return Create_rem(rs1, rs2, rs3);
		case InstructionType::remu:
			return Create_remu(rs1, rs2, rs3);
		default:
			throw std::runtime_error("Invalid instruction type");
	}
}

template<uint32_t ArraySize>
static std::unique_ptr<RISCV_Program> CreateRandomProgram(const std::array<InstructionType, ArraySize>& instructionTypes, size_t size)
{
	auto program = std::make_unique<RISCV_Program>("Program size: " + std::to_string(size));
	FRandom::TCRandom random = FRandom::GetTCRandom();

	for (uint32_t i = 0; i < 32; i++)
	{
		program->SetRegister(static_cast<Regs>(i), i);
	}

	for (size_t i = 0; i < size; i++)
	{
		const uint32_t index = FRandom::RandomRange(random, 0, static_cast<uint32_t>(instructionTypes.size()) - 1);
		const InstructionType type = instructionTypes[index];
		const uint32_t rawInstruction = RandomizeInstruction(type, random);

		program->AddInstruction(rawInstruction);
	}
	program->EndProgram();

	return program;
}

template<uint32_t ArraySize>
void CreateAndSaveTest(const std::array<InstructionType, ArraySize>& instructionTypes, const size_t size, const std::string& filepath)
{
	auto program = CreateRandomProgram<ArraySize>(instructionTypes, size);
	program->Run();
	program->ActualToExpectedRegisters();
	program->Save(filepath);
}

void TestRandomArithmeticInstructions()
{
	CreateAndSaveTest<29>(ArithmeticInstructions, 10, "InstructionTests/test_random1");
	CreateAndSaveTest<29>(ArithmeticInstructions, 10, "InstructionTests/test_random2");
	CreateAndSaveTest<29>(ArithmeticInstructions, 10, "InstructionTests/test_random3");
	CreateAndSaveTest<29>(ArithmeticInstructions, 10, "InstructionTests/test_random4");
	CreateAndSaveTest<29>(ArithmeticInstructions, 10, "InstructionTests/test_random5");

	CreateAndSaveTest<29>(ArithmeticInstructions, 100, "InstructionTests/test_random6");
	CreateAndSaveTest<29>(ArithmeticInstructions, 100, "InstructionTests/test_random7");
	CreateAndSaveTest<29>(ArithmeticInstructions, 100, "InstructionTests/test_random8");

	CreateAndSaveTest<29>(ArithmeticInstructions, 10000, "InstructionTests/test_random9");
	CreateAndSaveTest<29>(ArithmeticInstructions, 10000, "InstructionTests/test_random10");
}