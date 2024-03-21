#!/bin/bash

# Test is_lowercase_letter function
echo "Testing is_lowercase_letter..."
if ./test_helpers is_lowercase_letter a; then echo "Pass: 'a' is lowercase"; else echo "Fail: 'a' is lowercase"; fi
if ./test_helpers is_lowercase_letter A; then echo "Fail: 'A' is not lowercase"; else echo "Pass: 'A' is not lowercase"; fi

# Test validate_secret function
echo "Testing validate_secret..."
if ./test_helpers validate_secret "hello-world"; then echo "Pass: 'hello-world' is valid"; else echo "Fail: 'hello-world' is valid"; fi
if ./test_helpers validate_secret "Hello World!"; then echo "Fail: 'Hello World!' is not valid"; else echo "Pass: 'Hello World!' is not valid"; fi
if ./test_helpers validate_secret "$(printf 'a%.0s' {1..257})"; then echo "Fail: 257 chars is not valid"; else echo "Pass: 257 chars is not valid"; fi


