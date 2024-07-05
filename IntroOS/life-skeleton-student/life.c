#include <stdio.h>
#include <stdlib.h>
#include "life.h"

LifeBoard* create_life_board(int width, int height) {
    // 分配内存并初始化结构体
    LifeBoard* board = (LifeBoard*)malloc(sizeof(LifeBoard));
    if (board == NULL) {
        fprintf(stderr, "Failed to allocate memory for LifeBoard\n");
        return NULL;
    }

    // 初始化 width 和 height
    board->width = width;
    board->height = height;

    // 初始化 cells
    board->cells = (LifeCell*)calloc(width * height, sizeof(LifeCell));
    if (board->cells == NULL) {
        fprintf(stderr, "Failed to allocate memory for cells\n");
        // 如果 cells 分配失败，释放已分配的内存，并返回 NULL
        free(board);
        return NULL;
    }

    return board;
}

void destroy_life_board(LifeBoard* board) {
    if (board != NULL) {
        // 释放 cells 内存
        free(board->cells);
        // 释放 LifeBoard 结构体内存
        free(board);
    }
}

LifeCell at(const LifeBoard* board, int x, int y) {
    return board->cells[y * board->width + x];
}

void set_at(LifeBoard* board, int x, int y, LifeCell value) {
    board->cells[y * board->width + x] = value;
}

int width(LifeBoard* board) {
    return board->width;
}

int height(LifeBoard* board) {
    return board->height;
}

int is_equal(const LifeBoard* first, const LifeBoard* second) {
    if (first->width != second->width || first->height != second->height) {
        return 0;
    }
    for (int i = 0; i < first->width * first->height; i++) {
        if (first->cells[i] != second->cells[i]) {
            return 0;
        }
    }
    return 1;
}

void swap(LifeBoard* first, LifeBoard* second) {
    if (first == NULL || second == NULL) return;
    // 仅交换cells指针
    LifeCell *temp = first->cells;
    first->cells = second->cells;
    second->cells = temp;
}

void print_life_board(const LifeBoard* board) {
    if (board == NULL || board->cells == NULL) {
        fprintf(stderr, "Error: LifeBoard or cells is NULL.\n");
        return;
    }
    
    printf("%d %d\n", board->width, board->height);
    for (int y = 0; y < board->height; y++) {
        for (int x = 0; x < board->width; x++) {
            printf("%c", at(board, x, y) ? '*' : '.');
        }
        printf("\n");
    }
}

void read_life_board(FILE* stream, LifeBoard* board) {
    int result;
    char c;

    // 首先尝试读取板的宽度和高度
    result = fscanf(stream, "%d %d", &board->width, &board->height);
    if (result != 2) {
        fprintf(stderr, "Error: Unable to read width and height from the file.\n");
        return;
    }

    // 忽略当前行剩余部分，直到换行符
    while ((c = fgetc(stream)) != '\n' && c != EOF);  // 读到换行或文件末尾

    // 为cells分配内存
    board->cells = (LifeCell*)calloc(board->width * board->height, sizeof(LifeCell));
    if (board->cells == NULL) {
        fprintf(stderr, "Failed to allocate memory for cells\n");
        return;
    }

    // 读取板格状态数据
    for (int y = 0; y < board->height; y++) {
        for (int x = 0; x < board->width; x++) {
            c = fgetc(stream);  // 读取一个字符
            // 设置cell值，' ' 或 '.' 表示死细胞，其他表示活细胞
            board->cells[y * board->width + x] = (c != ' ' && c != '.') ? 1 : 0;
        }
        while ((c = fgetc(stream)) != '\n' && c != EOF);  // 读到换行或文件末尾，准备读取下一行
    }
}

// 计算活细胞邻居数量（包括自己）
int count_live_neighbors(LifeBoard *state, int x, int y) {
    int live_neighbors = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < state->width && ny >= 0 && ny < state->height) {
                live_neighbors += at(state, nx, ny);
            }
        }
    }
    return live_neighbors;
}