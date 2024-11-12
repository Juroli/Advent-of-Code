
#pragma once


#include <memory>

#include "TAoC_Solver.h"


std::unique_ptr<TAoC_Solver> Get_Solver( int ayear, int aday, char apart );

