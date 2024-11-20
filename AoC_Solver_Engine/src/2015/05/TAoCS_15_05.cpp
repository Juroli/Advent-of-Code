
#include "TAoCS_15_05.h"

#include <vector>

#include "Utils/Strings/TStringParser.hpp"



namespace
{

bool IsVowel( char const& pchar ) noexcept
{
	static char vowel[5] = { 'a', 'e', 'i', 'o', 'u' };
	for (int i = 0; i < 5; ++i)
	{
		if (pchar == vowel[i])
		{
			return true;
		}
	}

	return false;
}

}


namespace y15::d05
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



std::string TAoCS_P1::i_Solve_Run() const
{
	return STR_IMPLEMENTED;
}


bool TAoCS_P1::IsNice( std::string_view pstr ) const noexcept
{

	bool double_char = false;

	const char bad[4][2] = {
		{ 'a', 'b'},
		{ 'c', 'd'},
		{ 'p', 'q'},
		{ 'x', 'y'},
	};

	int nvowel = 0;

	char prec = pstr[0];

	if (IsVowel( prec ))
	{
		++nvowel;
	}

	for (auto cc = 1u; cc < pstr.size(); ++cc)
	{
		if (IsVowel( pstr[cc] ))
		{
			++nvowel;
		}

		if (prec == pstr[cc])
		{
			double_char = true;
		}

		for (int i = 0; i < 4; ++i)
		{
			if (prec == bad[i][0] && pstr[cc] == bad[i][1])
			{
				return false;
			}
		}

		prec = pstr[cc];
	}

	if (nvowel >= 3 && double_char)
	{
		return true;
	}

	return false;
}




std::string TAoCS_P1::i_Solve_Run( const std::string& input ) const
{
	int num_nice = 0;

	TStringParser parser( input );

	while (parser)
	{
		auto curr = parser.Extract_Line();

		if (IsNice( curr ))
		{
			++num_nice;
		}
	}

	return std::to_string( num_nice );
}


TTestInput_Group TAoCS_P1::i_Test_Prepare() const
{
	return {
		{ "ugknbfddgicrmopn", "nice"},
		{ "aaa", "nice"},
		{ "jchzalrnumimnmhp", "naughty"},
		{ "haegwjzuvuyypxyu", "naughty"},
		{ "dvszwmarrgswjxmb", "naughty"},
	};

}


std::string TAoCS_P1::i_Test_Run( const std::string& astrin ) const
{
	return IsNice( astrin )? "nice": "naughty";
}



//__________________________________________________________________________________________________



bool TAoCS_P2::IsNice( std::string_view pstr ) const noexcept
{
	// Test 1
	if (pstr.size() < 4)
	{
		return false;
	}

	bool found = false;

	for (size_t i = 1u; i < pstr.size() && !found; ++i)
	{
		for (size_t j = i + 2u; j < pstr.size() && !found; ++j)
		{
			if (pstr[i - 1] == pstr[j - 1]
				&& pstr[i] == pstr[j])
			{
				found = true;
			}
		}
	}

	if (!found)
	{
		return false;
	}

	for (size_t i = 2u; i < pstr.size(); ++i)
	{
		if (pstr[i] == pstr[i - 2])
		{
			return true;
		}
	}

	return false;
}




std::string TAoCS_P2::i_Solve_Run() const
{
	return STR_IMPLEMENTED;
}


std::string TAoCS_P2::i_Solve_Run( const std::string& input ) const
{
	int num_nice = 0;
	TStringParser parser( input );

	while (parser)
	{
		auto curr = parser.Extract_Line();

		if (IsNice( curr ))
		{
			++num_nice;
		}
	}

	return std::to_string( num_nice );
}


TTestInput_Group TAoCS_P2::i_Test_Prepare() const
{
	return {
		{ "qjhvhtzxzqqjkmpb", "nice"},
		{ "xxyxx", "nice"},
		{ "uurcxstgmygtbstg", "naughty"},
		{ "ieodomkazucvgmuy", "naughty"},
	};

}


std::string TAoCS_P2::i_Test_Run( const std::string& astrin ) const
{
	return IsNice( astrin ) ? "nice" : "naughty";
}



//__________________________________________________________________________________________________


}

