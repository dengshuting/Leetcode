# 566 Reshape the Matrix
## 1.题目描述
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum：

```
Input: [-2,1,-3,4,-1,2,1,-5,4],

Output: 6

Explanation: [4,-1,2,1] has the largest sum = 6.
```

## 2.题目分析
题目要求得出和最大的子数组并返回这个最大值。感觉和121. Best Time to Buy and Sell Stock 差不多。解题思路是遍历数组，用一个变量cur来记录当前子数组的和。划分子数组的依据是如果遍历到元素k时，(cur + k) <= k，代表之前的结果对于增加cur是无用的，所以抛弃之前的结果。在遍历的过程中用一个值max来记录过程中最大的cur值，也就是最大的子数组和。时间复杂度O(N)。

## 3.Accpted Code
```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int cur = 0, max;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] + cur <= nums[i]) {
                cur = nums[i];
            } else {
                cur += nums[i];
            }
            if (i == 0) max = nums[i];
            else max = cur > max ? cur : max;
        }
        return max;
    } 
};
```

## 4.Consider more
If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.

用分治法解决。动态规划，暂时还没想到。