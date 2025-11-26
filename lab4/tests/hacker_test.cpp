#include "gtest/gtest.h"
#include "../hacker.hpp"
#include "../md5.hpp"
#include "../sha256.hpp"
#include <cstring>

// Helper to compute MD5 hash
void compute_md5_hash(const char* password, word32* hash) {
    MD5 md5;
    word32 data[16] = {0};
    int len = strlen(password);
    
    memcpy(data, password, len);
    unsigned char* byte_data = (unsigned char*)data;
    byte_data[len] = 0x80;
    data[14] = len * 8;
    
    md5.InitState(hash);
    md5.Transform(hash, data);
}

// Helper to compute SHA256 hash
std::array<uint8_t, 32> compute_sha256_hash(const char* password) {
    SHA256 sha;
    word32 hash[8];
    word32 data[16] = {0};
    int len = strlen(password);
    
    memcpy(data, password, len);
    unsigned char* byte_data = (unsigned char*)data;
    byte_data[len] = 0x80;
    data[14] = len * 8;
    
    sha.InitState(hash);
    sha.Transform(hash, data);
    
    std::array<uint8_t, 32> result;
    std::memcpy(result.data(), hash, 32);
    return result;
}

class HackerMD5Test : public ::testing::Test {
protected:
    Hacker<MD5> hacker;
    char result[16];
    
    void SetUp() override {
        memset(result, 0, sizeof(result));
    }
};

class HackerSHA256Test : public ::testing::Test {
protected:
    Hacker<SHA256> hacker;
    char result[16];
    
    void SetUp() override {
        memset(result, 0, sizeof(result));
    }
};

// ============= MD5 Tests =============

TEST_F(HackerMD5Test, CrackFourCharPassword) {
    word32 target_hash[4];
    compute_md5_hash("pass", target_hash);
    
    bool success = hacker.hack(target_hash, result, 4, 4);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "pass");
}

TEST_F(HackerMD5Test, CrackFiveCharPassword) {
    word32 target_hash[4];
    compute_md5_hash("test2", target_hash);
    
    bool success = hacker.hack(target_hash, result, 5, 5);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "test2");
}

TEST_F(HackerMD5Test, CrackNumericPassword) {
    word32 target_hash[4];
    compute_md5_hash("1234", target_hash);
    
    bool success = hacker.hack(target_hash, result, 4, 4);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "1234");
}

TEST_F(HackerMD5Test, CrackMixedPassword) {
    word32 target_hash[4];
    compute_md5_hash("abc3", target_hash);
    
    bool success = hacker.hack(target_hash, result, 4, 4);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "abc3");
}

TEST_F(HackerMD5Test, CrackWithRange) {
    word32 target_hash[4];
    compute_md5_hash("key9", target_hash);
    
    // Search from 3 to 5 chars, should find 4-char password
    bool success = hacker.hack(target_hash, result, 3, 5);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "key9");
}

TEST_F(HackerMD5Test, FailToFindLongPassword) {
    word32 target_hash[4];
    compute_md5_hash("toolong", target_hash);
    
    // Only search up to 5 chars
    bool success = hacker.hack(target_hash, result, 4, 5);
    
    EXPECT_FALSE(success);
}

TEST_F(HackerMD5Test, FindFirstInAlphabet) {
    word32 target_hash[4];
    compute_md5_hash("aaaa", target_hash);
    
    bool success = hacker.hack(target_hash, result, 4, 4);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "aaaa");
}

TEST_F(HackerMD5Test, FindLastInAlphabet) {
    word32 target_hash[4];
    compute_md5_hash("9999", target_hash);
    
    bool success = hacker.hack(target_hash, result, 4, 4);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "9999");
}

TEST_F(HackerMD5Test, CrackShortestPassword) {
    word32 target_hash[4];
    compute_md5_hash("a", target_hash);
    
    bool success = hacker.hack(target_hash, result, 1, 3);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "a");
}

TEST_F(HackerMD5Test, MultipleCracks) {
    // Test that hacker can be reused
    word32 hash1[4], hash2[4];
    char result1[16] = {0}, result2[16] = {0};
    
    compute_md5_hash("foo1", hash1);
    compute_md5_hash("bar2", hash2);
    
    EXPECT_TRUE(hacker.hack(hash1, result1, 4, 4));
    EXPECT_STREQ(result1, "foo1");
    
    EXPECT_TRUE(hacker.hack(hash2, result2, 4, 4));
    EXPECT_STREQ(result2, "bar2");
}

// ============= SHA256 Tests =============

