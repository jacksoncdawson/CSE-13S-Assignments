#!/bin/bash

PROGRAM=./calc

EXPECTED_OUTPUT="5.0000000000"

ACTUAL_OUTPUT=$($PROGRAM <<< "3 2 +")

if [ "$ACTUAL_OUTPUT" == "$EXPECTED_OUTPUT" ]; then
    echo "Test passed: '3 2 +' gets '$ACTUAL_OUTPUT'."
else
    echo "Test failed: Input of '3 2 +' got '$ACTUAL_OUTPUT'."
fi

