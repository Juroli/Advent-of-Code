#pragma once




#include"TAoC_Solver.h"


class TAoCS_2015_01: public TAoC_Solver
{
public:

	std::string Solve_A( const std::string& input ) override;

	std::vector<TTest_result> Test_A() override;

};

