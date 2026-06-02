/**
 *
 * Module:
 *  raylib3d
 *
 * Description:
 *  raylib with 3d.
*/

#include <string>
#include <random>
#include <iostream>

#include <raylib/raylib.h>

int main( int count, char** ppArgs )
{
	SetConfigFlags( FLAG_WINDOW_RESIZABLE );
	InitWindow( 1280, 720, "Window in raylib" );

	SetTargetFPS( 60 );

	Camera cam{ 0 };
	cam.position = { 50.0f, 50.0f, 50.0f };
	cam.target = { 0.0f, 12.0f, 0.0f };
	cam.up = { 0.0f, 1.0f, 0.0f };
	cam.fovy = 45.0f;
	cam.projection = CAMERA_PERSPECTIVE;

	while( !WindowShouldClose() )
	{
		UpdateCamera( &cam, CAMERA_FREE );

		BeginDrawing();

		ClearBackground( { 0xFF, 0x0, 0xFF, 0xFF } );
		
		DrawFPS( 0, 0 );

		BeginMode3D( cam );

		DrawGrid( 20, 10.0f );

		EndMode3D();
		
		EndDrawing();
	}

	CloseWindow();
}
