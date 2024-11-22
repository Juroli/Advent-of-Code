
#include "Ports.hpp"

namespace y15::d07::v2
{




TInPort::TInPort( std::string_view in_name )
	: m_InName( in_name )
	, m_OutPort( nullptr )
{
}

TInPort::TInPort( std::string_view in_name, const TOutPort* aport )
	: m_InName( in_name )
	, m_OutPort( aport )
{
}


int TInPort::Level() const noexcept
{
	if (!IsLinked())
	{
		return -1;
	}

	return m_OutPort->Level() + 1;
}

void TInPort::Link( const TOutPort* aport ) noexcept
{
	m_OutPort = aport;
}

TSignal TInPort::ReadSignal() const
{
	if (!IsLinked())
	{
		throw std::exception( "Unlinked gate" );
	}
	return m_OutPort->ReadSignal();
}


}
