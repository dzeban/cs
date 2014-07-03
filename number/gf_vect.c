/*
 * Galois field operations implementation with SSE vectorization
 */

#include "gf.h"
#include <emmintrin.h>

__m128i GF_vectmulX(__m128i v)
{
    __m128i v1;
    __m128i mask;
    __m128i res;

    __m128i low_bit_mask = { 0xfefefefefefefefe, 0xfefefefefefefefe };
    __m128i high_bit_mask = { 0x8080808080808080, 0x8080808080808080 };
    __m128i modulo_mask = { 0x1d1d1d1d1d1d1d1d, 0x1d1d1d1d1d1d1d1d};

    unsigned char A[16] __attribute__((aligned(16)));
    int i;

    // Zero out
    mask = _mm_setzero_si128();

    // Form modulo mask from highest bits of v
    v1 = _mm_and_si128(v, high_bit_mask);
    mask = _mm_cmpgt_epi8(mask, v1);
    mask = _mm_and_si128(mask, modulo_mask);

    // Shift v and mask out lowest bits because
    // we can't shift in packed 8-bit integees
    res = v;
    res = _mm_slli_epi16(res, 1);
    res = _mm_and_si128(res, low_bit_mask);

    // Finally sum v and modulo
    res = _mm_xor_si128(res, mask);

    return res;
}

int main()
{
    __m128i a = { 0xabdd8801ff0baaf0, 0xabdd8801ff0baaf0 };
    __m128i ax;
    unsigned char A[16] __attribute__((aligned(16)));
    int i;

    ax = GF_vectmulX(a);

    _mm_store_si128((__m128i *)A, ax);

    for(i = 15; i >= 0; i--)
    {
        printf("%02x", A[i]);
    }

    printf("\n");
    return 0;
}
