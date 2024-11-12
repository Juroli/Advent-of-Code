#include "T2DMap.h"



bool operator==( TCoord const& pa, TCoord const& pb )
{
	return ((pa.x == pb.x) && (pa.y == pb.y));
}

void TDeliverer::Move( char pdir )
{
	switch (pdir)
	{
	case '^':
		{
			++m_Position.y;
			break;
		}
	case '>':
		{
			++m_Position.x;
			break;
		}
	case 'v':
		{
			--m_Position.y;
			break;
		}
	case '<':
		{
			--m_Position.x;
			break;
		}
	default:
		{
			//int breakpoint = 0;
		}
	}
}


T2DMap::T2DMap( const std::string& pstr, int anumdeliver )
	: m_LSanta(anumdeliver)
{
	i_ParseString( pstr );
}


void T2DMap::i_ParseString( const std::string& astr )
{

	TCoord workCoord = { 0, 0 };

	m_OldPos.push_back( workCoord );

	size_t DelID = 0;

	for( const auto& curr: astr)
	{
		m_LSanta[DelID].Move( curr );

		const auto find = std::find( m_OldPos.begin(), m_OldPos.end(), m_LSanta[DelID].Position() );

		if (find == m_OldPos.end())
		{
			m_OldPos.push_back( m_LSanta[DelID].Position() );
		}

		++DelID;
		DelID %= m_LSanta.size();
	}
}


