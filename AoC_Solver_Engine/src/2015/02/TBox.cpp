
#include "TBox.h"

#include <algorithm>



TBox::TBox( std::string const& pin )
{
	i_ParseInput( pin );

	i_CalcAree();
}

TBox::TBox( int pl, int pw, int ph )
// 	:
// 	m_l(pl),
// 	m_w(pw),
// 	m_h(ph)
{
	m_Dimension[0] = pl;
	m_Dimension[1] = pw;
	m_Dimension[2] = ph;

	i_CalcAree();
}

int TBox::PaperSize() const
{
	//auto minFace = std::min(std::min(m_Faces[0], m_Faces[1]), m_Faces[2]);

	return m_TotalArea + m_Faces[0];
}

int TBox::RibbonLenght() const
{
	return (2 * m_Dimension[0]) + (2 * m_Dimension[1]) + m_Volume;
}



void TBox::i_ParseInput( std::string const& pin )
{
	std::string work( pin );

	auto pos = work.find( 'x' );
	m_Dimension[0] = stoi( work.substr( 0, pos ) );
	work = work.substr( pos + 1 );

	pos = work.find( 'x' );
	m_Dimension[1] = stoi( work.substr( 0, pos ) );
	work = work.substr( pos + 1 );

	m_Dimension[2] = stoi( work );

	std::sort( m_Dimension.begin(), m_Dimension.end() );
}

void TBox::i_CalcAree()
{
	m_Faces[0] = m_Dimension[0] * m_Dimension[1];
	m_Faces[1] = m_Dimension[1] * m_Dimension[2];
	m_Faces[2] = m_Dimension[2] * m_Dimension[0];

	std::sort( m_Faces.begin(), m_Faces.end() );

	m_Volume = m_Dimension[0] * m_Dimension[1] * m_Dimension[2];

	m_TotalArea = 2 * (m_Faces[0] + m_Faces[1] + m_Faces[2]);
}


