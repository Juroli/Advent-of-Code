#pragma once




#include"TAoC_Solver.h"


class TAoCS_2015_01_A: public TAoC_Solver
{
public:

	std::string Solve( const std::string& input ) override;

	std::vector<TTest_result> Test() override;

};


class TAoCS_2015_01_B : public TAoC_Solver
{
public:

	std::string Solve( const std::string& input ) override;

	std::vector<TTest_result> Test() override;

};

