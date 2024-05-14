#include "raylib.h"

#include "../includes/spaceship.h"
#include "../includes/asteroid.h"
#include "../includes/asteroid_container.h"
#include "../includes/collision.h"

#define screenHeight 800
#define screenWidth  800

int MAX_ASTEROIDS_SIZE =  3; //at the end there are 4 times small asteroids
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
	
	int score = 0;
	int currScore = 0;
	double timer = 1;
	GameState state = { 1, 1 };

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	
	
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		currScore = collide(ship, asteroidsContainer);
		updateAsteroids(asteroidsContainer);
		if(state.menu){
			DrawText("Asteroid", 240, 330, 70, WHITE);
			DrawText("press C to start", 300, 400, 20, WHITE);
			if(IsKeyPressed(KEY_C)) state.menu = 0;
		}
		//-------------  Update  -----------//
		else if(score >=  MAX_ASTEROIDS_SIZE /** 3 */* 10){
			timer = -1.2;
			MAX_ASTEROIDS_SIZE += 3;
			freeAsteroids(asteroidsContainer);
			asteroidsContainer = createAsteroids(MAX_ASTEROIDS_SIZE);

			score = 0;

		}
		else if(currScore <= -1 || score < 0){
			DrawText("Game over", 200, 330, 70, WHITE);
			DrawText("press C to restart", 280, 400, 20, WHITE);
			score = -1;
			if(IsKeyPressed(KEY_C)){
				MAX_ASTEROIDS_SIZE = 3;
				freeAsteroids(asteroidsContainer);
				asteroidsContainer = createAsteroids(MAX_ASTEROIDS_SIZE);

				score = 0;
			}
		}
		else{
			score += currScore;
			DrawText(TextFormat("score: %04i", score), 30, 30, 20, WHITE);
			updateSpaceShip(ship);
			drawSpaceShip(ship);
		}
		if(score == 0 && timer < 0 && timer > -1.2) DrawText(TextFormat("Wawe: %i", (MAX_ASTEROIDS_SIZE / 3) - 1), 300, 330, 50, WHITE);

		//------------  Drawing  ----------//
		BeginDrawing();
		drawAsteroids(asteroidsContainer);

		//DrawFPS(30,30);
		timer += GetFrameTime(); ///timer

		//-----	-------  End Drawing ------//
		ClearBackground(BLACK);
		EndDrawing();				
	}
	
	//--------   De-Initialization --------//
	
	CloseWindow(); // Close window and OpenGL context
	unloadSpaceship(ship);
	freeAsteroids(asteroidsContainer);


	return 0;
}


