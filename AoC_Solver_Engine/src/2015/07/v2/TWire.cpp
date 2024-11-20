
#include "TWire.hpp"

#include "gsl/gsl"

//#include <boost/algorithm/string.hpp>
#include "Utils/Strings/Misc.hpp"




namespace y15::d07::v2
{

TWire::TWire( std::string_view aid )
	: m_ID( aid )
{
}

void TWire::Link( const TPortOut* aport ) noexcept
{
	m_InPort.Link( aport );
}


}



