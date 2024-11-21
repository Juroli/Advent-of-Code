
#pragma once


#include <string>
#include <vector>
//#include "TStringList.h"



enum class ETestType
{
	EXAMPLE,
	CUSTOM,
	FUZZY,
};


class TTestInput
{
public:

	static TTestInput Create_Example( std::string_view name, std::string_view input, std::string_view expected );
	static TTestInput Create_Custom( std::string_view name, std::string_view input, std::string_view expected );
	static TTestInput Create_Fuzzy( std::string_view name, std::string_view input );

private:

	TTestInput( ETestType type, std::string_view name, std::string_view input, std::string_view expected );

public:

	const ETestType& Type() const noexcept { return m_Type; }
	const std::string& Name() const noexcept { return m_Name; }
	const std::string& Input() const noexcept { return m_Input; }
	const std::string& Expected() const noexcept { return m_Expected; }



private:

	ETestType m_Type;
	std::string m_Name;
	std::string m_Input;
	std::string m_Expected;
};


class TTestResult: public TTestInput
{
public:

	TTestResult( const TTestInput& input, std::string_view received );

	const std::string& Received() const noexcept { return m_Received; }


	operator bool() const noexcept { return m_Received == Expected(); }


private:

	std::string m_Received;

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



