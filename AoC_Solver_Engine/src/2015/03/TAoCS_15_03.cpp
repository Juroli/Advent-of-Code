
#include "TAoCS_15_03.h"

#include "T2DMap.h"



namespace y15::d03
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
	if (input.empty())
	{
		throw std::exception( "Input is empty." );
	}

	T2DMap deliver( input, 1);
	return std::to_string( deliver.NHouses());
}


TTestResult_Group TAoCS_A::Test() const
{
	TTestInput_Group ltests = {
		{ ">", "2"},
		{ "^>v<", "4"},
		{ "^v^v^v^v^v", "2"},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) {return Solve( str ); } );
}


//__________________________________________________________________________________________________




std::string TAoCS_B::Solve( const std::string& input ) const
{
	if (input.empty())
	{
		throw std::exception( "Input is empty." );
	}

	T2DMap deliver( input, 2 );
	return std::to_string( deliver.NHouses() );
}


TTestResult_Group TAoCS_B::Test() const
{
	TTestInput_Group ltests = {
		{ "^v", "3"},
		{ "^>v<", "3"},
		{ "^v^v^v^v^v", "11"},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) {return Solve( str ); } );
}

}


