
#ifndef Ports_hpp_
#define Ports_hpp_

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER




#include <string>

#include "TWire.hpp"


namespace y15::d07
{


class BInPort
{
public:

	virtual const std::string& Name() const noexcept = 0;
	virtual bool IsLinked() const noexcept = 0;
	virtual TMeta MetaData() const noexcept = 0;

	virtual bool LinkInput( const TLPWire_Sorted& lista_wire ) noexcept = 0;

	virtual TSignal ReadSignal() const = 0;
};



class TInPort_Fixed: public BInPort
{
public:

	TInPort_Fixed( TSignal val ) : m_Name( std::to_string( val ) ), m_Value( val ) {}

	const std::string& Name() const noexcept override { return m_Name; }

	bool IsLinked() const noexcept override { return true; }

	TMeta MetaData() const noexcept override { return { true, 0 }; }

	bool LinkInput( const TLPWire_Sorted& lista_wire ) noexcept override { return false; }

	TSignal ReadSignal() const override { return m_Value; }

private:

	std::string m_Name;
	TSignal m_Value;
};



class TInPort_Wire: public BInPort
{
public:

	TInPort_Wire( std::string_view in_name );


	const std::string& Name() const noexcept override { return m_InName; }

	bool IsLinked() const noexcept override { return m_InWire != nullptr; }

	TMeta MetaData() const noexcept override;

	bool LinkInput( const TLPWire_Sorted& lista_wire ) noexcept override;

	TSignal ReadSignal() const override;


private:

	std::string m_InName;
	const TWire* m_InWire;
};



}


#endif // Ports_hpp_

