#include <iostream>
#include <vector>
#include <filesystem>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Not enough arguments." << std::endl;
        return 1;
    }

    std::vector<std::filesystem::path> directories;

    for (int i = 1; i < argc; ++i) {
        directories.emplace_back(argv[i]);
    }

    // need to scan directories and check hashes
    // then need to format the output response

    return 0;
}