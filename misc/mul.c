#include <stdlib.h>
#include <string.h>

#include "mul.h"

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

// sum 2 numbers represented as strings of digits
// todo: rewrite with va_args
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

    // sum may be 1 digit longer (e.g 99 + 99 = 198)
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

int mul_digit(char a, char b, int carry, char *c)
{
	int res;

	res = (a - '0') * (b - '0') + carry;
	carry = res / 10;
	*c = res % 10 + '0';
	return carry;
}

char *column_mul(char *a, char *b)
{
	int na, nb, nc;
	int carry;
	char *c;
	char **inter_prod;
	int i, j, n;

	na = strlen(a);
	nb = strlen(b);

	// Result digits count
	nc = na + nb;

	// Intermediate productions
	// nb strings, (na + 1) size each
	inter_prod = malloc(sizeof(char *) * nb);

	// Calculate inter products
	for (i = nb - 1; i >= 0; i--)
	{
		inter_prod[i] = malloc(sizeof(char) * nc);
		memset(inter_prod[i], '0', nc);

		// Shift inter products
		// inter_prod[i][2]: 00089991
		// inter_prod[i][1]: 00899910
		// inter_prod[i][0]: 08999100
		n = nc - (nb - i);
		carry = 0;
		for (j = na - 1; j >= 0; j--, n--)
		{
			carry = mul_digit(a[j], b[i], carry, &inter_prod[i][n]);
		}
		inter_prod[i][n] = carry + '0';
		// printf("inter_prod[%d]: %s\n", i, inter_prod[i]);
	}

	// Sum inter products
	c = malloc(sizeof(char) * (nc + 1));
	memset(c, ' ', nc);
	c[nc] = 0;
	carry = 0;
	for (i = nc - 1; i >= 0; i--)
	{
		n = 0;
		for (j = nb - 1; j >= 0; j--)
		{
			n += inter_prod[j][i] - '0';
		}
		n += carry;
		c[i] = n % 10 + '0';
		carry = n / 10;
	}

	for (i = 0; i < nb; i++)
	{
		free(inter_prod[i]);
	}
	free(inter_prod);

	return c;
}

