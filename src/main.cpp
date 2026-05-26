/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"


#include "raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define GUI_PHYSICS_IMPLEMENTATION
#pragma warning ( push )
#pragma warning ( disable : 4576)
#include "gui_physics.h"
#pragma warning ( pop )

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

//#include "PhysBody.h"
#include "World.h"
#include "world_camera.h"
#include "Random.h"
#include "PhysBody.h"
#include "PointEffector.h"
#include "GravitationalEffector.h"
#include "AreaEffector.h"
#include "DragEffector.h"

#include <vector>
#include <string>

GuiPhysicsState state;

void Addbody(World& world, WorldCamera& camera);
void Addeffector(World& world, WorldCamera& camera);

int main()
{
	World world;
	WorldCamera world_camera(Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }, 5);
	// set min(left - bottom) boundary(0, screen height) and max(right, top) boundary(screen width, 0)
		world.SetBounds(world_camera.ScreenToWorld({ 0, (float)GetScreenHeight() }), world_camera.ScreenToWorld({ (float)GetScreenWidth(), 0 }));
	/*world.AddEffector(new PointEffector(Vector2{ 300,200, }, 200.0f, -300000.0f));
	world.AddEffector(new AreaEffector(Vector2{ 900,200, }, 200.0f, 0, 300000.0f));
	world.AddEffector(new DragEffector(Vector2{ 300,600, }, 200.0f, 0.015f));

	world.AddEffector(new GravitationalEffector(Vector2{900,600}, 200, 40000.0f));*/


	world.bodies.reserve(1000000);

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	state = InitGuiPhysics();

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

	//SetTargetFPS(60);

	float timeAccumulator = 0.0f;


	bool simulate = true;

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		float dt = fminf(GetFrameTime(), 0.1f);

		float fixedTimeStep = 1.0f / state.FPSValue;

		if (IsKeyPressed(KEY_SPACE)) state.SimulateActive = !state.SimulateActive;

		bool MouseOverGui = state.PhysicsPanelActive && CheckCollisionPointRec(GetMousePosition(), Rectangle{ state.anchor02.x, state.anchor02.y, 304, 664 });

		if (IsKeyPressed(KEY_TAB)) state.PhysicsPanelActive = !state.PhysicsPanelActive;

		World::SetGravity(Vector2{ 0.0f, state.GravityValue });

		// if mouse over gui,
		if (!MouseOverGui) {
		
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ||
				(IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
			{
				if (IsKeyDown(KEY_LEFT_SHIFT))
				{
					Addeffector(world, world_camera);
				}
				else
				{
					Addbody(world, world_camera);
				}
			}
		}


		//update ( all this shit goes in world's update, or Step)
		if (state.SimulateActive) {
			timeAccumulator += dt;

			while (timeAccumulator > fixedTimeStep) {

				world.Step(fixedTimeStep);
				timeAccumulator -= fixedTimeStep;
			}

		}

		// drawing (add to world.draw)
		BeginDrawing();


		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);

		// draw some text using the default font
		std::string fps_text = "FPS: ";
		fps_text += std::to_string(GetFPS());
		DrawText(fps_text.c_str(), 200, 200, 20, WHITE);

		world_camera.Begin(); // set world camera
		// draw our texture to the screen
		world.Draw();

		world_camera.End(); // remove world camera


		GuiPhysics(&state);
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

void Addbody(World& world, WorldCamera& camera) {
	Physbody body; // all of this doesnt need to be moved.

	body.bodyType = (BodyType)state.BodyTypeActive;

	body.position = camera.ScreenToWorld(GetMousePosition());
	body.size = state.BodySizeValue;
	float angle = Random::GetRandomFloat() * (2 * PI);

	Vector2 direction;
	direction.x = cosf(angle);
	direction.y = sinf(angle);

	body.AddForce((direction * state.BodyVelocityValue), ForceMode::VelocityChange);

	//body.velocity = direction * (Random::GetRandomFloat() * 300);
	body.acceleration = Vector2{ 0,0 };
	body.mass = body.size * state.BodyMassValue;

	body.inverseMass = (body.bodyType == BodyType::Static) ? 0 : 1.0f / body.mass;

	body.restitution = state.BodyRestitutionValue;

	body.gravityScale = state.BodyGravityValue;

	body.damping = state.BodyDampingValue;

	world.AddBody(body);
}

void Addeffector(World& world, WorldCamera& camera) {
	Vector2 position = camera.ScreenToWorld(GetMousePosition());

	Effector* effector = nullptr;

	switch ((EffectorType) state.EffectorTypeActive)
	{
	case EffectorType::Area:
		effector = new AreaEffector(Vector2{ 900,200, }, 200.0f, 0, 300000.0f);
		break;
	case EffectorType::Drag:
		effector = new DragEffector(Vector2{ 300,600, }, 200.0f, 0.015f);
		break;
	case EffectorType::Gravitation:
		effector = new GravitationalEffector(Vector2{ 900,600 }, 200, 40000.0f);
		break;
	case EffectorType::Point:
		effector = new PointEffector(Vector2{ 300,200, }, 200.0f, -300000.0f);
		break;

	default:
		break;
	}
	if (effector) world.AddEffector(effector);
}
