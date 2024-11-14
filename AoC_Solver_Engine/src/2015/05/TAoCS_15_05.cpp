
#include "TAoCS_15_05.h"

#include <vector>



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


bool TAoCS_A::IsNice( std::string const& pstr ) const noexcept
{

	bool double_char = false;

	static char bad[4][2] = {
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


std::string TAoCS_A::Solve( const TStringList& input ) const
{
	int num_nice = 0;

	for (const auto& curr : input)
	{
		if (IsNice( curr ))
		{
			++num_nice;
		}
	}

	return std::to_string( num_nice );
}


std::vector<TTest_result> TAoCS_A::Test() const
{
	std::vector<TTest_input> ltests = {
		{ "ugknbfddgicrmopn", "nice"},
		{ "aaa", "nice"},
		{ "jchzalrnumimnmhp", "naughty"},
		{ "haegwjzuvuyypxyu", "naughty"},
		{ "dvszwmarrgswjxmb", "naughty"},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) { return IsNice( str )? "nice": "naughty"; });
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

