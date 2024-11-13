
#ifndef TMD5_H_
#define TMD5_H_


#include <vector>
#include <string>



class TMD5
{
public:

	TMD5();
	explicit TMD5( const std::string& pin );


	//	TMD5 &operator +=( std::string const &pstr );

	std::string String() const;

private:


	void i_MD5Update( const std::vector<uint8_t>& ainput );
	void i_MD5Update( std::vector<uint8_t>::const_iterator astart, const std::vector<uint8_t>::const_iterator& aend );

	void i_MD5Final();

	void i_MD5Transform( const uint32_t ax[16] );

	std::vector<uint8_t> i_Encode( const std::uint64_t& input );

private:


	uint64_t m_bytecount;

	uint8_t m_Block[64];

	uint32_t m_MD5[4];
	
};


std::string Calc_MD5( const std::string& input );



#endif // TMD5_H_

