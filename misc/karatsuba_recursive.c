#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mul.h"

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

char *combine(char **z1, char **z2, char **z3, int n)
{
    char *z1_shift, *z3_shift;
    char *res, *res_tmp;

    // Generalization of shifts regardless of n oddity
    z1_shift = shift(*z1, (n - n/2)*2);
    z3_shift = shift(*z3, (n - n/2));

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
        return column_mul(x, y);
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

char *copy_argv(char *argv)
{
    char *p;
    int n;

    n = strlen(argv);
    p = calloc(n + 1, sizeof(char));
    memcpy(p, argv, n);
    p[n] = 0;

    return p;
}

int main(int argc, char *argv[])
{
    char *x, *y;
	char *result_karatsuba;
	char *result_column_mul;
    clock_t start, end;
    unsigned long long time_karatsuba, time_column_mul;

    start = clock();
	result_column_mul = column_mul(argv[1], argv[2]);
    end = clock();
    time_column_mul = (unsigned long long)( (end - start) / CLOCKS_PER_SEC );

    // We need to copy argv strings because we
    // manipulate memory in karatsuba
    x = copy_argv(argv[1]);
    y = copy_argv(argv[2]);

    start = clock();
	result_karatsuba = karatsuba(&x, &y);
    end = clock();
    time_karatsuba = (unsigned long long)( (end - start) / CLOCKS_PER_SEC );

    if( !strcmp(result_column_mul, result_karatsuba) )
    {
        printf("\nProducts match: %s\n", result_column_mul);
    }
    else
    {
        printf("\nProducts don't match!\n");
        printf("Column product: %s\n", result_column_mul);
        printf("Karatsuba  product: %s\n", result_karatsuba);
    }

    printf("Column multiplication time: %llus\n", time_column_mul);
    printf("Karatsuba multiplication time: %llus\n", time_karatsuba);

    free(result_column_mul);
    free(result_karatsuba);
    free(x);
    free(y);
	return 0;
}
