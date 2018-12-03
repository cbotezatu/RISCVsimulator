#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include "Instruction.h"

Instruction DecodeInstruction(const uint32_t rawInstruction);
std::unique_ptr<std::vector<Instruction>> DecodeInstructions(const uint32_t* rawInstructions, const size_t instructionsCount);
std::string GetProgramAsString(const uint32_t* rawInstructions, const size_t instructionCount);