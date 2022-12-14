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
    int size;// ��������С
    Node* head;
    Node* tail;
    map<int, Node*> p;

public:
    // ɾ����ǰ�ڵ�
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
    // ����ǰ�ڵ���뵽ͷ��
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
    // ��ȡ�������� key ��Ӧ�� value
    int get(int key) {
        // 1.���� key ֵ����
        if (p.count(key) > 0)
        {
            Node* cur = p[key];
            int value = cur->value;
            remove(cur);   // �������ɾ����ϣ˫�������еĽڵ㣬����ɾ����ϣ���е�                 
            // ���ڵ����ֲ��뵽��������ͷ��
            setHead(cur);
            return value;
        }
        // 2.���� key ֵ������
        return -1;
    }
    // ��key-valueֵ���뻺����
    void put(int key, int value) {
        // 1.���� key ֵ����
        if (p.count(key) > 0)//�鿴�Ƿ����
        {
            // ɾ���� key ��Ӧ��ԭ���ڵ�
            Node* cur = p[key];
            cur->value = value;
            remove(cur);    // �������ɾ��˫�������еĽڵ㣬����ɾ����ϣ���е�                                
            setHead(cur);
        }
        else// 2.���� key ֵ������
        {
            Node* node = new Node(key, value);
            if (p.size() >= size)
            {
                // ɾ��β���ڵ�,��ϣ��˫����������Ƴ�
                map<int, Node*>::iterator it = p.find(tail->key);
                remove(tail);
                p.erase(it);
            }
            //else ��ʱ��Ϊ�����������ظ�������ֱ�Ӻϲ�ʹ��
            //��û���������½ڵ���뵽��������ͷ��
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
    lRUCache.put(1, 1); // ������ {1=1}
    lRUCache.print();
    lRUCache.put(2, 2); // ������ {1=1, 2=2}
    lRUCache.print();
    lRUCache.get(1);    // ���� 1
    lRUCache.print();
    lRUCache.put(3, 3); // �ò�����ʹ�ùؼ��� 2 ���ϣ������� {1=1, 3=3}
    lRUCache.print();
    lRUCache.get(2);    // ���� -1 (δ�ҵ�)
    lRUCache.print();
    lRUCache.put(4, 4); // �ò�����ʹ�ùؼ��� 1 ���ϣ������� {4=4, 3=3}
    lRUCache.print();
    lRUCache.get(1);    // ���� -1 (δ�ҵ�)
    lRUCache.print();
    lRUCache.get(3);    // ���� 3
    lRUCache.print();
    lRUCache.get(4);    // ���� 4
    lRUCache.print();
    return 0;
}