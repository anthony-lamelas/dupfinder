#include <gtest/gtest.h>
#include "../include/search.hpp"
#include <fstream>

TEST(SearchTest, EmptyDirectory) {
    std::filesystem::path test_dir = std::filesystem::temp_directory_path() / "empty_dir";
    std::filesystem::create_directory(test_dir);
    
    std::vector<std::filesystem::path> dirs = {test_dir};
    auto result = scan_directories(dirs);
    
    EXPECT_TRUE(result.empty());
    
    std::filesystem::remove(test_dir);
}

TEST(SearchTest, SingleFile) {
    std::filesystem::path test_dir = std::filesystem::temp_directory_path() / "single_file_dir";
    std::filesystem::create_directory(test_dir);
    
    std::ofstream file(test_dir / "test.txt");
    file << "content";
    file.close();
    
    std::vector<std::filesystem::path> dirs = {test_dir};
    auto result = scan_directories(dirs);
    
    EXPECT_FALSE(result.empty());
    
    std::filesystem::remove_all(test_dir);
}

TEST(SearchTest, FilesGroupedBySize) {
    std::filesystem::path test_dir = std::filesystem::temp_directory_path() / "size_group_dir";
    std::filesystem::create_directory(test_dir);
    
    std::ofstream f1(test_dir / "file1.txt");
    f1 << "abc";
    f1.close();
    
    std::ofstream f2(test_dir / "file2.txt");
    f2 << "xyz";
    f2.close();
    
    std::ofstream f3(test_dir / "file3.txt");
    f3 << "different";
    f3.close();
    
    std::vector<std::filesystem::path> dirs = {test_dir};
    auto result = scan_directories(dirs);
    
    EXPECT_EQ(result.size(), 2);
    
    std::filesystem::remove_all(test_dir);
}

TEST(SearchTest, NonExistentDirectory) {
    std::vector<std::filesystem::path> dirs = {"fake/directory/path"};
    auto result = scan_directories(dirs);
    
    EXPECT_TRUE(result.empty());
}
