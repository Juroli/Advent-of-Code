
#include "TAoCS_15_06.h"

#include <vector>

#include "Grid.hpp"


namespace y15::d06
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



std::string TAoCS_A::Solve( const std::string& input ) const
{
	TOps_Bool grid(1000, 1000);

	for (const auto& curr : input)
	{
		grid.ParseLine( curr );
	}

	return std::to_string( grid.SumAll() );
}


std::vector<TTest_result> TAoCS_A::Test() const
{
	std::vector<TTest_input> ltests = {
		{ "turn on 0,0 through 999,999", "1000000"},
		{ "toggle 0,0 through 999,0", "1000"},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) { return Solve( str ); } );
}


//__________________________________________________________________________________________________





std::string TAoCS_B::Solve( const std::string& input ) const
{
	TOps_Int grid( 1000, 1000 );

	for (const auto& curr : input)
	{
		grid.ParseLine( curr );
	}

	return std::to_string( grid.SumAll() );
}

std::vector<TTest_result> TAoCS_B::Test() const
{
	std::vector<TTest_input> ltests = {
		{ "turn on 0,0 through 0,0", "1"},
		{ "toggle 0,0 through 999,999", "2000000"},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) { return Solve( str ); } );
}


//__________________________________________________________________________________________________


}

