# ideal behavior: returns zero exit, prints sum

# Creates validation file
echo 2 > two.txt

# Runs the program with 2 positive integers
./calc 4 2 > output.txt 

# Ensures exit code is zero
if [ $? -ne 0 ]; then
    echo "Invalid exit code:" $?
    rm output.txt
    rm two.txt
    exit 1
fi

# Ensures correct summation
diff output.txt two.txt
if [ $? -eq 0 ]; then
    echo "calc divided the two integers!"
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
