//
// Created by hugo on 3/12/20.
//

#include "Exercise_2.h"
#include <queue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rc = 0;
    int inside_count = 0;
    int entering_count = 0;
    int leaving_count = 0;
    Queue_t client_queue;
    client_queue.list = ForwardList_factory();

    while (rc >= 0) {
        printf("%d clients in the waiting area\n", inside_count);
        if (inside_count < WAITING_AREA_SIZE)
            entering_count = rand() % (WAITING_AREA_SIZE - inside_count); // NOLINT(cert-msc30-c,cert-msc50-cpp)
        else
            entering_count = 0;

        if (inside_count > 0)
            leaving_count = rand() % inside_count; // NOLINT(cert-msc30-c,cert-msc50-cpp)
        else
            leaving_count = 0;

        printf("\n%d clients entering\n", entering_count);
        for (int i = 0; i < entering_count; i++) {
            client_t *client = malloc(sizeof(client_t));
            Queue_push(&client_queue, client);
        }
        inside_count += entering_count;

        printf("%d clients leaving\n\n", leaving_count);
        for (int i = 0; i < leaving_count; i++) {
            client_t *client = Queue_pop(&client_queue);
            // Do what you want with the client
            free(client);
        }
        inside_count -= leaving_count;
        sleep(1);
    }
}