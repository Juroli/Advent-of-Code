
#include "BenchmarkMD5.hpp"

#include "gsl/gsl"

#include "nanobench.h"


#include "TMD5.hpp"

extern "C"
{

#include "orig_refactor/c/global.h"
#include "orig_refactor/c/md5.h"

}



namespace libMD5
{


std::string Benchmark_TMD5( const std::string& str )
{
	TMD5 check( str );
	return check.String();
}

std::string Benchmark_cMD5( std::string& str )
{
	MD5_CTX context;
	unsigned char digest[16];

	MD5Init( &context );
	MD5Update( &context, reinterpret_cast<unsigned char*>(str.data()), gsl::narrow_cast<unsigned int>(str.size()) );
	MD5Final( digest, &context );

	return { reinterpret_cast<char*>(digest) };
}


void Benchmark_Compare()
{
	ankerl::nanobench::Bench().run( "cMD5", [&] {

		//for(auto i = 0u; i < 1000000; ++i)
		{
			auto str = std::to_string( 1 );	// i );
			//const auto result = Bench_TMD5( std::to_string( i ) );
			const auto result = Benchmark_cMD5( str );
			ankerl::nanobench::doNotOptimizeAway( result );
		}
		} );

	ankerl::nanobench::Bench().run( "TMD5", [&] {

		//for (auto i = 0u; i < 1000000; ++i)
		{
			const auto result = Benchmark_TMD5( std::to_string( 1 ) );	// i ) );
			ankerl::nanobench::doNotOptimizeAway( result );
		}
		} );

}

}


