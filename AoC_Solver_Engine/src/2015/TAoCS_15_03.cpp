#include "TAoCS_15_03.h"

#include "03/T2DMap.h"

namespace y15
{

std::string TAoCS_03_A::Solve( const TStringList& input ) const
{
	if (input.empty())
	{
		throw std::exception( "Input is empty." );
	}

	T2DMap deliver( input.front(), 1);
	return std::to_string( deliver.NHouses());
}

std::vector<TTest_result> TAoCS_03_A::Test() const
{
	std::vector<TTest_input> ltests = {
		{ ">", "2"},
		{ "^>v<", "4"},
		{ "^v^v^v^v^v", "2"},
	};

	return o_RunTests(ltests);
}


//__________________________________________________________________________________________________




std::string TAoCS_03_B::Solve( const TStringList& input ) const
{
	if (input.empty())
	{
		throw std::exception( "Input is empty." );
	}

	T2DMap deliver( input.front(), 2 );
	return std::to_string( deliver.NHouses() );
}


std::vector<TTest_result> TAoCS_03_B::Test() const
{
	std::vector<TTest_input> ltests = {
		{ "^v", "3"},
		{ "^>v<", "3"},
		{ "^v^v^v^v^v", "11"},
	};

	return o_RunTests( ltests );
}

}


