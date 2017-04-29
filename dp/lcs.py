def lcslen(x, y):
    # Allocate extra row and column for the empty sequence case.
    # Extra row and column is appended to the end and exploit
    # Python's ability of negative indices: x[-1] is the last elem.
    c = [[0 for _ in range(len(y) + 1)] for _ in range(len(x) + 1)]

    for i, xi in enumerate(x):
        for j, yj in enumerate(y):
            if xi == yj:
                c[i][j] = 1 + c[i-1][j-1]
            else:
                c[i][j] = max(c[i][j-1], c[i-1][j])
    return c

def backtrack(c, x, y, i, j):
    if i == -1 or j == -1:
        return ""
    elif x[i] == y[j]:
        return backtrack(c, x, y, i-1, j-1) + x[i]
    else:
        if c[i][j-1] > c[i-1][j]:
            return backtrack(c, x, y, i, j-1)
        else:
            return backtrack(c, x, y, i-1, j)

def lcs(x, y):
    c = lcslen(x,y)
    return backtrack(c, x, y, len(x)-1, len(y)-1)
