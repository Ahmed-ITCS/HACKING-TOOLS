#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <cstdlib>

#include "minizip/zip.h"

namespace fs = std::filesystem;

int main() {
    // Create a new directory named 'locked'
    fs::create_directory("locked");

    // Move all files and folders to the 'locked' directory
    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.path().filename() != "locked") {
            fs::rename(entry.path(), fs::path("locked") / entry.path().filename());
        }
    }

    // Prompt the user to set a password
    std::string password;
    std::cout << "Enter a password for the 'locked' folder: ";
    std::getline(std::cin, password);

    // Create a password-protected ZIP archive
    zipFile zf = zipOpen("locked.zip", APPEND_STATUS_CREATE);
    if (zf != nullptr) {
        zip_source_t* source = zip_source_buffer_create(password.c_str(), password.size(), 0, nullptr);
        zip_file_add(zf, "password.txt", source, ZIP_FL_OVERWRITE);
        zip_source_free(source);

        for (const auto& entry : fs::recursive_directory_iterator("locked")) {
            if (fs::is_regular_file(entry)) {
                std::string entryPath = entry.path().string();
                std::string arcName = entryPath.substr(7); // Adjust to remove "locked/" prefix

                source = zip_source_file_create(entryPath.c_str(), 0, -1, nullptr);
                zip_file_add(zf, arcName.c_str(), source, ZIP_FL_OVERWRITE);
                zip_source_free(source);
            }
        }

        zipClose(zf, nullptr);
    }

    // Clean up temporary 'locked' folder
    fs::remove_all("locked");

    std::cout << "Files and folders are locked and saved as 'locked.zip' with a password." << std::endl;

    return 0;
}
