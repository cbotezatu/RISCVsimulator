#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include "RISCV_Program.h"

std::unique_ptr<RISCV_Program> LoadProgram(const std::string& filePath);