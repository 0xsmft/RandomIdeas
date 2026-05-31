/**
 *
 * Module:
 *  raylibfirst
 *
 * Description:
 *  My first time using raylib.
*/

#include <string>
#include <random>
#include <iostream>

#include <raylib/raylib.h>

int main( int count, char** ppArgs ) 
{
	InitWindow( 1280, 720, "Window in raylib" );

	SetTargetFPS( 60 );

	while( !WindowShouldClose() )
	{
		BeginDrawing();

		ClearBackground( { 0xFF, 0x0, 0xFF, 0xFF } );

		DrawFPS( 0, 0 );

		EndDrawing();
	}

	CloseWindow();
}
