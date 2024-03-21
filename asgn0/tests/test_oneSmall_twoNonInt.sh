# ideal behavior: returns non-zero exit, prints "TOO BIG"

# Creates validation file
echo "BAD INPUT" > badInput.txt

# Runs the program with 1 small integer and 1 non-integer
./calc -513 a > output.txt 

# Ensures exit code is not zero
if [ $? -eq 0 ]; then
    echo "Invalid exit code:" $?
    rm output.txt
    rm badInput.txt
    exit 1
fi

# Ensures correct error message
diff output.txt badInput.txt
if [ $? -ne 0 ]; then
    echo "Program did not print 'BAD INPUT' correctly!"
    rm output.txt
    rm badInput.txt
    exit 1
fi

# Prints a message on success
echo "Error 'BAD INPUT' successfully printed!"

# Cleans up files created
rm output.txt
rm badInput.txt
exit 0
