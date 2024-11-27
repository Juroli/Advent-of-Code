
#include "TAoCS_15_03.h"

#include "T2DMap.h"



namespace y15::d03
{


std::unique_ptr<TAoC_Solver> Get_Solver( uint8_t apart )
{
	switch (apart)
	{
	case 1: return std::make_unique< TAoCS_P1>();
	case 2: return std::make_unique< TAoCS_P2>();
	default: throw std::exception( "Invalid part." );
	}
}



//__________________________________________________________________________________________________



//std::string TAoCS_P1::i_Solve_Run() const
//{
//	return STR_IMPLEMENTED;
//}


std::string TAoCS_P1::i_Solve_Run( std::string_view input ) const
{
	if (input == STR_SOLVE_CHECK)
	{
		return STR_IMPLEMENTED;
	}

	if (input.empty())
	{
		return { "" };
	}

	T2DMap deliver( input, 1 );
	return std::to_string( deliver.NHouses() );
}


TTestInput_Group TAoCS_P1::i_Test_Prepare() const
{
	return {
		TTestInput::Create_Example( "Ex01", ">", "2" ) ,
		TTestInput::Create_Example( "Ex02", "^>v<", "4" ) ,
		TTestInput::Create_Example( "Ex03", "^v^v^v^v^v", "2" ) ,
	};
}

std::string TAoCS_P1::i_Test_Run( std::string_view astrin ) const
{
	return Solve( astrin );
}



//__________________________________________________________________________________________________



//std::string TAoCS_P2::i_Solve_Run() const
//{
//	return STR_IMPLEMENTED;
//}


std::string TAoCS_P2::i_Solve_Run( std::string_view input ) const
{
	if (input == STR_SOLVE_CHECK)
	{
		return STR_IMPLEMENTED;
	}

	if (input.empty())
	{
		return { "" };
	}

	T2DMap deliver( input, 2 );
	return std::to_string( deliver.NHouses() );
}


TTestInput_Group TAoCS_P2::i_Test_Prepare() const
{
	return {
		TTestInput::Create_Example( "Ex01", "^v", "3" ) ,
		TTestInput::Create_Example( "Ex02", "^>v<", "3" ) ,
		TTestInput::Create_Example( "Ex03", "^v^v^v^v^v", "11" ) ,
	};
}

std::string TAoCS_P2::i_Test_Run( std::string_view astrin ) const
{
	return Solve( astrin );
}



}


