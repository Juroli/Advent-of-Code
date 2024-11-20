
#include "TAoCS_15_01.h"

#include <vector>


namespace y15::d01
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


std::string TAoCS_P1::i_Solve_Run( const std::string& input ) const
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


TTestInput_Group TAoCS_P1::i_Test_Prepare() const
{
	return {
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
}


std::string TAoCS_P1::i_Test_Run( const std::string& astrin ) const
{
	return Solve( astrin );
}


//__________________________________________________________________________________________________



std::string TAoCS_P2::i_Solve_Run() const
{
	return STR_IMPLEMENTED;
}


std::string TAoCS_P2::i_Solve_Run( const std::string& input ) const
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



TTestInput_Group TAoCS_P2::i_Test_Prepare() const
{
	return {
		{ ")", "1"},
		{ "()())", "5"}
	};
}

std::string TAoCS_P2::i_Test_Run( const std::string& astrin ) const
{
	return Solve( astrin );
}


//__________________________________________________________________________________________________


}

