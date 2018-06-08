class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int cur = 0, max = -9999;
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