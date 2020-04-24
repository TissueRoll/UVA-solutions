def solve(a, x):
    ans = 0
    for i in range(len(a)):
        ans += a[i]*x**(len(a)-i-1)
    return ans

while True:
    try:
        a = list(map(int,input().split()))
        b = list(map(int,input().split()))
        ans = 0
        for i in range(len(b)):
            if i == len(b)-1:
                print(solve(a,b[i]))
            else:
                print(solve(a,b[i]), end=" ")
    except EOFError:
        break
