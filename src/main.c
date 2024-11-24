#include "raylib.h"

#include "../includes/spaceship.h"
#include "../includes/asteroid.h"
#include "../includes/asteroid_container.h"
#include "../includes/collision.h"

#define screenHeight 800
#define screenWidth  800

int INITIAL_ASTEROIDS_SIZE =  3; //at the end there are 4 times small asteroids
#define SPACE_SHIP_RAY 30

typedef struct {
	int menu;
	int wawe;
	int currScore;
	int score;
} GameState;

void updateMenu(GameState* state,AsteroidContainer* asteroidsContainer,SpaceShip* ship);

int main(void){

	//----------   init variable -------//
	InitWindow(screenHeight, screenWidth, "Asteroid");
	InitAudioDevice();

	AsteroidContainer *asteroidsContainer = createAsteroids(INITIAL_ASTEROIDS_SIZE);
	
	SpaceShip *ship = (SpaceShip*)malloc(sizeof(Asteroid*));

	ship = initSpaceShip(
	        LoadTexture("./asset/spaceship.png"),
			(Vector2){ (float)screenWidth / 2, (float)screenHeight / 2 },//the centre of the screen
	        SPACE_SHIP_RAY
	);
	
	GameState state = { 1, 1, 0, 0 };

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	
	
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		state.currScore = collide(ship, asteroidsContainer);
		updateAsteroids(asteroidsContainer);
		updateMenu(&state, asteroidsContainer, ship);
		//------------  Drawing  ----------//
		updateSpaceShip(ship);
		BeginDrawing();
		drawAsteroids(asteroidsContainer);
		drawSpaceShip(ship);
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


void updateMenu(GameState* state,AsteroidContainer* asteroidsContainer,SpaceShip* ship){
	static double timer = 1;

	if(state->menu){
		DrawText("Asteroid", 240, 330, 70, WHITE);
		DrawText("press C to start", 300, 400, 20, WHITE);
		if(IsKeyPressed(KEY_C)) state->menu = 0;
	}
	//-------------  Update  -----------//
	else if(state->score >= INITIAL_ASTEROIDS_SIZE * 70 ){
		timer = -1.2;
		INITIAL_ASTEROIDS_SIZE += 3;
		reallocAsteroids(asteroidsContainer, INITIAL_ASTEROIDS_SIZE);
		state->wawe++;
		state->score = 0;
	}
	else if(state->currScore <= -1 || state->score < 0){
		DrawText("Game over", 200, 330, 70, WHITE);
		DrawText("press C to restart", 280, 400, 20, WHITE);
		state->score = -1;
		if(IsKeyPressed(KEY_C)){
			INITIAL_ASTEROIDS_SIZE = 3;
			printf("%d\n", &asteroidsContainer);
			
			reallocAsteroids(asteroidsContainer, INITIAL_ASTEROIDS_SIZE);
			printf("%d\n", &asteroidsContainer);
			state->score = 0;
		}
	}
	else{
		state->score += state->currScore;
		DrawText(TextFormat("score: %i", state->score), 30, 30, 20, WHITE);
		updateSpaceShip(ship);
		drawSpaceShip(ship);
	}
	if(state->score == 0 && timer < 0 && timer > -1.2) DrawText(TextFormat("Wawe: %i", state->wawe), 300, 330, 50, WHITE);
	timer += GetFrameTime(); ///timer
}
