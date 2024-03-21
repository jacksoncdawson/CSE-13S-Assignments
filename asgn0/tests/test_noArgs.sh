# Creates validation file
echo "NOT ENOUGH INPUT" > notEnoughResponse.txt

# Runs the program with NO arguments
./calc > output.txt 

# Ensures exit code is NOT Zero
if [ $? -eq 0 ]; then
    echo "Invalid exit code:" $?
    rm output.txt
    rm notEnoughResponse.txt
    exit 1
fi

# Ensures correct error message is printed
diff output.txt notEnoughResponse.txt
if [ $? -ne 0 ]; then
    echo "program output does not match expected error response!"
    rm output.txt
    rm notEnoughResponse.txt
    exit 1
fi

# Prints a message on success
echo "'NOT ENOUGH INPUT' successfully logged: PASS"

# Cleans up files created
rm output.txt
rm notEnoughResponse.txt
exit 0
