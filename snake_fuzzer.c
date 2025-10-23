// snake_fuzzer.c - Fuzzer for Snake Game

#include "snake_game.h"
#include <stdint.h>
#include <stddef.h>

// LibFuzzer entry point
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    // Process game commands
    process_game_command(data, size);
    return 0;
}
