
#include "TCircuit.hpp"

#include "Utils/Strings/Misc.hpp"

#include "fmt/format.h"

#include <algorithm>


namespace y15::d07::v2
{



void TCircuit::AddFromLine( std::string_view line )
{
	if (line.empty())
	{
		return;
	}

	const auto posarrow = line.find( "->" );

	if (posarrow == std::string::npos)
	{
		return;
	}

	const auto gate_def = trim_copy( line.substr( 0, posarrow ) );
	const auto wire_name = trim_copy( line.substr( posarrow + 2 ) );

	if ( gate_def.empty() || wire_name.empty() )
	{
		return;
	}

	//auto pgate = i_CreateGate( wire_name, gate_def );

	//if (pgate == nullptr)
	//{
	//	return;
	//}

	//m_LWires.AddWire( wire_name, gate_def, pgate.get() );
	//m_LGates.AddGate( std::move( pgate ) );
	//m_LGate_ToProcess.push_back( pgate.get() );
	//i_AddGate( std::move( pgate ) );
	i_AddGate( i_CreateGate( wire_name, gate_def ) );
	
	return;
}


bool TCircuit::IsReady() const noexcept
{
	//return m_LGates.IsLinked();

	if (!m_LGatePile.empty())
	{
		return false;
	}

	for (const auto& curr : m_LGateReady)
	{
		if (!curr->IsReady())
		{
			return false;
		}
	}

	return true;
}

//void TCircuit::BuildCircuit()
//{
//	//std::vector<BGate*> worklist;
//
//
//	size_t moved_gates = 1;
//
//	while (moved_gates > 0)
//	{
//		moved_gates = 0;
//		//auto itnew = m_LNewGates.begin();
//
//		//while (itnew != m_LNewGates.end())
//		for (auto& g_curr : m_LGatePile)
//		{
//			//const auto work_ptr = itnew->get();
//			if ( g_curr->IsReady())
//			{
//				//worklist.push_back( work_ptr );
//				m_LGateReady.push_back( g_curr );
//
//				++moved_gates;
//
//				//itnew = m_LNewGates.erase( itnew );
//			
//				for (const auto& tp_curr : m_LGatePile)
//				{
//					if (tp_curr != nullptr)
//					{
//						tp_curr->ProposeInputWire( g_curr );
//					}
//				}
//
//				g_curr = nullptr;
//			}
//			//else
//			//{
//			//	++itnew;
//			//}
//		}
//
//		m_LGatePile.erase( std::remove( m_LGatePile.begin(), m_LGatePile.end(), nullptr ), m_LGatePile.end());
//
//		//for (const auto& work_gate : worklist)
//		//{
//		//	for (const auto& new_gate : m_LNewGates)
//		//	{
//		//		new_gate->ProposeWire( work_gate );
//		//	}
//		//}
//
//		//moved_gates = worklist.size();
//
//		//worklist.clear();
//
//	}
//
//	if (!m_LGatePile.empty())
//	{
//		throw std::exception( "Unused gates" );
//	}
//}


TSignal TCircuit::Value( std::string_view wire_name ) const
{
	int curr_maxlvl = 0;

	for (const auto& curr : m_LGateReady)
	{
		if (!curr->IsReady())
		{
			throw std::exception( "Wire not ready" );
		}

		if (curr->Level() > curr_maxlvl)
		{
			curr_maxlvl = curr->Level();
		}

		if (curr->Level() < curr_maxlvl)
		{
			auto DEBUG_a = 0;
		}

		if (curr->Name() == wire_name)
		{
			return curr->Value();
		}
	}

	throw std::exception( "Invalid wire name" );

	//const auto wire = m_LGates.FindWire( wire_name );
	//const auto wpos = std::find_if( m_LGate.begin(), m_LGate.end(), [&wire_name]( const BGate* w ) { return (w->Name() == wire_name); } );

	//if (wpos == m_LGate.end())
	//{
	//	throw std::exception( "Invalid wire name" );
	//}

	//return (*wpos)->Value();
}


std::vector<TWireInfo> TCircuit::WireInfo_Snapshot() const
{
	//return m_LGates.WireInfo_Snapshot();
	std::vector<TWireInfo> result;

	for (const auto& curr : m_LGateReady)
	{
		if (curr == nullptr)
		{
			throw std::exception( "CRITICAL ERROR (1507 TCirc): Wires list corrupted!" );
		}

		result.push_back( { curr->Name(), curr->Value() } );
	}

	std::sort( result.begin(), result.end(), []( const v2::TWireInfo& p1, v2::TWireInfo& p2 )
		{ return (p1.Name < p2.Name); }
	);

	return result;
}

std::string TCircuit::PrintInput()
{
	std::string result;

	for (const auto& curr : m_GatesHolder)
	{
		result += fmt::format( "{}\n", curr->to_string() );
	}

	return result;
}




TPtrPort TCircuit::i_CreatePort( std::string_view input )
{
	if ( input.find_first_not_of( "0123456789" ) == std::string::npos)
	{
		// costante
		const auto value = static_cast<uint16_t>(std::stoul( std::string( input ) ));
		return std::make_unique<TInPort_Fixed>( value );
	}

	return std::make_unique<TInPort_Wire>( input );
}

std::unique_ptr<BGate> TCircuit::i_CreateGate( std::string_view wire_name, std::string_view gate_def )
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

void TCircuit::i_AddGate( std::unique_ptr<BGate> gate )
{
	if (gate == nullptr)
	{
		return;
	}

	auto locptr = gate.get();

	//m_LNewGates.AddGate( std::move( gate ) );
	m_GatesHolder.push_back( std::move( gate ) );

	for (const auto& curr : m_LGateReady)
	{
		//curr->ProposeInputWire( locptr );
		locptr->ProposeInputWire( curr );
	}

	if(locptr->IsReady())
	{
		i_TransferToReady( locptr );

		//const auto ins_pos = std::upper_bound( m_LGateReady.begin(), m_LGateReady.end(), locptr,
		//	[]( const BGate* pa, const BGate* pb ) { return pa->Level() < pb->Level(); }
		//);

		//m_LGateReady.insert( ins_pos, locptr );

		//i_ProposeToPile( locptr );

		i_ProcessPile();
	}
	else
	{
		m_LGatePile.push_back( locptr );
	}
}

void TCircuit::i_ProcessPile()
{
	size_t moved_gates = 1;

	while (moved_gates > 0)
	{
		moved_gates = 0;
		//auto itnew = m_LNewGates.begin();

		//while (itnew != m_LNewGates.end())
		for (auto& g_curr : m_LGatePile)
		{
			//const auto work_ptr = itnew->get();
			if (g_curr->IsReady())
			{

				++moved_gates;

				auto locptr = g_curr;
				g_curr = nullptr;

				i_TransferToReady( locptr );
			}
			//else
			//{
			//	++itnew;
			//}
		}

		m_LGatePile.erase( std::remove( m_LGatePile.begin(), m_LGatePile.end(), nullptr ), m_LGatePile.end() );

		//for (const auto& work_gate : worklist)
		//{
		//	for (const auto& new_gate : m_LNewGates)
		//	{
		//		new_gate->ProposeWire( work_gate );
		//	}
		//}

		//moved_gates = worklist.size();

		//worklist.clear();

	}
}

void TCircuit::i_TransferToReady( BGate* gate )
{
	//m_LGateReady.push_back( gate );
	const auto ins_pos = std::upper_bound( m_LGateReady.begin(), m_LGateReady.end(), gate,
		[]( const BGate* pa, const BGate* pb ) { return pa->Level() < pb->Level(); }
	);
	m_LGateReady.insert( ins_pos, gate );


	for (const auto& tp_curr : m_LGatePile)
	{
		if (tp_curr != nullptr)
		{
			tp_curr->ProposeInputWire( gate );
		}
	}
}




//const TOutPort* TCircuit::i_AddGate( std::string_view gate_def )
//{
//	auto work_ptr = i_CreateGate( gate_def );
//
//	if (work_ptr == nullptr)
//	{
//		return nullptr;
//	}
//
//	const TOutPort* oport = work_ptr.get();
//
//	m_LGates.AddGate( std::move( work_ptr ) );
//
//	return oport;
//}
//
//void TCircuit::i_AddWire( std::string_view wire_name, std::string_view in_name, const TOutPort* out_port )
//{
//	m_LWires.AddWire( wire_name, in_name, out_port );
//}




}




