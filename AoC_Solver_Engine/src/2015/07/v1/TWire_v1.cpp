
#include "TWire_v1.hpp"

#include "gsl/gsl"

//#include <boost/algorithm/string.hpp>
#include "Utils/Strings/Misc.hpp"



namespace y15::d07::v1
{

namespace impldet_
{

TWireIn::TWireIn( std::string_view pid )
	: m_NameInput( pid )
	, m_FixedVal( 0 )
	, m_Link( nullptr )

	, m_IsCashed( false )
	, m_CachedValue( 0 )

	, m_WatchLoop( -1 )
{
	i_CheckString();
}

//TWireIn::TWireIn( std::string&& pid )
//	: m_NameInput( std::move( pid ) )
//	, m_FixedVal( 0 )
//	, m_Link( nullptr )
//
//	, m_IsCashed( false )
//	, m_CachedValue( 0 )
//
//	, m_WatchLoop( -1 )
//{
//	i_CheckString();
//}


void TWireIn::CheckSet_Link( BWire const* pwire )
{
	if (!m_NameInput.empty() && pwire->Name() == m_NameInput)
	{
		m_Link = pwire;
	}
}

void TWireIn::Unlink( BWire const* pwire )
{
	if (!m_NameInput.empty() && pwire->Name() == m_NameInput)
	{
		if (m_Link != pwire)
		{
			int a = 0;
		}
		m_Link = nullptr;

		m_IsCashed = false;
		m_CachedValue = 0;
	}
}

uint16_t TWireIn::Value( int lvl ) const
{
	if (m_FixedVal == 1674)
	{
		int a = 0;
	}

	if (m_WatchLoop >= 0 && m_WatchLoop < lvl)
	{
		int a = 0;
	}

	if (!m_IsCashed)
	{
		m_WatchLoop = lvl;
		m_CachedValue = m_NameInput.empty() ? m_FixedVal : m_Link->Value( lvl );
		m_IsCashed = true;

		m_WatchLoop = -1;
	}

	return m_CachedValue;
}


int TWireIn::Level() const
{
	if (m_NameInput.empty())
	{
		return 0;
	}

	if (m_Link)
	{
		return m_Link->Level() + 1;
	}
	else
	{
		return -1;
	}
}

void TWireIn::ForceRecalc()
{
	m_IsCashed = false;
	m_CachedValue = 0;

	m_WatchLoop = -1;
}

void TWireIn::i_CheckString()
{
	if (m_NameInput.find_first_not_of( "0123456789" ) == std::string::npos)
	{
		m_FixedVal = gsl::narrow_cast<uint16_t>(std::stoul( m_NameInput ));
		m_NameInput.clear();
	}
}




}



//std::optional<nsDay07::TWire> TWire::Create_Wire(std::string pline)
std::unique_ptr<BWire> BWire::Create_Wire( std::string_view pline )
{
	if (pline.empty())
	{
		//		return std::optional<TWire>();
		return nullptr;
	}

	const auto posarrow = pline.find( "->" );

	if (posarrow != std::string::npos)
	{
		// Invalid row
		//		return false;

// 		TWire workwire(boost::trim_copy(pline.substr(posarrow + 2))
// 							, boost::trim_copy(pline.substr(0, posarrow)));
// 
// 		if(workwire._CalcWire())
// 		{
// 			return workwire;
// 		}

		//return _CalcWire( boost::trim_copy( pline.substr( posarrow + 2 ) )
		//	, boost::trim_copy( pline.substr( 0, posarrow ) ) );

		return _CalcWire( trim_copy( pline.substr( posarrow + 2 ) )
			, trim_copy( pline.substr( 0, posarrow ) ) );

	}

	// 	_Wire locwire;
	// 	locwire.Name = pline.substr(posarrow + 2);
	// 	locwire.Operation = pline.substr(0, posarrow);
	// 
	// 	boost::trim(locwire.Name);
	// 	boost::trim(locwire.Operation);


//	return std::optional<TWire>();
	return nullptr;
}

// bool TWire::CheckLink_Input_Wire(const TWire &pwire)
// {
// 	return m_Node->CheckLink_Input_Node(pwire.m_Node.get());
// }

std::unique_ptr<BWire> BWire::_CalcWire( std::string_view pname, std::string_view poper )
{
	//auto tmpstr = poper;				//m_Operation;

	auto pos = poper.find( ' ' );

	if (pos == std::string::npos)
	{
		// Parametro unico, dev'essere una costante o un link
// 		if (tmpstr.find_first_not_of("0123456789") == std::string::npos)
// 		{
// 			// costante
// 			auto value = static_cast<uint16_t>(std::stoul(tmpstr));
// 			m_Node = std::make_unique<TNode_Link>(m_Name, value);
// 		}
// 		else
//		{

		return std::make_unique<TWire_Link>( pname, poper );

		// 		auto locnode = std::make_unique<TWire_Link>(pname, tmpstr);
		// 		_Set_Node(std::move(locnode));

		// 			auto parent = _Find(tmpstr);
		// 
		// 			if (parent != nullptr
		// 					&& parent->Node() != nullptr)
		// 			{
		// 				auto locnode = std::make_unique<TNode_Link>(parent->Node());
		// 				Set_Node(std::move(locnode));
		// 			}

		//		}

		//		return true;
	}

	const auto firststr = poper.substr( 0, pos );
	const auto tmpstr = poper.substr( pos + 1 );

	if (firststr.empty())
	{
		return nullptr;		// false;
	}

	if (firststr == "NOT")
	{
		// Operazione NOT
		return std::make_unique<TWire_NOT>( pname, tmpstr );

		// 		auto locnode = std::make_unique<TNode_NOT>(m_Name, tmpstr);
		// 		_Set_Node(std::move(locnode));

		// 		auto parent = _Find(tmpstr);
		// 
		// 		if (parent != nullptr
		// 				&& parent->Node() != nullptr)
		// 		{
		// 			auto locnode = std::make_unique<TNode_NOT>(parent->Node());
		// 			pwire.Set_Node(std::move(locnode));
		// 		}

		//		return true;
	}

	pos = tmpstr.find( ' ' );
	auto oper = tmpstr.substr( 0, pos );
	auto secondstr = tmpstr.substr( pos + 1 );

	if (secondstr.empty())
	{
		return nullptr;		//false;
	}

	// 	auto firstparent = _Find(firststr);
	// 
	// 	if (firstparent == nullptr
	// 			|| firstparent->Node() == nullptr
	// 			)
	// 	{
	// 		return;
	// 	}

	if (oper == "LSHIFT")
	{
		auto offset = std::stoul( std::string( secondstr ) );

		//		auto locnode = std::make_unique<TNode_LSHIFT>(firstparent->Node(), offset);

		return std::make_unique<TWire_LSHIFT>( pname, firststr, offset );
		// 		auto locnode = std::make_unique<TNode_LSHIFT>( m_Name, firststr, offset);
		// 		_Set_Node(std::move(locnode));
		// 		return true;
	}

	if (oper == "RSHIFT")
	{
		auto offset = std::stoul( std::string( secondstr ) );
		//		auto locnode = std::make_unique<TNode_RSHIFT>(firstparent->Node(), offset);

		return std::make_unique<TWire_RSHIFT>( pname, firststr, offset );

		// 		auto locnode = std::make_unique<TNode_RSHIFT>(m_Name, firststr, offset);
		// 		_Set_Node(std::move(locnode));
		// 		return true;
	}

	// 	auto secondparent = _Find(secondstr);
	// 
	// 	if (secondparent == nullptr
	// 			|| secondparent->Node() == nullptr
	// 			)
	// 	{
	// 		return;
	// 	}

	if (oper == "AND")
	{
		//		auto locnode = std::make_unique<TNode_AND>(firstparent->Node(), secondparent->Node());
		return std::make_unique<TWire_AND>( pname, firststr, secondstr );
		// 		auto locnode = std::make_unique<TNode_AND>(m_Name, firststr, secondstr);
		// 		_Set_Node(std::move(locnode));
		// 		return true;
	}
	if (oper == "OR")
	{
		//		auto locnode = std::make_unique<TNode_OR>(firstparent->Node(), secondparent->Node());
		return std::make_unique<TWire_OR>( pname, firststr, secondstr );
		// 		auto locnode = std::make_unique<TNode_OR>(m_Name, firststr, secondstr);
		// 		_Set_Node(std::move(locnode));
		// 		return true;
	}

	return nullptr;	// false;
}


}


