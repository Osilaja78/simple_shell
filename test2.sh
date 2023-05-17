#!/bin/bash

# Test script for multiple commands execution

# Commands to execute
commands=("ls" "echo Hello World" "pwd")

# Iterate over each command
for cmd in "${commands[@]}"; do
    echo "Executing command: $cmd"
    echo "$cmd" | ./hsh
    echo "=================================="
done
