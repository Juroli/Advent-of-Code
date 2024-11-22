
#ifndef TGate_hpp_
#define TGate_hpp_

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER



#include "Ports.hpp"

#include <vector>
#include <memory>



namespace y15::d07::v2
{


class BGate: public TOutPort
{
public:

	BGate( std::string_view name );

	const std::string& Name() const noexcept override { return m_Name; }


	virtual bool IsLinked() const = 0;


private:

	std::string m_Name;


	// Inherited via TOutPort
	

};



class TGateList
{
public:

	void AddGate( std::unique_ptr<BGate>&& gate );

	//TWire* FindGate( std::string_view name ) const noexcept;

	bool IsLinked() const;

private:

	std::vector < std::unique_ptr <BGate>> m_LGates;

};



class TGate_Fixed : public BGate
{
public:

	TGate_Fixed( std::string_view name, const TSignal& signal );


	bool IsLinked() const override;

	int Level() const override;

	TSignal ReadSignal() const override;


private:

	TSignal m_Value;

};


//__________________________________________________________________________________________________


class TGate_Link : public BGate
{
public:

	TGate_Link( std::string_view gate_name, std::string_view in_name );


	bool IsLinked() const override;

	int Level() const override;

	TSignal ReadSignal() const override;


private:

	TInPort m_Input;

};


//__________________________________________________________________________________________________


class TGate_NOT : public BGate
{
public:

	TGate_NOT( std::string_view gate_name, std::string_view in_name );


	bool IsLinked() const override;

	int Level() const override;

	TSignal ReadSignal() const override;


private:

	TInPort m_Input;

};


//__________________________________________________________________________________________________


class TGate_AND : public BGate
{
public:

	TGate_AND( std::string_view gate_name, std::string_view in1_name, std::string_view in2_name );


	bool IsLinked() const override;

	int Level() const override;

	TSignal ReadSignal() const override;


private:

	TInPort m_Input_1;
	TInPort m_Input_2;

};


//__________________________________________________________________________________________________


class TGate_OR : public BGate
{
public:

	TGate_OR( std::string_view gate_name, std::string_view in1_name, std::string_view in2_name );


	bool IsLinked() const override;

	int Level() const override;

	TSignal ReadSignal() const override;


private:

	TInPort m_Input_1;
	TInPort m_Input_2;

};


//__________________________________________________________________________________________________


class TGate_LSHIFT : public BGate
{
public:

	TGate_LSHIFT( std::string_view gate_name, std::string_view in_name, int offset );


	bool IsLinked() const override;

	int Level() const override;

	TSignal ReadSignal() const override;


private:

	TInPort m_Input;
	int m_Offset;

};


//__________________________________________________________________________________________________


class TGate_RSHIFT : public BGate
{
public:

	TGate_RSHIFT( std::string_view gate_name, std::string_view in_name, int offset );


	bool IsLinked() const override;

	int Level() const override;

	TSignal ReadSignal() const override;


private:

	TInPort m_Input;
	int m_Offset;

};


}


#endif // TGate_hpp_
