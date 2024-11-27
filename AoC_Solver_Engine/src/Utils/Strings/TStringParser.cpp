
#include "TStringParser.hpp"




TStringParser::TStringParser( std::string_view astr )
	: m_String( astr )
	//, m_WorkString( m_StartString )
	, m_StartPos( 0 )
{
}


//std::string_view TStringParser::Extract_Token( const char adelim ) noexcept
//{
//	const auto start_pos = m_StartPos;
//	const auto end_pos = m_String.find( adelim, m_StartPos );
//
//	//std::string result( m_ItStart, ItEnd );
//	//std::string_view result( m_StartPos, ItEnd );
//
//	m_StartPos = std::max( end_pos + 1, m_String.size() );
//
//	//if (ItEnd == m_String.end())
//	//{
//	//	m_ItStart = ItEnd;
//	//}
//	//else
//	//{
//	//	m_ItStart = ItEnd + 1;
//	//}
//
//	return m_String.substr( start_pos, end_pos );
//}

std::string_view TStringParser::Extract_Token( std::string_view adelim ) noexcept
{
	const auto start_pos = m_StartPos;
	const auto end_pos = m_String.find( adelim, m_StartPos );

	if (end_pos != m_String.npos)
	{
		m_StartPos = std::min( end_pos + adelim.size(), m_String.size() );
	}
	else
	{
		m_StartPos = m_String.size();
	}
	

	return m_String.substr( start_pos, end_pos - start_pos );
}


std::string_view TStringParser::Extract_Line() noexcept
{
	return Extract_Token( "\n" );
}


