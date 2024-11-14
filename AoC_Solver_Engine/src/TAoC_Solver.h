
#pragma once


#include <string>
#include <vector>
#include <istream>


#include "Test_Common.h"
#include "TStringList.h"





class TAoC_Solver
{
public:

	virtual std::string Solve( const TStringList& input ) const = 0;

	virtual std::vector<TTest_result> Test() const = 0;


protected:

	std::vector<TTest_result> o_RunTests( const std::vector<TTest_input>& test_inputs ) const;

};


class TAoC_Solver_NULL : public TAoC_Solver
{
public:

	std::string Solve( const TStringList& input ) const override { return "* Not implemented! *"; }

	std::vector<TTest_result> Test() const override { return { { { "?", "?" }, "* Not implemented! *" } }; }

};


