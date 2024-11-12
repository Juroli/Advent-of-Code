
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
	TTest_input reference;
	std::string actual;

	operator bool() const noexcept { return actual == reference.expected; }
};




class TAoC_Solver
{
public:

	virtual std::string Solve( const TStringList& input ) const { return "* Not implemented! *"; }

	virtual std::vector<TTest_result> Test() const { return { { { "?", "?" }, "* Not implemented! *" } }; }


protected:

	std::vector<TTest_result> o_RunTests( const std::vector<TTest_input>& test_inputs ) const;

};

