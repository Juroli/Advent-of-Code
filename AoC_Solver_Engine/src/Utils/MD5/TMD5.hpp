
#ifndef TMD5_H_
#define TMD5_H_

//#include <istream>
//#include <array>

#include <vector>

#include <string>



class TMD5
{
public:

	TMD5();
	//	TMD5(std::istream const &pin);
	explicit TMD5( std::string const& pin );
	~TMD5();

	//	TMD5 &operator +=( std::string const &pstr );

	char Value( const unsigned int pid ) const { return m_digest[pid]; }

	std::string String() const;

private:

	void _CalcMD5();

	void _MD5Init();
	//void _MD5Update(char const *, uint32_t);
	void _MD5Update( std::vector<char> const& pinput );
	// 	void _MD5Update ( std::input_iterator_tag const &pstart
	// 					, std::input_iterator_tag const &pend
	// 					);
	//	void _O_MD5Update (std::vector<char> const &pinput, uint32_t inputLen);

	void _MD5Update( std::vector<char>::const_iterator pstart
		, std::vector<char>::const_iterator const& pend );

	// 	template <class TTInputIterator>
	// 	void _Tmpl_MD5Update(TTInputIterator const &pstart, TTInputIterator const &pend);

	void _MD5Final();


	//void _MD5Transform(uint32_t state[4], char const [64]);
	//void _MD5Transform (uint32_t state[4], std::array<char, 64> block);
	void _MD5Transform( char const [64] );
	//void _MD5Transform (std::array<char, 64> block);
	//void _Encode(char *, const std::uint32_t *, uint32_t);
	std::vector<char> _Encode( std::uint64_t const& input );

	//	void _Decode(std::uint32_t *, unsigned char const *, uint32_t);
	void _MD5_memcpy( char*, char const*, uint32_t );
	//	void _MD5_memset(unsigned char *, int, uint32_t);

private:

	/* MD5 context. */
	// 	struct MD5_CTX
	// 	{
	//uint32_t state[4];                                   /* state (ABCD) */
	//uint32_t m_count[2];					/* number of bits, modulo 2^64 (lsb first) */
	uint64_t m_bitcount;					/* number of bits, modulo 2^64 (lsb first) */

	char m_buffer[64];                         /* input buffer */

	union
	{
		char m_block[64];
		std::uint32_t m_xdata[16];
	};

	//std::array<char, 64> m_buffer;
														//};
														//std::array<unsigned int, 32> m_MD5;
	//std::array<unsigned int, 4> m_MD5;
	//uint32_t m_MD5[4];
	//unsigned char m_digest[16];
	//unsigned char *m_digest;

	union
	{
		uint32_t m_MD5[4];
		unsigned char m_digest[16];
		//unsigned char *m_digest;
	};

private:

	//static char PADDING[64];	// = {
	static std::vector<char> PADDING;
	//static std::array<char, 64> PADDING;
	// 		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	// 		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	// 		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	// 	};

	static const std::uint32_t S11 = 7;						//	#define S11 7
	static const std::uint32_t S12 = 12;						//	#define S12 12
	static const std::uint32_t S13 = 17;						//	#define S13 17
	static const std::uint32_t S14 = 22;						//	#define S14 22
	static const std::uint32_t S21 = 5;						//	#define S21 5
	static const std::uint32_t S22 = 9;						//	#define S22 9
	static const std::uint32_t S23 = 14;						//	#define S23 14
	static const std::uint32_t S24 = 20;						//	#define S24 20
	static const std::uint32_t S31 = 4;						//	#define S31 4
	static const std::uint32_t S32 = 11;						//	#define S32 11
	static const std::uint32_t S33 = 16;						//	#define S33 16
	static const std::uint32_t S34 = 23;						//	#define S34 23
	static const std::uint32_t S41 = 6;						//	#define S41 6
	static const std::uint32_t S42 = 10;						//	#define S42 10
	static const std::uint32_t S43 = 15;						//	#define S43 15
	static const std::uint32_t S44 = 21;						//	#define S44 21

