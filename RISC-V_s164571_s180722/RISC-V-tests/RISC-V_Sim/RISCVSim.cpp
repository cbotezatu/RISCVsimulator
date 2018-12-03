#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Processor.h"
#include "TestEncodeDecode.h"
#include "TestInstructions.h"
#include "ReadProgram.h"
#include "RISCV_Program.h"
#include "TestRandomInstructions.h"

void testFile(std::string filePath)
{
	const std::unique_ptr<RISCV_Program> test = LoadProgram(filePath);
	test->Test();

	std::cout << "SUCCESS" << std::endl;
}

int runAllTests()
{
	TestAllEncodeDecode();
	TestAllInstructions();
	TestRandomArithmeticInstructions();
	try
	{

		testFile("tests/task1/addlarge");
		testFile("tests/task1/addneg");
		testFile("tests/task1/addpos");
		testFile("tests/task1/shift");

		testFile("tests/task2/branchcnt");
		testFile("tests/task2/branchmany");

		//testFile("tests/task3/loop");
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
		std::cin.get();
		return -1;
	}
	std::cin.get();
	return 0;
}

int main(int argc, char* argv[])
{	
	//if no arguments then run all tests
	if (argc <= 1)
	{
		return runAllTests();
	}
	//or if the arguments was to run all tests
	else if ("--testAll" == std::string(argv[1]))
	{
		return runAllTests();
	}
	
	//for this next part atleast two arguments
	//are rquired
	if (argc <= 1)
	{
		std::cout << "Incorrect arguments" << std::endl;
		return -1;
	}

	std::string input;
	//default output file
	std::string output = "result";

	//first argument has to be this
	//and second has to be a valid riscv program file path
	if ("--run" == std::string(argv[1]))
	{
		input = std::string(argv[2]);
	}
	else
	{
		std::cout << "Incorrect arguments" << std::endl;
		return -1;
	}

	//if another output file was specified then
	//change the default to the specified file
	if (argc == 5 && "-o" == std::string(argv[3]))
	{
		output = std::string(argv[4]);
	}

	try
	{
		std::unique_ptr<RISCV_Program> program = LoadProgram(input);
		program->Run();
		program->PrintResult();
		program->SaveProgramResult(output);
		std::cout << "Program ran sucessfully" << std::endl;
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
		std::cin.get();
		return -1;
	}

	std::cin.get();
    return 0;
}

