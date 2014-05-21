#ifndef SSE_H
#define SSE_H

#include <xmmintrin.h> // SSE
#include <emmintrin.h> // SSE2
#include <pmmintrin.h> // SSE3
#include <tmmintrin.h> // SSSE3
#include <smmintrin.h> // SSE4.1
#include <nmmintrin.h> // SSE4.2

// mask for _mm_shuffle_ps. reversed _MM_SHUFFLE argument order
#define SHUFFLE( fp0, fp1, fp2, fp3 ) (((fp3) << 6) | ((fp2) << 4) | ((fp1) << 2) | ((fp0)))

// mask for _mm_blend_ps
#define BLEND( fp0, fp1, fp2, fp3 ) (((fp3) << 3) | ((fp2) << 2) | ((fp1) << 1) | (fp0))

// mask for _mm_insert_ps
#define INSERT( src, dst ) (((src) << 6) | ((dst) << 4))

// mask for _mm_insert_ps
#define INSERT_ZERO( i ) (1 << (i))

#define ForceInline __forceinline

#endif // SSE_H