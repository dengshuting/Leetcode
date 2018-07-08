# 1. Two Sum

## 1. 题目描述

Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

### Example
```
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
```

## 2. 题目分析
使用哈希表来达到O(n)时间O(n)空间。

## 3. Accepted Code
``` cpp
class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
        unordered_set<int> dif;
        vector<int> res;
        for (int i = 0; i < nums.size(); ++i) {
            if (dif.find(nums[i]) == dif.end()) {
                dif.insert(target - nums[i]);
            } else {
                for (int j = 0; j < nums.size(); ++j) {
                    if (nums[j] == target-nums[i]) {
                        res.push_back(j);
                        break;
                    }
                }
                res.push_back(i);
                break;
            }
        }
        return res;
	}
};
```