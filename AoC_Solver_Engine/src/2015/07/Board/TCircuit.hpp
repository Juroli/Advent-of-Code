

#ifndef TCircuit_hpp_
#define TCircuit_hpp_

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER



#include "TWire.hpp"
#include "TGate.hpp"

#include <vector>
#include <memory>




namespace y15::d07
{



using TLUptrGates = std::vector < std::unique_ptr <BGate>>;
using TLPtrGates = std::vector <BGate*>;
using TLPtrWires = std::vector <TWire*>;



class TCircuit
{
public:

	bool AddGate( std::unique_ptr<BGate> gate );

	bool IsReady() const noexcept;

	TSignal Value( std::string_view wire_name ) const;

	std::vector<TWireInfo> WireInfo_Snapshot() const;

	std::string PrintInput();

private:

	void i_AddGate( std::unique_ptr<BGate> gate);

	void i_ProcessPile();

	void i_TransferToReady( BGate* gate );

private:

	TLUptrGates m_GatesHolder;

	TLPtrGates m_LGatePile;

	TPGateList_Sorted m_LGateReady;
	TLPWire_Sorted m_LWireReady;

};


}



#endif // TCircuit_hpp_

