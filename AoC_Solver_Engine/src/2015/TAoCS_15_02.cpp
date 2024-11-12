
#include "TAoCS_15_02.h"

#include "02/TBox.h"


std::string y15::TAoCS_02_A::Solve( const TStringList& input )
{
	int paper_size = 0;

	for (const auto& curr : input)
	{
		const TBox box( curr );
		paper_size += box.PaperSize();
	}

	return std::to_string(paper_size);
}

std::vector<TTest_result> y15::TAoCS_02_A::Test()
{
	std::vector<TTest_input> ltests = {
		{ "2x3x4", "58"},
		{ "1x1x10", "43"},
	};

	std::vector<TTest_result> result;

	for (const auto& curr : ltests)
	{
		result.push_back( { curr, Solve( curr.input ) } );
	}

	return result;
}



