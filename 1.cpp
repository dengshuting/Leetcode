class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> nums2(nums), res;
        sort(nums2.begin(), nums2.end());
        int i = 0, j = nums2.size()-1;
        while (nums2[i] + nums2[j] != target) {
            if (nums2[i] + nums2[j] < target) {
                ++i;
            } else {
                --j;
            }
        }
        for (int k = 0; k < nums.size(); ++k) {
            if (nums[k] == nums2[i] || nums[k] == nums2[j]) res.push_back(k);
        }
        return res;
	}
};
