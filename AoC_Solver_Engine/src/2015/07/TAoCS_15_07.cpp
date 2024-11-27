

#include "TAoCS_15_07.h"

#include <vector>
#include "fmt/format.h"


#include "v1/TCircuit_v1.hpp"
#include "v2/TCircuit.hpp"

#include "y15d07_TInputParser.hpp"


namespace y15::d07
{

//using namespace y15::d07::v2;


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


std::string TAoCS_P1::ListWires_v1( std::string_view input ) const
{
	v1::TCircuit circuit;

	TStringParser parser( input );

	while (parser)
	{
		auto curr = parser.Extract_Line();

		auto currwire = v1::BWire::Create_Wire( curr );

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

std::string TAoCS_P1::ListWires_v2( std::string_view input ) const
{
	v2::TCircuit circuit;

	//TStringParser parser( input );
	TInputParser parser( input );

	while (parser)
	{
		//auto curr = parser.Extract_Line();

		//auto gate = v2::TCircuit::CreateGate_FromLine( curr );

		auto gate = parser.Extract_NextGate();

		if (gate)
		{
			circuit.AddGate( std::move(gate) );
		}
	}

	//circuit.BuildCircuit();

	if (!circuit.IsReady())
	{
		throw std::exception("Circuit is not ready.");
	}

	auto snapshot = circuit.WireInfo_Snapshot();


	std::string result;

	for (const auto& curr : snapshot)
	{
		result += fmt::format( "{}: {}\n", curr.Name, curr.Value );
	}

	return result;
}


//std::string TAoCS_P1::i_Solve_Run() const
//{
//	return STR_IMPLEMENTED;
//}


std::string TAoCS_P1::i_Solve_Run( std::string_view input ) const
{
	if (input == STR_SOLVE_CHECK)
	{
		return STR_IMPLEMENTED;
	}

	v2::TCircuit circuit;

	//TStringParser parser( input );
	TInputParser parser( input );

	while (parser)
	{
		//auto curr = parser.Extract_Line();


		/*		CIRCUIT V1		*
		auto currwire = BWire::Create_Wire( curr );

		if (currwire)
		{
			circuit.AddWire( std::move( currwire ) );
		}
		/*/

		//circuit.AddFromLine( curr );
		auto gate = parser.Extract_NextGate();

		if (gate)
		{
			circuit.AddGate( std::move( gate ) );
		}


		//*/
	}

	//circuit.BuildCircuit();

	return std::to_string( circuit.Value( "a" ) );

}


TTestInput_Group TAoCS_P1::i_Test_Prepare() const
{

	return {
		TTestInput::Create_Example( "Ex01",
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
		),
	};
}


std::string TAoCS_P1::i_Test_Run( std::string_view astrin ) const
{
	//return ListWires_v1( astrin );
	return ListWires_v2( astrin );
}



//__________________________________________________________________________________________________



//std::string TAoCS_P2::i_Solve_Run() const
//{
//	return STR_NOT_IMPLEMENTED;
//}


std::string TAoCS_P2::i_Solve_Run( std::string_view input ) const
{
	if (input == STR_SOLVE_CHECK)
	{
		return STR_NOT_IMPLEMENTED;
	}

	v1::TCircuit circuit;

	TStringParser parser( input );

	while (parser)
	{
		auto curr = parser.Extract_Line();

		auto currwire = v1::BWire::Create_Wire( curr );

		if (currwire)
		{
			circuit.AddWire( std::move( currwire ) );
		}
	}

	auto a_value = circuit.Value( "a" );

	std::string strwire = std::to_string( a_value ) + "->b";

	auto newwire = v1::BWire::Create_Wire( strwire );

	if (newwire)
	{
		circuit.ReplaceWire( std::move( newwire ) );
	}

	return std::to_string( circuit.Value( "a" ));
}


TTestInput_Group TAoCS_P2::i_Test_Prepare() const
{
	return {};
}


std::string TAoCS_P2::i_Test_Run( std::string_view astrin ) const
{
	return Solve( astrin );
}


//__________________________________________________________________________________________________


}

