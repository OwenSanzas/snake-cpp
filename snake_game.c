// snake_game.c - Simple Snake Game Logic

#include "snake_game.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// ==================== Level 3 Functions ====================

// Check if position is within bounds
int is_valid_position(int x, int y, int width, int height) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

// Check if two positions are equal
int positions_equal(Position p1, Position p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

// Generate random position
Position generate_random_position(int width, int height, unsigned int seed) {
    Position pos;
    pos.x = (seed * 17 + 23) % width;
    pos.y = (seed * 13 + 19) % height;
    return pos;
}

// ==================== Level 2 Functions ====================

// Check if snake collides with itself
int check_self_collision(Snake *snake) {
    if (!snake || snake->length < 2) return 0;

    Position head = snake->body[0];
    for (int i = 1; i < snake->length; i++) {
        if (positions_equal(head, snake->body[i])) {
            return 1;
        }
    }
    return 0;
}

// Check if snake collides with wall
int check_wall_collision(Snake *snake, int width, int height) {
    if (!snake) return 0;

    Position head = snake->body[0];
    return !is_valid_position(head.x, head.y, width, height);
}

// Check if snake eats food
int check_food_collision(Snake *snake, Position food) {
    if (!snake) return 0;
    return positions_equal(snake->body[0], food);
}

// Move snake body (shift all segments)
void move_snake_body(Snake *snake) {
    if (!snake || snake->length < 1) return;

    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i] = snake->body[i - 1];
    }
}

// Grow snake (add new segment)
void grow_snake(Snake *snake) {
    // === BUG: Comment out the bounds check to enable buffer overflow ===
    // if (!snake || snake->length >= MAX_SNAKE_LENGTH) return;
    // === Uncomment the line below to enable the bug ===
    if (!snake) return;  // Bug: removed MAX_SNAKE_LENGTH check!

    // DEBUG: Print when we exceed buffer bounds
    if (snake->length >= MAX_SNAKE_LENGTH) {
        fprintf(stderr, "WARNING: Snake length %d exceeds MAX_SNAKE_LENGTH %d!\n",
                snake->length, MAX_SNAKE_LENGTH);
    }

    Position tail = snake->body[snake->length - 1];
    snake->body[snake->length] = tail;
    snake->length++;
}

// ==================== Level 1 Functions ====================

// Initialize game state
GameState* init_game(int width, int height) {
    GameState *game = (GameState*)malloc(sizeof(GameState));
    if (!game) return NULL;

    game->width = width;
    game->height = height;
    game->score = 0;
    game->game_over = 0;

    // Initialize snake
    game->snake.length = 3;
    game->snake.direction = DIR_RIGHT;

    // Place snake in the middle
    int mid_x = width / 2;
    int mid_y = height / 2;
    game->snake.body[0].x = mid_x;
    game->snake.body[0].y = mid_y;
    game->snake.body[1].x = mid_x - 1;
    game->snake.body[1].y = mid_y;
    game->snake.body[2].x = mid_x - 2;
    game->snake.body[2].y = mid_y;

    // Place initial food
    game->food = generate_random_position(width, height, 42);

    return game;
}

// Update snake direction
void update_direction(Snake *snake, Direction new_dir) {
    if (!snake) return;

    // Prevent 180-degree turns
    if ((snake->direction == DIR_UP && new_dir == DIR_DOWN) ||
        (snake->direction == DIR_DOWN && new_dir == DIR_UP) ||
        (snake->direction == DIR_LEFT && new_dir == DIR_RIGHT) ||
        (snake->direction == DIR_RIGHT && new_dir == DIR_LEFT)) {
        return;
    }

    snake->direction = new_dir;
}

// Move snake head based on direction
void move_snake_head(Snake *snake) {
    if (!snake) return;

    Position new_head = snake->body[0];

    switch (snake->direction) {
        case DIR_UP:
            new_head.y--;
            break;
        case DIR_DOWN:
            new_head.y++;
            break;
        case DIR_LEFT:
            new_head.x--;
            break;
        case DIR_RIGHT:
            new_head.x++;
            break;
    }

    move_snake_body(snake);
    snake->body[0] = new_head;
}

// Handle food consumption
void handle_food(GameState *game) {
    if (!game) return;

    // === DEBUG: Make snake grow every move to trigger bug faster ===
    grow_snake(&game->snake);  // Always grow!
    game->score += 10;

    if (check_food_collision(&game->snake, game->food)) {
        // Generate new food
        unsigned int seed = game->score + game->snake.length;
        game->food = generate_random_position(game->width, game->height, seed);
    }
}

// Check all collisions
int check_collisions(GameState *game) {
    if (!game) return 0;

    // === DEBUG: Disable collision detection to let snake grow past MAX_SNAKE_LENGTH ===
    return 0;  // Always return no collision!

    if (check_wall_collision(&game->snake, game->width, game->height)) {
        return 1;
    }

    if (check_self_collision(&game->snake)) {
        return 1;
    }

    return 0;
}

// ==================== Entry Point ====================

// Main game update function
int update_game(GameState *game, Direction input_direction) {
    if (!game || game->game_over) {
        return -1;
    }

    // Update direction
    update_direction(&game->snake, input_direction);

    // Move snake
    move_snake_head(&game->snake);

    // Check collisions
    if (check_collisions(game)) {
        game->game_over = 1;
        return -2;
    }

    // Handle food
    handle_food(game);

    return 0;
}

// Process game commands
int process_game_command(const uint8_t *data, size_t size) {
    if (!data || size < 4) return -1;

    // Parse game dimensions from first 2 bytes
    int width = (data[0] % 20) + 10;   // 10-29
    int height = (data[1] % 20) + 10;  // 10-29

    // Initialize game
    GameState *game = init_game(width, height);
    if (!game) return -1;

    // Process commands from remaining bytes
    int moves = 0;
    for (size_t i = 2; i < size && !game->game_over; i++) {
        Direction dir = (Direction)(data[i] % 4);
        update_game(game, dir);
        moves++;
    }

    fprintf(stderr, "Game ended after %d moves, snake length: %d, game_over: %d\n",
            moves, game->snake.length, game->game_over);

    int final_score = game->score;
    int game_over = game->game_over;

    free(game);

    return game_over ? -2 : final_score;
}
