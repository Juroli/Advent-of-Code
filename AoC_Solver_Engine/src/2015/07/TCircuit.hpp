

#ifndef TCircuit_h__
#define TCircuit_h__

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER


#include "TWire.hpp"

//#include <optional>
#include <vector>

namespace y15::d07
{


class TCircuit
{

	using TWirePtr = std::unique_ptr<BWire>;
	using TWiresVector = std::vector<TWirePtr>;

public:

	TCircuit();

	//	void AddLine(std::string pstr);
	bool AddWire( std::unique_ptr<BWire>&& pwire );
	bool ReplaceWire( std::unique_ptr<BWire>&& pwire );

	uint16_t Value( const std::string& pwire );


	const TWiresVector& LWires() const noexcept { return m_WiresList; }

private:

	const BWire* i_FindWire( const std::string& pname );

	//	bool _ParseWire(std::string pline);

	//	void _FindWorkingWires();

		// Inserisce un Wire nel circuito. Se esiste un'altro con lo stesso nome lo sostituisce
	void i_InsertWire( std::unique_ptr<BWire>&& pwire );
	void i_RemoveWire( const std::string& pwname );
	void i_RemoveWire( const TWiresVector::const_iterator& piter );

	void i_SortWireList();

	//	void _CalcNode(TWire &pwire);

private:

	//	std::vector<TWire> m_UnlinkedWires;

	//	std::vector<TPtrWire> m_WiresList;
	TWiresVector m_WiresList;

	//	std::vector<TWire>::iterator m_ListFirstUnlinked;

};

}

#endif // TCircuit_h__

