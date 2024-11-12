

#include "TAoC_Index.h"


#include "2015/TAoC_15_Index.h"





std::unique_ptr<TAoC_Solver> Get_Solver( int ayear, int aday, char apart )
{
	if (ayear < 2015)
	{
		throw std::exception( "Invalid year." );
	}

	switch (ayear)
	{
	case 2015: return y15::Get_Solver( aday, apart );

	default: return nullptr;
	}

}
