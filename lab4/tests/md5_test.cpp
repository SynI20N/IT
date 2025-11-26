#include "gtest/gtest.h"
#include "../md5.hpp"
#include <cstring>
#include <iomanip>
#include <sstream>

// Helper to convert hash to hex string
std::string hash_to_hex(const word32* hash, int word_count) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < word_count; i++) {
        ss << std::setw(8) << hash[i];
    }
    return ss.str();
}

// Helper to compute MD5 hash
void compute_md5(const char* input, word32* output) {
    MD5 md5;
    word32 data[16] = {0};
    int len = strlen(input);
    
    memcpy(data, input, len);
    unsigned char* byte_data = (unsigned char*)data;
    byte_data[len] = 0x80;
    data[14] = len * 8;
    
    md5.InitState(output);
    md5.Transform(output, data);
}

class MD5Test : public ::testing::Test {
protected:
    MD5 md5;
    word32 hash[4];
};

TEST_F(MD5Test, InitStateTest) {
    md5.InitState(hash);
    
    EXPECT_EQ(hash[0], 0x67452301L);
    EXPECT_EQ(hash[1], 0xefcdab89L);
    EXPECT_EQ(hash[2], 0x98badcfeL);
    EXPECT_EQ(hash[3], 0x10325476L);
}

TEST_F(MD5Test, EmptyString) {
    compute_md5("", hash);
    std::string result = hash_to_hex(hash, 4);
    EXPECT_EQ(result, "d98c1dd404b2008f980980e97e42f8ec");
}

TEST_F(MD5Test, SingleCharacter) {
    compute_md5("a", hash);
    std::string result = hash_to_hex(hash, 4);
    EXPECT_EQ(result, "b975c10ca8b6f1c0e299c33161267769");
}

TEST_F(MD5Test, ShortPassword) {
    compute_md5("pass", hash);
    std::string result = hash_to_hex(hash, 4);
    EXPECT_EQ(result, "1cc91d1ac6257390f0dd719272bc44c9");
}

TEST_F(MD5Test, AlphanumericPassword) {
    compute_md5("abc123", hash);
    std::string result = hash_to_hex(hash, 4);
    EXPECT_EQ(result, "c4189ae9d538cb28368560f2032e9278");
}

TEST_F(MD5Test, NumericPassword) {
    compute_md5("12345", hash);
    std::string result = hash_to_hex(hash, 4);
    EXPECT_EQ(result, "0ecb7c826c708aea68a1344c7b4ef891");
}

TEST_F(MD5Test, LongerPassword) {
    compute_md5("password", hash);
    std::string result = hash_to_hex(hash, 4);
    EXPECT_EQ(result, "3bcc4d5fd665a75ade27831d99cf82b8");
}

TEST_F(MD5Test, ConsistentHashing) {
    // Same input should produce same output
    word32 hash1[4], hash2[4];
    compute_md5("test", hash1);
    compute_md5("test", hash2);
    
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(hash1[i], hash2[i]);
    }
}

TEST_F(MD5Test, DifferentInputsDifferentOutputs) {
    // Different inputs should produce different outputs
    word32 hash1[4], hash2[4];
    compute_md5("test1", hash1);
    compute_md5("test2", hash2);
    
    bool different = false;
    for (int i = 0; i < 4; i++) {
        if (hash1[i] != hash2[i]) {
            different = true;
            break;
        }
    }
    EXPECT_TRUE(different);
}

TEST_F(MD5Test, MultipleTransforms) {
    // Test that multiple Transform calls work correctly
    word32 hash1[4], hash2[4];
    word32 data[16] = {0};
    
    // First transform
    memcpy(data, "test", 4);
    ((unsigned char*)data)[4] = 0x80;
    data[14] = 4 * 8;
    
    md5.InitState(hash1);
    md5.Transform(hash1, data);
    
    // Second transform with same data
    md5.InitState(hash2);
    md5.Transform(hash2, data);
    
    // Should produce same result
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(hash1[i], hash2[i]);
    }
}

TEST_F(MD5Test, AllLowercaseLetters) {
    compute_md5("abcdefghijklmnopqrstuvwxyz", hash);
    std::string result = hash_to_hex(hash, 4);
    EXPECT_EQ(result, "d7d3fcc300e492616c49fb7d3be167ca");
}

TEST_F(MD5Test, AllDigits) {
    compute_md5("0123456789", hash);
    std::string result = hash_to_hex(hash, 4);
    EXPECT_EQ(result, "245e1e7866b5695de2869b97c7f2238d");
}