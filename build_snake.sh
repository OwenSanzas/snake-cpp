#!/bin/bash

# Build script for snake game fuzzer

set -e

echo "Building snake game fuzzer with libFuzzer and AddressSanitizer..."

clang -g -O1 -fsanitize=fuzzer,address \
    -o snake_fuzzer \
    snake_fuzzer.c snake_game.c

echo "Build complete: ./snake_fuzzer"
echo ""
echo "Run with: ./snake_fuzzer"
