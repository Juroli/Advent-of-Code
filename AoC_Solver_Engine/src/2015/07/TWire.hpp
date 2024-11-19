
#ifndef TWire_h__
#define TWire_h__

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER


//#include "TNodes.h"

#include <memory>
#include <string>
#include <optional>
#include <algorithm>

namespace y15::d07
{

class BWire;


namespace impldet_
{

class TWireIn
{
public:
	//		_TNodeIn();
	TWireIn( std::string_view pid );
	//TWireIn( std::string&& pid );

	//		_TNodeIn(uint16_t pval) : m_NameInput(""), m_FixedVal(pval), m_Link(nullptr)		{}

	// 		void Set_ID(const std::string &pid)						{ m_NameID = pid; }
	// 		void Set_ID(std::string &&pid)							{ m_NameID = std::move(pid); }

	void CheckSet_Link( const BWire* pwire );

	void Unlink( const BWire* pwire );

	bool Is_Linked() const { return (m_Link != nullptr) || (m_NameInput.empty()); }


	uint16_t Value( int lvl ) const;


	int Level() const;

	void ForceRecalc();

private:

	void i_CheckString();

private:

	std::string m_NameInput;
	uint16_t m_FixedVal;
	const BWire* m_Link;

	mutable bool m_IsCashed;
	mutable uint16_t m_CachedValue;

	mutable int m_WatchLoop;
};

}



class BWire
{
protected:

	BWire( std::string_view pname )
		: m_Name( pname )
		, m_Linked{ false }
		, m_Level{ 0 }
	{
	}

public:

	static std::unique_ptr<BWire> Create_Wire( std::string_view pline );

	BWire() = delete;

	BWire( BWire const& ) = delete;
	BWire( BWire&& pv ) noexcept
		: m_Name( std::move( pv.m_Name ) )
		, m_Linked( std::move( pv.m_Linked ) )
		, m_Level( std::move( pv.m_Level ) )
	{
	}

	BWire& operator = ( BWire const& ) = delete;
	BWire& operator = ( BWire&& pv ) noexcept = default;


	std::string const& Name() const { return m_Name; }

	bool IsLinked() const { return m_Linked; }

	int Level() const { return m_Level; }

	virtual uint16_t Value( int lvl ) const = 0;

	virtual void CheckLink_Input_Node( const BWire* pnode ) = 0;

	virtual void Unlink( const BWire* pnode ) = 0;

	virtual void Update() = 0;

	virtual void ForceRecalc() = 0;


private:

	//	void _Set_Node(std::unique_ptr<TNode_Base> &&pptr)		{ m_Node = std::move(pptr); }

	static std::unique_ptr<BWire> _CalcWire( std::string_view pname, std::string_view poper );

	std::string m_Name;

protected:

	bool m_Linked;
	int m_Level;
	//	std::string m_Operation;
	//	std::unique_ptr<BWire> m_Node;
};



//////////////////////////////////////////////////////////////////////////

class TWire_Link : public BWire
{
public:

	TWire_Link( std::string_view pname, std::string_view pnamein )
		: BWire( pname )
		, m_Input( pnamein )
	{
	}

	// 	TNode_Link(std::string const &pname
	// 					 , uint16_t pv
	// 	)
	// 		: TNode_Base(pname)		//, 0)
	// 		, m_Input(pv)
	// 	{}

	virtual uint16_t Value( int lvl ) const override { return m_Input.Value( lvl + 1 ); }


	// 	virtual bool IsLinked() const override					{ return m_Input.Is_Linked(); }
	// 
	// 	virtual int Level() const override						{ return m_Input.Level(); }

	virtual void CheckLink_Input_Node( const BWire* pnode ) override
	{
		m_Input.CheckSet_Link( pnode );

		Update();
	}

	virtual void Unlink( const BWire* pnode ) override
	{
		m_Input.Unlink( pnode );
		Update();
	}

