#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Nov  4 10:41:55 2018

@author: BotezatuCristian
"""

# Importing the needed libraries
import numpy as np
import pprint
from HelperFunctions import *
from InstructionExecutions import *
import sys

np.seterr(over='ignore', under='ignore')

def RunFile(filename):
    file = np.fromfile(filename, dtype=np.byte)
    LogFileName = filename.split('.')[:-1][0] + ".log"
    logfile = open(LogFileName, "w")

    # The correct setting for running code in the venus simulator
    memorySize = 0x80000000
    
    # Initializing the memoryArray, the registerArray and the PC (program counter)
    state = {
            "memorySize": memorySize,
            "memoryArray": np.zeros(memorySize, dtype=np.uint8),
            "registerArray": np.zeros(32, dtype=np.int32),
            "PC": np.int32(0),
            "hardwareErrorLev": np.int32(0)
            }
    
    # The correct setting for the other simulator
    # state["registerArray"][2] = 0x100000
    
    
    # Reading the file into memory
    for num, byte in enumerate(file):
        state["memoryArray"][num] = byte

    # Defining the instruction set (instructions have different components as part of the it and, thus, the size
    # differs in terms of number of bits. For example: LUI is encoded by 0b0110111 (it is of a U-type and has
    # only the opcode (7 bits))))
    instr_dict = {
        ("o", 0b0110111): {"instr": "LUI", "instr_type": "U", "execution": exec_lui},
        ("o", 0b0010111): {"instr": "AUIPC", "instr_type": "U", "execution": exec_auipc},
        ("o", 0b1101111): {"instr": "JAL", "instr_type": "UJ", "execution": exec_jal},
        ("o3", 0b0001100111): {"instr": "JALR", "instr_type": "I", "execution": exec_jalr},
        ("o3", 0b0001100011): {"instr": "BEQ", "instr_type": "SB", "execution": exec_beq},
        ("o3", 0b0011100011): {"instr": "BNE", "instr_type": "SB", "execution": exec_bne},
        ("o3", 0b1001100011): {"instr": "BLT", "instr_type": "SB", "execution": exec_blt},
        ("o3", 0b1011100011): {"instr": "BGE", "instr_type": "SB", "execution": exec_bge},
        ("o3", 0b1101100011): {"instr": "BLTU", "instr_type": "SB", "execution": exec_bltu},
        ("o3", 0b1111100011): {"instr": "BGEU", "instr_type": "SB", "execution": exec_bgeu},
        ("o3", 0b0000000011): {"instr": "LB", "instr_type": "I", "execution": exec_lb},
        ("o3", 0b0010000011): {"instr": "LH", "instr_type": "I", "execution": exec_lh},
        ("o3", 0b0100000011): {"instr": "LW", "instr_type": "I", "execution": exec_lw},
        ("o3", 0b1000000011): {"instr": "LBU", "instr_type": "I", "execution": exec_lbu},
        ("o3", 0b1010000011): {"instr": "LHU", "instr_type": "I", "execution": exec_lhu},
        ("o3", 0b0000100011): {"instr": "SB", "instr_type": "S", "execution": exec_sb},
        ("o3", 0b0010100011): {"instr": "SH", "instr_type": "S", "execution": exec_sh},
        ("o3", 0b0100100011): {"instr": "SW", "instr_type": "S", "execution": exec_sw},
        ("o3", 0b0000010011): {"instr": "ADDI", "instr_type": "I", "execution": exec_addi},
        ("o3", 0b0100010011): {"instr": "SLTI", "instr_type": "I", "execution": exec_slti},
        ("o3", 0b0110010011): {"instr": "SLTIU", "instr_type": "I", "execution": exec_sltiu},
        ("o3", 0b1000010011): {"instr": "XORI", "instr_type": "I", "execution": exec_xori},
        ("o3", 0b1100010011): {"instr": "ORI", "instr_type": "I", "execution": exec_ori},
        ("o3", 0b1110010011): {"instr": "ANDI", "instr_type": "I", "execution": exec_andi},
        ("o37", 0b00000000010010011): {"instr": "SLLI", "instr_type": "I", "execution": exec_slli},
        ("o37", 0b00000001010010011): {"instr": "SRLI", "instr_type": "I", "execution": exec_srli},
        ("o37", 0b01000001010010011): {"instr": "SRAI", "instr_type": "I", "execution": exec_srai},
        ("o37", 0b00000000000110011): {"instr": "ADD", "instr_type": "R", "execution": exec_add},
        ("o37", 0b01000000000110011): {"instr": "SUB", "instr_type": "R", "execution": exec_sub},
        ("o37", 0b00000000010110011): {"instr": "SLL", "instr_type": "R", "execution": exec_sll},
        ("o37", 0b00000000100110011): {"instr": "SLT", "instr_type": "R", "execution": exec_slt},
        ("o37", 0b00000000110110011): {"instr": "SLTU", "instr_type": "R", "execution": exec_sltu},
        ("o37", 0b00000001000110011): {"instr": "XOR", "instr_type": "R", "execution": exec_xor},
        ("o37", 0b00000001010110011): {"instr": "SRL", "instr_type": "R", "execution": exec_srl},
        ("o37", 0b01000001010110011): {"instr": "SRA", "instr_type": "R", "execution": exec_sra},
        ("o37", 0b00000001100110011): {"instr": "OR", "instr_type": "R", "execution": exec_or},
        ("o37", 0b00000001110110011): {"instr": "AND", "instr_type": "R", "execution": exec_and},
        ("all", 0b00000000000000000001000000001111): {"instr": "FENCE.I", "instr_type":"?"},
        ("all", 0b00000000000000000000000001110011): {"instr": "ECALL"	, "instr_type":"?", "execution": exec_ecall},
        ("all", 0b00000000000100000000000001110011): {"instr": "EBREAK"	, "instr_type":"?"}
        }
        
    # Running through instructions in the memory
    while state["hardwareErrorLev"] == 0:
        pprint.pprint('\n\n################################################################\n', logfile)
        # Fetching the instructions
        instruction = np.uint32(state["memoryArray"][state["PC"]] + 
                                state["memoryArray"][state["PC"]+1]*(2**8) + 
                                state["memoryArray"][state["PC"]+2]*(2**16) + 
                                state["memoryArray"][state["PC"]+3]*(2**24))
        # Slicing out the bits for funct3, funct7 and opcode
        funct3 = bits_slice(instruction, 12, 14)
        funct7 = bits_slice(instruction, 25, 31)
        opcode = bits_slice(instruction, 0, 6)
        # Concatenate all the above components into a well defined instruction
        concatInstructions_all = (funct7 << 10) + (funct3 << 7) + (opcode)
        concatInstr_opcode_funct3 = (funct3 << 7) + (opcode) 
        concatInstr_opcode = opcode


        # Decoding the instructions
        if ("o37", concatInstructions_all) in instr_dict.keys():
            instr_dec = instr_dict[("o37", concatInstructions_all)]
            instruction_key = ("o37", concatInstructions_all)
            
        elif ("o3", concatInstr_opcode_funct3) in instr_dict.keys():
            instr_dec = instr_dict[("o3", concatInstr_opcode_funct3)]
            instruction_key = ("o3", concatInstr_opcode_funct3)
            
        elif ("o", concatInstr_opcode) in instr_dict.keys():
            instr_dec = instr_dict[("o", concatInstr_opcode)]
            instruction_key = ("o", concatInstr_opcode)
            
        elif ("all", instruction) in instr_dict.keys():
            instr_dec = instr_dict[("all", instruction)]
            instruction_key = ("all", instruction)
        else:
            state["hardwareErrorLev"] = 4
            pprint.pprint("instruction: " + hex(instruction), logfile)
            # printing some of the memory to the logfile
            for nr, byte in enumerate(state["memoryArray"][:500]):
                pprint.pprint(str(nr) + ": " + str(hex(byte)), logfile)

            break

        # decodedInstruction contains the values from the 32-bit instruction, necessary for execution, but in decoded format.
        # We have also added some extra values for debugging purposes.
        decodedInstruction = {'instruction_key': instruction_key,
                              'instruction_key_bin': np.binary_repr(instruction_key[1], 32),
                              'instruction': np.binary_repr(instruction, 32),
                              'instruction_hex': hex(instruction),
                              'concatInstructions': np.binary_repr(concatInstructions_all, 32),
                              'instrType': instr_dec["instr_type"], 
                              'instrText': instr_dec["instr"]}
        
        # Adding registers and immediate fields for the decoded instructions
        if instr_dec["instr_type"] in ("R", "I", "U", "UJ"):
            rd = bits_slice(instruction, 7, 11)
            decodedInstruction['rd'] = rd
            
        if instr_dec["instr_type"] in ("R", "I", "S", "SB"):
            rs1 = bits_slice(instruction, 15, 19)
            decodedInstruction['rs1'] = rs1
            decodedInstruction['funct3'] = funct3
            
        if instr_dec["instr_type"] in ("R", "S", "SB"):
            rs2 = bits_slice(instruction, 20, 24)
            decodedInstruction['rs2'] = rs2
            
        if instr_dec["instr_type"] == "R":
            decodedInstruction['funct7'] = funct7
    
        if instr_dec["instr_type"] == "I":
            decodedInstruction['immediate'] = bits_slice(instruction, 20, 31)
            decodedInstruction['immediate_length'] = 12
            decodedInstruction['immediate_bin'] = bin(decodedInstruction['immediate'])
            decodedInstruction['immediate_ext'] = sign_extender(decodedInstruction["immediate"],
                                                                decodedInstruction['immediate_length'])
            
        if instr_dec["instr_type"] == "S":
            decodedInstruction['immediate'] = (bits_slice(instruction, 25, 31) << 5) + bits_slice(instruction, 7, 11)
            decodedInstruction['immediate_length'] = 12
            decodedInstruction['immediate_bin'] = bin(decodedInstruction['immediate'])
            decodedInstruction['immediate_ext'] = sign_extender(decodedInstruction["immediate"],
                                                                decodedInstruction['immediate_length'])
            
        if instr_dec["instr_type"] == "SB" :
            decodedInstruction['immediate'] = (bits_slice(instruction, 8, 11) << 1) \
                + (bits_slice(instruction, 25, 30) << 5) \
                + (bits_slice(instruction, 7, 7) << 11) \
                + (bits_slice(instruction, 31, 31) << 12)
            decodedInstruction['immediate_length'] = 12
            decodedInstruction['immediate_bin'] = bin(decodedInstruction['immediate'])
            decodedInstruction['immediate_ext'] = sign_extender(decodedInstruction["immediate"],
                                                                decodedInstruction['immediate_length'])
    
        if instr_dec["instr_type"] == "U":
            decodedInstruction['immediate'] = np.int32(bits_slice(instruction, 12, 31))
            decodedInstruction['immediate_length'] = 20
            decodedInstruction['immediate_bin'] = bin(decodedInstruction['immediate'])
            decodedInstruction['immediate_ext'] = sign_extender(decodedInstruction["immediate"],
                                                                decodedInstruction['immediate_length'])
    
        if instr_dec["instr_type"] == "UJ":
            decodedInstruction['immediate'] = (bits_slice(instruction, 21, 30)) +\
                                              (bits_slice(instruction, 20, 20) << 10) +\
                                              (bits_slice(instruction, 12, 19) << 11) +\
                                              (bits_slice(instruction, 31, 31) << 19)
            decodedInstruction['immediate_bin'] = bin(decodedInstruction['immediate'])
            decodedInstruction['immediate_length'] = 19
            decodedInstruction['immediate_ext'] = sign_extender(decodedInstruction["immediate"],
                                                                decodedInstruction['immediate_length'])
        if instr_dec["instr"] in ("SLLI", "SRLI", "SRAI"):
            decodedInstruction['immediate'] = bits_slice(decodedInstruction['immediate'], 0, 4)
            decodedInstruction['immediate_length'] = 5
    
        # selecting instruction function to be executed, from instruction dictionary:
        instruction_function = instr_dict[decodedInstruction["instruction_key"]]["execution"]
    
        pprint.pprint('\n\nNEW INSTRUCTION################################################################\n', logfile)
        pprint.pprint(decodedInstruction, logfile)
        pprint.pprint('\n\nBEFORE EXECUTION################################################################\n', logfile)
        pprint.pprint(state, logfile)
    
        # Executing instruction, on the computer state:
        instruction_function(decodedInstruction, state)
    
        pprint.pprint('\n\nAFTER EXECUTION################################################################\n', logfile)
        pprint.pprint(state, logfile)
    
        state["registerArray"][0] = 0
        
        # If the instruction was NOT a jump/branch instruction, we increment the PC:
        if not(decodedInstruction["instrText"] in ("JAL", "JALR", "BEQ", "BNE", "BLT", "BGE", "BLTU", "BGEU")):
            state["PC"] = state["PC"] + 4
    
        # And before continuing to next instruction, we just make sure that the PC is not out of bounds.
        if 0 > state["PC"] > memorySize - 3:
            state["hardwareErrorLev"] = 1    


    errormessages = {
        0: "Everything is good",
        1: "PC out of bounds",
        2: "The program has run succesfully",
        3: "Ends the program with return code: {}".format(state["registerArray"][11]),
        4: "Instruction not found in the dictionary",
        5: "Trying to load/store in memory out of bounds"
    }
    print("Exited with hardware error level {}".format(state["hardwareErrorLev"]))
    print(errormessages[state["hardwareErrorLev"]])

    pprint.pprint("Exited with hardware error level {}".format(state["hardwareErrorLev"]), logfile)
    pprint.pprint(errormessages[state["hardwareErrorLev"]], logfile)

    logfile.close()
    
    outfile = filename.split('.')[:-1][0] + ".test_res"
    
    state["registerArray"].tofile(outfile)
