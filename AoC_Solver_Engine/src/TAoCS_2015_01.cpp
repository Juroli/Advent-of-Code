
#include "TAoCS_2015_01.h"

#include <vector>


std::string TAoCS_2015_01::Solve_A( const std::string& input )
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



std::vector<TTest_result> TAoCS_2015_01::Test_A()
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
		result.push_back( { curr, Solve_A( curr.input ) } );
	}

	return result;
}

