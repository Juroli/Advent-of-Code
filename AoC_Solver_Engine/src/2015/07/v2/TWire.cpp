
#include "TWire.hpp"

#include "gsl/gsl"


#include "Utils/Strings/Misc.hpp"




namespace y15::d07::v2
{


TWire::TWire( std::string_view wname )		//, std::string_view in_name)			//, const TOutPort* aport )
	: m_Name( wname )
	, m_Meta{ false, 0 }
	//, m_InPort( in_name, aport)
{
	//if (aport == nullptr)
	//{
	//	throw std::exception( "Invalid port: is null." );
	//}
}

//bool TWire::IsReady() const noexcept
//{
//	return m_InPort.IsLinked();
//}


//void TWire::LinkTo( const TOutPort* aport ) noexcept
//{
//	m_InPort.Link( aport );
//}

//int TWire::Level() const
//{
//	return m_InPort.Level();
//}

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

//TSignal TWire::ReadSignal() const
//{
//	return m_InPort.ReadSignal();
//}




//void TWireList::AddWire( std::string_view wire_name, std::string_view in_name)		//, const TOutPort* out_port )
//{
//	m_LWire.push_back( std::make_unique<TWire>( wire_name, in_name ) );		// , out_port ) );
//}
//
//TWire* TWireList::FindWire( std::string_view name ) const noexcept
//{
//	const auto pos = std::find_if( m_LWire.begin(), m_LWire.end(), [&name]( const std::unique_ptr<TWire>& w ) { return (w->Name() == name); });
//
//	if (pos == m_LWire.end())
//	{
//		return nullptr;
//	}
//	
//	return pos->get();
//}
//
//
//std::vector<TWireInfo> TWireList::Info_Snapshot() const
//{
//	std::vector<TWireInfo> result;
//
//	for (const auto& curr : m_LWire)
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



}



