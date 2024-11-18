
#pragma once


#include <string>
#include <vector>
#include <istream>

#include <functional>

#include "Test_Common.h"



struct TPuzzleID
{
	uint16_t Year;
	uint8_t Day;
	uint8_t Part;
};


enum class EImpl
{
	NONE,
	TEST,
	FULL,
};


class TAoC_Solver
{
public:

	virtual EImpl Implemented() const noexcept = 0;

	virtual std::string Solve( const std::string& input ) const = 0;

	virtual TTestResult_Group Test() const = 0;


protected:

	TTestResult_Group o_RunTests( const TTestInput_Group& test_inputs
		, std::function<std::string(const std::string&)> funct
		) const;

};


class TAoC_Solver_NULL : public TAoC_Solver
{
public:

	EImpl Implemented() const noexcept override { return EImpl::NONE; }

	std::string Solve( const std::string& input ) const override { return "* Not implemented! *"; }

	TTestResult_Group Test() const override { return { { { "?", "?" }, "* Not implemented! *" } }; }

};


