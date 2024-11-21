
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



//std::string TAoCS_P1::i_Solve_Run() const
//{
//	return STR_IMPLEMENTED;
//}


std::string TAoCS_P1::i_Solve_Run( const std::string_view input ) const
{
	if (input == STR_SOLVE_CHECK)
	{
		return STR_IMPLEMENTED;
	}

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


TTestInput_Group TAoCS_P1::i_Test_Prepare() const
{
	return {
		TTestInput::Create_Example( "Ex01",  "abcdef", "609043" ) ,
		TTestInput::Create_Example( "Ex02",  "pqrstuv", "1048970" ) ,
	};
}

std::string TAoCS_P1::i_Test_Run( std::string_view astrin ) const
{
	return Solve( astrin );
}



//__________________________________________________________________________________________________



//std::string TAoCS_P2::i_Solve_Run() const
//{
//	return STR_IMPLEMENTED;
//}


std::string TAoCS_P2::i_Solve_Run( std::string_view input ) const
{
	if (input == STR_SOLVE_CHECK)
	{
		return STR_IMPLEMENTED;
	}

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


TTestInput_Group TAoCS_P2::i_Test_Prepare() const
{
	return {};
}


std::string TAoCS_P2::i_Test_Run( std::string_view astrin ) const
{
	return Solve( astrin );
}



//__________________________________________________________________________________________________


}

