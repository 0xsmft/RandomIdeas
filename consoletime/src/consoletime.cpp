/**
 *
 * Module:
 *  consoletime
 *
 * Description:
 *  Console output current time.
*/

#include <chrono>
#include <iostream>
#include <thread>

int main( int count, char** ppArgs )
{
	while( true )
	{
		const std::chrono::zoned_time zonedTime{ std::chrono::current_zone(), std::chrono::system_clock::now() };

		std::string fmtTime = std::format( "{:%A, %Ec%z - Week %V}", zonedTime );
		std::cout << fmtTime << "\r";

		std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
	}

	return 0;
}
