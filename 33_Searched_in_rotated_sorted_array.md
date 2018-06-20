# 33. Search in Rotated Sorted Array

## 1. 题目描述
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of O(log n).

### Example 1:

```
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4
```

### Example 2:
```
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
```

## 2. 题目分析
二分查找，感觉比153. Find Minimum in Rotated Sorted Array难，因为要同时考虑target值和mid值。

我的分类方法是：
1. 先总的分成数列有翻转和数列没有翻转两类，用nums[l]与nums[r]的值对比来判定。

2. 对于数列没有翻转的情况，就使用正常的二分查找。

3. 对于数列翻转了的情况，再分别判断nums[mid]和target的相对位置来进行二分查找。


## 3. Accepted Code
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.size() == 0) return -1;
        int l = 0, r = nums.size() - 1, idx = -1;
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            if (nums[l] > nums[r]) {
                if (nums[mid] > nums[l]) {
                    if (nums[l] <= target && target < nums[mid]) r = mid;
                    else l = mid;
                } else {
                    if (nums[mid] < target && target <= nums[r]) l = mid;
                    else r = mid;
                }
            } else {
                if (nums[l] < target && target <= nums[mid]) {
                    r = mid;
                } else if (nums[mid] < target && target < nums[r]) {
                    l = mid;
                } else {
                    break;
                } 
            }
        }
        if (nums[l] == target) idx = l;
        if (nums[r] == target) idx = r;
        return idx;
    }
};
```