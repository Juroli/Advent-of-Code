
#include "TCircuit.hpp"

#include "Utils/Strings/Misc.hpp"


namespace y15::d07::v2
{



void TCircuit::ParseLine( std::string_view line )
{
	if (line.empty())
	{
		return;
	}

	const auto posarrow = line.find( "->" );

	if (posarrow != std::string::npos)
	{
		const auto gate_def = trim_copy( line.substr( 0, posarrow ) );
		const auto wire_name = trim_copy( line.substr( posarrow + 2 ) );

		const auto out_port = i_AddGate( gate_def );
		i_AddWire( wire_name, gate_def, out_port );
		
	}

	return;

}

bool TCircuit::IsReady() const noexcept
{
	return m_LGates.IsLinked();
}

TSignal TCircuit::Value( std::string_view wire_name ) const
{
	const auto wire = m_LWires.FindWire( wire_name );

	if (wire == nullptr)
	{
		throw std::exception( "Invalid wire name" );
	}

	return wire->ReadSignal();
}

std::vector<TWireInfo> TCircuit::WireInfo_Snapshot() const
{
	return m_LWires.Info_Snapshot();
}




std::unique_ptr<BGate> TCircuit::i_CreateGate( std::string_view gate_def )
{

	auto pos = gate_def.find( ' ' );

	if (pos == std::string::npos)
	{
		// Parametro unico, dev'essere una costante o un link
		
		if (gate_def.find_first_not_of("0123456789") == std::string::npos)
		{
			// costante
			auto value = static_cast<uint16_t>(std::stoul( std::string( gate_def ) ));

			return std::make_unique<TGate_Fixed>( gate_def, value );
		}
		else
		{

			return std::make_unique<TGate_Link>( gate_def, gate_def );

		}
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
		return std::make_unique<TGate_NOT>( gate_def, tmpstr );
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
		return std::make_unique<TGate_AND>( gate_def, firststr, secondstr );
	}

	if (oper == "OR")
	{
		return std::make_unique<TGate_OR>( gate_def, firststr, secondstr );
	}


	if (oper == "LSHIFT")
	{
		auto offset = std::stoul( std::string( secondstr ) );

		return std::make_unique<TGate_LSHIFT>( gate_def, firststr, offset );
	}

	if (oper == "RSHIFT")
	{
		auto offset = std::stoul( std::string( secondstr ) );

		return std::make_unique<TGate_RSHIFT>( gate_def, firststr, offset );
	}

	return nullptr;
}


const TOutPort* TCircuit::i_AddGate( std::string_view gate_def )
{
	auto work_ptr = i_CreateGate( gate_def );

	if (work_ptr == nullptr)
	{
		return nullptr;
	}

	const TOutPort* oport = work_ptr.get();

	m_LGates.AddGate( std::move( work_ptr ) );

	return oport;
}

void TCircuit::i_AddWire( std::string_view wire_name, std::string_view in_name, const TOutPort* out_port )
{
	m_LWires.AddWire( wire_name, in_name, out_port );
}




}




