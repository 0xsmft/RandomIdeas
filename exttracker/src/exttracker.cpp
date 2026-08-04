/**
 *
 * Module:
 *  exttracker
 *
 * Description:
 *  Scan a directory and log the different file extensions.
*/

#include <iostream>
#include <filesystem>
#include <map>

int main( int count, char** ppArgs )
{
	if( count == 1 )
	{
		std::cout << "Usage " << ppArgs[ 0 ] << " <dir>\n";

		return 1;
	}

	const std::filesystem::path dir = ppArgs[ 1 ];
	if( !std::filesystem::exists( dir ) )
	{
		std::cout << ppArgs[ 1 ] << " no such directory.\n";
		return 1;
	}

	std::map<std::filesystem::path, uint64_t> exts;

	for( const auto& rEntry : std::filesystem::recursive_directory_iterator( dir ) )
	{
		if( rEntry.is_directory() )
			continue;

		const auto& rPath = rEntry.path();

		if( rPath.has_extension() )
		{
			++exts[ rPath.extension() ];
		}
		else
		{
			++exts[ "No Extension" ];
		}
	}

	uint64_t sum = 0llu;
	std::cout << dir.string() << ":\n";
	for( const auto& [ext, num] : exts )
	{
		sum += num;
		std::cout << " " << ext << " - " << num << "\n";
	}
	
	std::cout << sum << " total files.\n";

	return 0;
}
