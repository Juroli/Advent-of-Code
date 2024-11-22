

#ifndef TCircuit_hpp_
#define TCircuit_hpp_

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER



#include "TWire.hpp"
#include "TGate.hpp"

//#include <optional>
#include <vector>
#include <memory>




namespace y15::d07::v2
{

//struct TWireInfo
//{
//	std::string Name;
//	TSignal Value;
//};


class TCircuit
{
public:


	void ParseLine( std::string_view line );

	bool IsReady() const noexcept;

	TSignal Value( std::string_view wire_name ) const;

	std::vector<TWireInfo> WireInfo_Snapshot() const;

private:

	std::unique_ptr<BGate> i_CreateGate( std::string_view gate_def );

	const TOutPort* i_AddGate( std::string_view gate_def );
	void i_AddWire( std::string_view wire_name, std::string_view in_name, const TOutPort* out_port );


private:

	TWireList m_LWires;

	TGateList m_LGates;

};


}



#endif // TCircuit_hpp_

