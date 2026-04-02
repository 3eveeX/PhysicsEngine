/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "raymath.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <vector>

struct Body{
	    Vector2 position;
		Vector2 velocity;
		Vector2 acceleration;
		float mass;
		float size;
		float restitution;
};

float GetRandomFloat() {
	return (float)GetRandomValue(0, 10000) / 10000.0f;
}

void AddForce(Body& body, Vector2 force)
{
	body.acceleration += force * (1/body.mass);
}

void Integrator(Body& body, float deltaTime)
{
	body.velocity += body.acceleration * deltaTime;
	body.position += body.velocity * deltaTime;
}

Vector2 gravity{ 0, 9.81f };

int main ()
{

    std::vector<Body> bodies;
	bodies.reserve(1000);
	
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
		float deltaTime = GetFrameTime();

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsKeyDown(KEY_GRAVE) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
		{
			Body body;
			body.position = GetMousePosition();
			float angle = GetRandomFloat() * (2 * PI);
			Vector2 direction;
			direction.x = cosf(angle);
			direction.y = sinf(angle);

			body.velocity = direction * (50.0f + GetRandomFloat() * 500);
			body.acceleration = { 0,0 };
			body.mass = body.size;
			body.size = GetRandomValue(5, 20);
			body.restitution =   GetRandomFloat() -0.1f;
			bodies.push_back(body);
		}

		//update
		for (auto& body : bodies)
		{
			body.acceleration = { 0, 100 * body.mass };
			body.velocity.x += body.acceleration.x * deltaTime;
			body.velocity.y += body.acceleration.y * deltaTime;
			body.position.x += body.velocity.x * deltaTime;
			body.position.y += body.velocity.y * deltaTime;

			body.velocity += (gravity * 100) * deltaTime;

			if(body.position.y + body.size> GetScreenHeight())
			{
				body.position.y = GetScreenHeight() - body.size;
				body.velocity.y *= -body.restitution;
			}
			if(body.position.x + body.size > GetScreenWidth())
			{
				body.position.x = GetScreenWidth() - body.size;
				body.velocity.x *= -body.restitution;
			}
			 else if(body.position.x + body.size < 0)
			{
				body.position.x = body.size;
				body.velocity.x *= -body.restitution;
			}
			 else if(body.position.y + body.size < 0)
			{
				body.position.y = body.size;
				body.velocity.y *= -body.restitution;
			}
		}

		// draw
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,WHITE);

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE); 

		for (const auto& body : bodies)
		 {
			 
			 DrawCircleV(body.position, body.size, WHITE);
		}
		
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
