
#pragma once


#include"TAoC_Solver.h"


namespace y15::d03
{

std::unique_ptr<TAoC_Solver> Get_Solver( char apart );


//__________________________________________________________________________________________________


class TAoCS_A : public TAoC_Solver
{
public:

	std::string Solve( const std::string& input ) const override;

	std::vector<TTest_result> Test() const override;

};


//__________________________________________________________________________________________________


class TAoCS_B : public TAoC_Solver
{
public:

	std::string Solve( const std::string& input ) const override;

	std::vector<TTest_result> Test() const override;

};



}

