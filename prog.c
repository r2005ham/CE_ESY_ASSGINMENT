#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define BUFFER_SIZE 8 

typedef struct RingBuf {
    char* rdPtr;
    char* wrPtr;
    char arr[BUFFER_SIZE];
    bool full;
} RingBuf;
void rb_reset(RingBuf* rb) {
    rb->rdPtr = rb->arr;
    rb->wrPtr = rb->arr;
    rb->full = false;
    memset(rb->arr, 0, BUFFER_SIZE);
}
void rb_write(RingBuf* rb, char newChar) {
    if (rb->full) 
        rb->rdPtr++;
        if (rb->rdPtr > &(rb->arr[BUFFER_SIZE - 1])) {
            rb->rdPtr = rb->arr;
        }
    }

    *(rb->wrPtr) = newChar;
    rb->wrPtr++;

    if (rb->wrPtr > &(rb->arr[BUFFER_SIZE - 1])) {
        rb->wrPtr = rb->arr;
    }

    if (rb->wrPtr == rb->rdPtr) {
        rb->full = true;
    }
}
char rb_read(RingBuf* rb) {
    char val = 0;
    if (rb->full || rb->rdPtr != rb->wrPtr) {
        val = *(rb->rdPtr);
        rb->rdPtr++;
        rb->full = false; 

        if (rb->rdPtr > &(rb->arr[BUFFER_SIZE - 1])) {
            rb->rdPtr = rb->arr;
        }
    }
    return val;
}

RingBuf* rb_init() {
    RingBuf* rb = (RingBuf*)malloc(sizeof(RingBuf));
    if (rb != NULL) {
        rb_reset(rb);
    }
    return rb;
}

void rb_free(RingBuf* rb) {
    free(rb);
}
int main() {
    RingBuf* rb = rb_init();
    char name[50];
    char fullText[100];
    printf("Enter your name: ");
    scanf("%s", name);
    strcpy(fullText, name);
    strcat(fullText, "CE-ESY");

    printf("\n--- Circular Buffer Execution ---\n");
    printf("Input Text: %s\n", fullText);
    printf("Buffer Capacity: %d\n", BUFFER_SIZE);

    for (int i = 0; i < strlen(fullText); i++) {
        rb_write(rb, fullText[i]);
    }

    printf("Data read from buffer: ");
    while (rb->full || rb->rdPtr != rb->wrPtr) {
        char tempChar = rb_read(rb);
        if (tempChar != 0) {
            printf("%c", tempChar);
        }
    }
    printf("\n");

    if (!rb->full && rb->rdPtr == rb->wrPtr) {
        printf("Status Check: Buffer is EMPTY.\n");
    } else {
        printf("Status Check: Buffer still contains data.\n");
    }

    printf("----------------------------------\n");

    rb_free(rb);
    return 0;
}
