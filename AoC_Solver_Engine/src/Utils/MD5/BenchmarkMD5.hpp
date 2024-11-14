
#pragma once


#include <string>


namespace libMD5
{

std::string Benchmark_TMD5( const std::string& str );
std::string Benchmark_cMD5( std::string& str );

void Benchmark_Compare();

}

