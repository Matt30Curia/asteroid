#include "../includes/bullet.h"


void initQueue(Queue* queue, size_t size) {
    queue->size = size - 1;
    Bullet *bullet = (Bullet*)malloc(sizeof(Bullet));
    bullet->isActive = false;

    queue->items = (Bullet*)malloc(sizeof(Bullet) * size);

    for (int i = 0; i < queue->size; i++) {
        queue->items[i] = *bullet;

    }
    queue->head = -1;
    queue->tail = -1;


}

// Check if the queue is full
bool isFull(Queue* queue) {
    if ((queue->head == queue->tail + 1) || (queue->head == 0 && queue->tail == queue->size - 1)) return true;
    return false;
}

// Check if the queue is empty
bool isEmpty(Queue* queue) {
    if (queue->head == -1) return true;
    return false;
}

// Adding an element
bool enQueue(Queue* queue, Bullet* element) {
    printf("aggiunto\n");
    if (isFull(queue))
        return false;
    else {

        if (queue->head == -1) queue->head = 0;
        queue->tail = (queue->tail + 1) % queue->size;
        queue->items[queue->tail] = *element;

    }
}

// Removing an element
Bullet* deQueue(Queue* queue) {
    printf("tolto\n");
    Bullet* element = (Bullet*)malloc(sizeof(Bullet));
    if (isEmpty(queue)) {

        return element;
    }
    else {
        element = &queue->items[queue->head];

        if (queue->head == queue->tail) {
            queue->head = -1;
            queue->tail = -1;
        }

        else {
            queue->head = (queue->head + 1) % queue->size;
        }

        return (element);
    }
}
