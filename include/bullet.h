#ifndef BULLET_H
#define BULLET_H

#define BULLET_SIZE 15


typedef struct Bullet {
    Vector2 position ;
    Vector2 direction;
    bool isActive = false; // Aggiunto un flag per indicare se il proiettile è attivo o meno
};


typedef struct Queue {
    int head = -1;  
    int tail = -1;
    Bullet items[BULLET_SIZE];
};


void initQueue(Queue* queue);
bool enQueue(Queue* queue, Bullet* element);
Bullet* deQueue(Queue* queue);



#endif
