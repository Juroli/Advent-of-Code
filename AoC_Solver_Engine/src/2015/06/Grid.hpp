
#pragma once


#include <vector>
#include <string>

#include <functional>

struct TCoord
{
	int x;
	int y;
};


class TGrid
{
public:

	TGrid() = delete;
	TGrid( int pwidth, int pheight );

	int Get( const TCoord& apos ) const;

	void RunOps( const TCoord& astart, const TCoord& aend, std::function<int8_t( const int8_t& )> afunc );

	int SumAll() const noexcept;

private:

	constexpr uint32_t i_ToID( const TCoord& apos ) const noexcept { return (apos.y * m_Width) + apos.x; }
	//constexpr uint32_t i_ToID( int ax, int ay ) const noexcept { return (ay * m_Width) + ax; }

private:

	uint32_t m_Width;
	uint32_t m_Height;

	std::vector<int8_t> m_Grid;
};


class TOps_Base
{
public:

	TOps_Base( int width, int height );

	virtual void TurnOn( const TCoord& astart, const TCoord& aend ) = 0;
	virtual void TurnOff( const TCoord& astart, const TCoord& aend ) = 0;
	virtual void Toggle( const TCoord& astart, const TCoord& aend ) = 0;


	void ParseLine( std::string pline );
	int SumAll() const noexcept { return m_Grid.SumAll(); }

private:

	static std::string i_ExtractToken( std::string& pstr, std::string const& delim );

protected:

	TGrid m_Grid;

};



class TOps_Bool : public TOps_Base
{
public:

	TOps_Bool( int width, int height ) : TOps_Base( width, height ) {}

	// Inherited via TOps_Base
	void TurnOn( const TCoord& astart, const TCoord& aend ) override { m_Grid.RunOps( astart, aend, []( const uint8_t& ) { return 1; } ); }
	void TurnOff( const TCoord& astart, const TCoord& aend ) override { m_Grid.RunOps( astart, aend, []( const uint8_t& ) { return 0; } ); }
	void Toggle( const TCoord& astart, const TCoord& aend ) override { m_Grid.RunOps( astart, aend, []( const uint8_t& val ) { return 1 - val; } ); }
};


class TOps_Int : public TOps_Base
{
public:

	TOps_Int( int width, int height ) : TOps_Base( width, height ) {}

	// Inherited via TOps_Base
	void TurnOn( const TCoord& astart, const TCoord& aend ) override { m_Grid.RunOps( astart, aend, []( const uint8_t& val ) { return val + 1; } ); }
	void TurnOff( const TCoord& astart, const TCoord& aend ) override { m_Grid.RunOps( astart, aend, []( const uint8_t& val ) { return std::max( val - 1, 0 ); } ); }
	void Toggle( const TCoord& astart, const TCoord& aend ) override { m_Grid.RunOps( astart, aend, []( const uint8_t& val ) { return val + 2; } ); }
};



