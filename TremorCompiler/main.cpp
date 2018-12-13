// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "preprocessor.h"

using namespace TremorCompiler;

int main()
{
	Preprocessor p;
	p.define("_DEBUG_", "1");
	std::cout << p.process("test.trm");
	return 0;
}