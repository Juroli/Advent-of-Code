
#include "TAoCS_15_02.h"

#include "02/TBox.h"


namespace y15
{


std::string TAoCS_02_A::Solve( const TStringList& input ) const
{
	int paper_size = 0;

	for (const auto& curr : input)
	{
		const TBox box( curr );
		paper_size += box.PaperSize();
	}

	return std::to_string( paper_size );
}

std::vector<TTest_result> TAoCS_02_A::Test() const
{
	std::vector<TTest_input> ltests = {
		{ "2x3x4", "58"},
		{ "1x1x10", "43"},
	};

	return o_RunTests( ltests );
}


//__________________________________________________________________________________________________


std::string TAoCS_02_B::Solve( const TStringList& input ) const
{
	int ribbon_length = 0;

	for (const auto& curr : input)
	{
		const TBox box( curr );
		ribbon_length += box.RibbonLength();
	}

	return std::to_string( ribbon_length );
}

std::vector<TTest_result> TAoCS_02_B::Test() const
{
	std::vector<TTest_input> ltests = {
		{ "2x3x4", "34"},
		{ "1x1x10", "14"},
	};

	return o_RunTests(ltests);
}

}

