#!/bin/bash

# Test case 1
echo "Test case 1: ls command"
echo "Expected output:"
/bin/ls
echo "Actual output:"
echo "/bin/ls" | ./hsh

# Test case 2
echo "Test case 2: echo command"
echo "Expected output:"
/bin/echo "Hello world"
echo "Actual output:"
echo "/bin/echo 'Hello world'" | ./hsh

# Test case 3
echo "Test case 3: pwd command"
echo "Expected output:"
/bin/pwd
echo "Actual output:"
echo "/bin/pwd" | ./hsh

# 4............
echo "expected"
echo " " | /bin/sh
echo "got"
echo " " | ./hsh

# 5..............
echo "expected"
echo "dfdd" | /bin/sh
echo "got"
echo "dfdd" | ./hsh
