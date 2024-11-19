

#include "TAoCS_15_07.h"

#include <vector>
#include "fmt/format.h"

#include "Utils/Strings/TStringParser.hpp"
#include "TCircuit.hpp"



namespace y15::d07
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


std::string TAoCS_P1::Test( std::string_view input ) const
{
	TCircuit circuit;

	TStringParser parser( input );

	while (parser)
	{
		auto curr = parser.Extract_Line();

		auto currwire = BWire::Create_Wire( curr );

		if (currwire)
		{
			circuit.AddWire( std::move( currwire ) );
		}
	}


	struct TWireStatus
	{
		std::string Name;
		uint16_t Signal;
	};


	std::vector<TWireStatus> snapshot;

	for (const auto& curr : circuit.LWires())
	{
		snapshot.push_back( { curr->Name(), curr->Value( 1 ) } );
	}

	std::sort( snapshot.begin(), snapshot.end(), []( const TWireStatus& p1, TWireStatus& p2 ) { return (p1.Name < p2.Name); } );

	std::string result;

	for (const auto& curr : snapshot)
	{
		result += fmt::format( "{}: {}\n", curr.Name, curr.Signal );
	}

	return result;
}

EImpl TAoCS_P1::Implemented() const noexcept
{
	return EImpl::FULL;
}


std::string TAoCS_P1::Solve( const std::string& input ) const
{

	TCircuit circuit;

	TStringParser parser( input );

	while (parser)
	{
		auto curr = parser.Extract_Line();

		auto currwire = BWire::Create_Wire( curr );

		if (currwire)
		{
			circuit.AddWire( std::move( currwire ) );
		}
	}

	return std::to_string( circuit.Value( "a" ) );

}


TTestResult_Group TAoCS_P1::Test() const
{

	TTestInput_Group ltests = {
		{ 
			"123 -> x\n"
			"456->y\n"
			"x AND y->d\n"
			"x OR y->e\n"
			"x LSHIFT 2->f\n"
			"y RSHIFT 2->g\n"
			"NOT x->h\n"
			"NOT y->i\n"
			, 
			"d: 72\n"
			"e: 507\n"
			"f: 492\n"
			"g: 114\n"
			"h: 65412\n"
			"i: 65079\n"
			"x: 123\n"
			"y: 456\n"
		},
	};

	return o_RunTests( ltests, [this]( const std::string& str ) { return Test( str ); } );
}


//__________________________________________________________________________________________________


EImpl TAoCS_P2::Implemented() const noexcept
{
	return EImpl::TEST;
}

std::string TAoCS_P2::Solve( const std::string& input ) const
{
	TCircuit circuit;

	TStringParser parser( input );

	while (parser)
	{
		auto curr = parser.Extract_Line();

		auto currwire = BWire::Create_Wire( curr );

		if (currwire)
		{
			circuit.AddWire( std::move( currwire ) );
		}
	}

	auto a_value = circuit.Value( "a" );

	std::string strwire = std::to_string( a_value ) + "->b";

	auto newwire = BWire::Create_Wire( strwire );

	if (newwire)
	{
		circuit.ReplaceWire( std::move( newwire ) );
	}

	return std::to_string( circuit.Value( "a" ));
}

TTestResult_Group TAoCS_P2::Test() const
{
	TTestInput_Group ltests = {
	};

	return o_RunTests( ltests, [this]( const std::string& str ) { return Solve( str ); } );
}


//__________________________________________________________________________________________________


}

