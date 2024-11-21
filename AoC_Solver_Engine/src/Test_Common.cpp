
#include "Test_Common.h"




TTestInput TTestInput::Create_Example( std::string_view name, std::string_view input, std::string_view expected )
{
	return { ETestType::EXAMPLE, name, input, expected };
}

TTestInput TTestInput::Create_Custom( std::string_view name, std::string_view input, std::string_view expected )
{
	return { ETestType::CUSTOM, name, input, expected };
}

TTestInput TTestInput::Create_Fuzzy( std::string_view name, std::string_view input )
{
	return { ETestType::FUZZY, name, input, " * FUZZY * " };
}

TTestInput::TTestInput( ETestType type, std::string_view name, std::string_view input, std::string_view expected )
	: m_Type( type )
	, m_Name( name )
	, m_Input( input )
	, m_Expected( expected )
{
}



TTestResult::TTestResult( const TTestInput& input, std::string_view received )
	: TTestInput( input )
	, m_Received( received )
{
}


TTestResult_Group::operator bool() const noexcept
{
	for (const auto& curr : m_LResults)
	{
		if (!curr)
		{
			return false;
		}
	}

	return true;
}

