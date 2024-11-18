
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


std::string TAoCS_A::Solve( const std::string& input ) const
{
	int piano = 0;


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
	}

	return std::to_string( piano );
}



TTestResult_Group TAoCS_A::Test() const
{

	TTestInput_Group ltests = {
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

	return o_RunTests( ltests, [this](const std::string& str){return Solve(str); } );
}

//__________________________________________________________________________________________________



std::string TAoCS_B::Solve( const std::string& input ) const
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

TTestResult_Group TAoCS_B::Test() const
{
	TTestInput_Group ltests = {
		{ ")", "1"},
		{ "()())", "5"}
	};

	return o_RunTests( ltests, [this]( const std::string& str ) {return Solve( str ); } );
}


//__________________________________________________________________________________________________


}

