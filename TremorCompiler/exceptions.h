#pragma once

#include <string>

#include "tokens.h"

class TremorException
{
public:
	std::string message;
	Location location;

	TremorException();
	TremorException(const std::string &msg);
	TremorException(const std::string &msg, Location loc);
};