
#include "TAoCS_15_04.h"

#include <vector>

#include "Utils/MD5/JMD5.hpp"



namespace y15::d04
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
		throw std::exception( "No input" );
	}

	std::string base_str( input );

	for (auto iter = 1u; true; ++iter)
	{
		std::string str = base_str + std::to_string( iter );

		const auto result = Calc_MD5( str );

		bool found = true;
		for (auto i = 0u; i < 5; ++i)
		{
			if (result[i] != '0')
			{
				found = false;
			}
		}

		if (found)
		{
			return std::to_string( iter );
		}
	}

	return "";
}


TTestResult_Group TAoCS_P1::Test() const
{
	TTestInput_Group ltests = {
		{ "abcdef", "609043"},
		{ "pqrstuv", "1048970"},
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
		throw std::exception( "No input" );
	}

	std::string base_str( input );

	for (auto iter = 1u; true; ++iter)
	{
		std::string str = base_str + std::to_string( iter );

		const auto result = Calc_MD5( str );

		bool found = true;
		for (auto i = 0u; i < 6; ++i)
		{
			if (result[i] != '0')
			{
				found = false;
			}
		}

		if (found)
		{
			return std::to_string( iter );
		}
	}

	return "";
}

TTestResult_Group TAoCS_P2::Test() const
{
	TTestInput_Group ltests = {
	};

	return o_RunTests( ltests, [this]( const std::string& str ) {return Solve( str ); } );
}


//__________________________________________________________________________________________________


}

