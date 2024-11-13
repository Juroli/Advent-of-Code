
#include "TMD5.hpp"

#include <vector>

#include "gsl/gsl"


//char TMD5::PADDING[64] = {
//std::array<char, 64> TMD5::PADDING = {
const std::vector<uint8_t> PADDING = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};


constexpr uint32_t S11 = 7;						//	#define S11 7
constexpr uint32_t S12 = 12;						//	#define S12 12
constexpr uint32_t S13 = 17;						//	#define S13 17
constexpr uint32_t S14 = 22;						//	#define S14 22
constexpr uint32_t S21 = 5;						//	#define S21 5
constexpr uint32_t S22 = 9;						//	#define S22 9
constexpr uint32_t S23 = 14;						//	#define S23 14
constexpr uint32_t S24 = 20;						//	#define S24 20
constexpr uint32_t S31 = 4;						//	#define S31 4
constexpr uint32_t S32 = 11;						//	#define S32 11
constexpr uint32_t S33 = 16;						//	#define S33 16
constexpr uint32_t S34 = 23;						//	#define S34 23
constexpr uint32_t S41 = 6;						//	#define S41 6
constexpr uint32_t S42 = 10;						//	#define S42 10
constexpr uint32_t S43 = 15;						//	#define S43 15
constexpr uint32_t S44 = 21;						//	#define S44 21

static constexpr uint32_t _F( uint32_t x, uint32_t y, uint32_t z ) { return ((x & y) | ((~x) & z)); }
static constexpr uint32_t _G( uint32_t x, uint32_t y, uint32_t z ) { return (x & z) | (y & (~z)); }
static constexpr uint32_t _H( uint32_t x, uint32_t y, uint32_t z ) { return (x ^ y ^ z); }
static constexpr uint32_t _I( uint32_t x, uint32_t y, uint32_t z ) { return (y ^ (x | (~z))); }

// ROTATE_LEFT rotates x left n bits.
static constexpr uint32_t _BitRotation_Left( uint32_t x, int n ) { return ((x << n) | (x >> (32 - n))); }
//std::uint32_t _BitRotation_Left(std::uint32_t x, int n)					{ return _rotl(x, n); }


static constexpr uint32_t _FF( uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac )
{
	return _BitRotation_Left( a + _F( b, c, d ) + x + ac, s ) + b;
}

static constexpr uint32_t _GG( uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac )
{
	return _BitRotation_Left( a + _G( b, c, d ) + x + ac, s ) + b;
}

static constexpr uint32_t _HH( uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac )
{
	return _BitRotation_Left( a + _H( b, c, d ) + x + ac, s ) + b;
}

static constexpr uint32_t _II( uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac )
{
	return _BitRotation_Left( a + _I( b, c, d ) + x + ac, s ) + b;
}






TMD5::TMD5()
	: m_bytecount( 0 )
	, m_MD5 { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 }
//: m_digest(reinterpret_cast<unsigned char *>(m_MD5))
{
	//_MD5Init();
}

// TMD5::TMD5(std::istream const &pin)
// {
// 	_MD5Init();
// }

TMD5::TMD5( const std::string& pin )
	: m_bytecount( 0 )
	, m_MD5{ 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 }

//: m_digest(reinterpret_cast<unsigned char *>(m_MD5))
{
	//_MD5Init();
	//_MD5Update(buffer.data(), buffer.size());
	//_MD5Update(pin.data(), pin.size());
	//_MD5Update(pin);		//.data());
	i_MD5Update( std::vector<uint8_t>( pin.begin(), pin.end() ) );

	i_MD5Final();

}


TMD5::~TMD5()
{
	// 	for(auto &curr : m_count)
	// 	{
	// 		curr = 0;
	// 	}
	// 	for(auto &curr : m_buffer)
	// 	{
	// 		curr = 0;
	// 	}
	// 
	// 	for(auto &curr : m_MD5)
	// 	{
	// 		curr = 0;
	// 	}
}

