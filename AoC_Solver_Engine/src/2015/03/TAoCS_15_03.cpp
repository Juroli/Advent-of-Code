
#include "TAoCS_15_03.h"

#include "T2DMap.h"



namespace y15::d03
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
	return STR_IMPLEMENTED;
}


std::string TAoCS_P1::i_Solve_Run( const std::string& input ) const
{
	if (input.empty())
	{
		return { "" };
	}

	T2DMap deliver( input, 1 );
	return std::to_string( deliver.NHouses() );
}


TTestInput_Group TAoCS_P1::i_Test_Prepare() const
{
	return {
		{ ">", "2"},
		{ "^>v<", "4"},
		{ "^v^v^v^v^v", "2"},
	};
}

std::string TAoCS_P1::i_Test_Run( const std::string& astrin ) const
{
	return Solve( astrin );
}



//__________________________________________________________________________________________________



std::string TAoCS_P2::i_Solve_Run() const
{
	return STR_IMPLEMENTED;
}


std::string TAoCS_P2::i_Solve_Run( const std::string& input ) const
{
	if (input.empty())
	{
		return { "" };
	}

	T2DMap deliver( input, 2 );
	return std::to_string( deliver.NHouses() );
}


TTestInput_Group TAoCS_P2::i_Test_Prepare() const
{
	return {
		{ "^v", "3"},
		{ "^>v<", "3"},
		{ "^v^v^v^v^v", "11"},
	};
}

std::string TAoCS_P2::i_Test_Run( const std::string& astrin ) const
{
	return Solve( astrin );
}



}


