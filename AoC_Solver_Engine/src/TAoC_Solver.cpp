#include "TAoC_Solver.h"




EImpl TAoC_Solver::Implemented() const noexcept
{

	const auto Result_Solve = i_Solve_Run( STR_SOLVE_CHECK );

	if (Result_Solve == STR_IMPLEMENTED)
	{
		return EImpl::SOLUTION;
	}
	else if(Result_Solve != STR_NOT_IMPLEMENTED)
	{
		return EImpl::ERROR;
	}


	const auto input_test = i_Test_Prepare();

	if (input_test.size() == 1)
	{
		const TTestInput test = input_test.front();

		if (test.Name() == STR_NOT_IMPLEMENTED
			&& test.Input() == STR_NOT_IMPLEMENTED
			&& test.Expected() == STR_NOT_IMPLEMENTED
			)
		{
			return EImpl::NONE;
		}
	}

	return EImpl::TEST;

}


std::string TAoC_Solver::Solve( std::string_view input ) const
{
	return i_Solve_Run(input);
}

TTestResult_Group TAoC_Solver::Test() const
{
	TTestResult_Group result;

	const auto test_inputs = i_Test_Prepare();

	for (const auto& curr : test_inputs)
	{
		result.Add( { curr, i_Test_Run( curr.Input() ) } );
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


