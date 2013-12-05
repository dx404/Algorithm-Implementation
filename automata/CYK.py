# Author: Duo Zhao
# an partial implementation of CYK algorithm 
# for testing string membership to a Context-free grammar
# Category: Dynamic programming (without backtracking)

def getCYK_table(s, g):
    n = len(s)
    gDict = dict()
    for h, b in g:
        if b in gDict:
            gDict[b] = ''.join(sorted(gDict[b] + h))
        else:
            gDict[b] = h
    gTable = [['']*(n+1) for _ in xrange(n+1)] #2D array in python

    for j in xrange(0, n):
        if s[j] in gDict:
            gTable[j][j+1] = gDict[s[j]]

    for d in xrange(2, n+1):
        for i in xrange(0, n - d + 1):
            j = i + d 
            for p in xrange(i+1, j):
                gTable[i][j] = ''.join(sorted(set(gTable[i][j] + backDerive(gTable[i][p], gTable[p][j], gDict))))
    
    return gTable

def backDerive(x, y, gDict):
    nh = ''
    for s in x:
        for t in y:
            sym = ''.join(s+t)
            if sym in gDict:
                nhc = gDict[sym]
                if nhc not in nh:
                    nh += nhc
    return ''.join(sorted(set(nh)))


if __name__ == "__main__":
    g=[
        ('S', 'AB'), \
        ('S', 'BC'), \
        ('A', 'BA'), \
        ('A', 'a'), \
        ('B', 'CC'), \
        ('B', 'b'), \
        ('C', 'AB'), \
        ('C', 'a')
      ];
    t = getCYK_table('ababaa', g)
    for row in t:
        print row
