#include <fstream>
#include "md5.hpp"
#include "sha256.hpp"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <omp.h>
#include <chrono>
#include <array>
#include "hacker.hpp"
#ifdef TEST
#include "gtest/gtest.h"
#endif

// Helper function to compute hash using HashFunction interface
template <typename T>
void compute_hash_generic(const char* password, word32* hash) {
    T hash_obj;
    word32 data[16] = {0};
    int len = strlen(password);
    
    memcpy(data, password, len);
    unsigned char* byte_data = (unsigned char*)data;
    byte_data[len] = 0x80;
    data[14] = len * 8;
    
    hash_obj.InitState(hash);
    hash_obj.Transform(hash, data);
}

// Specialized for MD5
void compute_md5_hash(const char* password, word32* hash) {
    compute_hash_generic<MD5>(password, hash);
}

// Specialized for SHA256
std::array<uint8_t, 32> compute_sha256_hash(const char* password) {
    word32 hash[8];
    compute_hash_generic<SHA256>(password, hash);
    
    std::array<uint8_t, 32> result;
    std::memcpy(result.data(), hash, 32);
    return result;
}

// Helper function to print hash
void print_hash(const word32* hash, int word_count) {
    for (int i = 0; i < word_count; i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(8) << hash[i];
    }
    std::cout << std::dec;
}

// Helper function to print hash from byte array
void print_hash_bytes(const std::array<uint8_t, 32>& hash) {
    for (int i = 0; i < 32; i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)hash[i];
    }
    std::cout << std::dec;
}

int main(int argc, char** argv) {
#ifdef TEST
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    // Test passwords
    const char* test_passwords[] = {
        "pass", "test2", "abcd2", "xyz9", "hell",
        "12345", "key4", "dai2a", "code", "myash"
    };
    
    int thread_counts[] = {1, 2, 4, 8};
    
    std::cout << "Password Cracking Benchmark\n";
    std::cout << "============================\n\n";
    
    // Test MD5
    // std::cout << "=== MD5 Hash Testing ===\n\n";
    // for (int threads : thread_counts) {
    //     omp_set_num_threads(threads);
        
    //     std::cout << "Testing with " << threads << " thread(s):\n";
    //     std::cout << std::string(70, '-') << "\n";
        
    //     double total_time = 0.0;
    //     int successful_cracks = 0;
        
    //     for (int i = 0; i < 10; i++) {
    //         const char* original_password = test_passwords[i];
            
    //         // Compute target hash
    //         word32 target_hash[4];
    //         compute_md5_hash(original_password, target_hash);
            
    //         std::cout << "Test " << (i + 1) << ": Password = \"" << original_password << "\"\n";
    //         std::cout << "  MD5 Hash = ";
    //         print_hash(target_hash, 4);
    //         std::cout << "\n";
            
    //         // Try to crack it
    //         Hacker<MD5> hacker;
    //         char cracked_password[16] = {0};
            
    //         auto start = std::chrono::high_resolution_clock::now();
    //         bool success = hacker.hack(target_hash, cracked_password);
    //         auto end = std::chrono::high_resolution_clock::now();
            
    //         double elapsed = std::chrono::duration<double>(end - start).count();
    //         total_time += elapsed;
            
    //         if (success) {
    //             successful_cracks++;
    //             std::cout << "  ✓ Cracked: \"" << cracked_password << "\" in " 
    //                      << std::fixed << std::setprecision(3) << elapsed << "s\n";
    //         } else {
    //             std::cout << "  ✗ Failed to crack in " 
    //                      << std::fixed << std::setprecision(3) << elapsed << "s\n";
    //         }
    //         std::cout << "\n";
    //     }
        
    //     std::cout << "Summary: " << successful_cracks << "/10 cracked, "
    //               << "Average time: " << std::fixed << std::setprecision(3) 
    //               << (total_time / 10.0) << "s\n\n";
    // }
    
    // Test SHA256
    std::cout << "\n=== SHA256 Hash Testing ===\n\n";
    for (int threads : thread_counts) {
        omp_set_num_threads(threads);
        
        std::cout << "Testing with " << threads << " thread(s):\n";
        std::cout << std::string(70, '-') << "\n";
        
        double total_time = 0.0;
        int successful_cracks = 0;
        
        for (int i = 0; i < 10; i++) {
            const char* original_password = test_passwords[i];
            
            // Compute target hash
            std::array<uint8_t, 32> target_hash = compute_sha256_hash(original_password);
            
            std::cout << "Test " << (i + 1) << ": Password = \"" << original_password << "\"\n";
            std::cout << "  SHA256 Hash = ";
            print_hash_bytes(target_hash);
            std::cout << "\n";
            
            // Try to crack it using unified interface
            Hacker<SHA256> hacker;
            char cracked_password[16] = {0};
            
            auto start = std::chrono::high_resolution_clock::now();
            bool success = hacker.hack(target_hash, cracked_password);
            auto end = std::chrono::high_resolution_clock::now();
            
            double elapsed = std::chrono::duration<double>(end - start).count();
            total_time += elapsed;
            
            if (success) {
                successful_cracks++;
                std::cout << "  ✓ Cracked: \"" << cracked_password << "\" in " 
                         << std::fixed << std::setprecision(3) << elapsed << "s\n";
            } else {
                std::cout << "  ✗ Failed to crack in " 
                         << std::fixed << std::setprecision(3) << elapsed << "s\n";
            }
            std::cout << "\n";
        }
        
        std::cout << "Summary: " << successful_cracks << "/10 cracked, "
                  << "Average time: " << std::fixed << std::setprecision(3) 
                  << (total_time / 10.0) << "s\n\n";
    }
    
    return 0;
#endif
}