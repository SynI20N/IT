#include "hash_func.hpp"
#include "md5.hpp"
#include <type_traits>
#include <omp.h>
#include <cstring>

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
    
    ~Hacker() {
        delete hash_class_;
    }
    
private:
    T* hash_class_;
    
    static constexpr char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    static constexpr int charset_size = 36;
    
    bool bruteforce_length(const word32 *target_hash, char* result, int length) {
        bool found = false;
        long long total_combinations = 1;
        for (int i = 0; i < length; i++) {
            total_combinations *= charset_size;
        }
        
        #pragma omp parallel
        {
            char password[16] = {0};
            word32 state[4];
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
                
                // Prepare data for hashing (convert password to word32 array)
                memset(data, 0, sizeof(data));
                memcpy(data, password, length);
                
                // Add padding (MD5 padding)
                unsigned char* byte_data = (unsigned char*)data;
                byte_data[length] = 0x80;
                
                // Add length in bits at the end (little-endian)
                word32 bit_length = length * 8;
                data[14] = bit_length;
                
                // Compute hash
                local_hash.InitState(state);
                local_hash.Transform(state, data);
                
                // Compare with target
                if (state[0] == target_hash[0] && 
                    state[1] == target_hash[1] && 
                    state[2] == target_hash[2] && 
                    state[3] == target_hash[3]) {
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