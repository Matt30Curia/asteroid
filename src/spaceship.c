#include "../includes/spaceship.h"

 
SpaceShip* initSpaceShip(Texture2D texture, Vector2 pos, int ray) {

    Queue bullets;
    initQueue(&bullets, MAX_BULLET);
    SpaceShip *s = (SpaceShip *)malloc(sizeof(SpaceShip));

    s->texture = texture;
    s->position = pos;
    s->velocity = (Vector2){0,0};
    s->bullets = bullets;
    s->rotation = 0;
    s->cooldown = TIMER;
    s->ray = ray;
    s->laser = LoadSound("./asset/laser.ogg");
    s->engine = LoadSound("./asset/engine.ogg");

    return s;
}


void addBullet(SpaceShip* spaceship, Vector2 direction, bool isKeyDown) {

    if (spaceship->cooldown <= 0 && isKeyDown) {

        Vector2 updatedPosition = Vector2Add(direction, spaceship->position);
        Bullet newbullet = { updatedPosition, direction, true };
        enQueue(&spaceship->bullets, &newbullet);
        PlaySound(spaceship->laser);
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
            printf("TOLGO %d\n", tempBullet.isActive);
            velocity = Vector2Scale(tempBullet.direction, 10);//add define for velocity
            newBullet = (Bullet){ Vector2Add(tempBullet.position, velocity), tempBullet.direction, true };

            spaceship->bullets.items[i] = newBullet;

            // Controllo se il proiettile è uscito dai limiti dello schermo
            if ((newBullet.position.x > 800 || newBullet.position.y > 800 || newBullet.position.x < 0 || newBullet.position.y < 0 )) {


                    spaceship->bullets.items[i].isActive = false;
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
            finalPosition = Vector2Add(position, Vector2Scale(tempBullet.direction, 20));//bullet dimension

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
    if (IsKeyDown(KEY_UP)) PlaySound(space_ship->engine);

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


void unloadSpaceship(SpaceShip* space_ship){
    UnloadTexture(space_ship->texture);
}