	virtual void Update() override
	{
		m_Linked = m_Input.Is_Linked();

		m_Level = m_Input.Level();
	}

	virtual void ForceRecalc() override
	{
		m_Input.ForceRecalc();
	}

private:

	impldet_::TWireIn m_Input;
};

//////////////////////////////////////////////////////////////////////////

class TWire_NOT : public BWire				//<1>
{
public:

	TWire_NOT( std::string_view pname, std::string_view pnamein	)
		: BWire( pname )
		, m_Input( pnamein )
	{
		//		m_Inputs[0].Set_ID(pidparent1);
	}

	virtual uint16_t Value( int lvl ) const override { return ~m_Input.Value( lvl + 1 ); }

	//	virtual bool IsInputLinked() const override { return m_Input.Is_Linked(); }

	virtual void CheckLink_Input_Node( BWire const* pnode ) override
	{
		m_Input.CheckSet_Link( pnode );
		Update();
	}

	virtual void Unlink( const BWire* pnode ) override
	{
		m_Input.Unlink( pnode );
		Update();
	}

	//	virtual int Level() const override { return m_Input.Level(); }

	virtual void Update() override
	{
		m_Linked = m_Input.Is_Linked();

		m_Level = m_Input.Level();
	}

	virtual void ForceRecalc() override
	{
		m_Input.ForceRecalc();
	}

private:

	impldet_::TWireIn m_Input;
	//TNode_Base const *m_Parent;
};

//////////////////////////////////////////////////////////////////////////

class TWire_AND : public BWire				//<2>
{
public:

	TWire_AND( std::string_view pname, std::string_view pnamein1, std::string_view pnamein2 )
		: BWire( pname )
		, m_Input_1( pnamein1 )
		, m_Input_2( pnamein2 )
	{
		// 		m_Inputs[0].Set_ID(pidparent1);
		// 		m_Inputs[1].Set_ID(pidparent2);
	}

	virtual uint16_t Value( int lvl ) const override { return (m_Input_1.Value( lvl + 1 ) & m_Input_2.Value( lvl + 1 )); }

	// 	virtual bool IsInputLinked() const override		{ return (m_Input_1.Is_Linked() && m_Input_2.Is_Linked()); }
	// 
	// 	virtual int Level() const override					
	// 	{
	// 		if(m_Input_1.Level() == 0 || m_Input_2.Level() == 0)
	// 		{
	// 			return 0;
	// 		}
	// 
	// 		return (std::max(m_Input_1.Level(),m_Input_2.Level()) + 1);
	// 	
	// 	}

	virtual void CheckLink_Input_Node( BWire const* pnode ) override
	{
		m_Input_1.CheckSet_Link( pnode );
		m_Input_2.CheckSet_Link( pnode );

		Update();
	}

	virtual void Unlink( const BWire* pnode ) override
	{
		m_Input_1.Unlink( pnode );
		m_Input_2.Unlink( pnode );
		Update();
	}

	virtual void Update() override
	{
		m_Linked = (m_Input_1.Is_Linked() && m_Input_2.Is_Linked());

		if (m_Input_1.Level() < 0 || m_Input_2.Level() < 0)
		{
			m_Level = -1;
		}
		else
		{
			m_Level = std::max( m_Input_1.Level(), m_Input_2.Level() );
		}
	}

	virtual void ForceRecalc() override
	{
		m_Input_1.ForceRecalc();
		m_Input_2.ForceRecalc();
	}

private:

	impldet_::TWireIn m_Input_1;
	impldet_::TWireIn m_Input_2;

};

//////////////////////////////////////////////////////////////////////////

class TWire_OR : public BWire				//<2>
{
public:

	TWire_OR( std::string_view pname, std::string_view pnamein1, std::string_view pnamein2 )
		: BWire( pname )
		, m_Input_1( pnamein1 )
		, m_Input_2( pnamein2 )
	{
		// 		m_Inputs[0].Set_ID(pidparent1);
		// 		m_Inputs[1].Set_ID(pidparent2);
	}

