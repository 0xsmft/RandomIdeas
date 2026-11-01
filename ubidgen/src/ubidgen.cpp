/**
 *
 * Module:
 *  ubidgen
 *
 * Description:
 *  Unqiue Build ID generator (for Saturn, 0xsmft, mftcode, picokrnl, etc)
*/

#include <iostream>
#include <random>

static std::random_device s_RandomDevice;
static std::mt19937_64 s_RandomEngine( s_RandomDevice() );

static uint16_t RandNumber0To99()
{
	static std::uniform_int_distribution<uint16_t> rangeDist( 0, 99 );
	return rangeDist( s_RandomEngine );
}

static char RandLetterAToZUpperCase()
{
	static std::uniform_int_distribution<std::uint16_t> rangeDist( 0x41, 0x5A );
	return ( char ) rangeDist( s_RandomEngine );
}

int main( int count, char** ppArgs ) 
{
	const auto number = RandNumber0To99();
	const char letter = RandLetterAToZUpperCase();

	std::string res = std::format( "{}{:02}AP", letter, number );
	std::cout << res << "\n";

	return 0;
}
