#!/bin/bash

# Create a new directory named 'locked'
mkdir locked

# Move all files and folders to the 'locked' directory
mv * locked/

# Prompt the user to set a passwor
$password = "haha"
# read -s -p "Enter a password for the 'locked' folder: " password
# echo

# Zip the 'locked' folder with password encryption
zip -er locked.zip locked -P "$password"

# Clean up temporary 'locked' folder
rm -r locked

echo "Files and folders are locked and saved as 'locked.zip' with a password."
