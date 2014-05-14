#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mul_digit(char a, char b, int carry, char *c)
{
	int res;
	
	res = (a - '0') * (b - '0') + carry;
	carry = res / 10;
	*c = res % 10 + '0';
	return carry;
}

char *sum(char *a, char *b)
{
}

char *sub(char *a, char *b)
{
}

char *shift(char *a, int n)
{
}

char *karatsuba_mul(char *x, char *y)
{
	char *res;
	int carry;
	int nx, ny;
	char *a, *b, *c, *d;
	char *z1, *z2, *z3, *z4;

	nx = strlen(x);
	ny = strlen(y);

	res = calloc((nx + ny + 1), sizeof(char));
	memset(res, ' ', nx + ny + 1);

	if(nx == 1 && ny ==1)
	{
		carry = mul_digit(x[0], y[0], 0, &res[nx + ny - 1]);
		res[nx + ny - 2] = carry + '0';
	}

	a  = calloc( n/2, sizeof(char) );
	b  = calloc( n/2, sizeof(char) );
	c  = calloc( n/2, sizeof(char) );
	d  = calloc( n/2, sizeof(char) );
	z1 = calloc( n,   sizeof(char) );
	z2 = calloc( n,   sizeof(char) );
	z3 = calloc( n,   sizeof(char) );
	z4 = calloc( n,   sizeof(char) );

	z1 = karatsuba_mul(a, c);
	z2 = karatsuba_mul(b, d);
	z3 = karatsuba_mul(sum(a,b), sum(c,d));
	z4 = sub(z3, z2);
	z4 = sub(z4, z1);
	
	res = sum(shift(z1, n), shift(z4, n/2));
	res = sum(res, z2);

	free(a);
	free(b);
	free(c);
	free(d);
	free(z1);
	free(z2);
	free(z3);
	free(z4);

	return res;
}

int main(int argc, char *argv[])
{
	char *result;
	result = karatsuba_mul(argv[1], argv[2]);
	printf("\nProduction: %s\n", result);
	free(result);
	return 0;
}
