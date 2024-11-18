
#include "TAoCS_15_03.h"

#include "T2DMap.h"



namespace y15::d03
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


EImpl TAoCS_P1::Implemented() const noexcept
{
	return EImpl::FULL;
}


std::string TAoCS_P1::Solve( const std::string& input ) const
{
	if (input.empty())
	{
		throw std::exception( "Input is empty." );
	}

	T2DMap deliver( input, 1);
	return std::to_string( deliver.NHouses());
}


TTestResult_Group TAoCS_P1::Test() const
{
	TTestInput_Group ltests = {
		{ ">", "2"},
		{ "^>v<", "4"},
		{ "^v^v^v^v^v", "2"},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) {return Solve( str ); } );
}


//__________________________________________________________________________________________________




EImpl TAoCS_P2::Implemented() const noexcept
{
	return EImpl::FULL;
}


std::string TAoCS_P2::Solve( const std::string& input ) const
{
	if (input.empty())
	{
		throw std::exception( "Input is empty." );
	}

	T2DMap deliver( input, 2 );
	return std::to_string( deliver.NHouses() );
}


TTestResult_Group TAoCS_P2::Test() const
{
	TTestInput_Group ltests = {
		{ "^v", "3"},
		{ "^>v<", "3"},
		{ "^v^v^v^v^v", "11"},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) {return Solve( str ); } );
}

}


