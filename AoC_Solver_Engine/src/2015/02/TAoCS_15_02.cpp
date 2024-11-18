
#include "TAoCS_15_02.h"

#include <sstream>

#include "TBox.h"

#include "Utils/Strings/TStringParser.hpp"


namespace y15::d02
{


std::unique_ptr<TAoC_Solver> Get_Solver( char apart )
{
	switch (apart)
	{
	case 'A': return std::make_unique< TAoCS_A>();
	case 'B': return std::make_unique< TAoCS_B>();

	default: throw std::exception( "Invalid part." );
	}
}


//__________________________________________________________________________________________________


std::string TAoCS_A::Solve( const std::string& input ) const
{
	int paper_size = 0;

	TStringParser parser( input );

	while (parser)
	{
		auto curr = parser.GetLine();
		const TBox box( curr );
		paper_size += box.PaperSize();
	}

	return std::to_string( paper_size );
}

TTestResult_Group TAoCS_A::Test() const
{
	TTestInput_Group ltests = {
		{ "2x3x4", "58"},
		{ "1x1x10", "43"},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) {return Solve( str ); } );
}


//__________________________________________________________________________________________________


std::string TAoCS_B::Solve( const std::string& input ) const
{
	int ribbon_length = 0;

	TStringParser parser( input );

	while (parser)
	{
		auto curr = parser.GetLine();
		const TBox box( curr );
		ribbon_length += box.RibbonLength();
	}

	return std::to_string( ribbon_length );
}

TTestResult_Group TAoCS_B::Test() const
{
	TTestInput_Group ltests = {
		{ "2x3x4", "34"},
		{ "1x1x10", "14"},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) {return Solve( str ); } );
}

}

