#include <stdio.h>
#include <ctype.h>
#include <limits.h>

// Prints error message marking error positing with '^'
void show_expr_error(const char *s, int position)
{
	fprintf(stderr, "Invalid expression %s\n", s);

	// Shift to the start of expression in error message
	fprintf(stderr, "                   ");

	// Find error position and put '^' to it
	while (position--)
		fprintf(stderr, " ");
	fprintf(stderr, "^ \n");
}

int evaluate(const char *s)
{
	static int position = 0;
	char c = s[position++];
	if (c == 0)
		return INT_MAX;
	
	if (isdigit(c))
	{
		// Recursion base case
		return c - '0';
	}
	else
	{
		switch(c)
		{
			case '+':
				return evaluate(s) + evaluate(s);
			case '-':
				return evaluate(s) - evaluate(s);
			case '*':
				return evaluate(s) * evaluate(s);
			case '/':
				return evaluate(s) / evaluate(s);
			default:
				show_expr_error(s, position);
				return INT_MAX;
		}
	}
}

void usage()
{
	printf("./prefix_calc <expression>\n\n");
	printf("<expression> must be in prefix form\n");
	printf("and with 1-digit numbers and no spaces\n");
	printf("(Sorry, no error checking for now\n\n");
	printf("For example:\n");
	printf("+23\n");
	printf("*+234\n");
	printf("*2/-593\n");
}

int main(int argc, const char *argv[])
{
	int val = 0;

	if (argc < 2)
	{
		usage();
		return -1;
	}

	val = evaluate(argv[1]);
	if (val == INT_MAX)
	{
		printf("Invalid expression %s\n", argv[1]);
		return -1;
	}

	printf("%s = %d\n", argv[1], val);
	return 0;
}
