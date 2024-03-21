#!/bin/bash

# Path to XD executable
PROGRAM=./xd

echo -e '00000000: 3031 3233 3435 3637 3839 6162 6364 6566  0123456789abcdef\n00000010: 0a                                       .' > expected_output.txt

# Create a test input file
echo "0123456789abcdef" > testInput.txt

$PROGRAM testInput.txt > actual_output.txt

diff expected_output.txt actual_output.txt

if [ $? -eq 0 ]; then
    rm ./testInput.txt 
    rm ./actual_output.txt
    rm ./expected_output.txt
    exit 0
fi

rm ./testInput.txt
rm ./actual_output.txt
rm ./expected_output.txt
exit 1

