
#include "TAoCS_15_06.h"

#include <vector>

#include "Utils/Strings/TStringParser.hpp"


#include "Grid.hpp"


namespace y15::d06
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



//std::string TAoCS_P1::i_Solve_Run() const
//{
//	return STR_IMPLEMENTED;
//}


std::string TAoCS_P1::i_Solve_Run( std::string_view input ) const
{
	if (input == STR_SOLVE_CHECK)
	{
		return STR_IMPLEMENTED;
	}


	TOps_Bool grid(1000, 1000);

	TStringParser parser( input );

	while (parser)
	{
		auto curr = parser.Extract_Line();
		grid.ParseLine( curr );
	}

	return std::to_string( grid.SumAll() );
}


TTestInput_Group TAoCS_P1::i_Test_Prepare() const
{
	return {
		TTestInput::Create_Example( "Ex01", "turn on 0,0 through 999,999", "1000000" ),
		TTestInput::Create_Example( "Ex02", "toggle 0,0 through 999,0", "1000" ),
	};
}


std::string TAoCS_P1::i_Test_Run( std::string_view astrin ) const
{
	return Solve( astrin );
}



//__________________________________________________________________________________________________



//std::string TAoCS_P2::i_Solve_Run() const
//{
//	return STR_IMPLEMENTED;
//}


std::string TAoCS_P2::i_Solve_Run( std::string_view input ) const
{
	if (input == STR_SOLVE_CHECK)
	{
		return STR_IMPLEMENTED;
	}

	TOps_Int grid( 1000, 1000 );

	TStringParser parser( input );

	while (parser)
	{
		auto curr = parser.Extract_Line();
		grid.ParseLine( curr );
	}

	return std::to_string( grid.SumAll() );
}


TTestInput_Group TAoCS_P2::i_Test_Prepare() const
{
	return {
		TTestInput::Create_Example( "Ex01", "turn on 0,0 through 0,0", "1" ),
		TTestInput::Create_Example( "Ex02", "toggle 0,0 through 999,999", "2000000" ),
	};
}

std::string TAoCS_P2::i_Test_Run( std::string_view astrin ) const
{
	return Solve( astrin );
}


//__________________________________________________________________________________________________


}

