
#include "TAoCS_15_04.h"

#include <vector>


namespace y15::d04
{


std::unique_ptr<TAoC_Solver> Get_Solver( char apart )
{
	switch (apart)
	{
	case 'A': return std::make_unique< TAoCS_A>();
	case 'B': return std::make_unique< TAoCS_B>();

	default: throw std::exception("Invalid part.");
	}
}


//__________________________________________________________________________________________________


std::string TAoCS_A::Solve( const TStringList& input ) const
{
	return "* Not implemented! *";
}


std::vector<TTest_result> TAoCS_A::Test() const
{
	std::vector<TTest_input> ltests = {
		{ "abcdef", "609043"},
		{ "pqrstuv", "1048970"},
	};

	return o_RunTests( ltests );
}


//__________________________________________________________________________________________________


std::string TAoCS_B::Solve( const TStringList& input ) const
{
	return "* Not implemented! *";
}

std::vector<TTest_result> TAoCS_B::Test() const
{
	std::vector<TTest_input> ltests = {
		{ "", ""},
		{ "", ""},
	};

	return o_RunTests( ltests );
}


//__________________________________________________________________________________________________


}

