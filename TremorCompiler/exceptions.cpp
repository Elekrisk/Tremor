#include "exceptions.h"

TremorException::TremorException()
{

}

TremorException::TremorException(const std::string &msg)
{
	message = msg;
}

TremorException::TremorException(const std::string &msg, Location loc)
{
	message = msg;
	location = loc;
}