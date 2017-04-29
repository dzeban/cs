from lcs import lcslen

def print_diff(c, x, y, i, j):
    if i >= 0 and j >= 0 and x[i] == y[j]:
        print_diff(c, x, y, i-1, j-1)
        print("  " + x[i])
    elif j >= 0 and (i == 0 or c[i][j-1] >= c[i-1][j]):
        print_diff(c, x, y, i, j-1)
        print("+ " +  y[j])
    elif i >= 0 and (j == 0 or c[i][j-1] < c[i-1][j]):
        print_diff(c, x, y, i-1, j)
        print("- " + x[i])
    else:
        print("")

def diff(x, y):
    c = lcslen(x, y)
    return print_diff(c, x, y, len(x)-1, len(y)-1)
