

#include "TAoC_Index.h"


#include "2015/TAoC_15_Index.h"





std::unique_ptr<TAoC_Solver> Get_Solver( const TPuzzleID& id )
{
	if (id.Year < 2015)
	{
		throw std::exception( "Invalid year." );
	}

	switch (id.Year)
	{
	case 2015: return y15::Get_Solver( id );

	default: return nullptr;
	}

}
