#!/usr/bin/env python3
# create_big_crash.py - Generate larger testcase

testcase = bytearray()

# Game dimensions
testcase.append(10)
testcase.append(10)

# 500 moves - should definitely overflow MAX_SNAKE_LENGTH (100)
for i in range(500):
    testcase.append(i % 4)  # Cycle through all directions

with open('big_crash.bin', 'wb') as f:
    f.write(testcase)

print(f"Created big_crash.bin ({len(testcase)} bytes)")
print("This should cause 500 grow operations")
print("Run with: ./snake_fuzzer big_crash.bin")
