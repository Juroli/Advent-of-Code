
#ifndef TWire_hpp_
#define TWire_hpp_

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER


//#include "Ports.hpp"

#include <memory>
#include <vector>
#include <string>
//#include <optional>
//#include <algorithm>



namespace y15::d07::v2
{


using TSignal = uint16_t;



struct TWireInfo
{
	std::string Name;
	TSignal Value;
};


struct TMeta
{
	bool Ready;
	int Level;
};


class TWire			//: public TOutPort
{
public:

	TWire( std::string_view wname );		// , std::string_view in_name );		// , const TOutPort* aport );


	//bool IsReady() const noexcept;

	//void LinkTo( const TOutPort* aport ) noexcept;

	bool IsReady() const noexcept { return m_Meta.Ready; }
	int Level() const noexcept { return m_Meta.Level; }
	
	const TMeta& MetaData() const noexcept { return m_Meta; }

	void Set_MetaData( const TMeta& lvl ) { m_Meta = lvl; }

	

	const std::string& Name() const noexcept;

	//TSignal ReadSignal() const override;


	//virtual bool IsReady() const noexcept = 0;
	//virtual bool IsLinked() const noexcept = 0;

	TSignal Value() const;

protected:

	virtual void i_Update_Meta() = 0;

private:

	virtual TSignal i_ReadSignal() const = 0;

private:

	std::string m_Name;

	TMeta m_Meta;


	mutable bool m_Cached = false;
	mutable TSignal m_Cache = 0;

	//TInPort m_InPort;

};




class TLPWire_Sorted
{
public:


	void Add( TWire* wire );		// , const TOutPort* out_port );

	const TWire* FindWire( std::string_view name ) const noexcept;


	std::vector<TWireInfo> Info_Snapshot() const;

	const auto begin() const noexcept { return m_LWire.begin(); }
	const auto end() const noexcept { return m_LWire.end(); }

private:

	std::vector<TWire*> m_LWire;

};


}



#endif // TWire_h_


