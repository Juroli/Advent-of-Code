
#pragma once

#include <string>




class TStringParser
{
public:

	TStringParser() = delete;
	TStringParser( std::string_view astr );


	operator bool() const noexcept { return m_StartPos < m_String.size(); }	// { return m_ItStart != m_String.end(); }


	//std::string_view Extract_Token( const char adelim ) noexcept;
	std::string_view Extract_Token( std::string_view adelim ) noexcept;

	std::string_view Extract_Line() noexcept;

private:



private:

	std::string_view m_String;
	//std::string_view m_WorkString;

	//std::string_view::iterator m_ItStart;
	size_t m_StartPos;
};

