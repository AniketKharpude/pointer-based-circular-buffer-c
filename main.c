#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *buffer;
    int size;
    int front;
    int rear;
    int count;
} CircularBuffer;

CircularBuffer* createBuffer(int size) {
    CircularBuffer *cb = (CircularBuffer *)malloc(sizeof(CircularBuffer));
    if (cb == NULL) {
        printf("Memory allocation failed for buffer structure.\n");
        return NULL;
    }

    cb->buffer = (int *)malloc(size * sizeof(int));
    if (cb->buffer == NULL) {
        printf("Memory allocation failed for data buffer.\n");
        free(cb);
        return NULL;
    }

    cb->size = size;
    cb->front = 0;
    cb->rear = -1;
    cb->count = 0;
    return cb;
}

int isFull(CircularBuffer *cb) {
    return cb->count == cb->size;
}

int isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

void enqueue(CircularBuffer *cb, int data) {
    if (isFull(cb)) {
        printf("Buffer Overflow: Cannot insert %d\n", data);
        return;
    }

    cb->rear = (cb->rear + 1) % cb->size;
    cb->buffer[cb->rear] = data;
    cb->count++;

    printf("%d inserted into buffer.\n", data);
}

void dequeue(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("Buffer Underflow: No data to remove.\n");
        return;
    }

    int data = cb->buffer[cb->front];
    cb->front = (cb->front + 1) % cb->size;
    cb->count--;

    printf("%d removed from buffer.\n", data);
}

void displayBuffer(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("Buffer is empty.\n");
        return;
    }

    printf("Buffer elements: ");
    int i, index;
    for (i = 0; i < cb->count; i++) {
        index = (cb->front + i) % cb->size;
        printf("%d ", cb->buffer[index]);
    }
    printf("\n");
}

void freeBuffer(CircularBuffer *cb) {
    if (cb != NULL) {
        free(cb->buffer);
        free(cb);
    }
}

int main() {
    int size, choice, value;

    printf("Enter buffer size: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Invalid buffer size.\n");
        return 1;
    }

    CircularBuffer *cb = createBuffer(size);
    if (cb == NULL) {
        return 1;
    }

    while (1) {
        printf("\n--- Circular Buffer Menu ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                enqueue(cb, value);
                break;

            case 2:
                dequeue(cb);
                break;

            case 3:
                displayBuffer(cb);
                break;

            case 4:
                freeBuffer(cb);
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}