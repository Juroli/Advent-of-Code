
#include "Ports.hpp"




namespace y15::d07
{



TInPort_Wire::TInPort_Wire( std::string_view in_name )
	: m_InName( in_name )
	, m_InWire( nullptr )
{
}


TMeta TInPort_Wire::MetaData() const noexcept
{
	if (!IsLinked())
	{
		return { false, 0 };
	}

	return { m_InWire->IsReady(), m_InWire->Level() + 1};
}


bool TInPort_Wire::LinkInput( const TLPWire_Sorted& lista_wire ) noexcept
{
	if (!IsLinked())
	{
		m_InWire = lista_wire.FindWire( m_InName );
		return m_InWire != nullptr;
	}
	
	return false;
}


TSignal TInPort_Wire::ReadSignal() const
{
	if (!IsLinked())
	{
		throw std::exception( "Unlinked gate" );
	}
	return m_InWire->Value();
}



}
