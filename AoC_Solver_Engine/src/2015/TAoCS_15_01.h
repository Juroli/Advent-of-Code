#pragma once

#include"../TAoC_Solver.h"



namespace y15
{


class TAoCS_01_A : public TAoC_Solver
{
public:

	std::string Solve( const TStringList& input ) override;

	std::vector<TTest_result> Test() override;

};



class TAoCS_01_B : public TAoC_Solver
{
public:

	std::string Solve( const TStringList& input ) override;

	std::vector<TTest_result> Test() override;

};

}

