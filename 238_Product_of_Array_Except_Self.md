# 238. Product of Array Except Self

## 1. 题目描述
Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

### Example
```
Input:  [1,2,3,4]
Output: [24,12,8,6]
```
Please solve it without division and in O(n).

Follow up：Could you solve it with constant space complexity?

## 2. 解题思路
不可以用除法，要求把每个位置的值变成除自己以外的其他所有数字的乘积（拗口100）。这道题以前做过，没想出来查了别人的做法，然后脑子里就只记得那个奇妙的递归方法，就是follow up里面要求的常数空间的解法，唯一庆幸的是这个还是记住了。

想法就是把计算除位置i以外的所有数字的乘积变为计算位置i左边的所有数的乘积，和位置i右边所有数的乘积。使用递归，到位置i时，接受左边的数的乘积作为输入，然后把左边的数的乘积乘上自己作为输出传递给位置i+1，得到的返回结果是位置i+1及以后所有数的乘积，把得到的乘积乘以自己返回给上一级。这样，从上级得到的输入和调用递归得到的返回结果相乘就是位置i的值，同时向左、右两边传递了自己本身的值。

## 3. Accepted Code
```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        cal(nums, 0, 1);
        return nums;
    }
private:
    // cur是位置index的左边所有值的乘积，对位置index+1调用这个函数得到的结果是位置index的右边所有值的乘积
    int cal(vector<int>& nums, int index, int cur) {
        int val = nums[index];
        if (index < nums.size() - 1) {
            int future = cal(nums, index + 1, cur * nums[index]);
            nums[index] = cur * future;
            return val * future;
        } else {
            nums[index] = cur;
            return val;
        }
    }
};
```

## 4. 其他解法
使用两个大小为n的数组，分别为left和right，存储i位置左边的数的乘积和i位置右边的数的乘积，然后只要把两个数组点乘就能得到答案。这需要两个循环来创建left和right，一个从前往后，一个从后往前。优化的方式是创建数组left以后，在返回的过程中用一个变量rp存储右边乘积来代替数组right，这样就只需要一个数组的空间。

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> left;
        int lp = 1, rp = 1;
        for (int i = 0; i < nums.size(); ++i) {
            left.push_back(lp);
            lp *= nums[i];
        }
        for (int i = nums.size() - 1; i >= 0; --i) {
            left[i] *= rp;
            rp *= nums[i];
        }
        return left;
    }
};
```