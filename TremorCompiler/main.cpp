// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdio>

#include "preprocessor.h"

int main()
{
	Preprocessor p;
	
	//p.define("_DEBUG_", "1");
	std::cout << p.process("../Example.tmr");

	return 0;
}