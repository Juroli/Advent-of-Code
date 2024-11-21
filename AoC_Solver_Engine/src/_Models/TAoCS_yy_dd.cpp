
#include "TAoCS_yy_dd.h"

#include <vector>


namespace y00::d00
{


std::unique_ptr<TAoC_Solver> Get_Solver( uint8_t apart )
{
	switch (apart)
	{
	case 1: return std::make_unique< TAoCS_P1>();
	case 2: return std::make_unique< TAoCS_P2>();
	default: throw std::exception( "Invalid part." );
	}
}



//__________________________________________________________________________________________________


std::string TAoCS_P1::i_Solve_Run() const
{
	return STR_NOT_IMPLEMENTED;
}

std::string TAoCS_P1::i_Solve_Run( const std::string& input ) const
{
	return STR_NOT_IMPLEMENTED;
}


TTestInput_Group TAoCS_P1::i_Test_Prepare() const
{
	return {
		TTestInput::Create_Example( "Ex01", "?", STR_NOT_IMPLEMENTED ),
		TTestInput::Create_Example( "", "", "" ),
	};
}


std::string TAoCS_P1::i_Test_Run( const std::string& astrin) const
{
	return Solve( astrin );
}



//__________________________________________________________________________________________________



std::string TAoCS_P2::i_Solve_Run() const
{
	return STR_NOT_IMPLEMENTED;
}


std::string TAoCS_P2::i_Solve_Run( const std::string& input ) const
{
	return STR_NOT_IMPLEMENTED;
}


TTestInput_Group TAoCS_P2::i_Test_Prepare() const
{
	return {
		TTestInput::Create_Example( "Ex01", "?", STR_NOT_IMPLEMENTED ),
		TTestInput::Create_Example( "", "", "" ),
	};
}


std::string TAoCS_P2::i_Test_Run( const std::string& astrin ) const
{
	return Solve( astrin );
}


//__________________________________________________________________________________________________





}

