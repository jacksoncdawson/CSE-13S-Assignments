# ideal behavior: returns zero exit, prints sum

# Creates validation file
echo 0 > zero.txt

# Runs the program with 1 positive and 1 negative arguments
./calc -2 2 > output.txt 

# Ensures exit code is zero
if [ $? -ne 0 ]; then
    echo "Invalid exit code:" $?
    rm output.txt
    rm zero.txt
    exit 1
fi

# Ensures correct summation
diff output.txt zero.txt
if [ $? -ne 0 ]; then
    echo "calc summed the two integers incorrectly!"
    rm output.txt
    rm zero.txt
    exit 1
fi

# Prints a message on success
echo "Inputs correctly summed: PASS"

# Cleans up files created
rm output.txt
rm zero.txt
exit 0
