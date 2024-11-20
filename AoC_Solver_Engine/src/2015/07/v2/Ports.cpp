
#include "Ports.hpp"

namespace y15::d07::v2
{




TPortIn::TPortIn()
	: m_OutPort( nullptr )
{
}


void TPortIn::Link( const TPortOut* aport ) noexcept
{
	m_OutPort = aport;
}

TSignal TPortIn::ReadSignal() const
{
	return m_OutPort->ReadSignal();
}


}
