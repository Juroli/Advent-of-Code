
#pragma once

#include"../TAoC_Solver.h"


namespace y15
{


class TAoCS_02_A : public TAoC_Solver
{
public:

	std::string Solve( const TStringList& input ) const override;

	std::vector<TTest_result> Test() const override;

};



class TAoCS_02_B : public TAoC_Solver
{
public:

	std::string Solve( const TStringList& input ) const override;

	std::vector<TTest_result> Test() const override;

};

}


