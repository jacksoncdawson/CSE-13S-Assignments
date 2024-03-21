# ideal behavior: returns non-zero exit, prints "TOO BIG"

# Creates validation file
echo "NOT ENOUGH INPUT" > notEnoughInput.txt

# Runs the program with 1 small integer
./calc -513 > output.txt 

# Ensures exit code is not zero
if [ $? -eq 0 ]; then
    echo "Invalid exit code:" $?
    rm output.txt
    rm notEnoughInput.txt
    exit 1
fi

# Ensures correct error message
diff output.txt notEnoughInput.txt
if [ $? -ne 0 ]; then
    echo "Program did not print 'NOT ENOUGH INPUT' correctly!"
    rm output.txt
    rm notEnoughInput.txt
    exit 1
fi

# Prints a message on success
echo "Error 'NOT ENOUGH INPUT' successfully printed!"

# Cleans up files created
rm output.txt
rm notEnoughInput.txt
exit 0
