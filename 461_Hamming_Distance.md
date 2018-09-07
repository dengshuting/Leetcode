# 461. Hamming Distance

## 1. 题目描述
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given two integers x and y, calculate the Hamming distance.

**Note:**

0 \leq x, y \leq 2<sup>31</sup>

**Example:**

```
Input: x = 1, y = 4

Output: 2

Explanation:

1 (0 0 0 1)
4 (0 1 0 0)
     ↑   ↑

The above arrows point to positions where the corresponding bits are different.
```

## 2. 解题思路
要计算两个数字的不同的bit的个数，先用异或把不同的bit全部找出，变成1，然后再计算1的个数。

## 3. Accepted Code
```cpp
// 4ms
class Solution {
public:
    int hammingDistance(int x, int y) {
        int toCnt = x ^ y, cnt = 0, mask = 1;
        while (toCnt > 0) {
            if (toCnt & mask) ++cnt;
            toCnt >>= 1;
        }
        return cnt;
    }
};
```

## 4. 其他count 1 bits的方法
问题已经转换成为计算1的个数，上面用了最最最普通的办法，就是一个一个计算，这样速度比较慢。https://www.cnblogs.com/graphics/archive/2010/06/21/1752421.html 列出了很多不同的方法，继续学习！