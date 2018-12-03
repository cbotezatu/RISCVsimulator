import RISC_V_simulator
import argparse
import os

parser = argparse.ArgumentParser(description='Simulate a RISC-V I32 program')
parser.add_argument('Filename', metavar='Filename', type=str)
args = parser.parse_args()

if not os.path.isfile(args.Filename):
    print("file not found")
else:
    print("Running simulator on ", args.Filename)
    print("Output will be saved in .test_res and .log files")
    RISC_V_simulator.RunFile(args.Filename)