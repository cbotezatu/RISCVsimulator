import RISC_V_simulator
import os

#dir = 'RISC-V-tests/RISC-V_Sim/InstructionTests'
dir = 'test_files'

for file in [file for file in os.listdir(dir) if os.fsdecode(file).endswith(".bin")]:
    filename = os.fsdecode(file)
    if filename.endswith(".bin"):
        print('runSmart:' + filename)
        RISC_V_simulator.RunFile(dir + '/' + filename)
    else:
        print("Not a .bin file")
