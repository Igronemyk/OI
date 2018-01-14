#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstddef>

using namespace std;

const int INF = 0x3f3f3f3f;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Splay {
    struct Node {
        Node *father,*childs[2];
        int value,changeValue,size;
        int leftMaxValue,rightMaxValue,maxValue,sumValue;
        bool rev;

        Node(Node *father,int value) : father(father) , value(value) , changeValue(INF) , size(1) , leftMaxValue(max(0,value)),  rightMaxValue(max(0,value)) , maxValue(value) , sumValue(value) , rev(false) {
            childs[0] = NULL;
            childs[1] = NULL;
        }
    };

    Node *root;

    Splay() {
        root = NULL;
    }

    void updateInfo(Node *now) {
        //TODO
    }

    void rotate(Node *now) {
        Node *father = now->father,*anc = father->father;
        if(anc != NULL) {
            anc->childs[anc->childs[1] == father] = now;
        }
        now->father = anc;
        father->father = now;
        int direction = father->childs[0] == now;
        father->childs[!direction] = now->childs[direction];
        now->childs[direction] = father;
        if(father->childs[!direction] != NULL) {
            father->childs[direction]->father = father;
        }
        updateInfo(father);
        updateInfo(now);
        if(father == root) {
            root = now;
        }
    }

    void splay(Node *now) {
        splay(now,NULL);
    }

    void splay(Node *now,Node *dist) {
        if(now == NULL || now == dist) return;
        while(now->father != dist) {
            pushDown(now);
            Node *father = now->father,*anc = father->father;
            if(father != dist) {
                if((anc->childs[0] == father) ^(father->childs[0] == now)) {
                    rotate(now);
                }else {
                    rotate(father);
                }
            }
            rotate(now);
        }
    }

    void pushDown(Node *now) {
        //TODO
    }

    void updateReverseTag(Node *now) {
        //TODO
    }

    void updateChangeTag(Node *now,int tag) {
        //TODO
    }

    Node *getKth(int rank) {
        //TODO
    }

    int getSum(int left,int right) {
        //TODO
    }

    void insert(int x,int y,int *values) {

    }

    void remove(int left,int right) {
        //TODO
    }

    void reverse(int left,int right) {
        //TODO
    }

    int getMaxSum() {
        //TODO
    }

    static Node *buildTree(int left,int right,int *values) {
        return buildTree(NULL,left,right,values);
    }

    static Node * buildTree(Node *father,int left,int right,int *values) {
        int mid = (left + right) >> 1;
        Node *now = new Node(father,values[mid]);
        if(left == right) return now;
        now->childs[0] = buildTree(now,left,mid,values);
        now->childs[1] = buildTree(now,mid + 1,right,values);
        return now;
    }
};

int main() {
    abcdefg
    return 0;
}
