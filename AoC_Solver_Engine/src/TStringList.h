
#pragma once


//using TStringList = std::vector<std::string >;



class TStringList
{
public:

	TStringList() = default;
	TStringList( const std::string& str ) : m_StrList(1, str) {}


	void push_back( const std::string& str ) { m_StrList.push_back( str ); }


	auto begin() const noexcept { return m_StrList.begin(); }
	auto begin() noexcept { return m_StrList.begin(); }

	auto end() const noexcept { return m_StrList.end(); }
	auto end() noexcept { return m_StrList.end(); }

private:

	std::vector<std::string > m_StrList; 
};


