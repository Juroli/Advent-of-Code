
#pragma once


#include"../TAoC_Solver.h"


namespace y15
{


class TAoCS_03_A : public TAoC_Solver
{
public:

	std::string Solve( const TStringList& input ) const override;

	std::vector<TTest_result> Test() const override;

};


//__________________________________________________________________________________________________


class TAoCS_03_B : public TAoC_Solver
{
public:

	std::string Solve( const TStringList& input ) const override;

	std::vector<TTest_result> Test() const override;

};



}

