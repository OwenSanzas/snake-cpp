#!/usr/bin/env python3
# create_crash.py - Generate binary testcase to trigger buffer overflow

# Create a testcase that makes the snake eat 100+ foods
testcase = bytearray()

# First 2 bytes: game dimensions (small board)
testcase.append(10)  # width = 10
testcase.append(10)  # height = 10

# Next 200 bytes: all zeros (DIR_UP movements)
# This will make snake keep moving and potentially eating food
for i in range(200):
    testcase.append(0)  # DIR_UP

# Write to binary file
with open('crash_testcase.bin', 'wb') as f:
    f.write(testcase)

print(f"Created crash_testcase.bin ({len(testcase)} bytes)")
print("Run with: ./snake_fuzzer crash_testcase.bin")
