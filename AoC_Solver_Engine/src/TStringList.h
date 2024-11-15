
#pragma once

#include <vector>
#include <string>

using TStringList = std::vector<std::string >;



//class TStringList
//{
//public:
//
//	TStringList() = default;
//	TStringList( std::initializer_list<std::string> ail ) : m_StrList( ail ) {}
//	TStringList( const std::string& str ) : m_StrList(1, str) {}
//
//
//	auto empty() const noexcept { return m_StrList.empty(); }
//	auto size() const noexcept { return m_StrList.size(); }
//
//
//	void push_back( const std::string& str ) { m_StrList.push_back( str ); }
//
//
//	//operator std::string() const;
//
//	auto front() const noexcept { return m_StrList.front(); }
//	auto back() const noexcept { return m_StrList.back(); }
//
//
//	auto begin() const noexcept { return m_StrList.begin(); }
//	//auto begin() noexcept { return m_StrList.begin(); }
//
//	auto end() const noexcept { return m_StrList.end(); }
//	//auto end() noexcept { return m_StrList.end(); }
//
//private:
//
//	std::vector<std::string > m_StrList; 
//};


