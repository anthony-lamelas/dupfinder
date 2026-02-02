#pragma once

#include <filesystem>
#include <unordered_map>
#include <vector>
#include <cstdint>

std::unordered_map<uintmax_t, std::vector<std::filesystem::path>>
scan_directories(const std::vector<std::filesystem::path>& directories);