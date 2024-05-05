#ifndef SPACESHIP_H 
#define SPACESHIP_H

#include "asteroid/bullet.h"

#define TIMER 0.7f
#define MAX_BULLET 15

typedef struct  {
    Texture2D texture;
    Vector2 position;
    Vector2 velocity;
    Queue bullets;

    int rotation;
    float cooldown;

    int ray;
} SpaceShip ;

SpaceShip* initSpaceShip(Texture2D texture, Vector2 pos, int ray) {

    Queue bullet;
    initQueue(&bullet);
    return spaceShip{
        texture, pos,{},bullet, 0, TIMER, ray
    };
}

bool isEqual(
    double a,           // primo double da comparare
    double b,           // secondo double da comparare
    double myepsilon)   // un numero piccolo per riferimento di comparazione
{
    if (islessequal(
        fabs(a - b),
        myepsilon * (isgreater(fabs(a), fabs(b)) ? fabs(a) : fabs(b)))) {
        // se sono (approssimativamente) uguali ritorna true
        return true;
    }
    // se sono (approssimativamente) diversi ritorna false
    return false;
}


void addBullet(SpaceShip* spaceship, Vector2 direction, bool isKeyDown) {

    if (spaceship->cooldown <= 0 && isKeyDown) {

        Vector2 updatedPosition = Vector2Add(direction, spaceship->position);
        Bullet newbullet = { updatedPosition, direction, true };
        enQueue(&spaceship->bullets, &newbullet);

        spaceship->cooldown = TIMER;

    }
    spaceship->cooldown -= GetFrameTime();
}

void updateBullet(SpaceShip* spaceship) {

    Vector2 velocity;
    Bullet newBullet;

    Bullet tempBullet;

    for (int i = 0; i < MAX_BULLET; i++) {
        tempBullet = spaceship->bullets.items[i];

        if (tempBullet.isActive) {

            velocity = Vector2Scale(tempBullet.direction, 10);
            newBullet = { Vector2Add(tempBullet.position, velocity), tempBullet.direction, true };

            spaceship->bullets.items[i] = newBullet;

            // Controllo se il proiettile è uscito dai limiti dello schermo
            if (newBullet.position.x > 800 || newBullet.position.y > 800 || newBullet.position.x < 0 || newBullet.position.y < 0) {

                tempBullet.isActive = false; // Imposto il flag isActive su false
                deQueue(&spaceship->bullets);
            }

        }
    }
}

void drawBullet(SpaceShip* spaceship) {

    Vector2 finalPosition;
    Vector2 position;

    Bullet tempBullet;

    for (int i = 0; i < MAX_BULLET; i++) {
        tempBullet = spaceship->bullets.items[i];

        if (tempBullet.isActive) { // Di segno solo i proiettili attivi

            position = tempBullet.position;
            finalPosition = Vector2Add(position, Vector2Scale(tempBullet.direction, 20));

            DrawLineV(position, finalPosition, WHITE);
        }
    }
}


void updateSpaceShip(SpaceShip* space_ship)
{
    // Coefficiente di slittamento
    float slideCoefficient = 0.92f;

    // rotazione
    if (IsKeyDown(KEY_RIGHT)) space_ship->rotation += 300.0f * GetFrameTime();
    if (IsKeyDown(KEY_LEFT))  space_ship->rotation -= 300.0f * GetFrameTime();

    // Calcolo della direzione della navicella
    Vector2 direction = { cosf(space_ship->rotation * DEG2RAD), sinf(space_ship->rotation * DEG2RAD) };
    addBullet(space_ship, direction, IsKeyDown(KEY_SPACE));

    // Calcolo del movimento principale
    float movementSpeed = 300.0f * GetFrameTime();
    Vector2 mainMovement = Vector2Scale(direction, movementSpeed * (IsKeyDown(KEY_UP) - IsKeyDown(KEY_DOWN)));

    // Applicazione dello slittamento solo se i tasti direzionali non sono premuti
    Vector2 slide = Vector2Scale(space_ship->velocity, slideCoefficient * (!IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN)));

    // Aggiornamento della velocità
    Vector2 acceleration = Vector2Add(mainMovement, slide);
    space_ship->velocity = Vector2Lerp(space_ship->velocity, acceleration, 0.2f); // Applicazione di una transizione graduale

    // Aggiornamento della posizione
    space_ship->position = Vector2Add(space_ship->position, space_ship->velocity);


    updateBullet(space_ship);

    //render dei proiettili
    drawBullet(space_ship);

    // Gestione dei bordi dello schermo
    if (space_ship->position.x > 800) space_ship->position.x = 0;
    if (space_ship->position.y > 800) space_ship->position.y = 0;
    if (space_ship->position.x < 0) space_ship->position.x = 800;
    if (space_ship->position.y < 0) space_ship->position.y = 800;
}


void drawSpaceShip(const SpaceShip* space_ship) {

    float width = space_ship->texture.width, height = space_ship->texture.height;

    const Rectangle source = { 0,0, width, height };
    Rectangle dest = { space_ship->position.x, space_ship->position.y, width / 2,  height / 2 };

    const Vector2 origin = { width / 4, height / 4 };

    DrawTexturePro(space_ship->texture, source, dest, origin, space_ship->rotation, WHITE);

}

#endif 
