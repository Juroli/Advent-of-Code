
#pragma once

#include <vector>


#include "AoC_Solver.hpp"



bool Check_TestResults( const TTestResult_Group& results );

void Print_TestResults( const TTestResult_Group& results );


TTestResult_Group Run_Test( const TPuzzleID& apid );

bool RunPrint_Test( const TPuzzleID& apid );

void RunPrint_Tests( const TPuzzleID& apid_start, const TPuzzleID& apid_end );

