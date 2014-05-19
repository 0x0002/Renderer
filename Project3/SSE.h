#ifndef SSE_H
#define SSE_H

#include <xmmintrin.h>
#include <smmintrin.h>
#include <emmintrin.h>

// mask for _mm_shuffle_ps. reversed _MM_SHUFFLE argument order
#define SHUFFLE( fp0, fp1, fp2, fp3 ) (((fp3) << 6) | ((fp2) << 4) | ((fp1) << 2) | ((fp0)))

// mask for _mm_blend_ps
#define BLEND( fp0, fp1, fp2, fp3 ) (((fp3) << 3) | ((fp2) << 2) | ((fp1) << 1) | (fp0))

#define ForceInline __forceinline

#endif // SSE_H