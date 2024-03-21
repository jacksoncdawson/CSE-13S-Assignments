# ideal behavior: returns zero exit, prints sum

# Creates validation file
echo -4 > negativeFour.txt

# Runs the program with 2 negative integers
./calc -2 -2 > output.txt 

# Ensures exit code is zero
if [ $? -ne 0 ]; then
    echo "Invalid exit code:" $?
    echo "program output:"; cat output.txt
    echo "expected output:"; cat negativeFour.txt
    rm output.txt
    rm negativeFour.txt
    exit 1
fi

# Ensures correct summation
diff output.txt negativeFour.txt
if [ $? -ne 0 ]; then
    echo "calc summed the two integers incorrectly!"
    rm output.txt
    rm negativeFour.txt
    exit 1
fi

# Prints a message on success
echo "Inputs correctly summed: PASS"

# Cleans up files created
rm output.txt
rm negativeFour.txt
exit 0
