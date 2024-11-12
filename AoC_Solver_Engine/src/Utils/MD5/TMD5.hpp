
#ifndef TMD5_h__
#define TMD5_h__

#include <istream>
#include <array>


class TMD5
{
public:

	TMD5();
	//	TMD5(std::istream const &pin);
	TMD5( std::string const& pin );
	~TMD5();

	TMD5& operator +=( std::string const& pstr );

	unsigned char Value( unsigned int pid ) const { return m_digest[pid]; }

	std::string String() const;

private:

	void _CalcMD5();

	void _MD5Init();
	void _MD5Update( unsigned char*, uint32_t );
	void _MD5Final();


	void _MD5Transform( uint32_t state[4], unsigned char[64] );
	void _Encode( unsigned char*, const std::uint32_t*, uint32_t );
	void _Decode( std::uint32_t*, unsigned char*, uint32_t );
	void _MD5_memcpy( unsigned char*, unsigned char*, uint32_t );
	void _MD5_memset( unsigned char*, int, uint32_t );

private:

	/* MD5 context. */
	// 	struct MD5_CTX
	// 	{
	//uint32_t state[4];                                   /* state (ABCD) */
	uint32_t m_count[2];					/* number of bits, modulo 2^64 (lsb first) */
	unsigned char m_buffer[64];                         /* input buffer */
	//};
	//std::array<unsigned int, 32> m_MD5;
//std::array<unsigned int, 4> m_MD5;
	uint32_t m_MD5[4];
	unsigned char m_digest[16];

private:

	static unsigned char PADDING[64];	// = {
	// 		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	// 		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	// 		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	// 	};

	const std::uint32_t S11 = 7;						//	#define S11 7
	const std::uint32_t S12 = 12;						//	#define S12 12
	const std::uint32_t S13 = 17;						//	#define S13 17
	const std::uint32_t S14 = 22;						//	#define S14 22
	const std::uint32_t S21 = 5;						//	#define S21 5
	const std::uint32_t S22 = 9;						//	#define S22 9
	const std::uint32_t S23 = 14;						//	#define S23 14
	const std::uint32_t S24 = 20;						//	#define S24 20
	const std::uint32_t S31 = 4;						//	#define S31 4
	const std::uint32_t S32 = 11;						//	#define S32 11
	const std::uint32_t S33 = 16;						//	#define S33 16
	const std::uint32_t S34 = 23;						//	#define S34 23
	const std::uint32_t S41 = 6;						//	#define S41 6
	const std::uint32_t S42 = 10;						//	#define S42 10
	const std::uint32_t S43 = 15;						//	#define S43 15
	const std::uint32_t S44 = 21;						//	#define S44 21

	std::uint32_t _F( std::uint32_t x, std::uint32_t y, std::uint32_t z ) { return ((x & y) | ((~x) & z)); }
	std::uint32_t _G( std::uint32_t x, std::uint32_t y, std::uint32_t z ) { return (x & z) | (y & (~z)); }
	std::uint32_t _H( std::uint32_t x, std::uint32_t y, std::uint32_t z ) { return (x ^ y ^ z); }
	std::uint32_t _I( std::uint32_t x, std::uint32_t y, std::uint32_t z ) { return (y ^ (x | (~z))); }

	// ROTATE_LEFT rotates x left n bits.
	std::uint32_t _BitRotation_Left( std::uint32_t x, int n ) { return ((x << n) | (x >> (32 - n))); }


	std::uint32_t _FF( std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d,
		std::uint32_t x, int s, std::uint32_t ac )
	{
		return _BitRotation_Left( a + _F( b, c, d ) + x + ac, s ) + b;
	}
	std::uint32_t _GG( std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d,
		std::uint32_t x, int s, std::uint32_t ac )
	{
		return _BitRotation_Left( a + _G( b, c, d ) + x + ac, s ) + b;
	}

	std::uint32_t _HH( std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d,
		std::uint32_t x, int s, std::uint32_t ac )
	{
		return _BitRotation_Left( a + _H( b, c, d ) + x + ac, s ) + b;
	}
	std::uint32_t _II( std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d,
		std::uint32_t x, int s, std::uint32_t ac )
	{
		return _BitRotation_Left( a + _I( b, c, d ) + x + ac, s ) + b;
	}


};


#endif // TMD5_h__

