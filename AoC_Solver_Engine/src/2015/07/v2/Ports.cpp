
#include "Ports.hpp"

namespace y15::d07::v2
{




TInPort_Wire::TInPort_Wire( std::string_view in_name )
	: m_InName( in_name )
	, m_InWire( nullptr )
{
}

TInPort_Wire::TInPort_Wire( std::string_view in_name, const TWire* aport )
	: m_InName( in_name )
	, m_InWire( aport )
{
}

//bool TInPort::IsReady() const noexcept
//{
//	return IsLinked() && m_OutWire->IsReady();
//}


TMeta TInPort_Wire::MetaData() const noexcept
{
	if (!IsLinked())
	{
		return { false, 0 };
	}

	return { m_InWire->Ready(), m_InWire->Level() + 1 };
}

void TInPort_Wire::CheckLink( const TWire* wire ) noexcept
{
	if (wire == nullptr)
	{
		return;
	}

	if(wire->Name() == m_InName )
	{
		m_InWire = wire;
	}
}

//void TInPort::Link( const TWire* aport ) noexcept
//{
//	
//}

TSignal TInPort_Wire::ReadSignal() const
{
	if (!IsLinked())
	{
		throw std::exception( "Unlinked gate" );
	}
	return m_InWire->Value();
}


}
