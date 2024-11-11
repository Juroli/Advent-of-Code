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

		if (lparams.size() > 1)
		{
			const auto fpath = lparams[1] + R"(\2015\01\input.txt)";
			const auto input = Read_Input( fpath );

			TAoCS_2015_01 solver;

			const auto result = solver.Solve_A( input );

			fmt::print( "Question 2015 01 A - Result: {}\n", result );
		}
		else
		{
			TAoCS_2015_01 aoc_day;

			const auto restest = aoc_day.Test_A();

			Print_TestResults( restest );
		}
	}
	
	catch (std::exception e)
	{
		fmt::print( " * EXCEPTION: {}\n", e.what() );
	}


	return 0;
}

