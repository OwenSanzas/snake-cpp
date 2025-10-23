# Snake Game - Expected Results

## Program Overview

Snake game implementation with **14 functions** organized in 3 levels.

## Call Graph

```
LLVMFuzzerTestOneInput (snake_fuzzer.c)
  └─> process_game_command (snake_game.c)
       └─> init_game (snake_game.c)
       │    └─> generate_random_position (snake_game.c)
       └─> update_game (snake_game.c)
            ├─> update_direction (snake_game.c)
            ├─> move_snake_head (snake_game.c)
            │    └─> move_snake_body (snake_game.c)
            ├─> check_collisions (snake_game.c)
            │    ├─> check_wall_collision (snake_game.c)
            │    │    └─> is_valid_position (snake_game.c)
            │    └─> check_self_collision (snake_game.c)
            │         └─> positions_equal (snake_game.c)
            └─> handle_food (snake_game.c)
                 ├─> check_food_collision (snake_game.c)
                 │    └─> positions_equal (snake_game.c)
                 ├─> grow_snake (snake_game.c)
                 └─> generate_random_position (snake_game.c)
```

## Expected Reachable Functions

From `LLVMFuzzerTestOneInput`, the following **13 functions** should be reachable:

### Level 0 (Entry Point)
1. `process_game_command` - Main game command processor

### Level 1 (Direct calls)
2. `init_game` - Initialize game state
3. `update_game` - Main game update loop

### Level 2 (Called by Level 1)
4. `generate_random_position` - Generate random food position (called by init_game and handle_food)
5. `update_direction` - Update snake direction (called by update_game)
6. `move_snake_head` - Move snake head (called by update_game)
7. `check_collisions` - Check all collisions (called by update_game)
8. `handle_food` - Handle food consumption (called by update_game)

### Level 3 (Called by Level 2)
9. `move_snake_body` - Shift snake body segments (called by move_snake_head)
10. `check_wall_collision` - Check wall collision (called by check_collisions)
11. `check_self_collision` - Check self collision (called by check_collisions)
12. `check_food_collision` - Check food collision (called by handle_food)
13. `grow_snake` - Grow snake by one segment (called by handle_food)

### Level 4 (Helper functions)
14. `is_valid_position` - Check if position is valid (called by check_wall_collision)
15. `positions_equal` - Compare two positions (called by check_self_collision and check_food_collision)

## Function Count

- **Total functions defined**: 15 (including LLVMFuzzerTestOneInput)
- **Functions reachable from fuzzer**: 13
- **Unreachable functions**: 0

## Expected CSV Output

```csv
Fuzzer,Fuzzer_File,Reachable_Function,Function_File,Line_Number
snake_fuzzer,snake_fuzzer.c,process_game_command,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,init_game,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,update_game,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,generate_random_position,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,update_direction,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,move_snake_head,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,check_collisions,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,handle_food,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,move_snake_body,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,check_wall_collision,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,check_self_collision,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,check_food_collision,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,grow_snake,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,is_valid_position,snake_game.c,<line>
snake_fuzzer,snake_fuzzer.c,positions_equal,snake_game.c,<line>
```

## Complexity Features

- **Multi-level call chains**: Up to 4 levels deep
- **Branching logic**: Multiple conditional paths
- **Data structures**: Structs with arrays (Snake, GameState, Position)
- **Loops**: For loops in collision checking
- **Enums**: Direction enumeration
- **Multiple call sites**: Some functions called from multiple locations

## Notes

- `positions_equal` is called from multiple functions
- `generate_random_position` is called from init_game and handle_food
- All functions are reachable through fuzzer input
- No dead code in this implementation
