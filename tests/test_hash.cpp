#include <gtest/gtest.h>
#include "../include/hash.hpp"
#include <fstream>
#include <filesystem>

TEST(HashTest, IdenticalFilesHaveSameHash) {
    std::filesystem::path test_file = std::filesystem::temp_directory_path() / "test_file.txt";
    
    std::ofstream file(test_file);
    file << "Hello, World!";
    file.close();
    
    uint64_t hash1 = hash_file(test_file);
    uint64_t hash2 = hash_file(test_file);
    
    EXPECT_EQ(hash1, hash2);
    
    std::filesystem::remove(test_file);
}

TEST(HashTest, DifferentContentDifferentHash) {
    std::filesystem::path file1 = std::filesystem::temp_directory_path() / "file1.txt";
    std::filesystem::path file2 = std::filesystem::temp_directory_path() / "file2.txt";
    
    std::ofstream f1(file1);
    f1 << "Content A";
    f1.close();
    
    std::ofstream f2(file2);
    f2 << "Content B";
    f2.close();
    
    uint64_t hash1 = hash_file(file1);
    uint64_t hash2 = hash_file(file2);
    
    EXPECT_NE(hash1, hash2);
    
    std::filesystem::remove(file1);
    std::filesystem::remove(file2);
}

TEST(HashTest, NonExistentFileThrows) {
    std::filesystem::path fake_file = "this_does_not_exist.txt";
    
    EXPECT_THROW(hash_file(fake_file), std::runtime_error);
}

TEST(HashTest, EmptyFileHash) {
    std::filesystem::path empty_file = std::filesystem::temp_directory_path() / "empty.txt";
    
    std::ofstream f(empty_file);
    f.close();
    
    EXPECT_NO_THROW(hash_file(empty_file));
    
    std::filesystem::remove(empty_file);
}

TEST(HashTest, CheckHashesNoDuplicates) {
    std::unordered_map<uintmax_t, std::vector<std::filesystem::path>> size_groups;
    
    size_groups[100].push_back("file1.txt");
    size_groups[200].push_back("file2.txt");
    
    auto result = check_hashes(size_groups);
    
    EXPECT_TRUE(result.empty());
}
