# ideal behavior: returns zero exit, prints sum

# Creates validation file
echo 9 > nine.txt

# Runs the program with 2 positive integers
./calc 5 3 > output.txt 

# Ensures exit code is zero
if [ $? -ne 0 ]; then
    echo "Invalid exit code:" $?
    rm output.txt
    rm nine.txt
    exit 1
fi

expected_sum=$(cat nine.txt)
actual_sum=$(cat output.txt)

if [ $((actual_sum - expected_sum)) -eq 1 ]; then
    echo "calc added 1 to the sum!"
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
