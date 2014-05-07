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

	return c;
}

int main(int argc, char *argv[])
{
	char *result;
	result = column_mul(argv[1], argv[2]);
	printf("\nProduction: %s\n", result);
	return 0;
}