	virtual uint16_t Value( int lvl ) const override { return (m_Input_1.Value( lvl + 1 ) | m_Input_2.Value( lvl + 1 )); }

	//	virtual bool IsInputLinked() const override { return (m_Input_1.Is_Linked() && m_Input_2.Is_Linked()); }

	virtual void CheckLink_Input_Node( BWire const* pnode ) override
	{
		m_Input_1.CheckSet_Link( pnode );
		m_Input_2.CheckSet_Link( pnode );

		Update();
	}

	virtual void Unlink( const BWire* pnode ) override
	{
		m_Input_1.Unlink( pnode );
		m_Input_2.Unlink( pnode );
		Update();
	}

	virtual void Update() override
	{
		m_Linked = m_Input_1.Is_Linked() && m_Input_2.Is_Linked();

		if (m_Input_1.Level() < 0 || m_Input_2.Level() < 0)
		{
			m_Level = -1;
		}
		else
		{
			m_Level = std::max( m_Input_1.Level(), m_Input_2.Level() );
		}
	}

	virtual void ForceRecalc() override
	{
		m_Input_1.ForceRecalc();
		m_Input_2.ForceRecalc();
	}

private:

	impldet_::TWireIn m_Input_1;
	impldet_::TWireIn m_Input_2;

	// 	TNode_Base const *m_ParentA;
	// 	TNode_Base const *m_ParentB;
};

//////////////////////////////////////////////////////////////////////////

class TWire_LSHIFT : public BWire
{
public:

	TWire_LSHIFT( std::string_view pname
		, std::string_view pnamein
		, int poffset
	)
		: BWire( pname )
		, m_Input( pnamein )
		, m_Offset( poffset )
	{
		//		m_Inputs[0].Set_ID(pidparent1);
	}

	virtual uint16_t Value( int lvl ) const override { return (m_Input.Value( lvl + 1 ) << m_Offset); }

	//	virtual bool IsInputLinked() const override { return m_Input.Is_Linked(); }

	virtual void CheckLink_Input_Node( BWire const* pnode ) override
	{
		m_Input.CheckSet_Link( pnode );
		Update();
	}

	virtual void Unlink( const BWire* pnode ) override
	{
		m_Input.Unlink( pnode );
		Update();
	}

	virtual void Update() override
	{
		m_Linked = m_Input.Is_Linked();

		m_Level = m_Input.Level();
	}

	virtual void ForceRecalc() override
	{
		m_Input.ForceRecalc();
	}

private:

	//	TNode_Base const *m_Parent;
	impldet_::TWireIn m_Input;
	int m_Offset;
};

//////////////////////////////////////////////////////////////////////////

class TWire_RSHIFT : public BWire
{
public:

	TWire_RSHIFT( std::string_view pname, std::string_view pnamein, int poffset )
		: BWire( pname )
		, m_Input( pnamein )
		, m_Offset( poffset )
	{
		//		m_Inputs[0].Set_ID(pidparent1);
	}

	virtual uint16_t Value( int lvl ) const override { return (m_Input.Value( lvl + 1 ) >> m_Offset); }

	//	virtual bool IsInputLinked() const override { return m_Input.Is_Linked(); }

	virtual void CheckLink_Input_Node( BWire const* pnode ) override
	{
		m_Input.CheckSet_Link( pnode );
		Update();
	}

	virtual void Unlink( const BWire* pnode ) override
	{
		m_Input.Unlink( pnode );
		Update();
	}

	virtual void Update() override
	{
		m_Linked = m_Input.Is_Linked();

		m_Level = m_Input.Level();
	}

	virtual void ForceRecalc() override
	{
		m_Input.ForceRecalc();
	}

private:

	//	TNode_Base const *m_Parent;
	impldet_::TWireIn m_Input;
	int m_Offset;
};



}

#endif // TWire_h__


