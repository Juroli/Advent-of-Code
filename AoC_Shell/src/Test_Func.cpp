

#include "Test_Func.hpp"

#include "fmt/core.h"



bool Check_TestResults( const TTestResult_Group& results )
{
	for (const auto& curr : results)
	{
		if (!curr)
		{
			return false;
		}
	}

	return true;
}

void Print_TestResults( const TTestResult_Group& results )
{
	int progressivo = 1;
	for (const auto& curr : results)
	{
		fmt::print( "Test {}/{}: ", progressivo, results.size() );

		if (curr)
		{
			fmt::print( "OK\n" );
		}
		else
		{
			fmt::print( "ERROR: expected: {}, received: {}\n", curr.reference.expected, curr.actual );
		}

		++progressivo;
	}
}


TTestResult_Group Run_Test( const TPuzzleID& apid )
{
	const auto solver = Get_Solver( apid );
	return solver->Test();
}


bool RunPrint_Test( const TPuzzleID& apid )
{
	fmt::print( " - Question {} {:02} {}\n\n", apid.Year, apid.Day, apid.Part );

	const auto restest = Run_Test( apid );

	//if ( !test_ok )
	{
		Print_TestResults( restest );
	}

	return Check_TestResults( restest );
}


void RunPrint_Tests( const TPuzzleID& apid_start, const TPuzzleID& apid_end )
{
	const uint8_t START_DAY = 1;
	const uint8_t END_DAY = 25;

	const uint8_t START_PART = 1;
	const uint8_t END_PART = 2;

	for (auto y = apid_start.Year; y <= apid_end.Year; ++y)
	{
		const auto d_start = (y == apid_start.Year) ? apid_start.Day : START_DAY;
		const auto d_end = (y == apid_end.Year) ? apid_end.Day : END_DAY;

		for (auto d = d_start; d <= d_end; ++d)
		{
			for (auto p = START_PART; p <= END_PART; ++p)
			{

				if (Run_Test( { y, d, p } ))
				{
					fmt::print( "o" );
				}
				else
				{
					fmt::print( "x" );
				}
			}

			fmt::print( " " );
		}

		fmt::print( "\n\n" );
	}
}


