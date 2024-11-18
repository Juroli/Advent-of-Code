

#include "TAoCS_15_07.h"

#include <vector>


namespace y15::d07
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
	return "* Not implemented! *";
}


TTestResult_Group TAoCS_A::Test() const
{
	std::string tmp = { "123 -> x\n"
		"456->y\n"
		"x AND y->d\n"
		"x OR y->e\n"
		"x LSHIFT 2->f\n"
		"y RSHIFT 2->g\n"
		"NOT x->h\n"
		"NOT y->i\n" 
	};

	TTestInput_Group ltests = {
		{ 
			"123 -> x\n"
			"456->y\n"
			"x AND y->d\n"
			"x OR y->e\n"
			"x LSHIFT 2->f\n"
			"y RSHIFT 2->g\n"
			"NOT x->h\n"
			"NOT y->i\n"
			, ""},
		{ {""}, ""},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) { return Solve( str ); } );
}


//__________________________________________________________________________________________________


std::string TAoCS_B::Solve( const std::string& input ) const
{
	return "* Not implemented! *";
}

TTestResult_Group TAoCS_B::Test() const
{
	TTestInput_Group ltests = {
		{ "", ""},
		{ "", ""},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) { return Solve( str ); } );
}


//__________________________________________________________________________________________________


}

