#!/bin/bash

# Run make to compile the program
make m

# Give execute permission to the mandatory_tests binary
chmod +x mandatory_tests

# Run the mandatory_tests and save the output to a file
./mandatory_tests > outputs/gnl_m_output.txt

# Compare the output with the expected output (adjust the path to your expected output file if necessary)
if diff outputs/gnl_m_output.txt outputs/mandatory.txt > /dev/null; then
    # If diff finds no differences, print success message in green
    echo -e "\033[0;32mTests passed\033[0m"
else
    # If there are differences, print failure message in red (optional)
    echo -e "\033[0;31mTests failed\033[0m"
fi

make fclean
rm -rf outputs/gnl_m_output.txt
