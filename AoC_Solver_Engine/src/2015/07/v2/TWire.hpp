
#ifndef TWire_h__
#define TWire_h__

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER


#include "Ports.hpp"

//#include <memory>
//#include <string>
//#include <optional>
//#include <algorithm>



namespace y15::d07::v2
{


class TWire: public TPortOut
{
public:

	TWire( std::string_view aid );


	void Link( const TPortOut* aport ) noexcept;



private:

	std::string m_ID;

	TPortIn m_InPort;


};



}



#endif // TWire_h__


