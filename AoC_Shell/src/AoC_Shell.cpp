// AoC_Shell.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "gsl/narrow"
#include "fmt/core.h"

#include <fstream>

#include "AoC_Solver.hpp"





std::vector<std::string> ReadMainParams( int argc, char* argv[] )
{
	std::vector<std::string> result;

	for (auto i = 0; i < argc; ++i)
	{
		result.push_back( argv[i] );
	}

	return result;
}




void Print_TestResults( const std::vector<TTest_result>& results )
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
			fmt::print( "ERROR: expected: {}, received: {}\n", curr.nominal.expected, curr.result );
		}

		++progressivo;
	}
}


TStringList Read_Input( const std::string& path )
{
	std::ifstream file( path );
	if (!file.good())
	{
		throw std::exception( "File not found!" );
	}

	TStringList result;

	std::string strline;

	
	while (file.good())
	{
		std::getline( file, strline );

		if (!strline.empty())
		{
			result.push_back( strline );
		}
	}

	return result;
}


int main( int argc, char* argv[] )
{
	try
	{
		const auto lparams = ReadMainParams( argc, argv );


		//std::unique_ptr<TAoC_Solver> solver = std::make_unique<TAoCS_2015_01_A>();
		std::unique_ptr<TAoC_Solver> solver = std::make_unique<y15::TAoCS_02_A>();

		const int YEAR = 2015;
		const int DAY = 2;
		const char PART = 'A';

		/**/
		bool force_test = false;
		/*/
		bool force_test = true;
		//*/


		if (force_test || lparams.size() < 2)
		{
			const auto restest = solver->Test();

			Print_TestResults( restest );
		}
		else
		{
			const auto fpath = fmt::format( "{}\\{}\\{:02}\\input.txt", lparams[1], YEAR, DAY );
			const auto input = Read_Input( fpath );

			const auto result = solver->Solve( input );

			fmt::print( "Question {} {:02} {} - Result: {}\n", YEAR, DAY, PART, result );
		}
	}
	
	catch (std::exception e)
	{
		fmt::print( " * EXCEPTION: {}\n", e.what() );
	}


	return 0;
}

