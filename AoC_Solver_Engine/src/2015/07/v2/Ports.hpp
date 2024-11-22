
#ifndef Ports_hpp_
#define Ports_hpp_

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER



//#include <cstdint>
#include <string>

namespace y15::d07::v2
{


using TSignal = uint16_t;



class TOutPort
{
public:


	virtual const std::string& Name() const noexcept = 0;

	virtual int Level() const = 0;

	virtual TSignal ReadSignal() const = 0;

private:

};



class TInPort
{
public:

	TInPort( std::string_view in_name );
	TInPort( std::string_view in_name, const TOutPort* aport );


	bool IsLinked() const noexcept { return m_OutPort != nullptr; }

	int Level() const noexcept;

	void Link( const TOutPort* aport ) noexcept;

	TSignal ReadSignal() const;


private:

	std::string m_InName;
	const TOutPort* m_OutPort;
};



}


#endif // Ports_hpp_

