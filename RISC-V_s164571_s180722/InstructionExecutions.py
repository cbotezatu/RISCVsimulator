# Executing instructions
# RECASTING IS KEEPING THE BINARY REPRESENTATION OF THE NUMBER UNTOUCHED -> LETTING US DEAL WITH THE SIGNED AND
# UNSIGNED REPRESENTATION OF CERTAIN NUMBERS.
import numpy as np
from HelperFunctions import *

# ADD
def exec_add(decodedInstruction, state):
    state["registerArray"][decodedInstruction["rd"]] = state["registerArray"][decodedInstruction["rs1"]] + \
                                                       state["registerArray"][decodedInstruction["rs2"]]


# LUI
def exec_lui(decodedInstruction, state):
    state["registerArray"][decodedInstruction["rd"]] = np.int32(decodedInstruction["immediate_ext"] << 12)


# ADDI
def exec_addi(decodedInstruction, state):
    state["registerArray"][decodedInstruction["rd"]] = state["registerArray"][decodedInstruction["rs1"]] + \
                                                       decodedInstruction['immediate_ext']


# ECALL
def exec_ecall(decodedInstruction, state):
    if state["registerArray"][10] == 1:
        print(state["registerArray"][11])
    elif state["registerArray"][10] == 4:
        print("Print something")
    elif state["registerArray"][10] == 9:
        print("Allocate memory")
    elif state["registerArray"][10] == 10:
        state["hardwareErrorLev"] = 2
    elif state["registerArray"][10] == 11:
        print(chr(state["registerArray"][11]))
    elif state["registerArray"][10] == 17:
        state["hardwareErrorLev"] = 3


# NOP
def exec_nop(decodedInstruction, state):
    pass


# AUIPC
def exec_auipc(decodedInstruction, state):
    state["registerArray"][decodedInstruction["rd"]] = state["PC"] + (decodedInstruction["immediate_ext"] << 12)


# JAL
def exec_jal(decodedInstruction, state):
    state["registerArray"][decodedInstruction["rd"]] = state["PC"] + 4
    state["PC"] = state["PC"] + 2 * decodedInstruction['immediate_ext']


# JALR
def exec_jalr(decodedInstruction, state):
    state["registerArray"][decodedInstruction["rd"]] = state["PC"] + 4
    state["PC"] = bitmask(1, 31) & \
                  (state["registerArray"][decodedInstruction["rs1"]] + decodedInstruction['immediate_ext'])


# BEQ
def exec_beq(decodedInstruction, state):
    if state["registerArray"][decodedInstruction["rs1"]] == state["registerArray"][decodedInstruction["rs2"]]:
        state["PC"] = state["PC"] + decodedInstruction['immediate_ext']
    else:
        state["PC"] += 4


# BNE
def exec_bne(decodedInstruction, state):
    if state["registerArray"][decodedInstruction["rs1"]] != state["registerArray"][decodedInstruction["rs2"]]:
        state["PC"] = state["PC"] + decodedInstruction['immediate_ext']
    else:
        state["PC"] += 4


# BLT
def exec_blt(decodedInstruction, state):
    if state["registerArray"][decodedInstruction["rs1"]] < state["registerArray"][decodedInstruction["rs2"]]:
        state["PC"] = state["PC"] + decodedInstruction['immediate_ext']
    else:
        state["PC"] += 4


# BGE
def exec_bge(decodedInstruction, state):
    if state["registerArray"][decodedInstruction["rs1"]] >= state["registerArray"][decodedInstruction["rs2"]]:
        state["PC"] = state["PC"] + decodedInstruction['immediate_ext']
    else:
        state["PC"] += 4


# BLTU
def exec_bltu(decodedInstruction, state):
    if np.uint32(state["registerArray"][decodedInstruction["rs1"]]) < np.uint32(
            state["registerArray"][decodedInstruction["rs2"]]):
        state["PC"] = state["PC"] + decodedInstruction['immediate_ext']
    else:
        state["PC"] += 4


# BGEU
def exec_bgeu(decodedInstruction, state):
    if np.uint32(state["registerArray"][decodedInstruction["rs1"]]) >= \
            np.uint32(state["registerArray"][decodedInstruction["rs2"]]):
        state["PC"] = state["PC"] + decodedInstruction['immediate_ext']
    else:
        state["PC"] += 4


