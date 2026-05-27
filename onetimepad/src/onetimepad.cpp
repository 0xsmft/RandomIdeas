/**
 *
 * Module:
 *  onetimepad
 *
 * Description:
 *  One-Time Pad encryption.
*/

#include <iostream>
#include <filesystem>
#include <fstream>
#include <random>
#include <windows.h>

static std::random_device s_RandomDevice;
static std::mt19937 s_RandomEngine( s_RandomDevice() );
static std::uniform_int_distribution<int> s_Dist( 1, 255 );

static void Encode( const std::filesystem::path& rPath ) 
{
	std::ifstream dataFile( rPath );

	std::filesystem::path keyFilePath = rPath;
	keyFilePath.replace_extension( ".key" );

	std::filesystem::path encryptedFilePath = rPath;
	encryptedFilePath.replace_extension( ".out" );

	std::ofstream keyFile( keyFilePath, std::ios::trunc | std::ios::binary );
	std::ofstream encryptedFile( encryptedFilePath, std::ios::trunc | std::ios::binary );

	char c = -1;
	while( true )
	{
		dataFile.get( c );

		if( dataFile.eof() || dataFile.fail() )
			break;

		const uint8_t key = s_Dist( s_RandomEngine );
		const char outChar = c ^ key;

		keyFile << key;
		encryptedFile << outChar;
	}

	keyFile.close();
	encryptedFile.close();
	dataFile.close();
}

static void Decode( const std::filesystem::path& rEncodedPath, const std::filesystem::path& rKeyPath )
{
	std::ifstream encodedFile( rEncodedPath, std::ios::binary );
	std::ifstream keyFile( rKeyPath, std::ios::binary );

	std::filesystem::path outPath = rKeyPath;
	outPath.replace_extension( ".out.enc" );

	std::ofstream outFile( outPath );

	while( true )
	{
		uint8_t key = 0;
		keyFile.read( reinterpret_cast< char* >( &key ), sizeof( uint8_t ) );

		char encodedChar = -1;
		encodedFile >> encodedChar;
	
		if( keyFile.eof() || encodedFile.eof() || keyFile.fail() || encodedFile.fail() )
			break;

		const auto outChar = char( encodedChar ^ key );
		outFile << outChar;
	}

	outFile.close();
	encodedFile.close();
	keyFile.close();
}

int main( int count, char** ppArgs )
{
	if( count < 2 )
	{
		std::cout << "Usage: " << ppArgs[ 0 ] << " <mode, one of the following: encode OR decode>\n";
		std::cout << " If mode is encode: an additional argument is needed for the file to be encoded.\n";
		std::cout << " If mode is decode: additional two arguments are needed: (1) the file that was encoded (2) the key to use.\n";
		return EXIT_FAILURE;
	}

	if( std::strcmp( ppArgs[ 1 ], "encode" ) == 0 )
	{
		if( count != 3 )
		{
			std::cout << "If mode is encode: an additional argument is needed for the file to be encoded.\n";
			return EXIT_FAILURE;
		}

		if( !std::filesystem::exists( ppArgs[ 2 ] ) )
		{
			std::cout << "File to encode '" << ppArgs[ 2 ] << "' does not exist!\n";
			return EXIT_FAILURE;
		}

		Encode( ppArgs[ 2 ] );
	}
	else if( std::strcmp( ppArgs[ 1 ], "decode" ) == 0 )
	{
		if( count != 4 )
		{
			std::cout << "If mode is decode: additional two arguments are needed: (1) the file that was encoded (2) the key to use.\n";
			return EXIT_FAILURE;
		}

		if( !std::filesystem::exists( ppArgs[ 2 ] ) )
		{
			std::cout << "Encoded file '" << ppArgs[ 2 ] << "' does not exist!\n";
			return EXIT_FAILURE;
		}

		if( !std::filesystem::exists( ppArgs[ 3 ] ) )
		{
			std::cout << "Key file '" << ppArgs[ 3 ] << "' does not exist!\n";
			return EXIT_FAILURE;
		}

		Decode( ppArgs[ 2 ], ppArgs[ 3 ] );
	}
	else
	{
		std::cout << "'" << ppArgs[ 1 ] << "' Unknown mode!\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
