
#include "TStringParser.hpp"




TStringParser::TStringParser( std::string_view astr )
	: m_String( std::move( astr ) )
	, m_ItStart( m_String.begin() )
{
}


std::string TStringParser::GetLine() noexcept
{
	const auto ItEnd = std::find( m_ItStart, m_String.end(), '\n' );

	std::string result( m_ItStart, ItEnd );

	

	if (ItEnd == m_String.end())
	{
		m_ItStart = ItEnd;
	}
	else
	{
		m_ItStart = ItEnd + 1;
	}

	return result;
}