# LB
def exec_lb(decodedInstruction, state):
    a = decodedInstruction['immediate_ext'] + state["registerArray"][decodedInstruction["rs1"]]
    if a < 0 or a > state["memorySize"]:
        state["hardwareErrorLev"] = 5
    else:
        state["registerArray"][decodedInstruction["rd"]] = sign_extender(state["memoryArray"][a], 8)


# LH
def exec_lh(decodedInstruction, state):
    a = decodedInstruction['immediate_ext'] + state["registerArray"][decodedInstruction["rs1"]]
    if a < 0 or a > state["memorySize"] - 1:
        state["hardwareErrorLev"] = 5
    else:
        state["registerArray"][decodedInstruction["rd"]] = \
            sign_extender(state["memoryArray"][a] + (state["memoryArray"][a + 1] << 8), 16)


# LW
def exec_lw(decodedInstruction, state):
    a = decodedInstruction['immediate_ext'] + state["registerArray"][decodedInstruction["rs1"]]
    if a < 0 or a > state["memorySize"] - 3:
        state["hardwareErrorLev"] = 5
    else:
        state["registerArray"][decodedInstruction["rd"]] = \
            state["memoryArray"][a] + \
            (state["memoryArray"][a + 1] << 8) + \
            (state["memoryArray"][a + 2] << 16) + \
            (state["memoryArray"][a + 3] << 24)


# LBU
def exec_lbu(decodedInstruction, state):
    a = decodedInstruction['immediate_ext'] + state["registerArray"][decodedInstruction["rs1"]]
    if a < 0 or a > state["memorySize"]:
        state["hardwareErrorLev"] = 5
    else:
        state["registerArray"][decodedInstruction["rd"]] = np.uint32(state["memoryArray"][a])


# LHU
def exec_lhu(decodedInstruction, state):
    a = decodedInstruction['immediate_ext'] + state["registerArray"][decodedInstruction["rs1"]]
    if a < 0 or a > state["memorySize"] - 1:
        state["hardwareErrorLev"] = 5
    else:
        state["registerArray"][decodedInstruction["rd"]] = state["memoryArray"][a] + (state["memoryArray"][a + 1] << 8)


# SB
def exec_sb(decodedInstruction, state):
    a = decodedInstruction['immediate_ext'] + state["registerArray"][decodedInstruction["rs1"]]
    if a < 0 or a > state["memorySize"]:
        state["hardwareErrorLev"] = 5
    else:
        state["memoryArray"][a] = bits_slice(state["registerArray"][decodedInstruction["rs2"]], 0, 7)


# SH
def exec_sh(decodedInstruction, state):
    a = decodedInstruction['immediate_ext'] + state["registerArray"][decodedInstruction["rs1"]]
    if a < 0 or a > state["memorySize"] - 1:
        state["hardwareErrorLev"] = 5
    else:
        state["memoryArray"][a] = bits_slice(state["registerArray"][decodedInstruction["rs2"]], 0, 7)
        state["memoryArray"][a + 1] = bits_slice(state["registerArray"][decodedInstruction["rs2"]], 8, 15)


# SW
def exec_sw(decodedInstruction, state):
    a = decodedInstruction['immediate_ext'] + state["registerArray"][decodedInstruction["rs1"]]
    if a < 0 or a > state["memorySize"] - 3:
        state["hardwareErrorLev"] = 5
    else:
        state["memoryArray"][a] = bits_slice(state["registerArray"][decodedInstruction["rs2"]], 0, 7)
        state["memoryArray"][a + 1] = bits_slice(state["registerArray"][decodedInstruction["rs2"]], 8, 15)
        state["memoryArray"][a + 2] = bits_slice(state["registerArray"][decodedInstruction["rs2"]], 16, 23)
        state["memoryArray"][a + 3] = bits_slice(state["registerArray"][decodedInstruction["rs2"]], 24, 31)


# SLLI
def exec_slli(decodedInstruction, state):
    a = bits_slice(decodedInstruction["immediate"], 0, 4)
    # recast the left-shifted register as int32. This is done, because python allows for the left-shifting to
    # exceed the 32. The recasting, truncate the upper bits, so that the value fits into the 32 bits.
    state["registerArray"][decodedInstruction["rd"]] = np.int32(state["registerArray"][decodedInstruction["rs1"]] << a)


# SRLI
def exec_srli(decodedInstruction, state):
    a = bits_slice(decodedInstruction["immediate"], 0, 4)
    state["registerArray"][decodedInstruction["rd"]] = \
        np.int32(np.uint32(state["registerArray"][decodedInstruction["rs1"]]) >> a)



