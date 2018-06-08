class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> nums2(nums), res;
        sort(nums2.begin(), nums2.end());
        int i = 0, j = nums2.size()-1;
        while (nums2[i] + nums2[j] != target) {
            if (nums2[i] + nums2[j] < target) {
                ++i;
            } else if (nums2[i] + nums2[j] > target) {
                --j;
            }
        }
        for (int k = 0; k < nums.size(); ++k) {
            if (k == nums[i] || k == nums[j]) res.push_back(k);
        }
        return res;
	}
};

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
        unordered_set<int> dif;
        vector<int> res;
        for (int i = 0; i < nums; ++i) {
            if (dif.find(nums[i]) == dif.end()) {
                dif.push_back(target - nums[i]);
            } else {
                res.push_back(nums.find(target-nums[i]) - nums.begin());
                res.push_back(i);
                break;
            }
        }
        return res;
	}
};

















































































































































