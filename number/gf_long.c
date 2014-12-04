/*
 * Galois field operations implementation with simple vectorization
 */

#include "gf.h"


/* Multiply 8 field elements in vector `v` on x */
unsigned long long GF_longmulX(unsigned long long v)
{
    unsigned long long pmask;

    // Take highest bit in each element
    pmask = v & 0x8080808080808080;
    // Create mask with prime polinomial in places where bit is set
    pmask = pmask >> 7;
    pmask = pmask * 0x1d;

    // Shift and cut lowest bit
    v = v << 1;
    v = v & 0xfefefefefefefefe;

    // Now multiply
    return v ^ pmask;
}

int main()
{
    unsigned long long a = 0xabdd8801ff0baaf0;
    unsigned long long ax = GF_longmulX(a);

    printf("%016llx\n", ax);

    return 0;
}
