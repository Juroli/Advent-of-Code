#pragma once

#include"TAoC_Solver.h"



namespace y00::d00
{

std::unique_ptr<TAoC_Solver> Get_Solver( uint8_t apart );



class TAoCS_P1 : public TAoC_Solver
{
public:


	EImpl Implemented() const noexcept override;

	std::string Solve( const std::string& input ) const override;

	TTestResult_Group Test() const override;

};



class TAoCS_P2 : public TAoC_Solver
{
public:


	EImpl Implemented() const noexcept override;

	std::string Solve( const std::string& input ) const override;

	TTestResult_Group Test() const override;

};


}

