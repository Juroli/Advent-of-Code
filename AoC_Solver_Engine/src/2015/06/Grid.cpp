
#include "Grid.hpp"


TGrid::TGrid( int pwidth, int pheight )
	: m_Width( pwidth )
	, m_Height( pheight )
	, m_Grid( m_Width * m_Height, 0)
{
}


int TGrid::Get( const TCoord& apos ) const
{
	return m_Grid[i_ToID( apos )];
}


void TGrid::RunOps( const TCoord& astart, const TCoord& aend, std::function<int8_t(const int8_t&)> afunc )
{
	const auto startID = i_ToID( astart );
	const auto dx = aend.x - astart.x +1;
	const auto dy = aend.y - astart.y +1;

	auto rangeID = startID;
	for (auto y = 0; y < dy; ++y)
	{
		auto currID = rangeID;

		for (auto x = 0; x < dx; ++x)
		{
			m_Grid[currID] = afunc( m_Grid[currID] );

			++currID;
		}

		rangeID += m_Width;
	}
}


int TGrid::SumAll() const noexcept
{
	int result = 0;

	for (const auto& curr : m_Grid)
	{
		result += curr;
	}

	return result;
}


//__________________________________________________________________________________________________


TOps_Base::TOps_Base( int width, int height )
	: m_Grid(width, height)
{
}


void TOps_Base::ParseLine( std::string pline )
{
	enum class ecmd
	{
		NONE,
		SET_ON,
		SET_OFF,
		TOGGLE
	};

	ecmd operation = ecmd::NONE;

	// turn on 489,959 through 759,964
	std::string delim( " " );

	std::string work = i_ExtractToken( pline, delim );

	if (work == "turn")
	{
		work = i_ExtractToken( pline, delim );
		if (work == "on")
		{
			operation = ecmd::SET_ON;
		}
		else if (work == "off")
		{
			operation = ecmd::SET_OFF;
		}
	}
	else if (work == "toggle")
	{
		operation = ecmd::TOGGLE;
	}

	TCoord startcoord;
	work = i_ExtractToken( pline, delim );
	startcoord.x = std::stoi( i_ExtractToken( work, "," ) );
	startcoord.y = std::stoi( i_ExtractToken( work, "," ) );

	work = i_ExtractToken( pline, delim );
	if (work != "through")
	{
		int error = 0;
	}

	TCoord endcoord;
	work = i_ExtractToken( pline, delim );
	endcoord.x = std::stoi( i_ExtractToken( work, "," ) );
	endcoord.y = std::stoi( i_ExtractToken( work, "," ) );

	switch (operation)
	{
	case ecmd::SET_ON:
		TurnOn( startcoord, endcoord );
		break;
	case ecmd::SET_OFF:
		TurnOff( startcoord, endcoord );
		break;
	case ecmd::TOGGLE:
		Toggle( startcoord, endcoord );
		break;

	case ecmd::NONE:
	default:
		int error = 0;
		break;
	}
}


std::string TOps_Base::i_ExtractToken( std::string& pstr, std::string const& delim )
{
	auto pos = pstr.find( delim );
	std::string ret = pstr.substr( 0, pos );
	pstr = pstr.substr( pos + delim.size() );

	return ret;
}
