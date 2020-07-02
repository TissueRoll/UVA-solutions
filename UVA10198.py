ans = [0 for _ in range(1001)]
ans[0] = 1
for i in range(1,1001):
	ans[i] = 2*ans[i-1]
	if (i - 2 >= 0):
		ans[i] += ans[i-2]
	if (i - 3 >= 0):
		ans[i] += ans[i-3];

while True:
	try:
		print(ans[int(input())])
	except EOFError:
		break