# SRAI
def exec_srai(decodedInstruction, state):
    a = bits_slice(decodedInstruction["immediate"], 0, 4)
    state["registerArray"][decodedInstruction["rd"]] = np.int32(state["registerArray"][decodedInstruction["rs1"]] >> a)


# SLTI
def exec_slti(decodedInstruction, state):
    if state["registerArray"][decodedInstruction["rs1"]] < decodedInstruction['immediate_ext']:
        state["registerArray"][decodedInstruction["rd"]] = 1
    else:
        state["registerArray"][decodedInstruction["rd"]] = 0


# SLTIU
def exec_sltiu(decodedInstruction, state):
    if np.uint32(state["registerArray"][decodedInstruction["rs1"]]) < np.uint32(decodedInstruction['immediate_ext']):
        state["registerArray"][decodedInstruction["rd"]] = 1
    else:
        state["registerArray"][decodedInstruction["rd"]] = 0


# XORI
def exec_xori(decodedInstruction, state):
    state["registerArray"][decodedInstruction["rd"]] = \
        np.bitwise_xor(decodedInstruction['immediate_ext'], state["registerArray"][decodedInstruction["rs1"]])


# ORI
def exec_ori(decodedInstruction, state):
    state["registerArray"][decodedInstruction["rd"]] = \
        np.bitwise_or(decodedInstruction['immediate_ext'], state["registerArray"][decodedInstruction["rs1"]])


# ANDI
def exec_andi(decodedInstruction, state):
    state["registerArray"][decodedInstruction["rd"]] = \
        np.bitwise_and(decodedInstruction['immediate_ext'], state["registerArray"][decodedInstruction["rs1"]])


# SUB
def exec_sub(decodedInstruction, state):
     state["registerArray"][decodedInstruction["rd"]] = state["registerArray"][decodedInstruction["rs1"]] - \
                                                       state["registerArray"][decodedInstruction["rs2"]]


# SLL
def exec_sll(decodedInstruction, state):
    a = bits_slice(state["registerArray"][decodedInstruction["rs2"]], 0, 5)
    # recast the left-shifted register as int32. This is done, because python allows for the left-shifting to
    # exceed the 32. The recasting, truncate the upper bits, so that the value fits into the 32 bits.
    state["registerArray"][decodedInstruction["rd"]] = np.int32(state["registerArray"][decodedInstruction["rs1"]] << a)


# SLT
def exec_slt(decodedInstruction, state):
    if state["registerArray"][decodedInstruction["rs1"]] < state["registerArray"][decodedInstruction["rs2"]]:
        state["registerArray"][decodedInstruction["rd"]] = 1
    else:
        state["registerArray"][decodedInstruction["rd"]] = 0


# SLTU
def exec_sltu(decodedInstruction, state):
    if np.uint32(state["registerArray"][decodedInstruction["rs1"]]) < \
            np.uint32 (state["registerArray"][decodedInstruction["rs2"]]):
        state["registerArray"][decodedInstruction["rd"]] = 1
    else:
        state["registerArray"][decodedInstruction["rd"]] = 0


# XOR
def exec_xor(decodedInstruction, state):
    state["registerArray"][decodedInstruction["rd"]] = \
        np.bitwise_xor(state["registerArray"][decodedInstruction["rs1"]],
                       state["registerArray"][decodedInstruction["rs2"]])

# SRL
def exec_srl(decodedInstruction, state):
    a = bits_slice(state["registerArray"][decodedInstruction["rs2"]], 0, 5)
    state["registerArray"][decodedInstruction["rd"]] = \
        np.int32(np.uint32(state["registerArray"][decodedInstruction["rs1"]]) >> a)


# SRA
def exec_sra(decodedInstruction, state):
    a = bits_slice(state["registerArray"][decodedInstruction["rs2"]], 0, 5)
    state["registerArray"][decodedInstruction["rd"]] = (state["registerArray"][decodedInstruction["rs1"]] >> a)


# OR
def exec_or(decodedInstruction, state):
     state["registerArray"][decodedInstruction["rd"]] = \
        np.bitwise_or(state["registerArray"][decodedInstruction["rs2"]],
                      state["registerArray"][decodedInstruction["rs1"]])


# AND
def exec_and(decodedInstruction, state):
    state["registerArray"][decodedInstruction["rd"]] = \
     np.bitwise_and(state["registerArray"][decodedInstruction["rs2"]],
                    state["registerArray"][decodedInstruction["rs1"]])
