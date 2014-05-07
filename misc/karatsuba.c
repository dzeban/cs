#include <stdio.h>

/* 
   void karatsuba(char *a, char *b)
   {
       long a0, a1, b0, b1;
       long z1, z2, z3;
       int n, n2;
       
       n2 = n/2;
   
       a0 = split(a, n2);
       a1 = split(a + n2, n - n2); 
       b0 = split(b, n2);
       b1 = split(b + n2, n - n2);
   
       z1 = a0 * b0;
       z2 = a1 * b1;
       z3 = (a0 + a1) * (b0 + b1) - z1 - z2;
   
       return 
   }
   */

int mul_digit(char a, char b, char *c)
{
    int carry = 0;
    int res;
    
    res = (a - '0') * (b - '0');
    carry = res / 10;
    *c = res % 10 + '0';
    return carry;
}

char *column_mul(char *a, char *b)
{
    int na, nb, nc;
    char *c
    char **inter_prod;
    char *prod;
    
    na = strlen(a);
    nb = strlen(b);

    // Result digit count
    nc = na + nb + 1;

    // Intermediate productions
    // nb strings, (na + 1) size each
    inter_prod = malloc(sizeof(char *) * nb);
    
    for (int i = na - 1; i >= 0; i--)
    {
        inter_prod[i] = malloc(sizeof(char) * (na + 1));
        prod = inter_prod[i];
        n = na;
        for (int j = nb - 1; j >= 0; j--, n--)
        {
            carry = mul_digit(a[i], b[j], prod[n]);
            prod[n] += carry2;
            carry2 = carry;
        }
        prod[n] = carry
    }
}

int main(int argc, const char *argv[])
{
    char *result;
    result = karatsuba(argv[1], argv[2]);
    printf("%s\n", result);
    return 0;
}
