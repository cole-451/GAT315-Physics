/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "raymath.h"

//#include "PhysBody.h"
#include "World.h"
#include "Random.h"
#include "PhysBody.h"

#include <vector>











Vector2 gravity{ 0, 9.81f };


int main ()
{


	World::bodies.reserve(1000);

// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		float dt = GetFrameTime();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsKeyDown (KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))) {
			Physbody body; // all of this doesnt need to be moved.

			body.position = GetMousePosition();
			body.size =5.0f +( Random::GetRandomFloat() * 20.0f);
			float angle = Random::GetRandomFloat() * (2 *PI);

			Vector2 direction;
			direction.x = cosf(angle);
			direction.y = sinf(angle);

			body.velocity = direction * (Random::GetRandomFloat() * 300);
			body.acceleration = Vector2{ 0,0 };
			body.mass = 1.0f;

			body.restitution = 0.5f +(Random::GetRandomFloat() * 0.5f );

			World::bodies.push_back(body); //can be AddBody in World
		}
		//update

		//gravity update???
		for (auto& body : World::bodies) body.acceleration = Vector2{ 0,0 };
		for (auto& body : World::bodies) body.AddForce(gravity * 100.0f);


		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			Vector2 pos = GetMousePosition();
			for (auto& body : World::bodies) {
				Vector2 direction = pos - body.position;
				if (Vector2Length(direction) <= 100.0f) {
					Vector2 force = Vector2Normalize(direction) * -10000.0f;
					body.AddForce( force);
				}
			}

			DrawCircleLinesV(pos, 100, WHITE);
		}

		for (auto& body : World::bodies) World::SemiImplicitEuler(body, dt); // add to world update

		
		//barrier check: perhaps add to World
		for (auto& body : World::bodies)
		{
			//integration
			World::SemiImplicitEuler(body, dt);
			
			if (body.position.x - body.size > GetScreenWidth()) {
				body.position.x = GetScreenWidth() - body.size;
				body.velocity.x *= -body.restitution;
			}
			if (body.position.x - body.size < 0) {
				body.position.x = body.size;
				body.velocity.x *= -body.restitution;
			}
			if (body.position.y - body.size > GetScreenHeight()) {
				body.position.y = GetScreenHeight() - body.size;
				body.velocity.y *= -body.restitution;
			}
			if (body.position.y - body.size < 0) {
				body.position.y = body.size;
				body.velocity.y *= body.restitution;
			}
		}

		// drawing
		BeginDrawing();
		for ( auto& body : World::bodies)
		{
			
			body.DrawCircle(body.position, body.size, PURPLE);
		}

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,WHITE);

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
