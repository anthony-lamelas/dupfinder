#include <filesystem>
#include <iostream>
#include <vector>

#include "../include/hash.hpp"
#include "../include/search.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Not enough arguments." << std::endl;
    return 1;
  }

  std::vector<std::filesystem::path> directories;

  for (int i = 1; i < argc; ++i) {
    directories.emplace_back(argv[i]);
  }

  auto size_groups = scan_directories(directories);
  auto duplicates = check_hashes(size_groups);

  for (const auto &[size, hash_map] : duplicates) {
    for (const auto &[hash, files] : hash_map) {
      std::cout << "New Set of Duplicates of size " << size << " MB"
                << std::endl;
      for (const auto &path : files) {
        std::cout << path << std::endl;
      }
    }
  }

  return 0;
}