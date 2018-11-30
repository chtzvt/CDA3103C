#!/usr/bin/env bash

echo -e "Available tests:\n\t[1] Short test\n\t[2] Intermediate test\n\t[3] Long test\n"
read -p 'Select testing level [default=2]: ' TESTLEVEL
TESTLEVEL=${TESTLEVEL:-2}

echo -e "\n=== BEGIN TESTING ===\n"

echo -e "\nCurrent date:      \t`date`\nBuilding from commit: \t`git log -1 --oneline`\nChosen test:     \t[$TESTLEVEL]"

echo -e "\nCurrent repo status: \n---\n`git status`\n---"

echo -e "\nRemoving any old test artifacts..."
rm -f ./tmp/*
rm -f ./spimtest

echo -e "\nCompiling..."
gcc -o ./spimtest ../project.c ../spimcore.c

echo -e "\nExecuting with test input..."
./spimtest ../input_file.asc <resources/test_input$TESTLEVEL.txt >tmp/test_output$TESTLEVEL.txt

echo -e "\nDiff results: \n---"
diff tmp/test_output$TESTLEVEL.txt resources/test_output$TESTLEVEL.txt

if [ $? -eq 0 ]; then
   echo -e "\n---\nPass! Congratulations :)"
else
   echo -e "\n---\nOh no! More work is needed..."
fi

echo -e "\n=== END TESTING ===\n"
