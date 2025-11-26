#include "gtest/gtest.h"
#include "../sha256.hpp"
#include <cstring>
#include <iomanip>
#include <sstream>

// Helper to convert byte array to hex string
std::string bytes_to_hex(const std::array<uint8_t, 32>& bytes) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < 32; i++) {
        ss << std::setw(2) << (unsigned int)bytes[i];
    }
    return ss.str();
}

// Helper to compute SHA256 hash using standard interface
std::array<uint8_t, 32> compute_sha256(const char* input) {
    SHA256 sha;
    sha.update(input);
    return sha.digest();
}

// Helper to compute SHA256 using Transform interface
void compute_sha256_transform(const char* input, word32* output) {
    SHA256 sha;
    word32 data[16] = {0};
    int len = strlen(input);
    
    memcpy(data, input, len);
    unsigned char* byte_data = (unsigned char*)data;
    byte_data[len] = 0x80;
    data[14] = len * 8;
    
    sha.InitState(output);
    sha.Transform(output, data);
}

class SHA256Test : public ::testing::Test {
protected:
    SHA256 sha;
};

TEST_F(SHA256Test, EmptyString) {
    sha.update("");
    std::array<uint8_t, 32> digest = sha.digest();
    std::string result = bytes_to_hex(digest);
    
    // SHA256("") = e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
    EXPECT_EQ(result, "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
}

TEST_F(SHA256Test, SingleCharacter) {
    std::array<uint8_t, 32> digest = compute_sha256("a");
    std::string result = bytes_to_hex(digest);
    
    // SHA256("a") = ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb
    EXPECT_EQ(result, "ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb");
}

TEST_F(SHA256Test, ABC) {
    std::array<uint8_t, 32> digest = compute_sha256("abc");
    std::string result = bytes_to_hex(digest);
    
    // SHA256("abc") = ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
    EXPECT_EQ(result, "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
}

TEST_F(SHA256Test, ShortPassword) {
    std::array<uint8_t, 32> digest = compute_sha256("pass");
    std::string result = bytes_to_hex(digest);
    
    // SHA256("pass") = d74ff0ee8da3b9806b18c877dbf29bbde50b5bd8e4dad7a3a725000feb82e8f1
    EXPECT_EQ(result, "d74ff0ee8da3b9806b18c877dbf29bbde50b5bd8e4dad7a3a725000feb82e8f1");
}

TEST_F(SHA256Test, NumericPassword) {
    std::array<uint8_t, 32> digest = compute_sha256("12345");
    std::string result = bytes_to_hex(digest);
    
    // SHA256("12345") = 5994471abb01112afcc18159f6cc74b4f511b99806da59b3caf5a9c173cacfc5
    EXPECT_EQ(result, "5994471abb01112afcc18159f6cc74b4f511b99806da59b3caf5a9c173cacfc5");
}

TEST_F(SHA256Test, LongerPassword) {
    std::array<uint8_t, 32> digest = compute_sha256("password");
    std::string result = bytes_to_hex(digest);
    
    // SHA256("password") = 5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8
    EXPECT_EQ(result, "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8");
}

TEST_F(SHA256Test, ConsistentHashing) {
    // Same input should produce same output
    std::array<uint8_t, 32> digest1 = compute_sha256("test");
    std::array<uint8_t, 32> digest2 = compute_sha256("test");
    
    EXPECT_EQ(digest1, digest2);
}

TEST_F(SHA256Test, DifferentInputsDifferentOutputs) {
    // Different inputs should produce different outputs
    std::array<uint8_t, 32> digest1 = compute_sha256("test1");
    std::array<uint8_t, 32> digest2 = compute_sha256("test2");
    
    EXPECT_NE(digest1, digest2);
}

TEST_F(SHA256Test, MultipleTransforms) {
    // Test that multiple Transform calls work correctly
    word32 hash1[8], hash2[8];
    
    compute_sha256_transform("test", hash1);
    compute_sha256_transform("test", hash2);
    
    // Should produce same result
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(hash1[i], hash2[i]);
    }
}

TEST_F(SHA256Test, InitStateTest) {
    word32 state[8];
    sha.InitState(state);
    
    // Check initial state values
    EXPECT_EQ(state[0], 0x6a09e667);
    EXPECT_EQ(state[1], 0xbb67ae85);
    EXPECT_EQ(state[2], 0x3c6ef372);
    EXPECT_EQ(state[3], 0xa54ff53a);
    EXPECT_EQ(state[4], 0x510e527f);
    EXPECT_EQ(state[5], 0x9b05688c);
    EXPECT_EQ(state[6], 0x1f83d9ab);
    EXPECT_EQ(state[7], 0x5be0cd19);
}

TEST_F(SHA256Test, ToStringMethod) {
    std::array<uint8_t, 32> digest = compute_sha256("hello");
    std::string result = SHA256::toString(digest);
    
    // SHA256("hello") = 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824
    EXPECT_EQ(result, "2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824");
}

TEST_F(SHA256Test, IncrementalUpdate) {
    SHA256 sha1, sha2;
    
    // Hash in one go
    sha1.update("hello");
    sha1.update("world");
    std::array<uint8_t, 32> digest1 = sha1.digest();
    
    // Hash as single string
    sha2.update("helloworld");
    std::array<uint8_t, 32> digest2 = sha2.digest();
    
    // Should produce same result
    EXPECT_EQ(digest1, digest2);
}

TEST_F(SHA256Test, LongInput) {
    std::string long_input = "The quick brown fox jumps over the lazy dog";
    std::array<uint8_t, 32> digest = compute_sha256(long_input.c_str());
    std::string result = bytes_to_hex(digest);
    
    // SHA256("The quick brown fox jumps over the lazy dog")
    EXPECT_EQ(result, "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592");
}

TEST_F(SHA256Test, AllLowercaseLetters) {
    std::array<uint8_t, 32> digest = compute_sha256("abcdefghijklmnopqrstuvwxyz");
    std::string result = bytes_to_hex(digest);
    
    // SHA256("abcdefghijklmnopqrstuvwxyz")
    EXPECT_EQ(result, "71c480df93d6ae2f1efad1447c66c9525e316218cf51fc8d9ed832f2daf18b73");
}