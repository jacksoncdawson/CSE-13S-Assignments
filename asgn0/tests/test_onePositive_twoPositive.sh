# ideal behavior: returns zero exit, prints sum

# Creates validation file
echo 4 > four.txt

# Runs the program with 2 positive integers
./calc 2 2 > output.txt 

# Ensures exit code is zero
if [ $? -ne 0 ]; then
    echo "Invalid exit code:" $?
    cat output.txt
    rm output.txt
    rm four.txt
    exit 1
fi

# Ensures correct summation
diff output.txt four.txt
if [ $? -ne 0 ]; then
    echo "calc summed the two integers incorrectly!"
    rm output.txt
    rm four.txt
    exit 1
fi

# Prints a message on success
echo "Inputs correctly summed: PASS"

# Cleans up files created
rm output.txt
rm four.txt
exit 0
