#include "raylib.h"
#include "raymath.h"

#include "space_ship.h"
#include "asteroids.h"
#include "collisions.h"


#define screenHeight 800
#define screenWidth  800

#define MAX_LARGE_ASTEROIDS 12 //at the end there are 4 times small asteroids
#define SPACE_SHIP_RAY 50

int main(void){

	//----------   init variable -------//
	InitWindow(screenHeight, screenWidth, "Asteroid");

	AsteroidsContainer *asteroidsContainer = initAsteroids(MAX_LARGE_ASTEROIDS)
	
	SpaceShip *ship = initSpaceShip(
	        LoadTexture("./asset/spaceship.png"),
	        { (float)screenWidth / 2, (float)screenHeight / 2 },
	        SPACE_SHIP_RAY
	);
	
	

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	
	
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		//-------------  Update  -----------//
		updateSpaceShip(ship);
		updateSpaceShip(asteroidsContainer);
		collide(ship, asteroidsContainer);

		//------------  Drawing  ----------//
		BeginDrawing();
		DrawAsteroid(asteroidsContainer);
		DrawSpaceShip(ship);


		//------------  End Drawing ------//
		ClearBackground(BLACK);
		EndDrawing();		

		
	}
	
	//--------   De-Initialization --------//
	
	CloseWindow(); // Close window and OpenGL context
	UnloadSpaceShip(ship);
	UnloadAsteroids(asteroidsContainer);


	return 0;
}


