
#include "Misc.hpp"



void trim_l( std::string& astr, std::string_view aws )
{
	astr.erase( 0, astr.find_first_not_of( aws ) );
}

void trim_r( std::string& astr, std::string_view aws )
{
	astr.erase( astr.find_last_not_of( aws ) + 1 );
}

void trim( std::string& astr, std::string_view aws )
{
	trim_l( astr, aws );
	trim_r( astr, aws );
}


std::string_view trim_l_copy( std::string_view astr, std::string_view aws )
{
	return astr.substr( astr.find_first_not_of( aws ) );
}

std::string_view trim_r_copy( std::string_view astr, std::string_view aws )
{
	return astr.substr( 0, astr.find_last_not_of( aws ) + 1 );
}

std::string_view trim_copy( std::string_view astr, std::string_view aws )
{
	return astr.substr( astr.find_first_not_of( aws ), astr.find_last_not_of( aws ) + 1 );
}



