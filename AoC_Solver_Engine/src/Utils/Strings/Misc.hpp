
#pragma once


#include <string>
#include <locale>


constexpr char WHITE_SPACES[] = " \t\n\r\f\v";


void trim_l( std::string& astr, std::string_view aws = WHITE_SPACES );
void trim_r( std::string& astr, std::string_view aws = WHITE_SPACES );
void trim( std::string& astr, std::string_view aws = WHITE_SPACES );


std::string_view trim_l_copy( std::string_view astr, std::string_view aws = WHITE_SPACES );
std::string_view trim_r_copy( std::string_view astr, std::string_view aws = WHITE_SPACES );
std::string_view trim_copy( std::string_view astr, std::string_view aws = WHITE_SPACES );


