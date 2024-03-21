# ideal behavior: returns zero exit, prints sum

# Creates validation file
echo 9 > nine.txt

# Runs the program with 2 positive integers
./calc 3 3 > output.txt 

# Ensures exit code is zero
if [ $? -ne 0 ]; then
    echo "Invalid exit code:" $?
    rm output.txt
    rm nine.txt
    exit 1
fi

# Ensures correct summation
diff output.txt nine.txt
if [ $? -eq 0 ]; then
    echo "calc multiplied the two integers!"
    rm output.txt
    rm nine.txt
    exit 1
fi

# Prints a message on success
echo "Inputs correctly summed: PASS"

# Cleans up files created
rm output.txt
rm nine.txt
exit 0
