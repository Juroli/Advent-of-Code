
#ifndef TWire_hpp_
#define TWire_hpp_

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER


#include "Ports.hpp"

#include <memory>
#include <vector>
//#include <string>
//#include <optional>
//#include <algorithm>



namespace y15::d07::v2
{


struct TWireInfo
{
	std::string Name;
	TSignal Value;
};



class TWire: public TOutPort
{
public:

	TWire( std::string_view wname, std::string_view in_name, const TOutPort* aport );


	void LinkTo( const TOutPort* aport ) noexcept;

	int Level() const override;

	const std::string& Name() const noexcept override;

	TSignal ReadSignal() const override;


private:

	std::string m_Name;

	TInPort m_InPort;

};




class TWireList
{
public:


	void AddWire( std::string_view wire_name, std::string_view in_name, const TOutPort* out_port );

	TWire* FindWire( std::string_view name ) const noexcept;


	std::vector<TWireInfo> Info_Snapshot() const;

	const auto begin() const noexcept { return m_LWire.begin(); }
	const auto end() const noexcept { return m_LWire.end(); }

private:

	std::vector<std::unique_ptr<TWire>> m_LWire;

};


}



#endif // TWire_h_


