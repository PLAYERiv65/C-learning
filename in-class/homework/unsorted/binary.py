m = int(input("输入目标进制:"))
n = int(input("输入初始数字:"))

ans = ""

while n > 0:
    ans = str(n % m) + ans
    n = n // m

print(ans)
