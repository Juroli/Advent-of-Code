
#include "TAoCS_15_01.h"

#include <vector>


namespace y15::d01
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
	int piano = 0;

	for(const auto& str: input)
	{
		for (const auto& curr : str)
		{
			if (curr == '(')
			{
				++piano;
			}
			else if (curr == ')')
			{
				--piano;
			}
		}
	}

	return std::to_string( piano );
}



std::vector<TTest_result> TAoCS_A::Test() const
{

	std::vector<TTest_input> ltests = {
		{ "(())", "0"},
		{ "()()", "0"},
		{ "(((", "3"},
		{ "(()(()(", "3"},
		{ "))(((((", "3"},
		{ "())", "-1"},
		{ "))(", "-1"},
		{ ")))", "-3"},
		{ ")())())", "-3"},
	};

	return o_RunTests( ltests );
}

//__________________________________________________________________________________________________



std::string TAoCS_B::Solve( const TStringList& input ) const
{
	int piano = 0;

	int step = 1;

	for (const auto& str : input)
	{
		for (const auto& curr : str)
		{
			if (curr == '(')
			{
				++piano;
			}
			else if (curr == ')')
			{
				--piano;
			}

			if (piano == -1)
			{
				return std::to_string( step );
			}

			++step;
		}
	}

	return "-1";
}

std::vector<TTest_result> TAoCS_B::Test() const
{
	std::vector<TTest_input> ltests = {
		{ ")", "1"},
		{ "()())", "5"}
	};

	return o_RunTests( ltests );
}


//__________________________________________________________________________________________________


}

