#include "raylib.h"

#include "../includes/spaceship.h"
#include "../includes/asteroid.h"
#include "../includes/asteroid_container.h"
#include "../includes/collision.h"

#define screenHeight 800
#define screenWidth  800

#define MAX_ASTEROIDS_SIZE 12 //at the end there are 4 times small asteroids
#define SPACE_SHIP_RAY 50

int main(void){

	//----------   init variable -------//
	InitWindow(screenHeight, screenWidth, "Asteroid");

	AsteroidContainer *asteroidsContainer = createAsteroids(MAX_ASTEROIDS_SIZE);
	
	SpaceShip *ship = (SpaceShip*)malloc(sizeof(Asteroid*));

	ship = initSpaceShip(
	        LoadTexture("./asset/spaceship.png"),
			(Vector2){ (float)screenWidth / 2, (float)screenHeight / 2 },//the centre of the screen
	        SPACE_SHIP_RAY
	);
	
	

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	
	
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		//-------------  Update  -----------//
		updateSpaceShip(ship);
		updateAsteroids(asteroidsContainer);
		collide(ship, asteroidsContainer);

		//------------  Drawing  ----------//
		BeginDrawing();
		drawAsteroids(asteroidsContainer);
		drawSpaceShip(ship);


		//------------  End Drawing ------//
		ClearBackground(BLACK);
		EndDrawing();				
	}
	
	//--------   De-Initialization --------//
	
	CloseWindow(); // Close window and OpenGL context
	//unloadSpaceship(ship);
	freeAsteroids(asteroidsContainer);


	return 0;
}


