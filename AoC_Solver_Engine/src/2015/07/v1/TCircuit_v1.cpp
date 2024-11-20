
#include "TCircuit_v1.hpp"


namespace y15::d07::v1
{



TCircuit::TCircuit()
{

}


bool TCircuit::AddWire( std::unique_ptr<BWire>&& pwire )
{

	for (const auto& curr : m_WiresList)
	{
		if (curr->Name() == pwire->Name())
		{
			return false;
		}
	}

	i_InsertWire( std::move( pwire ) );

	return true;
}


bool TCircuit::ReplaceWire( std::unique_ptr<BWire>&& pwire )
{
	auto found = false;

	for (const auto& curr : m_WiresList)
	{
		if (curr->Name() == pwire->Name())
		{
			found = true;
		}
	}

	if (!found)
	{
		return false;
	}

	i_RemoveWire( pwire->Name() );

	i_InsertWire( std::move( pwire ) );

	for (auto& curr : m_WiresList)
	{
		curr->ForceRecalc();
	}

	return true;
}

uint16_t TCircuit::Value( const std::string& pwire )
{
	const auto res = i_FindWire( pwire );
	if (res == nullptr
		|| !res->IsLinked())		//  Node() == nullptr)
	{
		return 0;
	}

	//	return res->Node()->Value(1);
	return res->Value( 1 );
}

const BWire* TCircuit::i_FindWire( const std::string& pname )
{
	auto res = std::find_if( m_WiresList.begin(), m_WiresList.end(),
		[&pname]( const std::unique_ptr<BWire>& pa ) { return (pa->Name() == pname); } );
	if (res == m_WiresList.end())
	{
		return nullptr;
	}

	return res->get();
}




void TCircuit::i_InsertWire( std::unique_ptr<BWire>&& pwire )
{

	for (auto& curr : m_WiresList)
	{
		pwire->CheckLink_Input_Node( curr.get() );

		if (!curr->IsLinked())
		{
			curr->CheckLink_Input_Node( pwire.get() );
		}
	}

	m_WiresList.push_back( std::move( pwire ) );

	i_SortWireList();

}


void TCircuit::i_RemoveWire( const std::string& pwname )
{
	auto wfind = std::find_if( m_WiresList.begin(), m_WiresList.end()
		, [pwname]( const TWirePtr& pv ) { return (pv->Name() == pwname); } );

	i_RemoveWire( wfind );
}

void TCircuit::i_RemoveWire( const TWiresVector::const_iterator& piter )
{
	if (piter == m_WiresList.end())
	{
		return;
	}

	const auto wireptr = (*piter).get();

	for (auto& curr : m_WiresList)
	{
		curr->Unlink( wireptr );
	}

	m_WiresList.erase( piter );

	i_SortWireList();
}

void TCircuit::i_SortWireList()
{
	std::sort( m_WiresList.begin(), m_WiresList.end()
		, []( const std::unique_ptr<BWire>& p1, const std::unique_ptr<BWire>& p2 )
		{
			return (p1->Level() < p2->Level());
		}
	);
}

}


