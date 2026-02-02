#pragma once

#include <cstdint>
#include <filesystem>
#include <unordered_map>
#include <vector>

std::unordered_map<uintmax_t, std::vector<std::filesystem::path>>
scan_directories(const std::vector<std::filesystem::path> &directories);