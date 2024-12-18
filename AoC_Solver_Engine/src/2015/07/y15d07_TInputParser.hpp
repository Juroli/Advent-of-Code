
#pragma once


#include <memory>

#include "Utils/Strings/TStringParser.hpp"


#include "Board/TGate.hpp"



namespace y15::d07
{

class TInputParser
{
public:

	TInputParser( std::string_view input );

	operator bool() const noexcept { return m_Parser; }


	void Select_NextLine();
	std::unique_ptr<BGate> Create_CurrentGate();

	std::unique_ptr<BGate> Extract_NextGate();

private:

	static TPtrPort i_CreatePort( std::string_view input );
	static std::unique_ptr<BGate> i_CreateGate( std::string_view wire_name, std::string_view gate_def );

	static std::unique_ptr<BGate> i_CreateGate_FromLine( std::string_view line );

private:

	TStringParser m_Parser;

	std::string_view m_CurrentLine;
	
};


}

