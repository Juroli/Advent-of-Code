
#include "TAoC_15_Index.h"


#include "01/TAoCS_15_01.h"
#include "02/TAoCS_15_02.h"
#include "03/TAoCS_15_03.h"


namespace y15
{

std::unique_ptr<TAoC_Solver> Get_Solver( int aday, char apart )
{
	if (aday < 1 || aday > 25)
	{
		throw std::exception( "Invalid day." );
	}

	switch (aday)
	{
	case 1: return y15::d01::Get_Solver( apart );
	case 2: return y15::d02::Get_Solver( apart );
	case 3: return y15::d03::Get_Solver( apart );

	default: return std::make_unique<TAoC_Solver_NULL>();
	}

}


}
