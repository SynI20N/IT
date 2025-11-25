#ifndef CRYPTOPP_MD5_H
#define CRYPTOPP_MD5_H

#include "hash_func.hpp"

/// \brief MD5 message digest
class MD5 : HashFunction
{
public:
	void InitState(word32 *state);
	void Transform(word32 *digest, const word32 *data);
};

#endif
