
#include "y15d07_TInputParser.hpp"

#include "Utils/Strings/Misc.hpp"



namespace y15::d07
{

TInputParser::TInputParser( std::string_view input )
	: m_Parser( input )
{
}

std::unique_ptr<BGate> TInputParser::Extract_NextGate()
{
	while( m_Parser)
	{
		auto curr = m_Parser.Extract_Line();

		auto gate = i_CreateGate_FromLine( curr );

		if (gate != nullptr)
		{
			return gate;
		}
	}

	return nullptr;
}


TPtrPort TInputParser::i_CreatePort( std::string_view input )
{
	if (input.find_first_not_of( "0123456789" ) == std::string::npos)
	{
		// costante
		const auto value = static_cast<uint16_t>(std::stoul( std::string( input ) ));
		return std::make_unique<TInPort_Fixed>( value );
	}

	return std::make_unique<TInPort_Wire>( input );
}

std::unique_ptr<BGate> TInputParser::i_CreateGate( std::string_view wire_name, std::string_view gate_def )
{

	auto pos = gate_def.find( ' ' );

	if (pos == std::string::npos)
	{
		// Parametro unico, dev'essere una costante o un link

		//if (gate_def.find_first_not_of("0123456789") == std::string::npos)
		//{
		//	// costante
		//	auto value = static_cast<uint16_t>(std::stoul( std::string( gate_def ) ));

		//	return std::make_unique<TGate_Fixed>( wire_name, value );
		//}
		//else
		//{

		//	return std::make_unique<TGate_Link>( wire_name, gate_def );

		//}

		return std::make_unique<TGate_Link>( wire_name, i_CreatePort( gate_def ) );
	}


	const auto firststr = gate_def.substr( 0, pos );
	const auto tmpstr = gate_def.substr( pos + 1 );

	if (firststr.empty())
	{
		return nullptr;
	}

	if (firststr == "NOT")
	{
		// Operazione NOT
		return std::make_unique<TGate_NOT>( wire_name, i_CreatePort( tmpstr ) );
	}

	pos = tmpstr.find( ' ' );
	auto oper = tmpstr.substr( 0, pos );
	auto secondstr = tmpstr.substr( pos + 1 );

	if (secondstr.empty())
	{
		return nullptr;
	}


	if (oper == "AND")
	{
		return std::make_unique<TGate_AND>( wire_name, i_CreatePort( firststr ), i_CreatePort( secondstr ) );
	}

	if (oper == "OR")
	{
		return std::make_unique<TGate_OR>( wire_name, i_CreatePort( firststr ), i_CreatePort( secondstr ) );
	}


	if (oper == "LSHIFT")
	{
		//auto offset = std::stoul( std::string( secondstr ) );

		return std::make_unique<TGate_LSHIFT>( wire_name, i_CreatePort( firststr ), i_CreatePort( secondstr ) );	// offset );
	}

	if (oper == "RSHIFT")
	{
		//auto offset = std::stoul( std::string( secondstr ) );

		return std::make_unique<TGate_RSHIFT>( wire_name, i_CreatePort( firststr ), i_CreatePort( secondstr ) );	// offset );
	}

	return nullptr;
}


std::unique_ptr<BGate> TInputParser::i_CreateGate_FromLine( std::string_view line )
{
	if (line.empty())
	{
		return nullptr;
	}

	const auto posarrow = line.find( "->" );

	if (posarrow == std::string::npos)
	{
		return nullptr;
	}

	const auto gate_def = trim_copy( line.substr( 0, posarrow ) );
	const auto wire_name = trim_copy( line.substr( posarrow + 2 ) );

	if (gate_def.empty() || wire_name.empty())
	{
		return nullptr;
	}

	//auto upgate = i_CreateGate( wire_name, gate_def );

	//if (pgate == nullptr)
	//{
	//	return;
	//}

	//m_LWires.AddWire( wire_name, gate_def, pgate.get() );
	//m_LGates.AddGate( std::move( pgate ) );
	//m_LGate_ToProcess.push_back( pgate.get() );
	//i_AddGate( std::move( pgate ) );
	//i_AddGate( std::move( upgate ) );

	return i_CreateGate( wire_name, gate_def );
}


}
