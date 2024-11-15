
#pragma once

#include <vector>
#include <string>



struct TCoord
{
	int x;
	int y;
};

bool operator == ( TCoord const& pa, TCoord const& pb );



class TDeliverer
{
public:

	TCoord const& Position() const { return m_Position; }
	void Move( char pdir );

private:

	TCoord m_Position;

};



class T2DMap
{
public:

	//static const int N_DELIVERERS = 2;

	T2DMap( const std::string& astr, int anumdeliver );

	[[nodiscard]] auto NHouses() const { return m_OldPos.size(); }

private:

	void i_ParseString( const std::string& pstr );


private:


	std::vector<TCoord> m_OldPos;
	std::vector<TDeliverer> m_LSanta;
};



//void CalcSolution();


