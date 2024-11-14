
#include "TAoCS_yy_dd.h"

#include <vector>


namespace y00::d00
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
		{ "", ""},
		{ "", ""},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) { return Solve( str ); } );
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

	return o_RunTests( ltests, [this]( const std::string& str ) { return Solve( str ); } );
}


//__________________________________________________________________________________________________


}

