#include "hash_func.hpp"
#include "md5.hpp"
#include <type_traits>
#include <omp.h>
#include <cstring>

// Helper to determine hash output size at compile time
template <typename T>
struct HashTraits;

template <>
struct HashTraits<MD5> {
    static constexpr int OUTPUT_SIZE = 16; // 128 bit = 4 word32s
    static constexpr int OUTPUT_WORDS = 4;
};

template <>
struct HashTraits<SHA256> {
    static constexpr int OUTPUT_SIZE = 32; // 256 bit = 8 word32s
    static constexpr int OUTPUT_WORDS = 8;
};

template <typename T> requires std::is_base_of_v<HashFunction, T>
class Hacker {
public:
    Hacker() {
        hash_class_ = new T;
    }
    
    bool hack(const word32 *target_hash, char* result_password, int min_len = 4, int max_len = 6) {
        bool found = false;
        for (int len = min_len; len <= max_len && !found; len++) {
            found = bruteforce_length(target_hash, result_password, len);
        }
        return found;
    }

    bool hack(const std::array<uint8_t, 32>& target_hash, char* result_password, int min_len = 4, int max_len = 6) {
        word32 hash_words[8];
        std::memcpy(hash_words, target_hash.data(), 32);
        return hack(hash_words, result_password, min_len, max_len);
    }
    
    ~Hacker() {
        delete hash_class_;
    }
    
private:
    T* hash_class_;
    static constexpr char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    static constexpr int charset_size = 36;
    
    // Unified brute force using HashFunction interface
    bool bruteforce_length(const word32 *target_hash, char* result, int length) {
        bool found = false;
        long long total_combinations = 1;
        for (int i = 0; i < length; i++) {
            total_combinations *= charset_size;
        }
        
        constexpr int hash_words = HashTraits<T>::OUTPUT_WORDS;
        
        #pragma omp parallel
        {
            char password[16] = {0};
            word32 state[hash_words];
            word32 data[16] = {0};
            T local_hash;
            
            #pragma omp for schedule(dynamic, 1000)
            for (long long idx = 0; idx < total_combinations; idx++) {
                if (found) continue;
                
                // Generate password from index
                long long temp = idx;
                for (int i = 0; i < length; i++) {
                    password[i] = charset[temp % charset_size];
                    temp /= charset_size;
                }
                password[length] = '\0';
                
                // Prepare data for hashing
                memset(data, 0, sizeof(data));
                memcpy(data, password, length);
                
                // Add padding (works for both MD5 and SHA256 single-block messages)
                unsigned char* byte_data = (unsigned char*)data;
                byte_data[length] = 0x80;
                
                // Add length in bits at the end
                word32 bit_length = length * 8;
                data[14] = bit_length; // For MD5 (little-endian)
                
                // For SHA256, we need big-endian length at different position
                // But since we're using Transform interface, we pass raw data
                // and let the implementation handle it
                
                // Compute hash using HashFunction interface
                local_hash.InitState(state);
                local_hash.Transform(state, data);
                
                // Compare with target (compare only relevant words)
                bool match = true;
                for (int i = 0; i < hash_words; i++) {
                    if (state[i] != target_hash[i]) {
                        match = false;
                        break;
                    }
                }
                
                if (match) {
                    #pragma omp critical
                    {
                        if (!found) {
                            found = true;
                            strcpy(result, password);
                        }
                    }
                }
            }
        }
        return found;
    }
};