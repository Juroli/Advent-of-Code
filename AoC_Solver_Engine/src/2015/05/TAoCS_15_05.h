#pragma once

#include"TAoC_Solver.h"



namespace y15::d05
{

std::unique_ptr<TAoC_Solver> Get_Solver( char apart );



class TAoCS_A : public TAoC_Solver
{
public:

	bool IsNice( std::string const& pstr ) const noexcept;

	std::string Solve( const std::string& input ) const override;

	TTestResult_Group Test() const override;

};



class TAoCS_B : public TAoC_Solver
{
public:

	bool IsNice( std::string const& pstr ) const noexcept;

	std::string Solve( const std::string& input ) const override;

	TTestResult_Group Test() const override;

};


}