std::string TMD5::String() const
{
	std::string result( 32, '+' );
	//result.resize(32);

	const char lookup[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	int pos = 0;
	for (auto i = 0u; i < 4u; ++i)
	{
		result[pos++] = lookup[(m_MD5[i] >> 4) & 0x0F];
		result[pos++] = lookup[m_MD5[i] & 0x0F];

		result[pos++] = lookup[(m_MD5[i] >> 12) & 0x0F];
		result[pos++] = lookup[(m_MD5[i] >> 8) & 0x0F];

		result[pos++] = lookup[(m_MD5[i] >> 20) & 0x0F];
		result[pos++] = lookup[(m_MD5[i] >> 16) & 0x0F];

		result[pos++] = lookup[(m_MD5[i] >> 28) & 0x0F];
		result[pos++] = lookup[(m_MD5[i] >> 24) & 0x0F];
		
	}


	//const void* tmp_ptr = m_MD5;
	//const auto digest = static_cast<const uint8_t*>(tmp_ptr);

	//for (int i = 0, j = 0; i < 16; ++i)
	//{
	//	//char tmp1 = m_digest[i];
	//	//char tmp2 = (tmp1 >> 4) & 0x0F;
	//	//char tmp3 = tmp1 & 0x0F;

	//	result[j++] = lookup[(digest[i] >> 4) & 0x0F];
	//	result[j++] = lookup[digest[i] & 0x0F];
	//}

	return result;
}

//void TMD5::_CalcMD5()
//{
//
//}

// constexpr std::uint32_t F(std::uint32_t x, std::uint32_t y, std::uint32_t z)
// {
// 	return ((x & y) | ((~x) & z));
// }
// constexpr std::uint32_t G(std::uint32_t x, std::uint32_t y, std::uint32_t z)
// {
// 	return (x & z) | (y & (~z));
// }
// constexpr std::uint32_t H(std::uint32_t x, std::uint32_t y, std::uint32_t z)
// {
// 	return (x ^ y ^ z);
// }
// constexpr std::uint32_t I(std::uint32_t x, std::uint32_t y, std::uint32_t z)
// {
// 	return ( y ^ (x | (~z)));
// }
// 
// /* ROTATE_LEFT rotates x left n bits.
// */
// //#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
// constexpr std::uint32_t BitRotation_Left(std::uint32_t x, int n)
// {
// 	return ((x << n) | (x >> (32 - n)));
// }

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent re-computation.
*/
// #define FF(a, b, c, d, x, s, ac) { \
//  (a) += F ((b), (c), (d)) + (x) + (uint32_t)(ac); \
//  (a) = BitRotation_Left ((a), (s)); \
//  (a) += (b); \
// }
// #define GG(a, b, c, d, x, s, ac) { \
//  (a) += G ((b), (c), (d)) + (x) + (uint32_t)(ac); \
//  (a) = BitRotation_Left ((a), (s)); \
//  (a) += (b); \
//   }
// #define HH(a, b, c, d, x, s, ac) { \
//  (a) += H ((b), (c), (d)) + (x) + (uint32_t)(ac); \
//  (a) = BitRotation_Left ((a), (s)); \
//  (a) += (b); \
//   }
// #define II(a, b, c, d, x, s, ac) { \
//  (a) += I ((b), (c), (d)) + (x) + (uint32_t)(ac); \
//  (a) = BitRotation_Left ((a), (s)); \
//  (a) += (b); \
//   }

// constexpr std::uint32_t FF(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d,
// 	std::uint32_t x, int s, std::uint32_t ac)
// {
// 	return BitRotation_Left(a + F(b, c, d) + x + ac, s) + b;
// }
// constexpr std::uint32_t GG(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d,
// 	std::uint32_t x, int s, std::uint32_t ac)
// {
// 	return BitRotation_Left(a + G(b, c, d) + x + ac, s) + b;
// }
// 
// constexpr std::uint32_t HH(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d,
// 	std::uint32_t x, int s, std::uint32_t ac)
// {
// 	return BitRotation_Left(a + H(b, c, d) + x + ac, s) + b;
// }
// constexpr std::uint32_t II(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d,
// 	std::uint32_t x, int s, std::uint32_t ac)
// {
// 	return BitRotation_Left(a + I(b, c, d) + x + ac, s) + b;
// }


/* MD5 initialization. Begins an MD5 operation, writing a new context.
*/
//void TMD5::_MD5Init()		/* context */
//{
//	//m_count[0] = m_count[1] = 0;
//	m_bytecount = 0;
//	/* Load magic initialization constants.
//	*/
//	m_MD5 = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };
//
//	//m_MD5[0] = 0x67452301;
//	//m_MD5[1] = 0xefcdab89;
//	//m_MD5[2] = 0x98badcfe;
//	//m_MD5[3] = 0x10325476;
//}

/* MD5 block update operation. Continues an MD5 message-digest
operation, processing another message block, and updating the
context.
*/
//void TMD5::_MD5Update (char const *input, uint32_t inputLen)

void TMD5::i_MD5Update( const std::vector<uint8_t>& ainput )
{
	//_MD5Update(pinput, pinput.size());
	i_MD5Update( ainput.begin(), ainput.end() );
}

// void TMD5::_O_MD5Update (std::vector<char> const &pinput, uint32_t inputLen)
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
// }


void TMD5::i_MD5Update( std::vector<uint8_t>::const_iterator astart
	, const std::vector<uint8_t>::const_iterator& aend )
{
	//uint32_t i;			//, index;		//, partLen;

	/* Compute number of bytes mod 64 */
	// index = (m_count[0] >> 3) & 0x3F;
	//index = (m_count[0] / 8) % 64;
	uint32_t index = m_bytecount % 64;

	/* Update number of bits */
	// 	if ((m_count[0] += (inputLen << 3))
	// 		< (inputLen << 3))
	// 	{
	// 		m_count[1]++;
	// 	}
	// 	m_count[1] += (inputLen >> 29);

	//uint32_t inputLen = 0;

	//uint8_t block[64];

	//	uint32_t partLen = 64 - index;

	//	uint32_t i = 0;

	while (astart < aend)
	{
		m_Block[index] = *astart;

		++index;
		++astart;
		//++inputLen;
		++m_bytecount;

		if (index >= 64)
		{
			void* block_ptr = m_Block;
			i_MD5Transform( static_cast<uint32_t*>(block_ptr) );
			index = 0;
		}
	}

	/* Transform as many times as possible.
	*/
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

	//m_bytecount += inputLen;		// *8;
}



/* MD5 finalization. Ends an MD5 message-digest operation, writing the
the message digest and zeroizing the context.
*/
void TMD5::i_MD5Final()
{
	//char bits[8];
	// std::string bits(8, '0');
//	unsigned char const *bits_2 = reinterpret_cast<unsigned char *>(m_count);

	//uint32_t index, padLen;

	/* Save number of bits */
	//_Encode (bits, m_count, 8);
	const std::vector<uint8_t> bits = i_Encode( m_bytecount * 8 );

	/* Pad out to 56 mod 64.
	*/
	//index = (m_count[0] >> 3) & 0x3f;
	const uint32_t index = m_bytecount % 64;
	const uint32_t padLen = (index < 56) ? (56 - index) : (120 - index);
	//_MD5Update (PADDING, padLen);
	i_MD5Update( PADDING.begin(), PADDING.begin() + padLen );

	/* Append length (before padding) */
	//_MD5Update (bits, 8);
	i_MD5Update( bits.begin(), bits.begin() + 8 );

	/* Store state in digest */
//	_Encode (m_digest, m_MD5, 16);

	/* Zeroize sensitive information.
	*/
	//_MD5_memset ((POINTER)context, 0, sizeof (*context));

}

/* MD5 basic transformation. Transforms state based on block.
*/
//void TMD5::_MD5Transform (uint32_t state[4], std::array<char, 64> block)	// const  char const block[64])
//void TMD5::i_MD5Transform( const uint8_t block[64] )
void TMD5::i_MD5Transform( const uint32_t ax[16] )
//void TMD5::_MD5Transform (std::array<char, 64> block)
{
	uint32_t a = m_MD5[0];			//state[0];
	uint32_t b = m_MD5[1];			//state[1];
	uint32_t c = m_MD5[2];			//state[2];
	uint32_t d = m_MD5[3];			//state[3];

	//std::uint32_t x[16];
	//const std::uint32_t* x = reinterpret_cast<std::uint32_t const*>(block);
	//std::uint32_t const *x = reinterpret_cast<std::uint32_t const *>(block.data());

//	_Decode (x, block, 64);

	/* Round 1 */
	a = _FF( a, b, c, d, ax[0], S11, 0xd76aa478 ); /* 1 */
	d = _FF( d, a, b, c, ax[1], S12, 0xe8c7b756 ); /* 2 */
	c = _FF( c, d, a, b, ax[2], S13, 0x242070db ); /* 3 */
	b = _FF( b, c, d, a, ax[3], S14, 0xc1bdceee ); /* 4 */
	a = _FF( a, b, c, d, ax[4], S11, 0xf57c0faf ); /* 5 */
	d = _FF( d, a, b, c, ax[5], S12, 0x4787c62a ); /* 6 */
	c = _FF( c, d, a, b, ax[6], S13, 0xa8304613 ); /* 7 */
	b = _FF( b, c, d, a, ax[7], S14, 0xfd469501 ); /* 8 */
	a = _FF( a, b, c, d, ax[8], S11, 0x698098d8 ); /* 9 */
	d = _FF( d, a, b, c, ax[9], S12, 0x8b44f7af ); /* 10 */
	c = _FF( c, d, a, b, ax[10], S13, 0xffff5bb1 ); /* 11 */
	b = _FF( b, c, d, a, ax[11], S14, 0x895cd7be ); /* 12 */
	a = _FF( a, b, c, d, ax[12], S11, 0x6b901122 ); /* 13 */
	d = _FF( d, a, b, c, ax[13], S12, 0xfd987193 ); /* 14 */
	c = _FF( c, d, a, b, ax[14], S13, 0xa679438e ); /* 15 */
	b = _FF( b, c, d, a, ax[15], S14, 0x49b40821 ); /* 16 */

	/* Round 2 */
	a = _GG( a, b, c, d, ax[1], S21, 0xf61e2562 ); /* 17 */
	d = _GG( d, a, b, c, ax[6], S22, 0xc040b340 ); /* 18 */
	c = _GG( c, d, a, b, ax[11], S23, 0x265e5a51 ); /* 19 */
	b = _GG( b, c, d, a, ax[0], S24, 0xe9b6c7aa ); /* 20 */
	a = _GG( a, b, c, d, ax[5], S21, 0xd62f105d ); /* 21 */
	d = _GG( d, a, b, c, ax[10], S22, 0x2441453 ); /* 22 */
	c = _GG( c, d, a, b, ax[15], S23, 0xd8a1e681 ); /* 23 */
	b = _GG( b, c, d, a, ax[4], S24, 0xe7d3fbc8 ); /* 24 */
	a = _GG( a, b, c, d, ax[9], S21, 0x21e1cde6 ); /* 25 */
	d = _GG( d, a, b, c, ax[14], S22, 0xc33707d6 ); /* 26 */
	c = _GG( c, d, a, b, ax[3], S23, 0xf4d50d87 ); /* 27 */
	b = _GG( b, c, d, a, ax[8], S24, 0x455a14ed ); /* 28 */
	a = _GG( a, b, c, d, ax[13], S21, 0xa9e3e905 ); /* 29 */
	d = _GG( d, a, b, c, ax[2], S22, 0xfcefa3f8 ); /* 30 */
	c = _GG( c, d, a, b, ax[7], S23, 0x676f02d9 ); /* 31 */
	b = _GG( b, c, d, a, ax[12], S24, 0x8d2a4c8a ); /* 32 */

	/* Round 3 */
	a = _HH( a, b, c, d, ax[5], S31, 0xfffa3942 ); /* 33 */
	d = _HH( d, a, b, c, ax[8], S32, 0x8771f681 ); /* 34 */
	c = _HH( c, d, a, b, ax[11], S33, 0x6d9d6122 ); /* 35 */
	b = _HH( b, c, d, a, ax[14], S34, 0xfde5380c ); /* 36 */
	a = _HH( a, b, c, d, ax[1], S31, 0xa4beea44 ); /* 37 */
	d = _HH( d, a, b, c, ax[4], S32, 0x4bdecfa9 ); /* 38 */
	c = _HH( c, d, a, b, ax[7], S33, 0xf6bb4b60 ); /* 39 */
	b = _HH( b, c, d, a, ax[10], S34, 0xbebfbc70 ); /* 40 */
	a = _HH( a, b, c, d, ax[13], S31, 0x289b7ec6 ); /* 41 */
	d = _HH( d, a, b, c, ax[0], S32, 0xeaa127fa ); /* 42 */
	c = _HH( c, d, a, b, ax[3], S33, 0xd4ef3085 ); /* 43 */
	b = _HH( b, c, d, a, ax[6], S34, 0x4881d05 ); /* 44 */
	a = _HH( a, b, c, d, ax[9], S31, 0xd9d4d039 ); /* 45 */
	d = _HH( d, a, b, c, ax[12], S32, 0xe6db99e5 ); /* 46 */
	c = _HH( c, d, a, b, ax[15], S33, 0x1fa27cf8 ); /* 47 */
	b = _HH( b, c, d, a, ax[2], S34, 0xc4ac5665 ); /* 48 */

	/* Round 4 */
	a = _II( a, b, c, d, ax[0], S41, 0xf4292244 ); /* 49 */
	d = _II( d, a, b, c, ax[7], S42, 0x432aff97 ); /* 50 */
	c = _II( c, d, a, b, ax[14], S43, 0xab9423a7 ); /* 51 */
	b = _II( b, c, d, a, ax[5], S44, 0xfc93a039 ); /* 52 */
	a = _II( a, b, c, d, ax[12], S41, 0x655b59c3 ); /* 53 */
	d = _II( d, a, b, c, ax[3], S42, 0x8f0ccc92 ); /* 54 */
	c = _II( c, d, a, b, ax[10], S43, 0xffeff47d ); /* 55 */
	b = _II( b, c, d, a, ax[1], S44, 0x85845dd1 ); /* 56 */
	a = _II( a, b, c, d, ax[8], S41, 0x6fa87e4f ); /* 57 */
	d = _II( d, a, b, c, ax[15], S42, 0xfe2ce6e0 ); /* 58 */
	c = _II( c, d, a, b, ax[6], S43, 0xa3014314 ); /* 59 */
	b = _II( b, c, d, a, ax[13], S44, 0x4e0811a1 ); /* 60 */
	a = _II( a, b, c, d, ax[4], S41, 0xf7537e82 ); /* 61 */
	d = _II( d, a, b, c, ax[11], S42, 0xbd3af235 ); /* 62 */
	c = _II( c, d, a, b, ax[2], S43, 0x2ad7d2bb ); /* 63 */
	b = _II( b, c, d, a, ax[9], S44, 0xeb86d391 ); /* 64 */

	m_MD5[0] += a;				// 	state[0] += a;
	m_MD5[1] += b;				// 	state[1] += b;
	m_MD5[2] += c;				// 	state[2] += c;
	m_MD5[3] += d;				// 	state[3] += d;

	/* Zeroize sensitive information.
	*/
	// 	for(auto &curr : x)
	// 	{
	// 		curr = 0;
	// 	}
		//_MD5_memset (x, 0, sizeof (x));
}

/* Encodes input (UINT4) into output (unsigned char). Assumes len is
a multiple of 4.
*/
// void TMD5::_Encode (char *output, std::uint32_t const *input, uint32_t len)
// {
// 	uint32_t i, j;
// 
// 	for (i = 0, j = 0; j < len; i++, j += 4) {
// 		output[j] = input[i] & 0xff;
// 		output[j+1] = (input[i] >> 8) & 0xff;
// 		output[j+2] = (input[i] >> 16) & 0xff;
// 		output[j+3] = (input[i] >> 24) & 0xff;
// 	}
// }

std::vector<uint8_t> TMD5::i_Encode( const std::uint64_t& input )
{
	//std::vector<uint8_t> result( sizeof( input ), 0u );
	////uint32_t i, j;

	//for (auto i = 0u, j = 0u; i < sizeof( input ); ++i, j += 8)
	//{
	//	result[i] = (input >> j) & 0xff;

	//	// 		output[j] = input & 0xff;
	//	// 		output[j + 1] = (input >> 8) & 0xff;
	//	// 		output[j + 2] = (input >> 16) & 0xff;
	//	// 		output[j + 3] = (input >> 24) & 0xff;
	//}

	//return result;

	return {
		gsl::narrow_cast<uint8_t>((input >> 0) & 0xff),
		gsl::narrow_cast<uint8_t>((input >> 8) & 0xff),
		gsl::narrow_cast<uint8_t>((input >> 16) & 0xff),
		gsl::narrow_cast<uint8_t>((input >> 24) & 0xff),
		gsl::narrow_cast<uint8_t>((input >> 32) & 0xff),
		gsl::narrow_cast<uint8_t>((input >> 40) & 0xff),
		gsl::narrow_cast<uint8_t>((input >> 48) & 0xff),
		gsl::narrow_cast<uint8_t>((input >> 56) & 0xff),
		};
}

/* Decodes input (unsigned char) into output (UINT4). Assumes len is
a multiple of 4.
*/
// void TMD5::_Decode (std::uint32_t *output, unsigned char const *input, uint32_t len)
// {
// 	uint32_t i, j;
// 
// 	for (i = 0, j = 0; j < len; i++, j += 4)
// 		output[i] = (static_cast<std::uint32_t>(input[j])
// 			| (static_cast<std::uint32_t>(input[j+1]) << 8) 
// 			| (static_cast<std::uint32_t>(input[j+2]) << 16)
// 			| (static_cast<std::uint32_t>(input[j+3]) << 24));
// }

/* Note: Replace "for loop" with standard memcpy if possible.
*/

//void TMD5::_MD5_memcpy( char* output, const char* input, uint32_t len )
//{
//	uint32_t i;
//
//	for (i = 0; i < len; i++)
//	{
//		output[i] = input[i];
//	}
//}

/* Note: Replace "for loop" with standard memset if possible.
*/
// void TMD5::_MD5_memset (unsigned char *output, int value, uint32_t len)
// {
// 	uint32_t i;
// 
// 	for (i = 0; i < len; i++)
// 		((char *)output)[i] = (char)value;
// }


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

std::string Calc_MD5( const std::string& input )
{
	TMD5 md5;

	return std::string();
}


