#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) a > b ? a : b
#define I(a) (a - '0')

// Don't make it more than 4 because
// 99999 * 99999 will overflow int.
#define BASE_CASE_DIGITS 4

int int_digits(int n)
{
    int d = 1;
    while (n)
    {
        n /= 10;
        d++;
    }
    return d;
}

// Align numbers length, prepending shorter with zeroes
void align(char **x, char **y)
{
    int nx, ny, nz, n;
    char **z;

    nx = strlen(*x);
    ny = strlen(*y);

    if (nx == ny)
        return;

    // Choose which number to align, assigning z to point to it
    if (nx > ny)
    {
        z = y;
        nz = ny;
    }
    else
    {
        z = x;
        nz = nx;
    }

    // To align we realloc memory pointed by z,
    // then we shift old value with memmove,
    // and finally prepend zeroes with memset
    n = max(nx, ny);
    *z = realloc(*z, n + 1);
    memmove(*z + (n - nz), *z, nz);
    memset(*z, '0', n - nz);
    (*z)[n] = 0;
    return;
}

char *base_mul(char *x, char *y)
{
    int xd, yd, zd;
    int d;
    char *res;

    xd = strtol(x, NULL, 10);
    yd = strtol(y, NULL, 10);
    zd = xd * yd;

    // Convert back to string
    d = int_digits(zd);
    res = calloc(d + 1, sizeof(char));
    snprintf(res, d, "%d", zd);
    res[d] = 0;
    return res;
}

// Splits x in 2 half - 'a' and b.
void split(char *x, int n, char **a, char **b)
{
    *a = calloc(n/2 + 1, sizeof(char));
    *b = calloc(n - n/2 + 1, sizeof(char));

    memcpy(*a, x, n/2);
    memcpy(*b, x + n/2, n - n/2);
    (*a)[n/2] = 0;
    (*b)[n - n/2] = 0;
}

void trim(char **d, int n)
{
    char *p;
    char *c;
    int lz; // leading zeroes

    p = *d;
    lz = strspn(p, "0");
    if (lz == 0)
        return;

    c = calloc(n - lz + 1, sizeof(char));
    memcpy(c, p + lz, n - lz + 1);
    free(p);
    *d = c;
}

// Sum 2 numbers represented as strings of digits
// TODO: Rewrite with va_args
char *sum(char **num1, char **num2)
{
    char *a, *b, *c;
    int n, nc;
    int i, j;
    int d, carry;

    align(num1, num2);
    a = *num1;
    b = *num2;
    n = strlen(a);

    // Sum may be 1 digit longer (e.g 99 + 99 = 198)
    nc = n + 1;

    c = calloc(nc + 1, sizeof(char));
    memset(c, '0', nc);
    c[nc] = 0;

    carry = 0;
    for (i = n - 1, j = nc - 1; i >= 0; i--, j--)
    {
        d = I(a[i]) + I(b[i]) + carry;
        c[j] = d % 10 + '0';
        carry = d / 10;
    }

    c[j] = carry + '0';

    trim(&c, nc);
    return c;
}

// Subtracts 2 numbers represented as strings of digits
// TODO: Rewrite with va_args
char *sub(char **num1, char **num2)
{
    char *a, *b, *c;
    int d, borrow;
    int n;
    int i;

    align(num1, num2);
    a = *num1;
    b = *num2;
    n = strlen(a);

    c = calloc(n + 1, sizeof(char));
    memset(c, '0', n);
    c[n] = 0;

    borrow = 0;
    for (i = n - 1; i >= 0; i--)
    {
        d = I(a[i]) - borrow - I(b[i]);
        borrow = 0;
        if (d < 0)
        {
            d += 10;
            borrow = 1;
        }

        c[i] = d + '0';
    }

    trim(&c, n);
    return c;
}

char *shift(char *a, int n)
{
    char *res;
    int nres, na;

    na = strlen(a);
    nres = na + n;
    res = calloc(nres + 1, sizeof(char));
    memset(res, '0', nres);
    memcpy(res, a, na);
    res[nres] = 0;
    return res;
}

char *combine(char **z1, char **z2, char **z3, int n)
{
    char *z1_shift, *z3_shift;
    char *res, *res_tmp;

    z1_shift = shift(*z1, n);
    z3_shift = shift(*z3, n/2);

    res_tmp = sum(&z1_shift, &z3_shift);
    res = sum(&res_tmp, z2);

    free(z1_shift);
    free(z3_shift);
    free(res_tmp);
    return res;
}

// Karatsuba multiplication takes double pointers because it changes memory
// under them with realloc in align subroutine
char *karatsuba(char **number1, char **number2)
{
    char *x, *y;
    char *a, *b, *c, *d;
    char *z1, *z2;
    char *z3, *z31, *z32, *z3_tmp1, *z3_tmp2;
    char *res;
    int n;

    align(number1, number2);
    x = *number1;
    y = *number2;
    n = strlen(x);

    if (n <= BASE_CASE_DIGITS)
    {
        return base_mul(x, y);
    }

    split(x, n, &a, &b);
    split(y, n, &c, &d);

    z1 = karatsuba(&a, &c);
    z2 = karatsuba(&b, &d);

    // Tricky z3 calculation
    // z3 = (a+b)(c+d) - z2 - z1
    z31 = sum(&a, &b);
    z32 = sum(&c, &d);
    z3_tmp1 = karatsuba(&z31, &z32);
    z3_tmp2 = sub(&z3_tmp1, &z2);
    z3 = sub(&z3_tmp2, &z1);

    res = combine(&z1, &z2, &z3, n);
    // printf("x: %s, y: %s\n", x, y);
    // printf("a: %s, b: %s, c: %s, d: %s\n", a, b, c, d);
    // printf("z1: %s, z2: %s, z3: %s\n", z1, z2, z3);
    // printf("res: %s\n", res);

    free(a); free(b); free(c); free(d);
    free(z1); free(z2); free(z31); free(z32); free(z3); free(z3_tmp1); free(z3_tmp2);

    return res;
}

int main(int argc, char *argv[])
{
	char *result;
    char *x, *y;
    int nx, ny;

    // We need to copy argv strings because we
    // manipulate memory in karatsuba
    nx = strlen(argv[1]);
    ny = strlen(argv[2]);

    x = calloc(nx + 1, sizeof(char));
    memcpy(x, argv[1], nx);
    x[nx] = 0;

    y = calloc(ny + 1, sizeof(char));
    memcpy(y, argv[2], ny);
    y[ny] = 0;

	result = karatsuba(&x, &y);
	printf("\nProduct: %s\n", result);
    free(x);
    free(y);
	free(result);
	return 0;
}
