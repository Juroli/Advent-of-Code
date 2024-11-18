
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


EImpl TAoCS_P1::Implemented() const noexcept
{
	return EImpl::FULL;
}


std::string TAoCS_P1::Solve( const std::string& input ) const
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



TTestResult_Group TAoCS_P1::Test() const
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



EImpl TAoCS_P2::Implemented() const noexcept
{
	return EImpl::FULL;
}


std::string TAoCS_P2::Solve( const std::string& input ) const
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

TTestResult_Group TAoCS_P2::Test() const
{
	TTestInput_Group ltests = {
		{ ")", "1"},
		{ "()())", "5"}
	};

	return o_RunTests( ltests, [this]( const std::string& str ) {return Solve( str ); } );
}


//__________________________________________________________________________________________________


}

