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
#include "PointEffector.h"
#include "GravitationalEffector.h"

#include <vector>
#include <string>

int main ()
{
	World world;
	world.AddEffector(new PointEffector(Vector2{ 200,200, }, 2.0f, 1.0f));
	world.AddEffector(new GravitationalEffector(10000.0f));


	world.bodies.reserve(1000000);

// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	//SetTargetFPS(60);

	float timeAccumulator = 0.0f;

	float fixedTimeStep = 1.0f / 60.0f;
	
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		float dt = GetFrameTime();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsKeyDown (KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))) {
			Physbody body; // all of this doesnt need to be moved.

			body.bodyType = (IsKeyDown(KEY_LEFT_ALT) ? BodyType::Static : BodyType::Dynamic);

			body.position = GetMousePosition();
			body.size =5.0f +( Random::GetRandomFloat() * 20.0f);
			float angle = Random::GetRandomFloat() * (2 *PI);

			Vector2 direction;
			direction.x = cosf(angle);
			direction.y = sinf(angle);

			body.AddForce(direction * ( Random::GetRandomFloat() * 300), ForceMode::VelocityChange);

			//body.velocity = direction * (Random::GetRandomFloat() * 300);
			body.acceleration = Vector2{ 0,0 };
			body.mass = body.size;

			body.inverseMass = (body.bodyType == BodyType::Static)? 0 : 1.0f / body.mass;

			body.restitution = 0.5f +(Random::GetRandomFloat() * 0.5f );

			body.gravityScale = 0.0f;

			body.damping = 0.3f;

			world.AddBody(body); 
		}
		//update ( all this shit goes in world's update, or Step)

		timeAccumulator += dt;

		while (timeAccumulator > fixedTimeStep) {
			world.Step(fixedTimeStep);
			timeAccumulator -= fixedTimeStep;
		}

		// drawing (add to world.draw)
		BeginDrawing();
		for ( auto& body : world.bodies) //draw in WORLD
		{
			body.DrawCircle(body.position, body.size, PURPLE);
		}

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		std::string fps_text = "FPS: ";
		fps_text += std::to_string(GetFPS());
		DrawText(fps_text.c_str(), 200, 200, 20, WHITE);

		// draw our texture to the screen
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
