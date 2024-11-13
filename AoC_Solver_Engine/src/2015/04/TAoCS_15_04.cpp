
#include "TAoCS_15_04.h"

#include <vector>

#include "Utils/MD5/TMD5.hpp"



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
	if (input.empty())
	{
		throw std::exception( "No input" );
	}

	std::string base_str( input.front() );

	for (auto iter = 1u; true; ++iter)
	{
		std::string str = base_str + std::to_string( iter );
		TMD5 check( str );

		auto const& result = check.String();

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

