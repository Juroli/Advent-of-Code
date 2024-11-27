
#include "TWire.hpp"




namespace y15::d07
{



TWire::TWire( std::string_view wname )
	: m_Name( wname )
	, m_Meta{ false, 0 }
{
}

const std::string& TWire::Name() const noexcept
{
	return m_Name;
}

TSignal TWire::Value() const
{
	if (!m_Cached)
	{
		m_Cache = i_ReadSignal();
		m_Cached = true;
	}

	return m_Cache;
}



//__________________________________________________________________________________________________



void TLPWire_Sorted::Add( TWire* wire )
{
	const auto ins_pos = std::upper_bound( m_LWire.begin(), m_LWire.end(), wire,
		[]( const TWire* pa, const TWire* pb ) { return pa->Name() < pb->Name(); }
	);
	m_LWire.insert( ins_pos, wire );
}

const TWire* TLPWire_Sorted::FindWire( std::string_view name ) const noexcept
{
	const auto pos = std::find_if( m_LWire.begin(), m_LWire.end(), [&name]( const TWire* w ) { return (w->Name() == name); });

	if (pos == m_LWire.end())
	{
		return nullptr;
	}
	
	return *pos;
}

std::vector<TWireInfo> TLPWire_Sorted::Info_Snapshot() const
{
	std::vector<TWireInfo> result;

	for (const auto& curr : m_LWire)
	{
		if (curr == nullptr)
		{
			throw std::exception( "CRITICAL ERROR (1507 TCirc): Wires list corrupted!" );
		}

		result.push_back( { curr->Name(), curr->Value() } );
	}

	return result;
}




}



