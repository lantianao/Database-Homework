#include<iostream>
#include<map>
#include<deque>
using namespace std;
struct Node
{
    int key;
    int value;
    Node* pre;
    Node* next;
    Node(int key, int value) : key(key), value(value), pre(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int size;// 缓冲区大小
    Node* head;
    Node* tail;
    map<int, Node*> p;

public:
    // 删除当前节点
    void remove(Node* cur)
    {
        if (cur == head)
            head = cur->next;
        else if (cur == tail)
            tail = cur->pre;
        else
        {
            cur->pre->next = cur->next;
            cur->next->pre = cur->pre;
        }
    }
    // 将当前节点插入到头部
    void setHead(Node* cur)
    {
        cur->next = head;
        if (head != nullptr)
            head->pre = cur;
        head = cur;

        if (tail == nullptr)
            tail = head;
    }

    LRUCache(int capacity) {
        this->size = capacity;
        head = nullptr;
        tail = nullptr;
    }
    // 获取缓冲区中 key 对应的 value
    int get(int key) {
        // 1.当该 key 值存在
        if (p.count(key) > 0)
        {
            Node* cur = p[key];
            int value = cur->value;
            remove(cur);   // 这里仅仅删除哈希双向链表中的节点，不必删除哈希表中的                 
            // 将节点重现插入到缓冲区的头部
            setHead(cur);
            return value;
        }
        // 2.当该 key 值不存在
        return -1;
    }
    // 将key-value值存入缓冲区
    void put(int key, int value) {
        // 1.当该 key 值存在
        if (p.count(key) > 0)//查看是否存在
        {
            // 删除该 key 对应的原来节点
            Node* cur = p[key];
            cur->value = value;
            remove(cur);    // 这里仅仅删除双向链表中的节点，不必删除哈希表中的                                
            setHead(cur);
        }
        else// 2.当该 key 值不存在
        {
            Node* node = new Node(key, value);
            if (p.size() >= size)
            {
                // 删除尾部节点,哈希表及双向链表均需移除
                map<int, Node*>::iterator it = p.find(tail->key);
                remove(tail);
                p.erase(it);
            }
            //else 此时因为动作和上面重复，所以直接合并使用
            //还没有满：将新节点插入到缓冲区的头部
            {
                setHead(node);
                p[key] = node;
            }
        }
    }
    void print() {
        for (auto it = p.begin(); it != p.end(); it++) {
            cout << it->first << " " << it->second->key<<' '<<it->second->value << endl;
        }
    }
    
};

int main() {
    LRUCache lRUCache = LRUCache(2);
    lRUCache.put(1, 1); // 缓存是 {1=1}
    lRUCache.print();
    lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
    lRUCache.print();
    lRUCache.get(1);    // 返回 1
    lRUCache.print();
    lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    lRUCache.print();
    lRUCache.get(2);    // 返回 -1 (未找到)
    lRUCache.print();
    lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    lRUCache.print();
    lRUCache.get(1);    // 返回 -1 (未找到)
    lRUCache.print();
    lRUCache.get(3);    // 返回 3
    lRUCache.print();
    lRUCache.get(4);    // 返回 4
    lRUCache.print();
    return 0;
}