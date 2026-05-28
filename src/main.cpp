/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/



#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <vector>
#include "World.h"
#include "Random.h"
#include "GravitationalEffector.h"
#include "PointEffector.h"	 
#include "AreaEffector.h" 
#include "DragEffector.h"
#include "Spring.h"
#include "world_camera.h"

#include "raylib.h"
#include "raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define GUI_PHYSICS_IMPLEMENTATION
#pragma warning ( push )
#pragma warning ( disable : 4576)
#include "gui_physics.h"
#pragma warning ( pop )

GuiPhysicsState state;

void AddBody(World& world, WorldCamera& camera);
void AddEffector(World& world, WorldCamera& camera);

int main ()
{

    
	
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");



	// Get GUI state
	state = InitGuiPhysics();
	GuiLoadStyle("raygui/styles/dark/style_dark.rgs");
	
	

	World world;
	WorldCamera world_camera(Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }, 5);
	world.SetBounds(world_camera.ScreenToWorld({ 0, (float)GetScreenHeight() }), world_camera.ScreenToWorld({ (float)GetScreenWidth(), 0 }));
	Body* selectedBody = nullptr;
				  
	float timeAccum = 0.0f;

	bool simulate = true;
	
	/*world.AddEffector(new PointEffector(Vector2{ 170, 170 }, 200, -30000.0f));
	world.AddEffector(new GravityEffector(Vector2{ 900, 600 }, 200, 30000.0f));
	world.AddEffector(new AreaEffector(Vector2{ 900, 170 }, 200, 0, 30000.0f));
	world.AddEffector(new DragEffector(Vector2{ 170, 600 }, 200, 30.0f));*/
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		float deltaTime = fminf(GetFrameTime(), 0.1f);
		SetTargetFPS(state.FPSValue);
		float fixedTimeStep = 1.0f / state.FPSValue;
		if(IsKeyPressed(KEY_SPACE))
		{
			state.SimulateActive = !state.SimulateActive;
		}
		if(IsKeyPressed(KEY_TAB))
		{
			state.PhysicsPanelActive = !state.PhysicsPanelActive;
		}

		World::SetGravity(Vector2{ 0.0f, state.GravityValue });

		bool mouseOverGui = state.PhysicsPanelActive && CheckCollisionPointRec(GetMousePosition(), Rectangle{ state.anchor02.x + 0, state.anchor02.y + 0, 304, 664 });
		if (!mouseOverGui)
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ||
				(IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
			{
				if (IsKeyDown(KEY_LEFT_SHIFT))
				{
					AddEffector(world, world_camera);
				}
				else
				{
					AddBody(world, world_camera);
				}
			}

			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
			{
				selectedBody = world.GetBodyIntersect(world_camera.ScreenToWorld(GetMousePosition()));
			}

			if(selectedBody)
			{
				if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_LEFT_CONTROL)) {
					Vector2 position = world_camera.ScreenToWorld(GetMousePosition());
					Vector2 force = Spring::GetSpringForce(position, selectedBody->position, 0, state.SpringStiffnessValue * state.SpringMultiplierValue);
					selectedBody->AddForce(force);

					DrawLineV(selectedBody->position, position, YELLOW);
				}
			}
		}
		//update
		if (state.SimulateActive)
		{
			timeAccum += deltaTime;
			while (timeAccum > fixedTimeStep)
			{
				world.Step(fixedTimeStep);
				timeAccum -= fixedTimeStep;
			}
		}
		

		// draw
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		world_camera.Begin();
		world.Draw();
		world_camera.End();

		DrawCircleLinesV(GetMousePosition(), state.BodySizeValue, WHITE);

		if (selectedBody) {
			DrawCircleLinesV(selectedBody->position, selectedBody->size + 5, YELLOW);
		}
		GuiPhysics(&state);

		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

void AddBody(World& world, WorldCamera& camera) {
	Body body;

	body.bodyType = (BodyType)(state.BodyTypeActive);

	body.position = camera.ScreenToWorld(GetMousePosition());
	float angle = GetRandomFloat() * (2 * PI);
	Vector2 direction;
	direction.x = cosf(angle);
	direction.y = sinf(angle);

	body.AddForce(direction * state.BodyVelocityValue, ForceMode::VelocityChange);
	body.acceleration = { 0,0 };
	body.size = state.BodySizeValue;
	body.mass = body.size * state.BodyMassValue;
	body.restitution = state.BodyRestitutionValue;
	body.gravityScale = state.BodyGravityValue;
	body.damping = state.BodyDampingValue;
	world.AddBody(body);
}

void AddEffector(World& world, WorldCamera& camera) {
	Vector2 position = camera.ScreenToWorld(GetMousePosition());
	float size = state.EffectorSizeValue;
	float force = state.EffectorForceValue;
	float angle = state.EffectorAngleValue;
	switch (state.EffectorTypeActive)
	{
	case 0:
		world.AddEffector(new PointEffector(position, size, force));
		break;
	case 1:
		world.AddEffector(new GravityEffector(position, size, force));
		break;
	case 2:
		world.AddEffector(new AreaEffector(position, size, angle, force));
		break;
	case 3:
		world.AddEffector(new DragEffector(position, size, force));
		break;
	default:
		break;
	}
}
