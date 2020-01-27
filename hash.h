#ifndef SUPER_FAST_HASH
#define SUPER_FAST_HASH

#include <stdint.h>
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

// Hashes a data (string of characters) to specified length into a 32-bit unsigned integer
// @param <data>: Data to be hashed
// @param <len>: How many bytes (characters) from start to be hashed
uint32_t SuperFastHash (const char * data, int len);

#endif // SUPER_FAST_HASH

// Author: Paul Hsieh
