#include "TAoC_Solver.h"




std::vector<TTest_result> TAoC_Solver::o_RunTests( const std::vector<TTest_input>& test_inputs
	, std::function<std::string( const std::string& )> funct
	) const
{
	std::vector<TTest_result> result;

	for (const auto& curr : test_inputs)
	{
		result.push_back( { curr, funct( curr.input ) } );
	}

	return result;
}


