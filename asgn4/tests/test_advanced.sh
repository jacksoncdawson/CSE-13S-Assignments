#!/bin/bash

PROGRAM=./calc

EXPECTED_OUTPUT="-0.9055783620 -1.3636150151"

ACTUAL_OUTPUT=$($PROGRAM <<< "24 s 144 9 + t")

if [ "$ACTUAL_OUTPUT" == "$EXPECTED_OUTPUT" ]; then
    echo "Test passed: '24 s 144 9 + t' gets '$ACTUAL_OUTPUT'."
    exit 0
else
    echo "Test failed: Input of '24 s 144 9 + t' got '$ACTUAL_OUTPUT'."
    exit 1
fi

