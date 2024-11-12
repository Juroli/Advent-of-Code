#include "TAoC_Solver.h"




std::vector<TTest_result> TAoC_Solver::o_RunTests( const std::vector<TTest_input>& test_inputs ) const
{
	std::vector<TTest_result> result;

	for (const auto& curr : test_inputs)
	{
		result.push_back( { curr, Solve( curr.input ) } );
	}

	return result;
}


