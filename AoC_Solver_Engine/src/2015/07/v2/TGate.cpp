#include "TGate.hpp"



namespace y15::d07::v2
{


BGate::BGate( std::string_view name )
	: m_Name( name )
{
}


void TGateList::AddGate( std::unique_ptr<BGate>&& gate )
{
	m_LGates.push_back( std::move( (gate) ) );
}

bool TGateList::IsLinked() const
{
	for (const auto& curr : m_LGates)
	{
		if (!curr->IsLinked())
		{
			return false;
		}
	}

	return true;
}


//__________________________________________________________________________________________________


TGate_Fixed::TGate_Fixed( std::string_view name, const TSignal& signal )
	: BGate( name )
	, m_Value( signal )
{
}


bool TGate_Fixed::IsLinked() const
{
	return true;
}

int TGate_Fixed::Level() const
{
	return 0;
}

TSignal TGate_Fixed::ReadSignal() const
{
	return m_Value;
}


//__________________________________________________________________________________________________


TGate_Link::TGate_Link( std::string_view gate_name, std::string_view in_name )
	: BGate( gate_name )
	, m_Input( in_name )
{
}

bool TGate_Link::IsLinked() const
{
	return m_Input.IsLinked();
}

int TGate_Link::Level() const
{
	return m_Input.Level();
}

TSignal TGate_Link::ReadSignal() const
{
	return m_Input.ReadSignal();
}


//__________________________________________________________________________________________________


TGate_NOT::TGate_NOT( std::string_view gate_name, std::string_view in_name )
	: BGate( gate_name )
	, m_Input( in_name )
{
}

bool TGate_NOT::IsLinked() const
{
	return m_Input.IsLinked();
}

int TGate_NOT::Level() const
{
	return m_Input.Level();
}

TSignal TGate_NOT::ReadSignal() const
{
	return ~m_Input.ReadSignal();
}


//__________________________________________________________________________________________________


TGate_AND::TGate_AND( std::string_view gate_name, std::string_view in1_name, std::string_view in2_name )
	: BGate( gate_name )
	, m_Input_1( in1_name )
	, m_Input_2( in2_name )
{
}

bool TGate_AND::IsLinked() const
{
	return (m_Input_1.IsLinked() && m_Input_2.IsLinked());
}

int TGate_AND::Level() const
{
	return std::max( m_Input_1.Level(), m_Input_2.Level() );
}

TSignal TGate_AND::ReadSignal() const
{
	return m_Input_1.ReadSignal() & m_Input_2.ReadSignal();
}


//__________________________________________________________________________________________________


TGate_OR::TGate_OR( std::string_view gate_name, std::string_view in1_name, std::string_view in2_name )
	: BGate( gate_name )
	, m_Input_1( in1_name )
	, m_Input_2( in2_name )
{
}

bool TGate_OR::IsLinked() const
{
	return (m_Input_1.IsLinked() && m_Input_2.IsLinked());
}

int TGate_OR::Level() const
{
	return std::max( m_Input_1.Level(), m_Input_2.Level() );
}

TSignal TGate_OR::ReadSignal() const
{
	return m_Input_1.ReadSignal() | m_Input_2.ReadSignal();
}


//__________________________________________________________________________________________________


TGate_LSHIFT::TGate_LSHIFT( std::string_view gate_name, std::string_view in_name, int offset )
	: BGate( gate_name )
	, m_Input( in_name )
	, m_Offset( offset )
{
}

bool TGate_LSHIFT::IsLinked() const
{
	return m_Input.IsLinked();
}

int TGate_LSHIFT::Level() const
{
	return m_Input.Level();
}

TSignal TGate_LSHIFT::ReadSignal() const
{
	return m_Input.ReadSignal() << m_Offset;
}


//__________________________________________________________________________________________________


TGate_RSHIFT::TGate_RSHIFT( std::string_view gate_name, std::string_view in_name, int offset )
	: BGate( gate_name )
	, m_Input( in_name )
	, m_Offset( offset )
{
}

bool TGate_RSHIFT::IsLinked() const
{
	return m_Input.IsLinked();
}

int TGate_RSHIFT::Level() const
{
	return m_Input.Level();
}

TSignal TGate_RSHIFT::ReadSignal() const
{
	return m_Input.ReadSignal() >> m_Offset;
}


}

