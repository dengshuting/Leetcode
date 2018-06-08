#153. Find Minimum in Rotated Sorted Array
## 1. 题目描述
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).

Find the minimum element.

You may assume no duplicate exists in the array.

```
Example 1:
Input: [3,4,5,1,2] 
Output: 1

Example 2:
Input: [4,5,6,7,0,1,2]
Output: 0
```

## 2. 题目分析
二分查找，因为题目中说明没有重复的元素，所以也不用考虑。判定条件nums[mid] > nums[left] && nums[mid] > nums[right]是因为侧例里面有没有进行翻转，就是完全按照顺序排列的情况。

## 3. Accepted Code
```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int min, left = 0, right = nums.size() - 1;
        while (right > left + 1) {
            int mid = (left + right) / 2;
            if (nums[mid] > nums[left] && nums[mid] > nums[right]) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return nums[right] < nums[left] ? nums[right] : nums[left];
    }
};
```