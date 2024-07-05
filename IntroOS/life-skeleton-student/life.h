#ifndef LIFE_H_
#define LIFE_H_

#include<stdio.h>
#include<stdlib.h>

typedef unsigned char LifeCell;

typedef struct {
    int width;
    int height;
    LifeCell *cells;
} LifeBoard;

LifeBoard* create_life_board(int width, int height);
void destroy_life_board(LifeBoard* board);
LifeCell at(const LifeBoard* board, int x, int y);
void set_at(LifeBoard* board, int x, int y, LifeCell value);
int width(LifeBoard* board);
int height(LifeBoard* board);
int is_equal(const LifeBoard* first, const LifeBoard* second);
void swap(LifeBoard* first, LifeBoard* second);
void print_life_board(const LifeBoard* board);
void read_life_board(FILE* stream, LifeBoard* board);
int count_live_neighbors(LifeBoard *state, int x, int y);
int deep_copy_life_board(LifeBoard *dest, const LifeBoard *src);
/*
 * Simulates the specified number of steps by the Game of Life rules,
 * updating the LifeBoard state to have the new state.
 *
 * Two versions: a serial version and a parallel version you must implement.
 */ 
void simulate_life_serial(LifeBoard *state, int steps);
void simulate_life_parallel(int threads, LifeBoard *state, int steps);
#endif
