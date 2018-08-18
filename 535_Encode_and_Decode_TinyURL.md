# 535. Encode and Decode TinyURL

## 1. 题目描述
TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.

Design the encode and decode methods for the TinyURL service. There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.

## 2. 解题思路
看了https://leetcode.com/discuss/interview-question/124658/Design-a-URL-Shortener-(-TinyURL-)-System/ 里面的内容，根据里面给出的解法来解。

TinyURL问题的关键是：
* TinyURL的字符数量
* one-to-one且可逆

对于字符数量的问题，假设使用大小写字母+数字来作为TinyURL的字符（共62个），则TinyURL需要n个字符，其中62^n要大于originalURL的数量。

这里做到one-to-one的方法是给每个要转换的originalURL分配一个逐步增加的ID，然后保存一个（ID, OriginalURL)的对应关系，再用函数进行ID和TinyURL之间的相互转换。转换方法其实就是62进制到19进制的转换，62进制的表达即是TinyURL，这样就做到了one-to-one以及可逆。

## 3. Accepted Code
```cpp
// 8ms
class Solution {
public:

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        int id = idToLong.size();
        idToLong[id] = longUrl;
        return idToShort(id);
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return idToLong[shortToId(shortUrl)];
    }
private:
    unordered_map<int, string> idToLong;
    
    int shortToId(string shortUrl) {
        const int base = 62;
        int idx = 1;
        int id = 0;
        for (int i = 0; i < shortUrl.size(); ++i) {
            char tmp = shortUrl[i];
            if (tmp - 'a' >= 0) {
                id += idx * (tmp - 'a');
            } else if (tmp - 'A' >= 0) {
                id += idx * (tmp - 'A' + 26);
            } else if (tmp - '0' >= 0) {
                id += idx * (tmp - '0' + 52);
            }
            idx *= base;
        }
        return id;
    }
    
    string idToShort(int id) {
        string cipherTable = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        string shortUrl;
        const int base = 62;
        while (id) {
            shortUrl += cipherTable[id % base];
            id /= base;
        }
        return shortUrl;
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
```

