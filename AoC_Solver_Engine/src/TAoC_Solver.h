
#pragma once


#include <string>
#include <vector>
#include <istream>


#include "TStringList.h"



struct TTest_input
{
	std::string input;
	std::string expected;
};

struct TTest_result
{
	TTest_input nominal;
	std::string result;

	operator bool() const noexcept { return result == nominal.expected; }
};




class TAoC_Solver
{
public:

	virtual std::string Solve( const TStringList& input ) { return {}; }

	virtual std::vector<TTest_result> Test() { return {}; }


};

