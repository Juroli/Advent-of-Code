
#pragma once

//#include <cstdint>
#include <string>

namespace y15::d07::v2
{


using TSignal = uint16_t;


class TPortOut
{
public:


	virtual const std::string& ID() const noexcept = 0;

	virtual TSignal ReadSignal() const = 0;

private:

};


class TPortIn
{
public:

	TPortIn();

	bool IsLinked() const noexcept { return m_OutPort != nullptr; }


	void Link( const TPortOut* aport ) noexcept;

	TSignal ReadSignal() const;


private:

	const TPortOut* m_OutPort;
};

}

