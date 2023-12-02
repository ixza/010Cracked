#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>

int main(int argc, char *argv[]) {
        if (argc == 2) {
        
    std::string fileIn = argv[1];
    std::filesystem::path path(fileIn);
    std::string directory = path.parent_path().string();
    std::string fileName = path.filename().string();
    std::string fileOut = directory+"\\010Editor Patched.exe";
    
    if (fileName != "010Editor.exe"){
        std::cerr << "File is not 010Editor.exe " << std::endl;
        return 1;
    }
    
    // Open the binary file in both input and output modes
    std::ifstream inputFile(fileIn, std::ios::binary);
    std::ofstream outputFile(fileOut, std::ios::binary);

    if (!inputFile.is_open() && !outputFile.is_open()) {
        std::cerr << "Error opening " << fileIn << "\n Make sure it isnt in a protected location like /Program Files/" << std::endl;
        return 1;
    }

    // Define the hex sequence to find and replace
    std::vector<unsigned char> searchPattern = {0x81, 0xFF, 0xDB, 0x00, 0x00, 0x00}; //00007FF646A05595 | 81FF DB000000            | cmp edi,DB    
    std::vector<unsigned char> noop = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90};

    // Read the input file into a vector
    inputFile.seekg(0, std::ios::end);
    std::streamsize fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    std::vector<unsigned char> fileContent(fileSize);
    if (inputFile.read(reinterpret_cast<char*>(fileContent.data()), fileSize)) {
        // Search for the pattern in the fileContent
        auto cmpBytes = std::search(fileContent.begin(), fileContent.end(),
                              searchPattern.begin(), searchPattern.end());

        if (cmpBytes != fileContent.end()) {
            std::copy(noop.begin(), noop.end(), cmpBytes); // Replace the pattern with the noop
            outputFile.write(reinterpret_cast<const char*>(fileContent.data()), fileSize);
            std::cout << fileOut << std::endl;
            std::cout << "Patched successfully" << std::endl;

        } else {
            std::cout << "Pattern not found in the file." << std::endl;
        }
    } else {
        std::cerr << "Error reading the input file!" << std::endl;
    }

    // Close the file streams
    inputFile.close();
    outputFile.close();

    return 0;
}else{
        std::cout << "Usage: " << argv[0] << " \"<fileIn>\"" << std::endl;
        return 1;
    }
}