
#include "TAoC_15_Index.h"


#include "01/TAoCS_15_01.h"
#include "02/TAoCS_15_02.h"
#include "03/TAoCS_15_03.h"
#include "04/TAoCS_15_04.h"
#include "05/TAoCS_15_05.h"
#include "06/TAoCS_15_06.h"
#include "07/TAoCS_15_07.h"
//#include "08/TAoCS_15_08.h"
//#include "09/TAoCS_15_09.h"
//#include "10/TAoCS_15_10.h"
//#include "11/TAoCS_15_11.h"
//#include "12/TAoCS_15_12.h"
//#include "13/TAoCS_15_13.h"
//#include "14/TAoCS_15_14.h"
//#include "15/TAoCS_15_15.h"
//#include "16/TAoCS_15_16.h"
//#include "17/TAoCS_15_17.h"
//#include "18/TAoCS_15_18.h"
//#include "19/TAoCS_15_19.h"
//#include "20/TAoCS_15_20.h"
//#include "21/TAoCS_15_21.h"
//#include "22/TAoCS_15_22.h"
//#include "23/TAoCS_15_23.h"
//#include "24/TAoCS_15_24.h"
//#include "25/TAoCS_15_25.h"


namespace y15
{

std::unique_ptr<TAoC_Solver> Get_Solver( const TPuzzleID& id )
{
	if (id.Day < 1 || id.Day > 25)
	{
		throw std::exception( "Invalid day." );
	}

	switch (id.Day)
	{
	case  1: return y15::d01::Get_Solver( id.Part );
	case  2: return y15::d02::Get_Solver( id.Part );
	case  3: return y15::d03::Get_Solver( id.Part );
	case  4: return y15::d04::Get_Solver( id.Part );
	case  5: return y15::d05::Get_Solver( id.Part );
	case  6: return y15::d06::Get_Solver( id.Part );
	case  7: return y15::d07::Get_Solver( id.Part );
	//case  8: return y15::d08::Get_Solver( id.Part );
	//case  9: return y15::d09::Get_Solver( id.Part );
	//case 10: return y15::d10::Get_Solver( id.Part );
	//case 11: return y15::d11::Get_Solver( id.Part );
	//case 12: return y15::d12::Get_Solver( id.Part );
	//case 13: return y15::d13::Get_Solver( id.Part );
	//case 14: return y15::d14::Get_Solver( id.Part );
	//case 15: return y15::d15::Get_Solver( id.Part );
	//case 16: return y15::d16::Get_Solver( id.Part );
	//case 17: return y15::d17::Get_Solver( id.Part );
	//case 18: return y15::d18::Get_Solver( id.Part );
	//case 19: return y15::d19::Get_Solver( id.Part );
	//case 20: return y15::d20::Get_Solver( id.Part );
	//case 21: return y15::d21::Get_Solver( id.Part );
	//case 22: return y15::d22::Get_Solver( id.Part );
	//case 23: return y15::d23::Get_Solver( id.Part );
	//case 24: return y15::d24::Get_Solver( id.Part );
	//case 25: return y15::d25::Get_Solver( id.Part );

	

	default: return std::make_unique<TAoC_Solver_NULL>();
	}

}


}
