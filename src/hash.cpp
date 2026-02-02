#include "../include/hash.hpp"
#include "xxhash.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cstdint>

// Hash function copied from xxhash GitHub
uint64_t hash_file(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    XXH64_state_t* state = XXH64_createState();
    XXH64_reset(state, 0);  

    constexpr size_t BUF_SIZE = 64 * 1024; 
    std::vector<char> buffer(BUF_SIZE);

    while (file) {
        file.read(buffer.data(), buffer.size());
        std::streamsize bytes_read = file.gcount();
        if (bytes_read > 0) {
            XXH64_update(state, buffer.data(), bytes_read);
        }
    }

    uint64_t hash = XXH64_digest(state);
    XXH64_freeState(state);

    return hash;
}


std::unordered_map<
    uintmax_t,
    std::unordered_map<uint64_t, std::vector<std::filesystem::path>>
>
check_hashes(const std::unordered_map<uintmax_t, std::vector<std::filesystem::path>>& size_groups) {
    std::unordered_map<uintmax_t, std::unordered_map<uint64_t, std::vector<std::filesystem::path>>> duplicates;
    
    for (const auto& [size, files] : size_groups) {
        if (files.size() < 2) {
            continue;
        }

        std::unordered_map<uint64_t, std::vector<std::filesystem::path>> hash_groups;

        for (const auto& file : files) {
            try {
                uint64_t hash = hash_file(file);
                hash_groups[hash].emplace_back(file);
            }
            catch (const std::exception&){
                continue;
            }
        }

        for (auto& [hash, paths] : hash_groups) {
            if (paths.size() > 1) {
                duplicates[size][hash] = std::move(paths);
            }
        }
    }
    return duplicates;
}
