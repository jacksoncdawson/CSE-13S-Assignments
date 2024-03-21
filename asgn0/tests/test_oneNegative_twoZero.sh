# ideal behavior: returns zero exit, prints sum

# Creates validation file
echo -2 > two.txt

# Runs the program with 2 positive integers
./calc -2 0 > output.txt 

# Ensures exit code is zero
if [ $? -ne 0 ]; then
    echo "Invalid exit code:" $?
    rm output.txt
    rm two.txt
    exit 1
fi

# Ensures correct summation
diff output.txt two.txt
if [ $? -ne 0 ]; then
    echo "calc summed the two integers incorrectly!"
    rm output.txt
    rm two.txt
    exit 1
fi

# Prints a message on success
echo "Inputs correctly summed: PASS"

# Cleans up files created
rm output.txt
rm two.txt
exit 0
