
#include "TestMD5.hpp"

#include "JMD5.hpp"


// TODO: Move lib tests in a Unit Test project. "TTest_result" is for AoC test, doesn't work well here.

TTestResult_Group Test_TMD5()
{
	TTestInput_Group ltests = {
		TTestInput::Create_Example( "MD5 T01", {""}, "d41d8cd98f00b204e9800998ecf8427e" ),
		TTestInput::Create_Example( "MD5 T02", {"a"}, "0cc175b9c0f1b6a831c399e269772661" ),
		TTestInput::Create_Example( "MD5 T03", {"abc"}, "900150983cd24fb0d6963f7d28e17f72" ),
		TTestInput::Create_Example( "MD5 T04", {"message digest"}, "f96b697d7cb7938d525a2f31aaf161d0" ),
		TTestInput::Create_Example( "MD5 T05", {"abcdefghijklmnopqrstuvwxyz"}, "c3fcd3d76192e4007dfb496cca67e13b" ),
		TTestInput::Create_Example( "MD5 T06", {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"}, "d174ab98d277d9f5a5611c2c9f419d9f" ),
		TTestInput::Create_Example( "MD5 T07", {"12345678901234567890123456789012345678901234567890123456789012345678901234567890"}, "57edf4a22be3c955ac49da2e2107b67a" ),
	};

	TTestResult_Group result;


	for (const auto& curr : ltests)
	{
		//TMD5 test( curr.input );

		result.Add( { curr, Calc_MD5( curr.Input() ) } );	// test.String()
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


		result.Add( { TTestInput::Create_Example( "MD5 Multi string", {"<many numbers>"}, "57edf4a22be3c955ac49da2e2107b67a" ), test.Get_MD5() } );
	}


	{
		TMD5_Continuous test;

		result.Add( { TTestInput::Create_Example( "MD5 Multi step 1", {""}, "d41d8cd98f00b204e9800998ecf8427e" ), test.Get_MD5() } );	//  ""

		test.Update( "a" );

		result.Add( { TTestInput::Create_Example( "MD5 Multi step 2", {"a"}, "0cc175b9c0f1b6a831c399e269772661" ), test.Get_MD5() } );	//  "a"

		test.Update( "bc" );

		result.Add( { TTestInput::Create_Example( "MD5 Multi step 3", {"abc"}, "900150983cd24fb0d6963f7d28e17f72" ), test.Get_MD5() } );	//  "abc"

	}



	return result;

}

