

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


using TLUptrGates = std::vector < std::unique_ptr <BGate>>;
using TLPtrGates = std::vector <BGate*>;
using TLPtrWires = std::vector <TWire*>;



class TCircuit
{
public:

	//static std::unique_ptr<BGate> CreateGate_FromLine( std::string_view line );

	bool AddGate( std::unique_ptr<BGate> gate );
	
	

	bool IsReady() const noexcept;


	//void BuildCircuit();


	TSignal Value( std::string_view wire_name ) const;

	std::vector<TWireInfo> WireInfo_Snapshot() const;

	std::string PrintInput();

private:

	//static TPtrPort i_CreatePort( std::string_view input );
	//static std::unique_ptr<BGate> i_CreateGate( std::string_view wire_name, std::string_view gate_def );

	void i_AddGate( std::unique_ptr<BGate> gate);
	//void i_CheckStagedItems();

	void i_ProcessPile();

	void i_TransferToReady( BGate* gate );

	//const TOutPort* i_AddGate( std::string_view gate_def );
	//void i_AddWire( std::string_view wire_name, std::string_view in_name, const TOutPort* out_port );


private:

	TLUptrGates m_GatesHolder;


	TLPtrGates m_LGatePile;

	//TWireList m_LStagedWires;
	//TGateList m_LNewGates;
	//TLPtrWires m_LWire;

	//TGateList m_LLinkedGates;

	//TWireList m_LWires;
	//TGateList m_LGates;
	TPGateList_Sorted m_LGateReady;
	TLPWire_Sorted m_LWireReady;

};


}



#endif // TCircuit_hpp_

