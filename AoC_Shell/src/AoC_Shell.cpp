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


std::string Read_Input( const std::string& path )
{
	std::ifstream file( path );
	if (!file.good())
	{
		throw std::exception( "File not found!" );
	}
	std::string strline;

	
	if (file.good())
	{
		std::getline( file, strline );
		return strline;
	}

	return {};
}


int main( int argc, char* argv[] )
{
	try
	{
		const auto lparams = ReadMainParams( argc, argv );


		//std::unique_ptr<TAoC_Solver> solver = std::make_unique<TAoCS_2015_01_A>();
		std::unique_ptr<TAoC_Solver> solver = std::make_unique<TAoCS_2015_01_B>();

		bool force_test = false;


		if (force_test || lparams.size() < 2)
		{
			const auto restest = solver->Test();

			Print_TestResults( restest );
		}
		else
		{
			const auto fpath = lparams[1] + R"(\2015\01\input.txt)";
			const auto input = Read_Input( fpath );

			const auto result = solver->Solve( input );

			fmt::print( "Question 2015 01 A - Result: {}\n", result );
		}
	}
	
	catch (std::exception e)
	{
		fmt::print( " * EXCEPTION: {}\n", e.what() );
	}


	return 0;
}

