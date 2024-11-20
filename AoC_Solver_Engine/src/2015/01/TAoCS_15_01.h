#pragma once

#include"TAoC_Solver.h"



namespace y15::d01
{

std::unique_ptr<TAoC_Solver> Get_Solver( uint8_t apart );



class TAoCS_P1 : public TAoC_Solver
{

private:

	std::string i_Solve_Run() const override;
	std::string i_Solve_Run( const std::string& input ) const override;

	TTestInput_Group i_Test_Prepare() const override;
	std::string i_Test_Run( const std::string& astrin ) const override;

};



class TAoCS_P2 : public TAoC_Solver
{

private:

	std::string i_Solve_Run() const override;
	std::string i_Solve_Run( const std::string& input ) const override;

	TTestInput_Group i_Test_Prepare() const override;
	std::string i_Test_Run( const std::string& astrin ) const override;

};


}

