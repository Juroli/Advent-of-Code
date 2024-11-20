// AoC_Shell.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "gsl/narrow"
#include "fmt/core.h"

#include <fstream>
#include <sstream>

#include "AoC_Solver.hpp"


#include "Aoc_Utils.hpp"

#include "Test_Func.hpp"



const uint16_t FIRST_YEAR = 2015;
const uint16_t LAST_YEAR = 2023;


const uint8_t FIRST_DAY = 1;
const uint8_t LAST_DAY = 25;

const uint8_t FIRST_PART = 1;
const uint8_t LAST_PART = 2;



std::vector<std::string> ReadMainParams( int argc, char* argv[] )
{
	std::vector<std::string> result;

	for (auto i = 0; i < argc; ++i)
	{
		result.push_back( argv[i] );
	}

	return result;
}




TStringList Read_Input_old( const std::string& path )
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

std::string Read_Input( const std::string& path )
{
	std::ifstream t( path );
	std::stringstream buffer;

	buffer << t.rdbuf();

	return buffer.str();
}


void Test_libs()
{
	//TODO: Move the tests in a Unit Test Project.

	const auto restest = Test_TMD5();
	Print_TestResults( restest );

	fmt::print( "\n" );
}


void Bench_libs()
{
	libMD5::Benchmark_Compare();
}


void PrintImplementationTable()
{
	fmt::print( "     |" );

	for (auto d = FIRST_DAY; d <= LAST_DAY; ++d)
	{
		fmt::print( " {:2}", d );
	}
	fmt::print( "\n" );


	fmt::print( "-----+" );
	for (auto d = FIRST_DAY; d <= LAST_DAY; ++d)
	{
		fmt::print( "---" );
	}
	fmt::print( "\n" );


	for (auto y = FIRST_YEAR; y <= LAST_YEAR; ++y)
	{
		fmt::print( "{} |", y );

		for (auto d = FIRST_DAY; d <= LAST_DAY; ++d)
		{
			fmt::print( " " );
			for (auto p = FIRST_PART; p <= LAST_PART; ++p)
			{
				const auto solver = Get_Solver( { y, d, p } );
				const auto impl = solver->Implemented();

				switch (impl)
				{
				case EImpl::NONE: fmt::print( "-" ); break;
				case EImpl::TEST: fmt::print( "x" ); break;
				case EImpl::SOLUTION: fmt::print( "o" ); break;
				}
			}

		}

		fmt::print( "\n" );
	}

	fmt::print( "\n" );
}


int main( int argc, char* argv[] )
{
	try
	{
		const auto lparams = ReadMainParams( argc, argv );


		//Test_libs();
		//Bench_libs();

		PrintImplementationTable();

		if (false)
		{

			TPuzzleID pid_start = { 2015, 1, 1 };
			TPuzzleID pid_end = { 2015, 7, 2 };

			RunPrint_Tests( pid_start, pid_end );
		}

		//return 0;

		TPuzzleID pid = { 2015, 7, 2 };
		//const int YEAR = 2015;
		//const int DAY = 7;
		//const char PART = 'A';


		

		const auto test_ok = RunPrint_Test( pid );
		

		if( test_ok && lparams.size() > 1 )
		{
			const auto solver = Get_Solver( pid );

			const auto fpath = fmt::format( "{}\\{}\\{:02}\\input.txt", lparams[1], pid.Year, pid.Day );
			const auto input = Read_Input( fpath );

			const auto result = solver->Solve( input );

			fmt::print( "Result of 'input' file: {}\n", result );
		}
	}
	
	catch (std::exception e)
	{
		fmt::print( " * EXCEPTION: {}\n", e.what() );
	}


	return 0;
}

