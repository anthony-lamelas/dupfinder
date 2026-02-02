#pragma once

#include <vector>
#include <unordered_map>
#include <filesystem>
#include <string>
#include <cstdint>

using Hash = std::string;

std::unordered_map<
    uintmax_t,
    std::unordered_map<Hash, std::vector<std::filesystem::path>>
>
check_hashes(const std::unordered_map<uintmax_t, std::vector<std::filesystem::path>>& size_groups);