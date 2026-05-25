/**
 *
 * Module:
 *  ceaserscipher
 *
 * Description:
 *  Ceaser's Cipher.
*/

#include <iostream>
#include <filesystem>
#include <fstream>

static void Encode( const std::filesystem::path& rPath )
{
	std::ifstream stream( rPath, std::ios::in );
	
	auto outPath = rPath;
	outPath.replace_extension( ".encode" );

	std::ofstream fout( outPath, std::ios::out );

	while( true )
	{
		const char c = stream.get();

		if( stream.eof() )
			break;
	
		if( c <= 31 )
			fout << c;
		else
			fout << char( c + 1 );
	}

	fout.close();
	stream.close();
}

static void Decode( const std::filesystem::path& rPath )
{
	// TODO: Not sure if binary here is needed, but my fear is that one time when we encode it may be counted
	// as a binary vale...
	std::ifstream stream( rPath, std::ios::in | std::ios::binary );

	auto outPath = rPath;
	outPath.replace_extension( ".decode" );

	std::ofstream fout( outPath, std::ios::out | std::ios::binary );

	char c;
	while( stream.get( c ) )
	{
		uint8_t uc = ( uint8_t ) c;

		if( c <= 31 )
			fout << uc;
		else
			fout << uint8_t( uc - 1 );
	}

	fout.close();
	stream.close();
}

int main( int count, char** ppArgs )
{
	if( count != 3 )
	{
		std::cout << "Usage: " << ppArgs[ 0 ] << " <target_file> <mode, one of the following: encode OR decode>\n";
		return EXIT_FAILURE;
	}

	if( !std::strcmp( ppArgs[ 2 ], "encode" ) )
	{
		if( !std::filesystem::exists( ppArgs[ 1 ] ) )
		{
			std::cout << "File to encode: " << ppArgs[ 1 ] << " does not exist!\n";
			return EXIT_FAILURE;
		}

		Encode( std::filesystem::path( ppArgs[ 1 ] ) );
	}
	else if( !std::strcmp( ppArgs[ 2 ], "decode" ) )
	{
		if( !std::filesystem::exists( ppArgs[ 1 ] ) )
		{
			std::cout << "File to decode: " << ppArgs[ 1 ] << " does not exist!\n";
			return EXIT_FAILURE;
		}

		Decode( std::filesystem::path( ppArgs[ 1 ] ) );
	}
	else
	{
		std::cout << "Invalid mode option: '" << ppArgs[ 1 ] << "' must be compress or decompress\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
