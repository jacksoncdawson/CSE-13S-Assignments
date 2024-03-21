#!/bin/bash

# Path to XD executable
PROGRAM=./xd

echo -e '00000000: 3031 320a                                012.' > expected_output.txt

# Create a test input file
echo "012" > testInput.txt

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

