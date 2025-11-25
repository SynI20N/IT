#include <fstream>
#include "md5.hpp"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <omp.h>
#include <chrono>
#include "hacker.hpp"
#ifdef TEST
#include "gtest/gtest.h"
#endif

// Helper function to compute hash of a password
void compute_hash(const char* password, word32* hash) {
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

// Helper function to print hash
void print_hash(const word32* hash) {
    for (int i = 0; i < 4; i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(8) << hash[i];
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
        "pass", "12345", "abc12", "xyz99", "hello",
        "world", "key42", "data5", "code7", "mhash8"
    };
    
    int thread_counts[] = {1, 2, 4, 8};
    
    std::cout << "Password Cracking Benchmark\n";
    std::cout << "============================\n\n";
    
    for (int threads : thread_counts) {
        omp_set_num_threads(threads);
        
        std::cout << "Testing with " << threads << " thread(s):\n";
        std::cout << std::string(50, '-') << "\n";
        
        double total_time = 0.0;
        int successful_cracks = 0;
        
        for (int i = 0; i < 10; i++) {
            const char* original_password = test_passwords[i];
            
            // Compute target hash
            word32 target_hash[4];
            compute_hash(original_password, target_hash);
            
            std::cout << "Test " << (i + 1) << ": Password = \"" << original_password << "\", Hash = ";
            print_hash(target_hash);
            std::cout << "\n";
            
            // Try to crack it
            Hacker<MD5> hacker;
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
        }
        
        std::cout << "\nSummary: " << successful_cracks << "/10 cracked, "
                  << "Average time: " << std::fixed << std::setprecision(3) 
                  << (total_time / 10.0) << "s\n\n";
    }
    
    return 0;
#endif
}