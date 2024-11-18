
#include "TAoCS_yy_dd.h"

#include <vector>


namespace y00::d00
{


std::unique_ptr<TAoC_Solver> Get_Solver( uint8_t apart )
{
	switch (apart)
	{
	case 1: return std::make_unique< TAoCS_P1>();
	case 2: return std::make_unique< TAoCS_P2>();
	default: throw std::exception( "Invalid part." );
	}
}


//__________________________________________________________________________________________________


EImpl TAoCS_P1::Implemented() const noexcept
{
	return EImpl::NONE;
}


std::string TAoCS_P1::Solve( const std::string& input ) const
{
	return "* Not implemented! *";
}


TTestResult_Group TAoCS_P1::Test() const
{
	TTestInput_Group ltests = {
		{ "", ""},
		{ "", ""},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) { return Solve( str ); } );
}


//__________________________________________________________________________________________________


EImpl TAoCS_P2::Implemented() const noexcept
{
	return EImpl::NONE;
}


std::string TAoCS_P2::Solve( const std::string& input ) const
{
	return "* Not implemented! *";
}

TTestResult_Group TAoCS_P2::Test() const
{
	TTestInput_Group ltests = {
		{ "", ""},
		{ "", ""},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) { return Solve( str ); } );
}


//__________________________________________________________________________________________________


}

