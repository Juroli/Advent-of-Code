
#ifndef TWire_hpp_
#define TWire_hpp_

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER



#include <vector>
#include <string>




namespace y15::d07
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



class TWire
{
public:

	TWire( std::string_view wname );


	bool IsReady() const noexcept { return m_Meta.Ready; }
	int Level() const noexcept { return m_Meta.Level; }
	
	const TMeta& MetaData() const noexcept { return m_Meta; }

	void Set_MetaData( const TMeta& lvl ) { m_Meta = lvl; }

	const std::string& Name() const noexcept;

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

};



//__________________________________________________________________________________________________



class TLPWire_Sorted
{
public:

	void Add( TWire* wire );

	const TWire* FindWire( std::string_view name ) const noexcept;

	std::vector<TWireInfo> Info_Snapshot() const;

	const auto begin() const noexcept { return m_LWire.begin(); }
	const auto end() const noexcept { return m_LWire.end(); }

private:

	std::vector<TWire*> m_LWire;

};




}



#endif // TWire_h_


