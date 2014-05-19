#ifndef _MUL_H
#define _MUL_H

#define I(a) (a - '0')
#define max(a, b) a > b ? a : b

char *column_mul(char *a, char *b);

void split(char *x, int n, char **a, char **b);
void trim(char **d, int n);
void align(char **x, char **y);
char *sum(char **num1, char **num2);
char *sub(char **num1, char **num2);
char *shift(char *a, int n);

#endif // _MUL_H
