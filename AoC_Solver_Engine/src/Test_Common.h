
#pragma once


#include <string>

//#include "TStringList.h"


struct TTest_input
{
	std::string input;
	std::string expected;
};

struct TTest_result
{
	TTest_input reference;
	std::string actual;

	operator bool() const noexcept { return actual == reference.expected; }
};




