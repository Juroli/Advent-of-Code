
#include "TAoCS_15_02.h"

#include <sstream>

#include "TBox.h"

#include "Utils/Strings/TStringParser.hpp"


namespace y15::d02
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

	int paper_size = 0;

	TStringParser parser( input );

	while (parser)
	{
		auto curr = parser.Extract_Line();
		const TBox box( curr );
		paper_size += box.PaperSize();
	}

	return std::to_string( paper_size );
}


TTestInput_Group TAoCS_P1::i_Test_Prepare() const
{
	return {
		TTestInput::Create_Example( "Ex. 01","2x3x4", "58" ) ,
		TTestInput::Create_Example( "Ex. 02", "1x1x10", "43" ) ,
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

	int ribbon_length = 0;

	TStringParser parser( input );

	while (parser)
	{
		auto curr = parser.Extract_Line();
		const TBox box( curr );
		ribbon_length += box.RibbonLength();
	}

	return std::to_string( ribbon_length );
}


TTestInput_Group TAoCS_P2::i_Test_Prepare() const
{
	return {
		TTestInput::Create_Example( "Ex. 01", "2x3x4", "34" ) ,
		TTestInput::Create_Example( "Ex. 02", "1x1x10", "14" ) ,
	};
}


std::string TAoCS_P2::i_Test_Run( std::string_view astrin ) const
{
	return Solve( astrin );
}


}

