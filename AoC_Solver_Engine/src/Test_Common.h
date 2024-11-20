
#pragma once


#include <string>
#include <vector>
//#include "TStringList.h"


struct TTestInput
{
	std::string input;
	std::string expected;
};

struct TTestResult
{
	TTestInput reference;
	std::string actual;

	operator bool() const noexcept { return actual == reference.expected; }
};



class TTestInput_Group
{
public:

	TTestInput_Group() = default;
	TTestInput_Group( std::initializer_list<TTestInput> ail ) : m_LInputs( ail ) {}


	auto empty() const noexcept { return m_LInputs.empty(); }
	auto size() const noexcept { return m_LInputs.size(); }


	void Add( const TTestInput& ain ) { m_LInputs.push_back( ain ); }

	const TTestInput& front() const noexcept { return m_LInputs.front(); }

	auto begin() const noexcept { return m_LInputs.begin(); }
	auto end() const noexcept { return m_LInputs.end(); }

private:

	std::vector<TTestInput> m_LInputs;

};


class TTestResult_Group
{
public:

	TTestResult_Group() = default;
	TTestResult_Group( std::initializer_list<TTestResult> ail ) : m_LResults(ail) {}

	operator bool() const noexcept;

	auto empty() const noexcept { return m_LResults.empty(); }
	auto size() const noexcept { return m_LResults.size(); }


	void Add( const TTestResult& ain ) { m_LResults.push_back( ain ); }

	const TTestResult& front() const noexcept { return m_LResults.front(); }

	auto begin() const noexcept { return m_LResults.begin(); }
	auto end() const noexcept { return m_LResults.end(); }

private:

	std::vector<TTestResult> m_LResults;

};



