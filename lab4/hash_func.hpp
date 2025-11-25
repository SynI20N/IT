#ifndef HASH_FUNC_HPP
#define HASH_FUNC_HPP

typedef unsigned int word32;

class HashFunction {
public:
	virtual void InitState(word32 *state) = 0;
	virtual void Transform(word32 *digest, const word32 *data) = 0;

    virtual ~HashFunction() {
        
    }
};

#endif