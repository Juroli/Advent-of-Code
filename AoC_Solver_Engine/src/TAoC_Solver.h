
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
	SOLUTION,
};


constexpr char STR_SOLVE_CHECK[] = "<*>Solve check<*>";
constexpr char STR_NOT_IMPLEMENTED[] = "<*>Not implemented<*>";
constexpr char STR_IMPLEMENTED[] = "<*>Implemented<*>";


class TAoC_Solver
{
public:

	EImpl Implemented() const noexcept;

	std::string Solve( const std::string& input ) const;

	TTestResult_Group Test() const;


private:

	virtual std::string i_Solve_Run() const = 0;
	virtual std::string i_Solve_Run( const std::string& input ) const = 0;

	virtual TTestInput_Group i_Test_Prepare() const = 0;
	virtual std::string i_Test_Run( const std::string& ) const = 0;


	//TTestResult_Group o_RunTests( const TTestInput_Group& test_inputs
	//	, std::function<std::string(const std::string&)> funct
	//	) const;

};


class TAoC_Solver_NULL : public TAoC_Solver
{
private:

	std::string i_Solve_Run() const override { return STR_NOT_IMPLEMENTED; };
	std::string i_Solve_Run( const std::string& input ) const override { return STR_NOT_IMPLEMENTED; }

	TTestInput_Group i_Test_Prepare() const override { return { TTestInput::Create_Example( "Ex01", "?", STR_NOT_IMPLEMENTED ) }; }
	std::string i_Test_Run( const std::string& ) const override { return STR_NOT_IMPLEMENTED; }

	//EImpl Implemented() const noexcept override { return EImpl::NONE; }

	// std::string Solve( const std::string& input ) const override { return STR_NOT_IMPLEMENTED; }

	// TTestResult_Group Test() const override { return { { { "?", STR_NOT_IMPLEMENTED }, "" } }; }

};


