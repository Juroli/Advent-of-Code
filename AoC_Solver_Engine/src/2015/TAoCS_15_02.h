
#pragma once

#include"../TAoC_Solver.h"


namespace y15
{


class TAoCS_02_A : public TAoC_Solver
{
public:

	std::string Solve( const TStringList& input ) override;

	std::vector<TTest_result> Test() override;

};



//class TAoCS_02_B : public TAoC_Solver
//{
//public:
//
//	std::string Solve( const std::string& input ) override;
//
//	std::vector<TTest_result> Test() override;
//
//};

}


