
#ifndef TMD5_H_
#define TMD5_H_


#include <array>
#include <vector>
#include <string>

#include <span>



namespace impldet_
{

class TSessionMD5
{
public:

	TSessionMD5();

	void Update( const std::span<const std::byte> adata );

	std::string Final();

private:

	void i_MD5Transform( const std::span<const uint32_t, 16>& ax ) noexcept;

	std::array<std::byte, 8> i_Encode( const std::uint64_t& input ) noexcept;

	std::string i_MD5_to_string() const;

private:

	uint64_t m_TotalByteCount;
	std::array<std::byte, 64> m_InputBuffer;
	std::array<uint32_t, 4> m_MD5;

};

}

//__________________________________________________________________________________________________


// Data can be added gradually and the result can be calculated multiple times for every partial step

class TMD5_Continuous
{

public:

	void Update( const std::string& pin );

	std::string Get_MD5() const;

private:

	impldet_::TSessionMD5 m_Session;

};


//__________________________________________________________________________________________________

// Direct operation: one string in -> one string out
std::string Calc_MD5( const std::string& input );




#endif // TMD5_H_

