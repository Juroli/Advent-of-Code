
#include "JMD5.hpp"

#include <bit>
#include "gsl/gsl"



namespace
{

const std::array<std::byte, 64> PADDING = {
	std::byte{0x80}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
	std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
	std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
	std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
	std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
	std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
	std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
	std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0}, std::byte{0},
};


constexpr uint32_t S11 = 7;
constexpr uint32_t S12 = 12;
constexpr uint32_t S13 = 17;
constexpr uint32_t S14 = 22;
constexpr uint32_t S21 = 5;
constexpr uint32_t S22 = 9;
constexpr uint32_t S23 = 14;
constexpr uint32_t S24 = 20;
constexpr uint32_t S31 = 4;
constexpr uint32_t S32 = 11;
constexpr uint32_t S33 = 16;
constexpr uint32_t S34 = 23;
constexpr uint32_t S41 = 6;
constexpr uint32_t S42 = 10;
constexpr uint32_t S43 = 15;
constexpr uint32_t S44 = 21;

static constexpr uint32_t _F( uint32_t x, uint32_t y, uint32_t z ) noexcept { return ((x & y) | ((~x) & z)); }
static constexpr uint32_t _G( uint32_t x, uint32_t y, uint32_t z ) noexcept { return (x & z) | (y & (~z)); }
static constexpr uint32_t _H( uint32_t x, uint32_t y, uint32_t z ) noexcept { return (x ^ y ^ z); }
static constexpr uint32_t _I( uint32_t x, uint32_t y, uint32_t z ) noexcept { return (y ^ (x | (~z))); }


static constexpr uint32_t _BitRotation_Left( uint32_t x, int n ) noexcept { return ((x << n) | (x >> (32 - n))); }


static constexpr uint32_t _FF( uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac ) noexcept
{
	return _BitRotation_Left( a + _F( b, c, d ) + x + ac, s ) + b;
}

static constexpr uint32_t _GG( uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac ) noexcept
{
	return _BitRotation_Left( a + _G( b, c, d ) + x + ac, s ) + b;
}

static constexpr uint32_t _HH( uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac ) noexcept
{
	return _BitRotation_Left( a + _H( b, c, d ) + x + ac, s ) + b;
}

static constexpr uint32_t _II( uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac ) noexcept
{
	return _BitRotation_Left( a + _I( b, c, d ) + x + ac, s ) + b;
}

}


//__________________________________________________________________________________________________


