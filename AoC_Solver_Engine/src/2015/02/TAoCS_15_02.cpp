
#include "TAoCS_15_02.h"

#include "TBox.h"


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


std::string TAoCS_A::Solve( const TStringList& input ) const
{
	int paper_size = 0;

	for (const auto& curr : input)
	{
		const TBox box( curr );
		paper_size += box.PaperSize();
	}

	return std::to_string( paper_size );
}

std::vector<TTest_result> TAoCS_A::Test() const
{
	std::vector<TTest_input> ltests = {
		{ "2x3x4", "58"},
		{ "1x1x10", "43"},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) {return Solve( str ); } );
}


//__________________________________________________________________________________________________


std::string TAoCS_B::Solve( const TStringList& input ) const
{
	int ribbon_length = 0;

	for (const auto& curr : input)
	{
		const TBox box( curr );
		ribbon_length += box.RibbonLength();
	}

	return std::to_string( ribbon_length );
}

std::vector<TTest_result> TAoCS_B::Test() const
{
	std::vector<TTest_input> ltests = {
		{ "2x3x4", "34"},
		{ "1x1x10", "14"},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) {return Solve( str ); } );
}

}

