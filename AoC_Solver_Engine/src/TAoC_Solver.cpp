#include "TAoC_Solver.h"




TTestResult_Group TAoC_Solver::o_RunTests( const TTestInput_Group& test_inputs
	, std::function<std::string( const std::string& )> funct
	) const
{
	TTestResult_Group result;

	for (const auto& curr : test_inputs)
	{
		result.Add( { curr, funct( curr.input ) } );
	}

	return result;
}


