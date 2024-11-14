
#ifndef TMD5_H_
#define TMD5_H_


#include <array>
#include <vector>
#include <string>

#include <span>


class TMD5
{
public:

	TMD5();
	explicit TMD5( const std::string& pin );


	//	TMD5 &operator +=( std::string const &pstr );

	std::string String() const;

private:


	void i_MD5Update( const std::vector<uint8_t>& ainput );
	void i_MD5Update( std::span<const std::byte> adata );

	void i_MD5Final();

	void i_MD5Transform( const std::span<const uint32_t, 16>& ax );

	std::array<std::byte, 8> i_Encode( const std::uint64_t& input );

private:


	uint64_t m_TotalByteCount;

	std::array<std::byte, 64> m_InputBuffer;

	std::array<uint32_t, 4> m_MD5;
	
};


std::string Calc_MD5( const std::string& input );



#endif // TMD5_H_

