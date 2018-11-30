#!/usr/bin/env bash

echo -e "\n=== BEGIN TESTING ===\n"

echo -e "Current date:      \t`date`\nBuilding from commit: \t`git log -1 --oneline`\n"
echo -e "\nCurrent repo status: \n---\n`git status`\n---"

echo -e "\nRemoving any old test artifacts..."
rm ./tmp/*
rm -f ./spimtest

echo -e "\nCompiling..."
gcc -o ./spimtest ../project.c ../spimcore.c

echo -e "\nExecuting with test input..."
./spimtest ../input_file.asc <resources/test_input.txt >tmp/test_output

echo -e "\nDiff results: \n---"
diff tmp/test_output resources/test_output.txt

if [ $? -eq 0 ]; then
   echo -e "\n---\nPass! Congratulations :)"
else
   echo -e "\n---\nOh no! More work is needed..."
fi

echo -e "\n=== END TESTING ===\n"
