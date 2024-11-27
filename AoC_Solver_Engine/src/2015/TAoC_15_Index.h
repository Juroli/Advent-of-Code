
#pragma once


#include <memory>
#include "TAoC_Solver.h"


namespace y15
{

std::unique_ptr<TAoC_Solver> Get_Solver( const TPuzzleID& id );

}


