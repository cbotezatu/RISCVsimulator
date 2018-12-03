# RISC-V_Sim
RISC-V simulator

Complete RISC-V simulator that implements the RV32I instruction set.

# Run on linux
From the base folder of this repository, run.
```
cd RISC-V_Sim
make
./RISC_V_Sim
```

# Run on windows
Load up the project with visual studio and you should be set.

# Tests
There are two types of tests. First one is to verify that the simulator is able to encode and decode instruction correctly.
those tests are located in the file TestEncodeDecode.cpp.

The other type of tests, verifies that the execution of the diffferent instructions is correct. These tests are created in TestInstructions.cpp.
These tests also creates a .bin file with the instructions encoded as ints, a .res file with the expected register values and a .s file with the assembly code in ascii. 
To create these test files you first have to create the folder RISC-V_Sim\InstructionTests as it's not created automatically. 
Then run the simulator and the test files can then be found in the InstructionTests folder you just created.
