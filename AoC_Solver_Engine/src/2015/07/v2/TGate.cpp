#include "TGate.hpp"

#include "fmt/format.h"


namespace y15::d07::v2
{


BGate::BGate( std::string_view wire_name )
	: TWire( wire_name )				//m_Name( name )
{
}


//void TGateList::AddGate( std::unique_ptr<BGate>&& gate )
//{
//	m_LGates.push_back( std::move( (gate) ) );
//}

//TWire* TGateList::FindWire( std::string_view name ) const noexcept
//{
//	const auto pos = std::find_if( m_LGates.begin(), m_LGates.end(), [&name]( const std::unique_ptr<BGate>& w ) { return (w->Name() == name); } );
//
//	if (pos == m_LGates.end())
//	{
//		return nullptr;
//	}
//
//	return pos->get();
//}

//bool TGateList::IsLinked() const
//{
//	for (const auto& curr : m_LGates)
//	{
//		if (!curr->IsLinked())
//		{
//			return false;
//		}
//	}
//
//	return true;
//}

//std::vector<TWireInfo> TGateList::WireInfo_Snapshot() const
//{
//	std::vector<TWireInfo> result;
//
//	for (const auto& curr : m_LGates)
//	{
//		if (curr == nullptr)
//		{
//			throw std::exception( "CRITICAL ERROR (1507 TCirc): Wires list corrupted!" );
//		}
//
//		result.push_back( { curr->Name(), curr->ReadSignal() } );
//	}
//
//	return result;
//}


//__________________________________________________________________________________________________


//TGate_Fixed::TGate_Fixed( std::string_view wire_name, const TSignal& signal )
//	: BGate( wire_name )
//	, m_Value( signal )
//{
//}


//bool TGate_Fixed::IsReady() const noexcept
//{
//	return true;
//}

//bool TGate_Fixed::IsLinked() const noexcept
//{
//	return true;
//}
//
//void TGate_Fixed::ProposeWire( const TWire* in_wire )
//{
//	return;
//}
//
//void TGate_Fixed::Update_Level()
//{
//	Set_MetaData( { false, 0 } );
//}
//
//TSignal TGate_Fixed::ReadSignal() const
//{
//	return m_Value;
//}
//
//std::string TGate_Fixed::to_string() const
//{
//
//	return fmt::format("{} -> {}", m_Value, Name() );
//}


//__________________________________________________________________________________________________


TGate_Link::TGate_Link( std::string_view wire_name, TPtrPort input )
	: BGate( wire_name )
	, m_Input( std::move(input) )
{
}

//bool TGate_Link::IsReady() const noexcept
//{
//	return m_Input.IsReady();
//}

bool TGate_Link::IsLinked() const noexcept
{
	return m_Input->IsLinked();
}

void TGate_Link::ProposeWire( const TWire* in_wire )
{
	m_Input->CheckLink( in_wire );
}

void TGate_Link::Update_Level()
{
	if(m_Input->IsLinked())
	{
		Set_MetaData( m_Input->MetaData() );
	}
}

std::string TGate_Link::to_string() const
{
	return fmt::format( "{} -> {}", m_Input->Name(), Name());
}


TSignal TGate_Link::i_ReadSignal() const
{
	return m_Input->ReadSignal();
}


//__________________________________________________________________________________________________


TGate_NOT::TGate_NOT( std::string_view wire_name, TPtrPort input )
	: BGate( wire_name )
	, m_Input( std::move( input ) )
{
}

bool TGate_NOT::IsLinked() const noexcept
{
	return m_Input->IsLinked();
}

void TGate_NOT::ProposeWire( const TWire* in_wire )
{
	m_Input->CheckLink( in_wire );
}

void TGate_NOT::Update_Level()
{
	if (m_Input->IsLinked())
	{
		Set_MetaData( m_Input->MetaData() );
	}
}

std::string TGate_NOT::to_string() const
{
	return fmt::format( "NOT {} -> {}", m_Input->Name(), Name() );
}


TSignal TGate_NOT::i_ReadSignal() const
{
	return ~m_Input->ReadSignal();
}



//__________________________________________________________________________________________________


TGate_AND::TGate_AND( std::string_view wire_name, TPtrPort input_1, TPtrPort input_2 )
	: BGate( wire_name )
	, m_Input_1( std::move( input_1 ) )
	, m_Input_2( std::move( input_2 ) )
{
}

bool TGate_AND::IsLinked() const noexcept
{
	return (m_Input_1->IsLinked() && m_Input_2->IsLinked());
}

void TGate_AND::ProposeWire( const TWire* in_wire )
{
	m_Input_1->CheckLink( in_wire );
	m_Input_2->CheckLink( in_wire );
}

void TGate_AND::Update_Level()
{
	if (m_Input_1->IsLinked() && m_Input_2->IsLinked())
	{
		const auto meta1 = m_Input_1->MetaData();
		const auto meta2 = m_Input_2->MetaData();

		Set_MetaData( { meta1.Ready && meta2.Ready
			, std::max( meta1.Level, meta2.Level )
			} );
	}
}

std::string TGate_AND::to_string() const
{
	return fmt::format( "{} AND {} -> {}", m_Input_1->Name(), m_Input_2->Name(), Name() );
}


TSignal TGate_AND::i_ReadSignal() const
{
	return m_Input_1->ReadSignal() & m_Input_2->ReadSignal();
}


//__________________________________________________________________________________________________


TGate_OR::TGate_OR( std::string_view wire_name, TPtrPort input_1, TPtrPort input_2 )
	: BGate( wire_name )
	, m_Input_1( std::move( input_1 ) )
	, m_Input_2( std::move( input_2 ) )
{
}

bool TGate_OR::IsLinked() const noexcept
{
	return (m_Input_1->IsLinked() && m_Input_2->IsLinked());
}

void TGate_OR::ProposeWire( const TWire* in_wire )
{
	m_Input_1->CheckLink( in_wire );
	m_Input_2->CheckLink( in_wire );
}

void TGate_OR::Update_Level()
{
	if (m_Input_1->IsLinked() && m_Input_2->IsLinked())
	{
		const auto meta1 = m_Input_1->MetaData();
		const auto meta2 = m_Input_2->MetaData();

		Set_MetaData( { meta1.Ready && meta2.Ready
			, std::max( meta1.Level, meta2.Level )
			} );
	}
}

std::string TGate_OR::to_string() const
{
	return fmt::format( "{} OR {} -> {}", m_Input_1->Name(), m_Input_2->Name(), Name() );
}


TSignal TGate_OR::i_ReadSignal() const
{
	return m_Input_1->ReadSignal() | m_Input_2->ReadSignal();
}


//__________________________________________________________________________________________________


TGate_LSHIFT::TGate_LSHIFT( std::string_view wire_name, TPtrPort input_1, TPtrPort input_2)	// int offset )
	: BGate( wire_name )
	, m_Input_1( std::move( input_1 ) )
	, m_Input_2( std::move( input_2 ) )
	//, m_Offset( offset )
{
}

bool TGate_LSHIFT::IsLinked() const noexcept
{
	return (m_Input_1->IsLinked() && m_Input_2->IsLinked());
}

void TGate_LSHIFT::ProposeWire( const TWire* in_wire )
{
	m_Input_1->CheckLink( in_wire );
	m_Input_2->CheckLink( in_wire );
}

void TGate_LSHIFT::Update_Level()
{
	if (m_Input_1->IsLinked() && m_Input_2->IsLinked())
	{
		const auto meta1 = m_Input_1->MetaData();
		const auto meta2 = m_Input_2->MetaData();

		Set_MetaData( { meta1.Ready && meta2.Ready
			, std::max( meta1.Level, meta2.Level )
			} );
	}
}

std::string TGate_LSHIFT::to_string() const
{
	return fmt::format( "{} LSHIFT {} -> {}", m_Input_1->Name(), m_Input_2->Name(), Name() );
}

TSignal TGate_LSHIFT::i_ReadSignal() const
{
	return m_Input_1->ReadSignal() << m_Input_2->ReadSignal();
}


//__________________________________________________________________________________________________


TGate_RSHIFT::TGate_RSHIFT( std::string_view wire_name, TPtrPort input_1, TPtrPort input_2 )		//int offset )
	: BGate( wire_name )
	, m_Input_1( std::move( input_1 ) )
	, m_Input_2( std::move( input_2 ) )
	//, m_Offset( offset )
{
}

bool TGate_RSHIFT::IsLinked() const noexcept
{
	return (m_Input_1->IsLinked() && m_Input_2->IsLinked());
}

void TGate_RSHIFT::ProposeWire( const TWire* in_wire )
{
	m_Input_1->CheckLink( in_wire );
	m_Input_2->CheckLink( in_wire );
}

void TGate_RSHIFT::Update_Level()
{
	if (m_Input_1->IsLinked() && m_Input_2->IsLinked())
	{
		const auto meta1 = m_Input_1->MetaData();
		const auto meta2 = m_Input_2->MetaData();

		Set_MetaData( { meta1.Ready && meta2.Ready
			, std::max( meta1.Level, meta2.Level )
			} );
	}
}

std::string TGate_RSHIFT::to_string() const
{
	return fmt::format( "{} RSHIFT {} -> {}", m_Input_1->Name(), m_Input_2->Name(), Name() );
}


TSignal TGate_RSHIFT::i_ReadSignal() const
{
	return m_Input_1->ReadSignal() >> m_Input_2->ReadSignal();
}


}

