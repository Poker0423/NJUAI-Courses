#include <pthread.h>
#include <stdlib.h>
#include "life.h"

typedef struct {
    int start_row;
    int end_row;
    LifeBoard *current;
    LifeBoard *next;
} ThreadData;

typedef struct {
    pthread_t *threads;
    ThreadData *thread_data;
    int thread_count;
} ThreadPool;

void* worker_function(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    for (int y = data->start_row; y < data->end_row; y++) {
        for (int x = 1; x < data->current->width - 1; x++) {
            int live_neighbors = count_live_neighbors(data->current, x, y);
            LifeCell current_cell = at(data->current, x, y);
            LifeCell new_cell = (live_neighbors == 3) || (live_neighbors == 4 && current_cell == 1) ? 1 : 0;
            set_at(data->next, x, y, new_cell);
        }
    }
    return NULL;
}

ThreadPool* create_thread_pool(int thread_count) {
    ThreadPool *pool = (ThreadPool *) malloc(sizeof(ThreadPool));
    pool->threads = (pthread_t *) malloc(thread_count * sizeof(pthread_t));
    pool->thread_data = (ThreadData *) malloc(thread_count * sizeof(ThreadData));
    pool->thread_count = thread_count;
    return pool;
}

void destroy_thread_pool(ThreadPool *pool) {
    free(pool->threads);
    free(pool->thread_data);
    free(pool);
}

void simulate_life_parallel(int threads, LifeBoard *state, int steps) {
    if (steps == 0) return;

    ThreadPool *pool = create_thread_pool(threads);
    LifeBoard* next_state = create_life_board(state->width, state->height);

    if (next_state == NULL) {
        fprintf(stderr, "Failed to allocate memory for next state.\n");
        destroy_thread_pool(pool);
        return;
    }

    int rows_per_thread = (state->height - 2) / threads;

    for (int step = 0; step < steps; step++) {
        for (int i = 0; i < threads; i++) {
            pool->thread_data[i].start_row = i * rows_per_thread + 1;
            pool->thread_data[i].end_row = (i == threads - 1) ? (state->height - 1) : ((i + 1) * rows_per_thread + 1);
            pool->thread_data[i].current = state;
            pool->thread_data[i].next = next_state;
            pthread_create(&pool->threads[i], NULL, worker_function, &pool->thread_data[i]);
        }

        for (int i = 0; i < threads; i++) {
            pthread_join(pool->threads[i], NULL);
        }

        swap(state, next_state);
    }

    destroy_thread_pool(pool);
    destroy_life_board(next_state);
}
