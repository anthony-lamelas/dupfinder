#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

using Hash = std::string;

std::unordered_map<
    uintmax_t, std::unordered_map<uint64_t, std::vector<std::filesystem::path>>>
check_hashes(
    const std::unordered_map<uintmax_t, std::vector<std::filesystem::path>>
        &size_groups);

uint64_t hash_file(const std::filesystem::path &path);