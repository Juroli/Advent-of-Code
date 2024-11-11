
#include "TAoCS_2015_01.h"

#include <vector>




std::string TAoCS_2015_01_A::Solve( const std::string& input )
{
	int piano = 0;

	for(const auto& curr: input)
	{
		if ( curr == '(')
		{
			++piano;
		}
		else if (curr == ')')
		{
			--piano;
		}
	}

	return std::to_string( piano );
}



std::vector<TTest_result> TAoCS_2015_01_A::Test()
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

	std::vector<TTest_result> result;

	for (const auto& curr : ltests)
	{
		result.push_back( { curr, Solve( curr.input ) } );
	}

	return result;
}

//__________________________________________________________________________________________________



std::string TAoCS_2015_01_B::Solve( const std::string& input )
{
	int piano = 0;

	int step = 1;

	for (const auto& curr : input)
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

	return "-1";
}

std::vector<TTest_result> TAoCS_2015_01_B::Test()
{
	std::vector<TTest_input> ltests = {
		{ ")", "1"},
		{ "()())", "5"}
	};

	std::vector<TTest_result> result;

	for (const auto& curr : ltests)
	{
		result.push_back( { curr, Solve( curr.input ) } );
	}

	return result;
}


//__________________________________________________________________________________________________

