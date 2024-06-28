import random

# 目标总和
target_sum = 384
# 整数个数
num_integers = 21
# 初始平均值
average = target_sum / num_integers
# 剩余要分配的值
remaining = target_sum
# 存储生成的整数
integers = []

# 生成整数，直到达到目标总和
for _ in range(num_integers - 1):
    # 随机生成一个数，范围在平均值附近波动，但不超过剩余值的一半
    # 这样可以确保最后一个数能够恰好达到剩余值
    random_value = random.randint(1, max(1, int(remaining / 2)))
    integers.append(random_value)
    remaining -= random_value

# 添加最后一个整数，使其总和恰好为目标值
integers.append(remaining)

# 打印结果，每个数之间用空格隔开
print(' '.join(map(str, integers)))