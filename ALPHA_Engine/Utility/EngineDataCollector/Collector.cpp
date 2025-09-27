#include <iostream>
#include <fstream>
#include <sstream>

#include "Parser.h"

int main(int argc, char* argv[]) {
    std::filesystem::path outputFile;
    std::vector<std::filesystem::path> dirs;

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " output.txt dir1 [dir2 ...]\n";
        return 1;
    }
    
    outputFile = argv[1];
    for (int i = 2; i < argc; ++i) {
        dirs.push_back(argv[i]);
    }
    

    auto headers = Parser::FindHeaderFiles(dirs);
    std::cout << "Found " << headers.size() << " header files total." << std::endl;

    std::unordered_set<std::string> allClasses;
    std::unordered_set<std::string> currentClasses = { "Component" }; // start with Component

    int iteration = 1;
    while (!currentClasses.empty()) {
        std::cout << "\n=== Iteration " << iteration << " ===" << std::endl;
        auto newClasses = Parser::ParseHeaders(headers, currentClasses);

        // Remove already found classes
        for (auto& cls : allClasses) {
            newClasses.erase(cls);
        }

        std::cout << "Found " << newClasses.size() << " new classes in this iteration:" << std::endl;
        for (const auto& cls : newClasses) {
            std::cout << "  " << cls << std::endl;
        }

        if (newClasses.empty()) break;

        allClasses.insert(newClasses.begin(), newClasses.end());
        currentClasses = std::move(newClasses);
        iteration++;
    }

    // Write results to file
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cerr << "Failed to open output file: " << outputFile << std::endl;
        return 1;
    }

    for (auto& cls : allClasses) {
        out << cls << "\n";
    }

    std::cout << "\n=== FINAL RESULTS ===" << std::endl;
    std::cout << "Found " << allClasses.size() << " classes inheriting from Component:" << std::endl;
    for (const auto& cls : allClasses) {
        std::cout << "  " << cls << std::endl;
    }
    std::cout << "Saved to " << outputFile << std::endl;

    return 0;
}