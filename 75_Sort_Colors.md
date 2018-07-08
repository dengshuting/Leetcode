# 75. Sort Colors

## 1. 题目描述

Given an array with n objects colored red, white or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note: You are not suppose to use the library's sort function for this problem.

### Example:
```
Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
```

### Follow up:
A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.

Could you come up with a one-pass algorithm using only constant space?

## 2. 解题思路
题目要求常数空间解决，还要求一遍过，因为整个数组就只有3个数字：0， 1， 2，所以就想只要把所有的0放到左边，所有的2放到右边即可。在这里我维持了3个指针，第一个指针指front向左边第一个非0的数，第二个指针back指向右边第一个非2的数（注意front左边和back右边的数都已经在对的位置上了，无需再进行操作），还有一个指针move起始于front，作用是找到0，和front对换位置；找到2，和back对换位置；找到1，则向前移动，直到所有数字都已经排完（move > back）。

要注意的是move指向的数字经过了一次调换以后未必就完全可以了，参考测试例子[1, 2, 0]。此时，front = 1, back = 0, move = 2。move应该和back交换，得到[1, 0, 2]。此时如果move向前移动了，则排序终止，未得到正确答案，所以基于此时move指向的是0，应该和front调换位置，然后move指向1，向前移动，排序结束。总的来说，move的作用是把遇到的所有0和2送到正确的位置，front和back则标记了“正确的位置”。

## 3. Accepted Code
```cpp
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int front = 0, move = 0, back = nums.size() - 1;
        while (nums[front] == 0) ++front;
        while (nums[back] == 2) --back;
        move = front;
        while (move <= back) {
            if (nums[move] == 0) {
                int tmp = nums[front];
                nums[front] = 0;
                nums[move] = tmp;
            } else if (nums[move] == 2) {
                int tmp = nums[back];
                nums[back] = 2;
                nums[move] = tmp;
            } else {
                ++move;
                continue;
            }
            while (nums[front] == 0) ++front;
            while (nums[back] == 2) --back;
            move = front;
        }
    }
};
```

## 3. 更漂亮的写法

自己解题的时候就像是有了目标和大概想法，然后生拼硬凑出的解法，遇到不过的时候再研究不过的到底是因为什么原因，然后一点一点打补丁。

看了0ms的其他解法，感觉比我的漂亮不是一点点。对于我曾经出错的那个问题的解决这里用了当move遇到1或者move跟0交换过的话都可以前进，因为未归位的2以后还可以遇到，到时候再处理；而如果move在交换过后指向的是0，则move不能前进，因为没有机会再对这个0进行操作了。

同时，这个写法没有跳过已经位置正确的0和2这个过程，时间消耗应该没有差很多，但是代码却简洁了不少。不过我没有这么做更大的原因还是因为脑子没有捋清楚，不知道跳过这个会不会出错，就干脆多写了。

```cpp
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int st = 0, ed = nums.size() - 1;
        for(int i = 0; i <= ed; ++i) {
            if(nums[i] == 0) swap(nums, i, st++);
            else if(nums[i] == 2) swap(nums, i--, ed--);
        }
    }
    void swap(vector<int>& nums, int a, int b) {
        int tmp = nums[a];
        nums[a] = nums[b];
        nums[b] = tmp;
    }
};
```

## 4. 其他解法

也就是Follow up里面提到的counting sort。数组里面只存在0， 1， 2三个数字，所以只需要遍历一遍记录下有多少个0， 1， 2，然后再在第二遍遍历的时候按照计数往数组里面填数即可。我觉得我应该是想不出来的....
```cpp
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int zero = 0, one = 0, two = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0) ++zero;
            if (nums[i] == 1) ++one;
            if (nums[i] == 2) ++two;
        }
        int k = 0;
        while (zero--) nums[k++] = 0;
        while (one--) nums[k++] = 1;
        while (two--) nums[k++] = 2;
    }
};
```

## 5. 总结

1. 遇到不止一次需要交换的时候要另外写一个swap函数。

2. 我的代码里面频繁出现while (nums[front] == 0) ++front;这样的语句，而且在同一段代码里面还会重复出现，这可能是一个思维的问题，要想办法转变过来，善用++和--。

3. 做题的时候要避免填填补补，要在一开始想清楚。