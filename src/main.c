#include "raylib.h"

#include "../includes/spaceship.h"
#include "../includes/asteroid.h"
#include "../includes/asteroid_container.h"
#include "../includes/collision.h"

#define screenHeight 800
#define screenWidth  800

#define MAX_ASTEROIDS_SIZE 10 //at the end there are 4 times small asteroids
#define SPACE_SHIP_RAY 30

typedef struct {
	int menu;
	int wawe;

} GameState;

int main(void){

	//----------   init variable -------//
	InitWindow(screenHeight, screenWidth, "Asteroid");
	InitAudioDevice();

	AsteroidContainer *asteroidsContainer = createAsteroids(MAX_ASTEROIDS_SIZE);
	
	SpaceShip *ship = (SpaceShip*)malloc(sizeof(Asteroid*));

	ship = initSpaceShip(
	        LoadTexture("./asset/spaceship.png"),
			(Vector2){ (float)screenWidth / 2, (float)screenHeight / 2 },//the centre of the screen
	        SPACE_SHIP_RAY
	);
	
	GameState state = { 1, 1 };

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	
	
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		updateAsteroids(asteroidsContainer);
		if(state.menu){
			DrawText("Asteroid", 240, 330, 70, WHITE);
			DrawText("press C to start", 300, 400, 20, WHITE);
			if(IsKeyPressed(KEY_C)) state.menu = 0;
		}
		//-------------  Update  -----------//
		else{
			printf("damage %d \n",collide(ship, asteroidsContainer));
			updateSpaceShip(ship);
			drawSpaceShip(ship);
		}




		//------------  Drawing  ----------//
		BeginDrawing();
		drawAsteroids(asteroidsContainer);

		//DrawFPS(30,30);

		//------------  End Drawing ------//
		ClearBackground(BLACK);
		EndDrawing();				
	}
	
	//--------   De-Initialization --------//
	
	CloseWindow(); // Close window and OpenGL context
	unloadSpaceship(ship);
	freeAsteroids(asteroidsContainer);


	return 0;
}


