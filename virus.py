import os
import shutil
import zipfile

# Create a new directory named 'locked'
os.mkdir("locked")

# Move all files and folders to the 'locked' directory
for item in os.listdir("."):
    if item != "locked":
        shutil.move(item, os.path.join("locked", item))

# Prompt the user to set a password
password = input("Enter a password for the 'locked' folder: ")

# Create a password-protected ZIP archive
with zipfile.ZipFile("locked.zip", "w", zipfile.ZIP_DEFLATED) as zipf:
    zipf.setpassword(password.encode())
    for root, _, files in os.walk("locked"):
        for file in files:
            file_path = os.path.join(root, file)
            arcname = os.path.relpath(file_path, "locked")
            zipf.write(file_path, arcname=arcname)

# Clean up temporary 'locked' folder
shutil.rmtree("locked")

print("Files and folders are locked and saved as 'locked.zip' with a password.")
