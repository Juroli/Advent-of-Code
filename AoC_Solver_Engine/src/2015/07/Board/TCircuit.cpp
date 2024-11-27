
#include "TCircuit.hpp"

#include "fmt/format.h"

#include <algorithm>




namespace y15::d07
{




bool TCircuit::AddGate( std::unique_ptr<BGate> gate )
{

	if (gate == nullptr)
	{
		return false;
	}

	const auto wire = m_LWireReady.FindWire( gate->Name() );

	if (wire == nullptr)
	{
		i_AddGate( std::move( gate ) );
		return true;
	}

	return false;
}


bool TCircuit::IsReady() const noexcept
{

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


TSignal TCircuit::Value( std::string_view wire_name ) const
{

	const auto pwire = m_LWireReady.FindWire( wire_name );

	if (pwire == nullptr)
	{
		throw std::exception( "Invalid wire name" );
	}

	return pwire->Value();
}


std::vector<TWireInfo> TCircuit::WireInfo_Snapshot() const
{

	return m_LWireReady.Info_Snapshot();
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




void TCircuit::i_AddGate( std::unique_ptr<BGate> gate )
{

	if (gate == nullptr)
	{
		return;
	}

	auto locptr = gate.get();

	m_GatesHolder.push_back( std::move( gate ) );

	for (const auto& curr : m_LGateReady)
	{
		locptr->LinkInput( m_LWireReady );
	}

	if(locptr->IsReady())
	{
		i_TransferToReady( locptr );

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

		for (auto& g_curr : m_LGatePile)
		{
			if (g_curr->IsReady())
			{

				++moved_gates;

				auto locptr = g_curr;
				g_curr = nullptr;

				i_TransferToReady( locptr );
			}
		}

		m_LGatePile.erase( std::remove( m_LGatePile.begin(), m_LGatePile.end(), nullptr ), m_LGatePile.end() );
	}
}


void TCircuit::i_TransferToReady( BGate* gate )
{

	m_LGateReady.Add( gate );
	m_LWireReady.Add( gate );

	for (const auto& tp_curr : m_LGatePile)
	{
		if (tp_curr != nullptr)
		{
			tp_curr->LinkInput( m_LWireReady );
		}
	}
}




}