	static std::uint32_t _F( std::uint32_t x, std::uint32_t y, std::uint32_t z ) { return ((x & y) | ((~x) & z)); }
	static std::uint32_t _G( std::uint32_t x, std::uint32_t y, std::uint32_t z ) { return (x & z) | (y & (~z)); }
	static std::uint32_t _H( std::uint32_t x, std::uint32_t y, std::uint32_t z ) { return (x ^ y ^ z); }
	static std::uint32_t _I( std::uint32_t x, std::uint32_t y, std::uint32_t z ) { return (y ^ (x | (~z))); }

	// ROTATE_LEFT rotates x left n bits.
	static std::uint32_t _BitRotation_Left( std::uint32_t x, int n ) { return ((x << n) | (x >> (32 - n))); }
	//std::uint32_t _BitRotation_Left(std::uint32_t x, int n)					{ return _rotl(x, n); }


	static std::uint32_t _FF( std::uint32_t a
		, std::uint32_t b
		, std::uint32_t c
		, std::uint32_t d
		, std::uint32_t x
		, std::uint32_t s
		, std::uint32_t ac
	)
	{
		return _BitRotation_Left( a + _F( b, c, d ) + x + ac, s ) + b;
	}

	static std::uint32_t _GG( std::uint32_t a
		, std::uint32_t b
		, std::uint32_t c
		, std::uint32_t d
		, std::uint32_t x
		, std::uint32_t s
		, std::uint32_t ac
	)
	{
		return _BitRotation_Left( a + _G( b, c, d ) + x + ac, s ) + b;
	}

	static std::uint32_t _HH( std::uint32_t a
		, std::uint32_t b
		, std::uint32_t c
		, std::uint32_t d
		, std::uint32_t x
		, std::uint32_t s
		, std::uint32_t ac
	)
	{
		return _BitRotation_Left( a + _H( b, c, d ) + x + ac, s ) + b;
	}

	static std::uint32_t _II( std::uint32_t a
		, std::uint32_t b
		, std::uint32_t c
		, std::uint32_t d
		, std::uint32_t x
		, std::uint32_t s
		, std::uint32_t ac
	)
	{
		return _BitRotation_Left( a + _I( b, c, d ) + x + ac, s ) + b;
	}


};

//template <class TTInputIterator>
// void TMD5::_Tmpl_MD5Update(TTInputIterator const &pstart, TTInputIterator const &pend)
// {
// 	//uint32_t i;			//, index;		//, partLen;
// 
// 	/* Compute number of bytes mod 64 */
// 	// index = (m_count[0] >> 3) & 0x3F;
// 	//index = (m_count[0] / 8) % 64;
// 	uint32_t index = (m_bitcount / 8) % 64; 
// 
// 	/* Update number of bits */
// 	// 	if ((m_count[0] += (inputLen << 3))
// 	// 		< (inputLen << 3))
// 	// 	{
// 	// 		m_count[1]++;
// 	// 	}
// 	// 	m_count[1] += (inputLen >> 29);
// 	m_bitcount += inputLen * 8;
// 
// 	uint32_t partLen = 64 - index;
// 
// 	uint32_t i = 0;
// 
// 	/* Transform as many times as possible.
// 	*/
// 	if (inputLen >= partLen)
// 	{
// 		_MD5_memcpy(&m_buffer[index], pinput.data(), partLen);
// 		_MD5Transform (m_buffer);
// 
// 		for (i = partLen; i + 63 < inputLen; i += 64)
// 		{
// 			_MD5Transform (&pinput.data()[i]);
// 		}
// 
// 		index = 0;
// 	}
// 	// 	else
// 	// 	{
// 	// 		i = 0;
// 	// 	}
// 
// 	/* Buffer remaining input */
// 	_MD5_memcpy(&m_buffer[index], &pinput.data()[i], inputLen-i);
// 
// }



#endif // TMD5_h__

