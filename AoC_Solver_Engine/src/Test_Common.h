
#pragma once


#include <string>
#include <vector>
//#include "TStringList.h"


struct TTest_input
{
	std::string input;
	std::string expected;
};

struct TTest_result
{
	TTest_input reference;
	std::string actual;

	operator bool() const noexcept { return actual == reference.expected; }
};



class TTestInput_Group
{
public:

	TTestInput_Group() = default;
	TTestInput_Group( std::initializer_list<TTest_input> ail ) : m_LInputs( ail ) {}


	auto empty() const noexcept { return m_LInputs.empty(); }
	auto size() const noexcept { return m_LInputs.size(); }


	void Add( const TTest_input& ain ) { m_LInputs.push_back( ain ); }


	auto begin() const noexcept { return m_LInputs.begin(); }
	auto end() const noexcept { return m_LInputs.end(); }

private:

	std::vector<TTest_input> m_LInputs;

};


class TTestResult_Group
{
public:

	TTestResult_Group() = default;
	TTestResult_Group( std::initializer_list<TTest_result> ail ) : m_LResults(ail) {}

	operator bool() const noexcept;

	auto empty() const noexcept { return m_LResults.empty(); }
	auto size() const noexcept { return m_LResults.size(); }


	void Add( const TTest_result& ain ) { m_LResults.push_back( ain ); }


	auto begin() const noexcept { return m_LResults.begin(); }
	auto end() const noexcept { return m_LResults.end(); }

private:

	std::vector<TTest_result> m_LResults;

};



