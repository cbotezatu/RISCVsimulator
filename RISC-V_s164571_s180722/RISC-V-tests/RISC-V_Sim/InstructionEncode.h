#pragma once

#include <cstdint>
#include "Register.h"

struct MultiInstruction
{
	uint32_t instruction1;
	uint32_t instruction2;
};

uint32_t Create_lb(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_lh(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_lw(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_lbu(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_lhu(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_fence();
uint32_t Create_fence_i();
uint32_t Create_addi(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_slli(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_slti(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_sltiu(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_xori(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_srli(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_srai(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_ori(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_andi(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_auipc(const Regs rd, const uint32_t immediate);
uint32_t Create_sb(const Regs rs1, const Regs rs2, const uint32_t immediate);
uint32_t Create_sh(const Regs rs1, const Regs rs2, const uint32_t immediate);
uint32_t Create_sw(const Regs rs1, const Regs rs2, const uint32_t immediate);
uint32_t Create_add(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_sub(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_sll(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_slt(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_sltu(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_xor(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_srl(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_sra(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_or(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_and(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_lui(const Regs rd, const uint32_t immediate);
uint32_t Create_beq(const Regs rs1, const Regs rs2, const uint32_t immediate);
uint32_t Create_bne(const Regs rs1, const Regs rs2, const uint32_t immediate);
uint32_t Create_blt(const Regs rs1, const Regs rs2, const uint32_t immediate);
uint32_t Create_bge(const Regs rs1, const Regs rs2, const uint32_t immediate);
uint32_t Create_bltu(const Regs rs1, const Regs rs2, const uint32_t immediate);
uint32_t Create_bgeu(const Regs rs1, const Regs rs2, const uint32_t immediate);
uint32_t Create_jalr(const Regs rd, const Regs rs1, const uint32_t immediate);
uint32_t Create_jal(const Regs rd, const uint32_t immediate);
uint32_t Create_ecall();
uint32_t Create_ebreak();
uint32_t Create_csrrw();
uint32_t Create_csrrs();
uint32_t Create_csrrc();
uint32_t Create_csrrwi();
uint32_t Create_csrrsi();
uint32_t Create_csrrci();
uint32_t Create_mul(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_mulh(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_mulhsu(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_mulhu(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_div(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_divu(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_rem(const Regs rd, const Regs rs1, const Regs rs2);
uint32_t Create_remu(const Regs rd, const Regs rs1, const Regs rs2);
MultiInstruction Create_li(const Regs rd, const uint32_t immediate);
