#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <stack>

using namespace std;

const int INF = 0x3f3f3f3f;
const int BUFFER_SIZE = 100000;
const int MAX_N = 50000;
const int MAX_KEY_SIZE = 110;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c >= '0' && c <= '9') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

template<typename T>
T read(char *str,int start) {
    T result = 0;
    while(str[start] <= '9' && str[start] >= '0') {result = result * 10 + str[start] - '0'; start++;}
    return result;
}

template<typename T>
struct Stack {
    T *values;
    int tail;

    Stack(int size) {
        values = new T[size];
        tail = 0;
    }

    void push(T value) {
        values[tail++] = value;
    }

    T top() {
        return values[tail - 1];
    }

    void pop() {
        tail--;
    }

    int size() {
        return tail;
    }

    bool empty() {
        return tail == 0;
    }

    void clear() {
        tail = 0;
    }
};

struct Node {
    char key[MAX_KEY_SIZE];
    int priority;
    Node *childs[2];

    Node() : priority(INF) {
        key[0] = 0;
        childs[0] = NULL;
        childs[1] = NULL;
    }

    void updateValue(char *str,int size,int priority) {
        this->priority = priority;
        memcpy(key,str,sizeof(char) * size);
        key[size] = 0;
        childs[0] = NULL;
        childs[1] = NULL;
    }

    bool operator < (const Node &otherNode) const {
        return strcmp(key,otherNode.key) < 0;
    }

} nodes[MAX_N];

Node * buildTree(Node *nodes,int size,Stack<Node *> *stk) {
    Node *tmpRoot = new Node();
    stk->clear();
    stk->push(tmpRoot);
    for(int i = 0;i < size;i++) {
        Node *tmpNode = &nodes[i],*prev = NULL;
        while(stk->top()->priority < tmpNode->priority) {
            prev = stk->top();
            stk->pop();
        }
        if(prev != NULL) {
            tmpNode->childs[0] = prev;
        }
        stk->top()->childs[1] = tmpNode;
        stk->push(tmpNode);
    }
    return tmpRoot->childs[1];
}

void print(Node *now) {
    if(now == NULL) return;
    printf("(");
    print(now->childs[0]);
    printf("%s/%d",now->key,now->priority);
    print(now->childs[1]);
    printf(")");
}

int main() {
    int n;
    char *buffer = new char[BUFFER_SIZE];
    Stack<Node *> *stk = new Stack<Node *>(MAX_N);
    while((n = read<int>()) != 0) {
        for(int i = 0;i < n;i++) {
            scanf("%s",buffer);
            int pos = 0;
            while(buffer[pos] != '/') {
                pos++;
            }
            int priority = read<int>(buffer,pos + 1);
            nodes[i].updateValue(buffer,pos,priority);
        }
        sort(nodes,nodes + n);
        Node *root = buildTree(nodes,n,stk);
        print(root);
        printf("\n");
    }
    return 0;
}