namespace impldet_
{

TSessionMD5::TSessionMD5()
	: m_TotalByteCount( 0 )
	, m_InputBuffer()
	, m_MD5{ 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 }
{
}


void TSessionMD5::Update( const std::span<const std::byte> adata )
{
	const int IN_BUFFER_LENGTH = 64;

	size_t currBuffLen = m_TotalByteCount % IN_BUFFER_LENGTH;
	auto outItBegin = m_InputBuffer.begin() + currBuffLen;

	auto inItBegin = adata.begin();
	auto inputSize = adata.size();


	while (inputSize > 0)
	{
		const auto copyMaxSize = IN_BUFFER_LENGTH - currBuffLen;
		const auto copySize = std::min( inputSize, copyMaxSize );
		const auto inItEnd = inItBegin + copySize;

		std::copy( inItBegin, inItEnd, outItBegin );

		currBuffLen += copySize;
		inputSize -= copySize;
		inItBegin += copySize;

		m_TotalByteCount += copySize;


		if (currBuffLen >= IN_BUFFER_LENGTH)
		{
			const auto work_block = std::bit_cast<std::array<uint32_t, 16>>(m_InputBuffer);

			i_MD5Transform( work_block );
			currBuffLen = 0;
			outItBegin = m_InputBuffer.begin();
		}
	}

}


/* MD5 finalization. Ends an MD5 message-digest operation, adding padding and writing the
the message digest.
*/

std::string TSessionMD5::Final()
{
	/* Save number of bits */
	const auto bits = i_Encode( m_TotalByteCount * 8 );

	/* Pad out to 56 mod 64. */
	const uint32_t index = m_TotalByteCount % 64;
	const uint32_t padLen = (index < 56) ? (56 - index) : (120 - index);
	//i_MD5Update( PADDING.begin(), PADDING.begin() + padLen );

	const std::span pad_span( PADDING );
	Update( pad_span.subspan( 0, padLen ) );

	/* Append length (before padding) */
	Update( bits );

	return i_MD5_to_string();
}


/* MD5 basic transformation. Transforms state based on block. */
void TSessionMD5::i_MD5Transform( const std::span<const uint32_t, 16>& ax ) noexcept
{

	uint32_t a = m_MD5[0];
	uint32_t b = m_MD5[1];
	uint32_t c = m_MD5[2];
	uint32_t d = m_MD5[3];


	/* Round 1 */
	a = _FF( a, b, c, d, ax[ 0], S11, 0xd76aa478 ); //  1
	d = _FF( d, a, b, c, ax[ 1], S12, 0xe8c7b756 ); //  2
	c = _FF( c, d, a, b, ax[ 2], S13, 0x242070db ); //  3
	b = _FF( b, c, d, a, ax[ 3], S14, 0xc1bdceee ); //  4
	a = _FF( a, b, c, d, ax[ 4], S11, 0xf57c0faf ); //  5
	d = _FF( d, a, b, c, ax[ 5], S12, 0x4787c62a ); //  6
	c = _FF( c, d, a, b, ax[ 6], S13, 0xa8304613 ); //  7
	b = _FF( b, c, d, a, ax[ 7], S14, 0xfd469501 ); //  8
	a = _FF( a, b, c, d, ax[ 8], S11, 0x698098d8 ); //  9
	d = _FF( d, a, b, c, ax[ 9], S12, 0x8b44f7af ); // 10
	c = _FF( c, d, a, b, ax[10], S13, 0xffff5bb1 ); // 11
	b = _FF( b, c, d, a, ax[11], S14, 0x895cd7be ); // 12
	a = _FF( a, b, c, d, ax[12], S11, 0x6b901122 ); // 13
	d = _FF( d, a, b, c, ax[13], S12, 0xfd987193 ); // 14
	c = _FF( c, d, a, b, ax[14], S13, 0xa679438e ); // 15
	b = _FF( b, c, d, a, ax[15], S14, 0x49b40821 ); // 16

	/* Round 2 */
	a = _GG( a, b, c, d, ax[ 1], S21, 0xf61e2562 ); // 17
	d = _GG( d, a, b, c, ax[ 6], S22, 0xc040b340 ); // 18
	c = _GG( c, d, a, b, ax[11], S23, 0x265e5a51 ); // 19
	b = _GG( b, c, d, a, ax[ 0], S24, 0xe9b6c7aa ); // 20
	a = _GG( a, b, c, d, ax[ 5], S21, 0xd62f105d ); // 21
	d = _GG( d, a, b, c, ax[10], S22, 0x02441453 ); // 22
	c = _GG( c, d, a, b, ax[15], S23, 0xd8a1e681 ); // 23
	b = _GG( b, c, d, a, ax[ 4], S24, 0xe7d3fbc8 ); // 24
	a = _GG( a, b, c, d, ax[ 9], S21, 0x21e1cde6 ); // 25
	d = _GG( d, a, b, c, ax[14], S22, 0xc33707d6 ); // 26
	c = _GG( c, d, a, b, ax[ 3], S23, 0xf4d50d87 ); // 27
	b = _GG( b, c, d, a, ax[ 8], S24, 0x455a14ed ); // 28
	a = _GG( a, b, c, d, ax[13], S21, 0xa9e3e905 ); // 29
	d = _GG( d, a, b, c, ax[ 2], S22, 0xfcefa3f8 ); // 30
	c = _GG( c, d, a, b, ax[ 7], S23, 0x676f02d9 ); // 31
	b = _GG( b, c, d, a, ax[12], S24, 0x8d2a4c8a ); // 32

	/* Round 3 */
	a = _HH( a, b, c, d, ax[ 5], S31, 0xfffa3942 ); // 33
	d = _HH( d, a, b, c, ax[ 8], S32, 0x8771f681 ); // 34
	c = _HH( c, d, a, b, ax[11], S33, 0x6d9d6122 ); // 35
	b = _HH( b, c, d, a, ax[14], S34, 0xfde5380c ); // 36
	a = _HH( a, b, c, d, ax[ 1], S31, 0xa4beea44 ); // 37
	d = _HH( d, a, b, c, ax[ 4], S32, 0x4bdecfa9 ); // 38
	c = _HH( c, d, a, b, ax[ 7], S33, 0xf6bb4b60 ); // 39
	b = _HH( b, c, d, a, ax[10], S34, 0xbebfbc70 ); // 40
	a = _HH( a, b, c, d, ax[13], S31, 0x289b7ec6 ); // 41
	d = _HH( d, a, b, c, ax[ 0], S32, 0xeaa127fa ); // 42
	c = _HH( c, d, a, b, ax[ 3], S33, 0xd4ef3085 ); // 43
	b = _HH( b, c, d, a, ax[ 6], S34, 0x04881d05 ); // 44
	a = _HH( a, b, c, d, ax[ 9], S31, 0xd9d4d039 ); // 45
	d = _HH( d, a, b, c, ax[12], S32, 0xe6db99e5 ); // 46
	c = _HH( c, d, a, b, ax[15], S33, 0x1fa27cf8 ); // 47
	b = _HH( b, c, d, a, ax[ 2], S34, 0xc4ac5665 ); // 48

	/* Round 4 */
	a = _II( a, b, c, d, ax[ 0], S41, 0xf4292244 ); // 49
	d = _II( d, a, b, c, ax[ 7], S42, 0x432aff97 ); // 50
	c = _II( c, d, a, b, ax[14], S43, 0xab9423a7 ); // 51
	b = _II( b, c, d, a, ax[ 5], S44, 0xfc93a039 ); // 52
	a = _II( a, b, c, d, ax[12], S41, 0x655b59c3 ); // 53
	d = _II( d, a, b, c, ax[ 3], S42, 0x8f0ccc92 ); // 54
	c = _II( c, d, a, b, ax[10], S43, 0xffeff47d ); // 55
	b = _II( b, c, d, a, ax[ 1], S44, 0x85845dd1 ); // 56
	a = _II( a, b, c, d, ax[ 8], S41, 0x6fa87e4f ); // 57
	d = _II( d, a, b, c, ax[15], S42, 0xfe2ce6e0 ); // 58
	c = _II( c, d, a, b, ax[ 6], S43, 0xa3014314 ); // 59
	b = _II( b, c, d, a, ax[13], S44, 0x4e0811a1 ); // 60
	a = _II( a, b, c, d, ax[ 4], S41, 0xf7537e82 ); // 61
	d = _II( d, a, b, c, ax[11], S42, 0xbd3af235 ); // 62
	c = _II( c, d, a, b, ax[ 2], S43, 0x2ad7d2bb ); // 63
	b = _II( b, c, d, a, ax[ 9], S44, 0xeb86d391 ); // 64

	m_MD5[0] += a;
	m_MD5[1] += b;
	m_MD5[2] += c;
	m_MD5[3] += d;

}


// Encodes input (uint64_t) into output (array<std::byte, 8>).
std::array<std::byte, 8> TSessionMD5::i_Encode( const std::uint64_t& input ) noexcept
{
	return {
		gsl::narrow_cast<std::byte>((input >>  0) & 0xff),
		gsl::narrow_cast<std::byte>((input >>  8) & 0xff),
		gsl::narrow_cast<std::byte>((input >> 16) & 0xff),
		gsl::narrow_cast<std::byte>((input >> 24) & 0xff),
		gsl::narrow_cast<std::byte>((input >> 32) & 0xff),
		gsl::narrow_cast<std::byte>((input >> 40) & 0xff),
		gsl::narrow_cast<std::byte>((input >> 48) & 0xff),
		gsl::narrow_cast<std::byte>((input >> 56) & 0xff),
	};
}


std::string TSessionMD5::i_MD5_to_string() const
{
	std::string result( 32, '+' );

	const char lookup[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	int pos = 0;
	for (auto i = 0u; i < 4u; ++i)
	{
		result[pos++] = lookup[(m_MD5[i] >>  4) & 0x0F];
		result[pos++] = lookup[ m_MD5[i]        & 0x0F];

		result[pos++] = lookup[(m_MD5[i] >> 12) & 0x0F];
		result[pos++] = lookup[(m_MD5[i] >>  8) & 0x0F];

		result[pos++] = lookup[(m_MD5[i] >> 20) & 0x0F];
		result[pos++] = lookup[(m_MD5[i] >> 16) & 0x0F];

		result[pos++] = lookup[(m_MD5[i] >> 28) & 0x0F];
		result[pos++] = lookup[(m_MD5[i] >> 24) & 0x0F];

	}

	return result;
}


}


//__________________________________________________________________________________________________


void TMD5_Continuous::Update( const std::string& pin )
{
	m_Session.Update( std::as_bytes( std::span( pin )) );	// , pin.end() ) );
}

std::string TMD5_Continuous::Get_MD5() const
{

	auto loc_session = m_Session;

	return loc_session.Final();
}



//__________________________________________________________________________________________________



std::string Calc_MD5( std::string_view input )
{
	impldet_::TSessionMD5 md5;
	md5.Update( std::as_bytes( std::span( input ) ) );
	return md5.Final();
}


