#pragma once

#include"TAoC_Solver.h"



namespace y15::d04
{

std::unique_ptr<TAoC_Solver> Get_Solver( char apart );



class TAoCS_A : public TAoC_Solver
{
public:

	std::string Solve( const TStringList& input ) const override;

	std::vector<TTest_result> Test() const override;

};



class TAoCS_B : public TAoC_Solver
{
public:

	std::string Solve( const TStringList& input ) const override;

	std::vector<TTest_result> Test() const override;

};


}

