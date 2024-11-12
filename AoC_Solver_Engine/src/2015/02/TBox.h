
#pragma once


#include <string>
//#include <vector>
#include <array>



class TBox
{
public:
	TBox() = delete;
	TBox( std::string const& pin );
	TBox( int pl, int pw, int ph );

	int PaperSize() const;
	int RibbonLenght() const;

private:

	void i_ParseInput( std::string const& pin );
	void i_CalcAree();

	// 	int m_l;
	// 	int m_w;
	// 	int m_h;

	std::array<int, 3> m_Dimension;
	std::array<int, 3> m_Faces;

	int m_Volume;

	int m_TotalArea;
};


