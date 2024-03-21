# ideal behavior: returns non-zero int, echoes "BAD INPUT"

# Creates validation file
echo "BAD INPUT" > badInput.txt

# Runs the program with 1 negative integer and 1 non-integer
./calc -2 a > output.txt 

# Ensures exit code is NOT Zero
if [ $? -eq 0 ]; then
    echo "Invalid exit code:" $?
    rm output.txt
    rm badInput.txt
    exit 1
fi

# Ensures correct message is printed in output.txt
diff output.txt badInput.txt
if [ $? -ne 0 ]; then
    echo "program output does not match expected error reponse!"
    rm output.txt
    rm badInput.txt
    exit 1
fi

# Prints a message on success
echo "'BAD INPUT' successfully logged: PASS"

# Cleans up files created
rm output.txt
rm badInput.txt
exit 0
