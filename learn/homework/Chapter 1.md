# 3.
## (1) 两层循环，没有跳过，复杂度O(n<sup>2</sup>)。
## (2) 两个循环，没有嵌套，复杂度O(n)。
## (3) 一个循环，但是每次i翻倍，复杂度O(logn)。
## (4) 一个循环，每次i+2，常数忽略，复杂度O(n)。
## (5) 两个限制条件，复杂度O(min(n,k))，k太小了当常数也行。
## (6) 两层循环，相当于等差数列求和，1+2+3+4......复杂度O(n<sup>2</sup>)。
## (7) 不等式运算易得y<$\sqrt[3]{n}$，复杂度为O($\sqrt[3]{n}$)。
## (8) a[i]!=k条件不知何时满足，复杂度不确定。