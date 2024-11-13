
#include "TMD5.hpp"

#include <vector>



//char TMD5::PADDING[64] = {
//std::array<char, 64> TMD5::PADDING = {
std::vector<char> TMD5::PADDING = {
	//	0x80
		-128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

TMD5::TMD5()
//: m_digest(reinterpret_cast<unsigned char *>(m_MD5))
{
	_MD5Init();
}

// TMD5::TMD5(std::istream const &pin)
// {
// 	_MD5Init();
// }

TMD5::TMD5( std::string const& pin )
//: m_digest(reinterpret_cast<unsigned char *>(m_MD5))
{
	_MD5Init();
	//_MD5Update(buffer.data(), buffer.size());
	//_MD5Update(pin.data(), pin.size());
	//_MD5Update(pin);		//.data());
	_MD5Update( std::vector<char>( pin.begin(), pin.end() ) );

	_MD5Final();

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

	char const lookup[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	for (int i = 0, j = 0; i < 16; ++i)
	{
		//char tmp1 = m_digest[i];
		//char tmp2 = (tmp1 >> 4) & 0x0F;
		//char tmp3 = tmp1 & 0x0F;

		result[j++] = lookup[(m_digest[i] >> 4) & 0x0F];
		result[j++] = lookup[m_digest[i] & 0x0F];
	}

	return result;
}

void TMD5::_CalcMD5()
{

}

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
void TMD5::_MD5Init()		/* context */
{
	//m_count[0] = m_count[1] = 0;
	m_bitcount = 0;
	/* Load magic initialization constants.
	*/
	m_MD5[0] = 0x67452301;
	m_MD5[1] = 0xefcdab89;
	m_MD5[2] = 0x98badcfe;
	m_MD5[3] = 0x10325476;
}

/* MD5 block update operation. Continues an MD5 message-digest
operation, processing another message block, and updating the
context.
*/
//void TMD5::_MD5Update (char const *input, uint32_t inputLen)

void TMD5::_MD5Update( std::vector<char> const& pinput )
{
	//_MD5Update(pinput, pinput.size());
	_MD5Update( pinput.begin(), pinput.end() );
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


void TMD5::_MD5Update( std::vector<char>::const_iterator pstart
	, std::vector<char>::const_iterator const& pend )
{
	//uint32_t i;			//, index;		//, partLen;

	/* Compute number of bytes mod 64 */
	// index = (m_count[0] >> 3) & 0x3F;
	//index = (m_count[0] / 8) % 64;
	uint32_t index = (m_bitcount / 8) % 64;

	/* Update number of bits */
	// 	if ((m_count[0] += (inputLen << 3))
	// 		< (inputLen << 3))
	// 	{
	// 		m_count[1]++;
	// 	}
	// 	m_count[1] += (inputLen >> 29);

	uint32_t inputLen = 0;

	//	uint32_t partLen = 64 - index;

	//	uint32_t i = 0;

	while (pstart != pend)
	{
		m_block[index] = *pstart;

		++index;
		++pstart;
		++inputLen;

		if (index >= 64)
		{
			_MD5Transform( m_block );
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

	m_bitcount += inputLen * 8;
}



/* MD5 finalization. Ends an MD5 message-digest operation, writing the
the message digest and zeroizing the context.
*/
void TMD5::_MD5Final()
{
	//char bits[8];
	// std::string bits(8, '0');
//	unsigned char const *bits_2 = reinterpret_cast<unsigned char *>(m_count);

	uint32_t index, padLen;

	/* Save number of bits */
	//_Encode (bits, m_count, 8);
	std::vector<char> bits = _Encode( m_bitcount );

	/* Pad out to 56 mod 64.
	*/
	//index = (m_count[0] >> 3) & 0x3f;
	index = (m_bitcount / 8) % 64;
	padLen = (index < 56) ? (56 - index) : (120 - index);
	//_MD5Update (PADDING, padLen);
	_MD5Update( PADDING.begin(), PADDING.begin() + padLen );

	/* Append length (before padding) */
	//_MD5Update (bits, 8);
	_MD5Update( bits.begin(), bits.begin() + 8 );

	/* Store state in digest */
//	_Encode (m_digest, m_MD5, 16);

	/* Zeroize sensitive information.
	*/
	//_MD5_memset ((POINTER)context, 0, sizeof (*context));

}

/* MD5 basic transformation. Transforms state based on block.
*/
//void TMD5::_MD5Transform (uint32_t state[4], std::array<char, 64> block)	// const  char const block[64])
void TMD5::_MD5Transform( char const block[64] )
//void TMD5::_MD5Transform (std::array<char, 64> block)
{
	std::uint32_t a = m_MD5[0];			//state[0];
	std::uint32_t b = m_MD5[1];			//state[1];
	std::uint32_t c = m_MD5[2];			//state[2];
	std::uint32_t d = m_MD5[3];			//state[3];

	//std::uint32_t x[16];
	std::uint32_t const* x = reinterpret_cast<std::uint32_t const*>(block);
	//std::uint32_t const *x = reinterpret_cast<std::uint32_t const *>(block.data());

//	_Decode (x, block, 64);

	/* Round 1 */
	a = _FF( a, b, c, d, x[0], S11, 0xd76aa478 ); /* 1 */
	d = _FF( d, a, b, c, x[1], S12, 0xe8c7b756 ); /* 2 */
	c = _FF( c, d, a, b, x[2], S13, 0x242070db ); /* 3 */
	b = _FF( b, c, d, a, x[3], S14, 0xc1bdceee ); /* 4 */
	a = _FF( a, b, c, d, x[4], S11, 0xf57c0faf ); /* 5 */
	d = _FF( d, a, b, c, x[5], S12, 0x4787c62a ); /* 6 */
	c = _FF( c, d, a, b, x[6], S13, 0xa8304613 ); /* 7 */
	b = _FF( b, c, d, a, x[7], S14, 0xfd469501 ); /* 8 */
	a = _FF( a, b, c, d, x[8], S11, 0x698098d8 ); /* 9 */
	d = _FF( d, a, b, c, x[9], S12, 0x8b44f7af ); /* 10 */
	c = _FF( c, d, a, b, x[10], S13, 0xffff5bb1 ); /* 11 */
	b = _FF( b, c, d, a, x[11], S14, 0x895cd7be ); /* 12 */
	a = _FF( a, b, c, d, x[12], S11, 0x6b901122 ); /* 13 */
	d = _FF( d, a, b, c, x[13], S12, 0xfd987193 ); /* 14 */
	c = _FF( c, d, a, b, x[14], S13, 0xa679438e ); /* 15 */
	b = _FF( b, c, d, a, x[15], S14, 0x49b40821 ); /* 16 */

	/* Round 2 */
	a = _GG( a, b, c, d, x[1], S21, 0xf61e2562 ); /* 17 */
	d = _GG( d, a, b, c, x[6], S22, 0xc040b340 ); /* 18 */
	c = _GG( c, d, a, b, x[11], S23, 0x265e5a51 ); /* 19 */
	b = _GG( b, c, d, a, x[0], S24, 0xe9b6c7aa ); /* 20 */
	a = _GG( a, b, c, d, x[5], S21, 0xd62f105d ); /* 21 */
	d = _GG( d, a, b, c, x[10], S22, 0x2441453 ); /* 22 */
	c = _GG( c, d, a, b, x[15], S23, 0xd8a1e681 ); /* 23 */
	b = _GG( b, c, d, a, x[4], S24, 0xe7d3fbc8 ); /* 24 */
	a = _GG( a, b, c, d, x[9], S21, 0x21e1cde6 ); /* 25 */
	d = _GG( d, a, b, c, x[14], S22, 0xc33707d6 ); /* 26 */
	c = _GG( c, d, a, b, x[3], S23, 0xf4d50d87 ); /* 27 */
	b = _GG( b, c, d, a, x[8], S24, 0x455a14ed ); /* 28 */
	a = _GG( a, b, c, d, x[13], S21, 0xa9e3e905 ); /* 29 */
	d = _GG( d, a, b, c, x[2], S22, 0xfcefa3f8 ); /* 30 */
	c = _GG( c, d, a, b, x[7], S23, 0x676f02d9 ); /* 31 */
	b = _GG( b, c, d, a, x[12], S24, 0x8d2a4c8a ); /* 32 */

	/* Round 3 */
	a = _HH( a, b, c, d, x[5], S31, 0xfffa3942 ); /* 33 */
	d = _HH( d, a, b, c, x[8], S32, 0x8771f681 ); /* 34 */
	c = _HH( c, d, a, b, x[11], S33, 0x6d9d6122 ); /* 35 */
	b = _HH( b, c, d, a, x[14], S34, 0xfde5380c ); /* 36 */
	a = _HH( a, b, c, d, x[1], S31, 0xa4beea44 ); /* 37 */
	d = _HH( d, a, b, c, x[4], S32, 0x4bdecfa9 ); /* 38 */
	c = _HH( c, d, a, b, x[7], S33, 0xf6bb4b60 ); /* 39 */
	b = _HH( b, c, d, a, x[10], S34, 0xbebfbc70 ); /* 40 */
	a = _HH( a, b, c, d, x[13], S31, 0x289b7ec6 ); /* 41 */
	d = _HH( d, a, b, c, x[0], S32, 0xeaa127fa ); /* 42 */
	c = _HH( c, d, a, b, x[3], S33, 0xd4ef3085 ); /* 43 */
	b = _HH( b, c, d, a, x[6], S34, 0x4881d05 ); /* 44 */
	a = _HH( a, b, c, d, x[9], S31, 0xd9d4d039 ); /* 45 */
	d = _HH( d, a, b, c, x[12], S32, 0xe6db99e5 ); /* 46 */
	c = _HH( c, d, a, b, x[15], S33, 0x1fa27cf8 ); /* 47 */
	b = _HH( b, c, d, a, x[2], S34, 0xc4ac5665 ); /* 48 */

	/* Round 4 */
	a = _II( a, b, c, d, x[0], S41, 0xf4292244 ); /* 49 */
	d = _II( d, a, b, c, x[7], S42, 0x432aff97 ); /* 50 */
	c = _II( c, d, a, b, x[14], S43, 0xab9423a7 ); /* 51 */
	b = _II( b, c, d, a, x[5], S44, 0xfc93a039 ); /* 52 */
	a = _II( a, b, c, d, x[12], S41, 0x655b59c3 ); /* 53 */
	d = _II( d, a, b, c, x[3], S42, 0x8f0ccc92 ); /* 54 */
	c = _II( c, d, a, b, x[10], S43, 0xffeff47d ); /* 55 */
	b = _II( b, c, d, a, x[1], S44, 0x85845dd1 ); /* 56 */
	a = _II( a, b, c, d, x[8], S41, 0x6fa87e4f ); /* 57 */
	d = _II( d, a, b, c, x[15], S42, 0xfe2ce6e0 ); /* 58 */
	c = _II( c, d, a, b, x[6], S43, 0xa3014314 ); /* 59 */
	b = _II( b, c, d, a, x[13], S44, 0x4e0811a1 ); /* 60 */
	a = _II( a, b, c, d, x[4], S41, 0xf7537e82 ); /* 61 */
	d = _II( d, a, b, c, x[11], S42, 0xbd3af235 ); /* 62 */
	c = _II( c, d, a, b, x[2], S43, 0x2ad7d2bb ); /* 63 */
	b = _II( b, c, d, a, x[9], S44, 0xeb86d391 ); /* 64 */

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

std::vector<char> TMD5::_Encode( std::uint64_t const& input )
{
	std::vector<char> retstr( sizeof( input ), '0' );
	//uint32_t i, j;

	for (auto i = 0u, j = 0u; i < sizeof( input ); ++i, j += 8)
	{
		retstr[i] = (input >> j) & 0xff;

		// 		output[j] = input & 0xff;
		// 		output[j + 1] = (input >> 8) & 0xff;
		// 		output[j + 2] = (input >> 16) & 0xff;
		// 		output[j + 3] = (input >> 24) & 0xff;
	}

	return retstr;
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

void TMD5::_MD5_memcpy( char* output, char const* input, uint32_t len )
{
	uint32_t i;

	for (i = 0; i < len; i++)
	{
		output[i] = input[i];
	}
}

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


