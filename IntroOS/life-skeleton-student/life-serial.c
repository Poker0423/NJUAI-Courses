#include "life.h"

void simulate_life_serial(LifeBoard *state, int steps) {
    if (steps == 0) return;
    LifeBoard *next_state = create_life_board(state->width, state->height);
    if (next_state == NULL) {
        fprintf(stderr, "Failed to allocate memory for next state.\n");
        return;
    }
    for (int step = 0; step < steps; step++) {
        // 更新下一个状态
        for (int y = 1; y < state->height - 1; y++) {
            for (int x = 1; x < state->width - 1; x++) {
                int live_neighbors = count_live_neighbors(state, x, y);
                LifeCell current_cell = at(state, x, y);
                LifeCell new_cell = (live_neighbors == 3) || (live_neighbors == 4 && current_cell == 1) ? 1 : 0;
                set_at(next_state, x, y, new_cell);
            }
        }
        // 交换两个状态的指针，使 next_state 成为新的 current state
        swap(state, next_state);
    }
    // 保证 next_state 被正确释放
    destroy_life_board(next_state);
}