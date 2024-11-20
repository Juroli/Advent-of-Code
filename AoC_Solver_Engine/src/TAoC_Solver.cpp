#include "TAoC_Solver.h"




EImpl TAoC_Solver::Implemented() const noexcept
{

	{
		const auto Result_Solve = i_Solve_Run();

		if (Result_Solve == STR_IMPLEMENTED)
		{
			return EImpl::SOLUTION;
		}
	}


	{
		const auto input_test = i_Test_Prepare();

		if ( input_test.empty()
			 || (!input_test.empty() && input_test.front().expected != STR_NOT_IMPLEMENTED)
			)
		{
			return EImpl::TEST;
		}
	}

	return EImpl::NONE;
}

std::string TAoC_Solver::Solve( const std::string& input ) const
{
	return i_Solve_Run(input);
}

TTestResult_Group TAoC_Solver::Test() const
{
	TTestResult_Group result;

	const auto test_inputs = i_Test_Prepare();

	for (const auto& curr : test_inputs)
	{
		result.Add( { curr, i_Test_Run( curr.input ) } );
	}

	return result;
}

//TTestResult_Group TAoC_Solver::o_RunTests( const TTestInput_Group& test_inputs
//	, std::function<std::string( const std::string& )> funct
//	) const
//{
//	TTestResult_Group result;
//
//	for (const auto& curr : test_inputs)
//	{
//		result.Add( { curr, funct( curr.input ) } );
//	}
//
//	return result;
//}


