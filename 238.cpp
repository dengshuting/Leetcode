class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        cal(nums, 0, 1);
        return nums;
    }
private:
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

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        calc(nums, 1, 0);
        return nums;
    }
private:
    int calc(vector<int>& nums, int left, int index) {
        int right = 1;
        if (index < nums.size()) {
            right = calc(nums, left * nums[index], index + 1);
            int tmp = nums[index];
            nums[index] = left * right;
            right *= tmp;
        }
        return right;
    }
        
};