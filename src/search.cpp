#include "../include/search.hpp"


std::unordered_map<
    uintmax_t, 
    std::vector<std::filesystem::path>
    > 
scan_directories(const std::vector<std::filesystem::path>& directories) {
    std::unordered_map<uintmax_t, std::vector<std::filesystem::path>> size_groups; 

    for (const std::filesystem::path& path: directories){
        
        // Check if valid 
        if (!std::filesystem::exists(path)) {
            continue;
        }

        for (auto& entry :
        std::filesystem::recursive_directory_iterator(
            path,
            std::filesystem::directory_options::skip_permission_denied
        )) {

            // Skip if not regular file
            if (!std::filesystem::is_regular_file(entry)) {
                continue;
            }

            try {
                uintmax_t size_bytes = entry.file_size();
                size_groups[size_bytes].push_back(entry.path());

            }
            catch (const std::filesystem::filesystem_error&) {
                continue;
            }
        }
    }
        
    return size_groups;
    }