
#ifndef TGate_hpp_
#define TGate_hpp_

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER



#include "Ports.hpp"

#include <vector>
#include <memory>



namespace y15::d07
{


class BGate : public TWire
{
public:

	BGate( std::string_view wire_name );

	//const std::string& Name() const noexcept override { return m_Name; }

	//virtual bool IsLinked() const = 0;
	virtual bool IsLinked() const noexcept = 0;

	//void ProposeInputWire( const TWire* in_wire );
	void LinkInput( const TLPWire_Sorted& lista_wire ) noexcept;

	virtual std::string to_string() const = 0;

private:

	//virtual bool i_CheckAddWire( const TWire* in_wire ) = 0;
	virtual bool i_LinkInput( const TLPWire_Sorted& lista_wire ) noexcept = 0;

	//int m_Level;

	//std::string m_Name;


	// Inherited via TOutPort
	

};



using TPtrPort = std::unique_ptr<BInPort>;


class TPGateList_Sorted
{
public:

	void Add( BGate* gate );

	bool empty() const noexcept { return m_LGate.empty(); }
	size_t size() const noexcept { return m_LGate.size(); }

	//TWire* FindWire( std::string_view name ) const noexcept;

	//bool IsLinked() const;

	bool Check_Data() const noexcept;


	//std::vector<TWireInfo> WireInfo_Snapshot() const;

	const auto begin() const noexcept { return m_LGate.begin(); }
	const auto end() const noexcept { return m_LGate.end(); }

private:

	std::vector<BGate*> m_LGate;

};



//class TGate_Fixed : public BGate
//{
//public:
//
//	TGate_Fixed( std::string_view wire_name, const TSignal& signal );
//
//
//	//bool IsReady() const noexcept override;
//
//	bool IsLinked() const noexcept override;
//
//	void ProposeWire( const TWire* in_wire ) override;
//
//	void Update_Level() override;
//
//	std::string to_string() const override;
//
//private:
//
//	TSignal i_ReadSignal() const override;
//
//private:
//
//	TSignal m_Value;
//
//};


//__________________________________________________________________________________________________


class TGate_Link : public BGate
{
public:

	TGate_Link( std::string_view wire_name, TPtrPort input );


	//bool IsReady() const noexcept override;

	bool IsLinked() const noexcept override;

	std::string to_string() const override;

private:

	//bool i_CheckAddWire( const TWire* in_wire ) override;
	bool i_LinkInput( const TLPWire_Sorted& lista_wire ) noexcept override;

	void i_Update_Meta() override;

	TSignal i_ReadSignal() const override;

private:

	TPtrPort m_Input;

};


//__________________________________________________________________________________________________


class TGate_NOT : public BGate
{
public:

	TGate_NOT( std::string_view wire_name, TPtrPort input );


	bool IsLinked() const noexcept override;

	std::string to_string() const override;

private:

	//bool i_CheckAddWire( const TWire* in_wire ) override;
	bool i_LinkInput( const TLPWire_Sorted& lista_wire ) noexcept override;

	void i_Update_Meta() override;

	TSignal i_ReadSignal() const override;

private:

	TPtrPort m_Input;

};


//__________________________________________________________________________________________________


class TGate_AND : public BGate
{
public:

	TGate_AND( std::string_view wire_name, TPtrPort input_1, TPtrPort input_2 );


	bool IsLinked() const noexcept override;

	std::string to_string() const override;

private:

	//bool i_CheckAddWire( const TWire* in_wire ) override;
	bool i_LinkInput( const TLPWire_Sorted& lista_wire ) noexcept override;

	void i_Update_Meta() override;

	TSignal i_ReadSignal() const override;

private:

	TPtrPort m_Input_1;
	TPtrPort m_Input_2;

};


//__________________________________________________________________________________________________


class TGate_OR : public BGate
{
public:

	TGate_OR( std::string_view wire_name, TPtrPort input_1, TPtrPort input_2 );


	bool IsLinked() const noexcept override;

	std::string to_string() const override;

private:

	//bool i_CheckAddWire( const TWire* in_wire ) override;
	bool i_LinkInput( const TLPWire_Sorted& lista_wire ) noexcept override;

	void i_Update_Meta() override;

	TSignal i_ReadSignal() const override;

private:

	TPtrPort m_Input_1;
	TPtrPort m_Input_2;

};


//__________________________________________________________________________________________________


class TGate_LSHIFT : public BGate
{
public:

	TGate_LSHIFT( std::string_view wire_name, TPtrPort input_1, TPtrPort input_2 );


	bool IsLinked() const noexcept override;

	std::string to_string() const override;

private:

	//bool i_CheckAddWire( const TWire* in_wire ) override;
	bool i_LinkInput( const TLPWire_Sorted& lista_wire ) noexcept override;

	void i_Update_Meta() override;

	TSignal i_ReadSignal() const override;

private:

	TPtrPort m_Input_1;
	TPtrPort m_Input_2;
	//int m_Offset;

};


//__________________________________________________________________________________________________


class TGate_RSHIFT : public BGate
{
public:

	TGate_RSHIFT( std::string_view wire_name, TPtrPort input_1, TPtrPort input_2 );


	bool IsLinked() const noexcept override;

	std::string to_string() const override;

private:

	//bool i_CheckAddWire( const TWire* in_wire ) override;
	bool i_LinkInput( const TLPWire_Sorted& lista_wire ) noexcept override;

	void i_Update_Meta() override;

	TSignal i_ReadSignal() const override;

private:

	TPtrPort m_Input_1;
	TPtrPort m_Input_2;
	//int m_Offset;

};


}


#endif // TGate_hpp_
