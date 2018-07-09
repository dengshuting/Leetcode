# 13. Roman to Integer

## 1. 题目说明
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

For example, two is written as II in Roman numeral, just two one's added together. Twelve is written as, XII, which is simply X + II. The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 

X can be placed before L (50) and C (100) to make 40 and 90. 

C can be placed before D (500) and M (1000) to make 400 and 900.

Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.

## 2. 解题思路
题目要求把罗马数字转为integer。罗马数字其实只有7个标志，表示1， 5， 10， 50， 100， 500， 1000。每个数字其实就是每个标志表示的数字的相加，字符的排列是按照其代表的数字从大到小的顺序，其中1， 10， 100可以放在一个数字前面来代表4X或者9X。所以问题就是简单的把字符对应成数字相加起来，唯一要注意的是如果有小的字符在大的字符前面的话，应该是减去小的字符。

## 3. Accepted Code
```cpp
// 44ms
class Solution {
public:
    int romanToInt(string s) {
        int sum = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (i < s.size() - 1 && mapInt(s[i]) < mapInt(s[i+1])) {
                sum -= mapInt(s[i]);
            } else {
                sum += mapInt(s[i]);
            }
        }
        return sum;
    }
private:
    int mapInt(char c) {
        int num;
        if (c == 'I') {
            num = 1;
        } else if (c == 'V') {
            num = 5;
        } else if (c == 'X') {
            num = 10;
        } else if (c == 'L') {
            num = 50;
        } else if (c == 'C') {
            num = 100;
        } else if (c == 'D') {
            num = 500;
        } else if (c == 'M') {
            num = 1000;
        }
        return num;
    }
};
```

## 4. 更快的方法
从100%上面看到的解法，跟我的不同是我是另外写了一个函数来进行字符转数字，这里是用了哈希map来存储这个转换，这里体现了哈希的优势。
```cpp
static auto x = [](){
    // turn off sync
    std::ios::sync_with_stdio(false);
    // untie in/out streams
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    
    int romanToInt(string s) {
        int result = 0;
        
        std::unordered_map<char, int> r2i({
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        });
        int len = s.size();
        for (int i=0; i<len; i++)
        {
            if (i != len-1 && r2i[s[i]] < r2i[s[i+1]])
                result -= r2i[s[i]];
            else
                result += r2i[s[i]];
        }
        return result;
    }
};
```