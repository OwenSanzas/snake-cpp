// snake_game.h - Snake Game Header

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <stdint.h>
#include <stddef.h>

#define MAX_SNAKE_LENGTH 100

// Direction enumeration
typedef enum {
    DIR_UP = 0,
    DIR_DOWN = 1,
    DIR_LEFT = 2,
    DIR_RIGHT = 3
} Direction;

// Position structure
typedef struct {
    int x;
    int y;
} Position;

// Snake structure
typedef struct {
    Position body[MAX_SNAKE_LENGTH];
    int length;
    Direction direction;
} Snake;

// Game state structure
typedef struct {
    Snake snake;
    Position food;
    int width;
    int height;
    int score;
    int game_over;
} GameState;

// Entry point
int process_game_command(const uint8_t *data, size_t size);

// Level 1 functions
GameState* init_game(int width, int height);
void update_direction(Snake *snake, Direction new_dir);
void move_snake_head(Snake *snake);
void handle_food(GameState *game);
int check_collisions(GameState *game);
int update_game(GameState *game, Direction input_direction);

// Level 2 functions
int check_self_collision(Snake *snake);
int check_wall_collision(Snake *snake, int width, int height);
int check_food_collision(Snake *snake, Position food);
void move_snake_body(Snake *snake);
void grow_snake(Snake *snake);

// Level 3 functions
int is_valid_position(int x, int y, int width, int height);
int positions_equal(Position p1, Position p2);
Position generate_random_position(int width, int height, unsigned int seed);

#endif // SNAKE_GAME_H
