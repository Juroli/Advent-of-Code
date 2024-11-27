
#pragma once


#include <memory>

#include "Utils/Strings/TStringParser.hpp"

//#include "v2/TWire.hpp"
#include "Board/TGate.hpp"



namespace y15::d07
{

class TInputParser
{
public:

	TInputParser( std::string_view input );

	operator bool() const noexcept { return m_Parser; }


	std::unique_ptr<BGate> Extract_NextGate();

private:

	static TPtrPort i_CreatePort( std::string_view input );
	static std::unique_ptr<BGate> i_CreateGate( std::string_view wire_name, std::string_view gate_def );

	static std::unique_ptr<BGate> i_CreateGate_FromLine( std::string_view line );

private:

	TStringParser m_Parser;
	
};


}

