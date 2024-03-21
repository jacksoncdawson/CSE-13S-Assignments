# ideal behavior: ?

# Creates validation file
echo "NOT ENOUGH INPUT" > notEnoughInput.txt

# Runs the program with 3 negative integers
./calc -2 -2 -2 > output.txt 

# Ensures exit code is zero
if [ $? -eq 0 ]; then
    echo "Invalid exit code:" $?
    rm output.txt
    rm notEnoughInput.txt
    exit 1
fi

# Ensures correct summation
diff output.txt notEnoughInput.txt
if [ $? -ne 0 ]; then
    echo "Program did not output 'NOT ENOUGH INPUT'"
    rm output.txt
    rm notEnoughInput.txt
    exit 1
fi

# Prints a message on success
echo "Program given '-2 -2 -2'"
echo "Program outputted:"; cat output.txt

# Cleans up files created
rm output.txt
rm notEnoughInput.txt
exit 0
