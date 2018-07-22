# 146. LRU Cache

## 1. 题目描述
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

### Follow up
Could you do both operations in O(1) time complexity?

### Example
```
LRUCache cache = new LRUCache( 2 /* capacity */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
```

## 2. 解题思路
题目要求在O(1)时间内完成LRU Cache，要支持put和get操作。LRU即Least Recently Use，缓存的大小是固定的，如果要往缓存中添加新的元素时缓存已经满了，则要把最近最少使用的元素清除，腾出空间给新的元素。

要在O(1)时间完成get和put，即要在O(1)时间进行查找，增加，和删除，这里自然会想到哈希表（unordered_map）。但是删除操作是要求存储容器维持一个顺序（LRU），这个是哈希做不到的。顺序+O(1)删除、增加=链表list。

结合哈希的O(1)查找和list的O(1)增加删除的方法是把指向list的元素的指针存进哈希中。（死活没想到...昏古奇）

### 3. Accepted Code
一开始用的STL list，总是报奇奇怪怪的编译错误，网上搜也搜索不到这个错误是什么意思，后来看别人的答案也用到了STL的list，才知道不是这个问题，只是眼花花犯了低级错误而已。
```cpp
class LRUCache {
public:
    LRUCache(int capacity) {
        size = capacity;
    }
    
    int get(int key) {
        int value = -1;
        if (ref.find(key) != ref.end()) {
            value = (*(ref[key])).second;
            store.erase(ref[key]);
            store.emplace_back(make_pair(key, value));
            ref[key] = --store.end();
        }
        return value;
    }
    
    void put(int key, int value) {
        if (ref.find(key) != ref.end()) {
            store.erase(ref[key]);
        }
        store.emplace_back(make_pair(key, value));
        ref[key] = --store.end();
        if (ref.size() > size) {
            ref.erase(ref.find(store.front().first));
            store.erase(store.begin());
        }
    }
private:
    int size;
    unordered_map<int, list<pair<int, int>>::iterator> ref;
    list<pair<int, int>> store;
};
```
在以为STL list不行的时候我还写了一个结构体版本的...
```cpp
struct Node {
    Node* prev;
    Node* next;
    int key;
    int value;
};

class LRUCache {
public:
    LRUCache(int capacity) {
        size = capacity;
        front = nullptr;
        back = nullptr;
    }

    void deleteElement(Node* node) {
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            front = node->next;
        }
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            back = node->prev;
        }
        delete(node);
    }

    void moveToBack(Node* node) {
        if (node->next != nullptr) {
            node->next->prev = node->prev;
            if (node->prev != nullptr) {
                node->prev->next = node->next;
            } else {
                front = node->next;
            }
            back->next = node;
            node->prev = back;
            node->next = nullptr;
            back = node;
        }
    }
    
    int get(int key) {
        int value = -1;
        if (ref.find(key) != ref.end()) {
            value = ref[key]->value;
            moveToBack(ref[key]);
        }
        return value;
    }
    
    void put(int key, int value) {
        if (ref.find(key) != ref.end()) {
            ref[key]->value = value;
            moveToBack(ref[key]);
        } else {
            Node *nodeptr = new Node{back, nullptr, key, value};
            if (back == nullptr) {
                back = nodeptr;
                front = nodeptr;
            } else {
                back->next = nodeptr;
                back = back->next;
            }
            ref[key] = nodeptr;
            if (ref.size() > size) {
                ref.erase(ref.find(front->key));
                deleteElement(front);
            }
        }
    }

private:
    Node* front;
    Node* back;
    int size;
    unordered_map<int, Node*> ref;
};
```

## 4. 坑与小笔记
### 1) 符号优先级
语句*(ref[key]).second报错（其中ref是unordered_map<int, list<pair<int, int>>::iterator），因为"."的优先级高于"\*"。这个要改成(\*(ref[key])).second

### 2) 迭代器运算
迭代器不支持运算符->，以及list的迭代器不支持算术运算以及关系运算，只能自增自减。

### 3) 迭代器失效
vector，deque是连续空间存储的，所以erase()操作会让指向erase的元素的后面的元素的iterator都失效。但是list和map不是连续空间存储的，所以erase操作只会让指向erase的元素的迭代器失效，但是指向其他元素的迭代器不会失效。

### 4) 用new来为结构体分配空间
在用struct实现的时候，我一开始是用Node node={back, nullptr, key, value}来创建新元素的，但是发现这样会导致每次调用put的时候创建的新元素都在同一个位置...因为离开了那个函数以后这个变量就被回收了，即使有指针指向它，那也是单方面的关系，指针失效了！所以这里应该要用new来创建（要记得和delete配套使用！！）才不会被回收。