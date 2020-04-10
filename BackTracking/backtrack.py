lst = [1, 2, 3]
bool = [False, False, False]
tmp = []


def backtrack(n, Max):
    if n == Max:
        print(tmp)
        return

    for i in range(Max):
        if not bool[i]:
            bool[i] = True
            tmp.append(lst[i])
            backtrack(n+1, Max)
            tmp.pop()
            bool[i] = False

Max = len(lst)
backtrack(0, Max)
