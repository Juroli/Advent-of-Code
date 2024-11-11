
#pragma once


#include <string>
#include <vector>
#include <istream>



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

	virtual std::string Solve_A( const std::string& input ) { return {}; }
	virtual std::string Solve_B( const std::string& input ) { return {}; }


	virtual std::vector<TTest_result> Test_A() { return {}; }
	virtual std::vector<TTest_result> Test_B() { return {}; }


};

