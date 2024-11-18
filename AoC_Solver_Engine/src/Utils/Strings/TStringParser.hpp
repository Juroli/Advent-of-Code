
#pragma once

#include <string>




class TStringParser
{
public:

	TStringParser() = delete;
	TStringParser( std::string_view astr );


	operator bool() const noexcept { return m_ItStart != m_String.end(); }

	std::string GetLine() noexcept;

private:



private:

	std::string_view m_String;

	std::string_view::iterator m_ItStart;
};

