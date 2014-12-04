#include "gf.h"

// Multiply element a by x by shifting 
// and reducing over prime polinomial
unsigned char GF_mulX(unsigned char a)
{
    // Char is 1 byte, but we shifting it, 
    // so we need to cast it to some 2-byte
    // type, for example short
    unsigned short aa;
    aa = a;
    aa <<= 1;
    
    // Reduce if we've exceeded GF(2^8)
    if (aa & 0x100)
        aa ^= f;

    return aa;
}

// Multiply 2 polynomials
unsigned char GF_mul(unsigned char a, unsigned char b)
{
    int bits = 7;
    unsigned char c = 0;

    // Multiplication is done by factorization as 
    // a consecutive addition of multiplications
    // of 'a' on 'x' on current highest bit.

    // Loop over 7 bits, last bit after loop
    while(bits--)
    {
        c ^= a * ((b & 0x80) >> 7);
        c = GF_mulX(c);
        b <<= 1;
    }

    // Last sum (b0 * a(x))
    c ^= a * ((b & 0x80) >> 7);

    return c;
}

// Precalculate powers of 'x'
void calc_powers()
{
    int i;
    unsigned char p;
    
    // start with x
    p = 1;
    POWERS[0] = 1;

    for(i = 1; i < 255; i++)
    {
        p = GF_mulX(p);
        POWERS[i] = p;
    }
}

// Computes 'a'th power of 'x'
unsigned char GF_pow(unsigned char a)
{
    return POWERS[a];
}

// Computes logarithm of 'a' base 'x'
unsigned char GF_log(unsigned char a)
{
    unsigned char i;
    for(i = 0; i < 255; i++)
    {
        if (POWERS[i] == a) 
        {
            return i;
        }
    }
}

// Computes inversion of a.
unsigned char GF_inv(unsigned char a)
{
    // a^(-1) = a^(256 - 2) = a^254
    // a = x^b, because x is a primitive element.
    // then
    // a^(-1) = (x^b)^(-1) = x^254b <=> x^(254b % 255)
    unsigned char b, inv_pow;

    b = GF_log(a);
    inv_pow = (254 * b) % 255;
    return GF_pow(inv_pow);
}

int cmp(const void *a, const void *b)
{
    return *(unsigned char *)a - *(unsigned char *)b;
}

int GF_primitives(unsigned char *primitives)
{
    unsigned char a, b;
    unsigned char E[253];
    unsigned char i, j, k;

    k = 0;
    for(a = 2; a != 255; a++)
    {
        // Calculate all powers of current a
        b = GF_log(a);
        j = 0;
        for(i = 2; i < 255; i++)
        {
            E[j++] = GF_pow((i * b) % 255);
        }

        // Sort it to make simple lookupfor identical elements
        qsort(E, 253, sizeof(unsigned char), cmp);

        // If we will not find identical elements then current 'a'
        // is primitive and we add it to array of primitives
        for(j = 0; j < 252; j++)
        {
            if(E[j] == E[j+1])
                break;
        }

        if(j == 252)
        {
            primitives[k++] = a;
        }
    }

    return k;
}

int main(int argc, const char *argv[])
{
    int i;
    int nprimitives;
    unsigned char primitives[256];

    printf("pow(log(0x56)) == 0x%02X\n", GF_pow(GF_log(0x56)));
    printf("mul(0x77, inv(0x77)) == %d\n", GF_mul(0x77, GF_inv(0x77)));

    nprimitives = GF_primitives(primitives);
    printf("\nPrimitives:\n");
    for(i = 0; i < nprimitives; i++)
    {
        if(i % 8 == 0) 
            printf("\n");

        printf("0x%02x ", primitives[i]);
    }
    printf("\nTotal: %d\n", nprimitives);

    printf("%02X\n", GF_mulX(0x88));

    return 0;
}
