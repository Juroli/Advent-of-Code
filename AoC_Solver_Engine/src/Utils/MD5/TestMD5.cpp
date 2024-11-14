
#include "TestMD5.hpp"

#include "TMD5.hpp"


// TODO: Move lib tests in a Unit Test project. "TTest_result" is for AoC test, doesn't work well here.

std::vector<TTest_result> Test_TMD5()
{
	std::vector<TTest_input> ltests = {
		{ "", "d41d8cd98f00b204e9800998ecf8427e"},
		{ "a", "0cc175b9c0f1b6a831c399e269772661"},
		{ "abc", "900150983cd24fb0d6963f7d28e17f72"},
		{ "message digest", "f96b697d7cb7938d525a2f31aaf161d0"},
		{ "abcdefghijklmnopqrstuvwxyz", "c3fcd3d76192e4007dfb496cca67e13b"},
		{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", "d174ab98d277d9f5a5611c2c9f419d9f"},
		{ "12345678901234567890123456789012345678901234567890123456789012345678901234567890", "57edf4a22be3c955ac49da2e2107b67a"},
	};

	std::vector<TTest_result> result;


	for (const auto& curr : ltests)
	{
		//TMD5 test( curr.input );

		result.push_back( { curr, Calc_MD5( curr.input ) } );	// test.String()
	}


	{
		TMD5_Continuous test;

		test.Update( "1234567890" );
		test.Update( "1234567890" );
		test.Update( "1234567890" );
		test.Update( "1234567890" );
		test.Update( "1234567890" );
		test.Update( "1234567890" );
		test.Update( "1234567890" );
		test.Update( "1234567890" );


		result.push_back( { { "Multi string", "57edf4a22be3c955ac49da2e2107b67a"}, test.Get_MD5()});
	}


	{
		TMD5_Continuous test;

		result.push_back( { { "Multi step 1", "d41d8cd98f00b204e9800998ecf8427e"}, test.Get_MD5() } );	//  ""

		test.Update( "a" );

		result.push_back( { { "Multi step 2", "0cc175b9c0f1b6a831c399e269772661"}, test.Get_MD5() } );	//  "a"

		test.Update( "bc" );

		result.push_back( { { "Multi step 3", "900150983cd24fb0d6963f7d28e17f72"}, test.Get_MD5() } );	//  "abc"

	}



	return result;

}