TEST_F(HackerSHA256Test, CrackFourCharPassword) {
    std::array<uint8_t, 32> target_hash = compute_sha256_hash("pass");
    
    bool success = hacker.hack(target_hash, result, 4, 4);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "pass");
}

TEST_F(HackerSHA256Test, CrackFiveCharPassword) {
    std::array<uint8_t, 32> target_hash = compute_sha256_hash("test2");
    
    bool success = hacker.hack(target_hash, result, 5, 5);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "test2");
}

TEST_F(HackerSHA256Test, CrackNumericPassword) {
    std::array<uint8_t, 32> target_hash = compute_sha256_hash("5678");
    
    bool success = hacker.hack(target_hash, result, 4, 4);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "5678");
}

TEST_F(HackerSHA256Test, CrackMixedPassword) {
    std::array<uint8_t, 32> target_hash = compute_sha256_hash("xyz9");
    
    bool success = hacker.hack(target_hash, result, 4, 4);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "xyz9");
}

TEST_F(HackerSHA256Test, CrackWithRange) {
    std::array<uint8_t, 32> target_hash = compute_sha256_hash("code");
    
    // Search from 3 to 5 chars
    bool success = hacker.hack(target_hash, result, 3, 5);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "code");
}

TEST_F(HackerSHA256Test, FailToFindLongPassword) {
    std::array<uint8_t, 32> target_hash = compute_sha256_hash("toolong");
    
    // Only search up to 5 chars
    bool success = hacker.hack(target_hash, result, 4, 5);
    
    EXPECT_FALSE(success);
}

TEST_F(HackerSHA256Test, FindShortPassword) {
    std::array<uint8_t, 32> target_hash = compute_sha256_hash("ab");
    
    bool success = hacker.hack(target_hash, result, 2, 4);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "ab");
}

TEST_F(HackerSHA256Test, FindAllLetters) {
    std::array<uint8_t, 32> target_hash = compute_sha256_hash("abcd");
    
    bool success = hacker.hack(target_hash, result, 4, 4);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "abcd");
}

TEST_F(HackerSHA256Test, FindAllNumbers) {
    std::array<uint8_t, 32> target_hash = compute_sha256_hash("0123");
    
    bool success = hacker.hack(target_hash, result, 4, 4);
    
    EXPECT_TRUE(success);
    EXPECT_STREQ(result, "0123");
}

TEST_F(HackerSHA256Test, MultipleCracks) {
    // Test that hacker can be reused
    std::array<uint8_t, 32> hash1 = compute_sha256_hash("key4");
    std::array<uint8_t, 32> hash2 = compute_sha256_hash("val5");
    char result1[16] = {0}, result2[16] = {0};
    
    EXPECT_TRUE(hacker.hack(hash1, result1, 4, 4));
    EXPECT_STREQ(result1, "key4");
    
    EXPECT_TRUE(hacker.hack(hash2, result2, 4, 4));
    EXPECT_STREQ(result2, "val5");
}

// ============= Cross-Algorithm Tests =============

TEST(HackerCrossTest, MD5AndSHA256SamePassword) {
    const char* password = "test";
    
    // MD5 crack
    word32 md5_hash[4];
    compute_md5_hash(password, md5_hash);
    Hacker<MD5> md5_hacker;
    char md5_result[16] = {0};
    
    // SHA256 crack
    std::array<uint8_t, 32> sha256_hash = compute_sha256_hash(password);
    Hacker<SHA256> sha256_hacker;
    char sha256_result[16] = {0};
    
    EXPECT_TRUE(md5_hacker.hack(md5_hash, md5_result, 4, 4));
    EXPECT_TRUE(sha256_hacker.hack(sha256_hash, sha256_result, 4, 4));
    
    EXPECT_STREQ(md5_result, password);
    EXPECT_STREQ(sha256_result, password);
}

TEST(HackerCrossTest, BothFailOnLongPassword) {
    const char* password = "verylongpassword";
    
    // MD5 crack
    word32 md5_hash[4];
    compute_md5_hash(password, md5_hash);
    Hacker<MD5> md5_hacker;
    char md5_result[16] = {0};
    
    // SHA256 crack
    std::array<uint8_t, 32> sha256_hash = compute_sha256_hash(password);
    Hacker<SHA256> sha256_hacker;
    char sha256_result[16] = {0};
    
    EXPECT_FALSE(md5_hacker.hack(md5_hash, md5_result, 4, 5));
    EXPECT_FALSE(sha256_hacker.hack(sha256_hash, sha256_result, 4, 5));
}