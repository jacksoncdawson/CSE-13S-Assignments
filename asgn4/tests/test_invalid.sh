#!/bin/bash

PROGRAM=./calc

EXPECTED_ERR="> error: unknown operation 'e'
> "

ACTUAL_ERR=$($PROGRAM <<< "e" 2>&1 > /dev/null)

if [ "$ACTUAL_ERR" == "$EXPECTED_ERR" ]; then
    echo "Test passed: 'e' gets '$ACTUAL_ERR'."
    exit 0
else
    echo "Test failed: Input of 'e' got '$ACTUAL_ERR'."
    exit 1
fi

