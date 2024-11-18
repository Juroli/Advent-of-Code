
#pragma once


#include <string>
#include <vector>
#include <istream>

#include <functional>

#include "Test_Common.h"



struct TPuzzleID
{
	int Year;
	int Day;
	char Part;
};



class TAoC_Solver
{
public:

	virtual std::string Solve( const std::string& input ) const = 0;

	virtual TTestResult_Group Test() const = 0;


protected:

	TTestResult_Group o_RunTests( const TTestInput_Group& test_inputs
		, std::function<std::string(const std::string&)> funct
		) const;

};


class TAoC_Solver_NULL : public TAoC_Solver
{
public:

	std::string Solve( const std::string& input ) const override { return "* Not implemented! *"; }

	TTestResult_Group Test() const override { return { { { "?", "?" }, "* Not implemented! *" } }; }

};


