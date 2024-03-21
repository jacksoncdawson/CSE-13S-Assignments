#!/bin/bash

TESTS_DIR="./tests"

make format
make

cd "$TESTS_DIR"

for test_script in *; do
    if [ -x "$test_script" ]; then  # Check if the file is executable
        echo "Running $test_script..."
        ./"$test_script"          
        echo "Finished running $test_script"
        echo "-----------------------------------"
    else
        echo "$test_script is not an executable file."
    fi
done

cd -

make clean

