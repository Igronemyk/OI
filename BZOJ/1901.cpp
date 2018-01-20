#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int MAX_VAL_RANGE = 1e9;

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
        int val,cnt,size;
        Node() : father(NULL) ,val(-1) , cnt(-1) , size(-1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }
        Node(Node *father,int val) : father(father) , val(val) , cnt(1) , size(1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }
    };

    Node *root;

    Splay() : root(NULL) { }


    void rotate(Node *now,int direction) {
        Node *fa = now->father,*anc = fa->father;
        now->father = anc;
        fa->father = now;
        if(anc != NULL) {
            anc->childs[anc->childs[1] == fa] = now;
        }
        fa->childs[!direction] = now->childs[direction];
        if(fa->childs[!direction] != NULL) {
            fa->childs[!direction]->father = fa;
        }
        now->childs[direction] = fa;
        if(root == fa) {
            root = now;
        }
        updateInfo(fa);
        updateInfo(now);
    }

    void splay(Node *now,Node *dist) {
        if(now == NULL || now == dist) return;
        while(now->father != dist) {
            if(now->father->father == dist) {
                rotate(now,now->father->childs[0] == now);
            }else {
                Node *fa = now->father,*anc = fa->father;
                if(anc->childs[0] == fa) {
                    if(fa->childs[0] == now) {
                        rotate(fa,1);
                        rotate(now,1);
                    }else {
                        rotate(now,0);
                        rotate(now,1);
                    }
                }else {
                    if(fa->childs[0] == now) {
                        rotate(now,1);
                        rotate(now,0);
                    }else {
                        rotate(fa,0);
                        rotate(now,0);
                    }
                }
            }
        }
    }

    Node * search(int key) {
        if(root == NULL) return NULL;
        Node *now = root,*result = NULL;
        while(true) {
            if(now->val > key) {
                if(now->childs[0] != NULL) {
                    now = now->childs[0];
                }else {
                    break;
                }
            }else if(now->val < key) {
                if(now->childs[1] != NULL) {
                    now = now->childs[1];
                }else {
                    break;
                }
            }else {
                result = now;
                break;
            }
        }
        splay(now,NULL);
        return result;
    }

    Node * searchMin(Node *now) {
        Node *father = now->father;
        while(now->childs[0] != NULL) {
            now = now->childs[0];
        }
        splay(now,father);
        return now;
    }

    Node *searchMax(Node *now) {
        Node *father = now->father;
        while(now->childs[1] != NULL) {
            now = now->childs[1];
        }
        splay(now,father);
        return now;
    }

    void insert(int key) {
        if(root == NULL) {
            root = new Node(NULL,key);
            return;
        }
        Node *now = root,*result = NULL;
        while(true) {
            if(now->val > key) {
                if(now->childs[0] == NULL) {
                    now->childs[0] = new Node(now,key);
                    result = now->childs[0];
                    break;
                }else {
                    now = now->childs[0];
                }
            }else if(now->val < key) {
                if(now->childs[1] == NULL) {
                    now->childs[1] = new Node(now,key);
                    result = now->childs[1];
                    break;
                }else {
                    now = now->childs[1];
                }
            }else {
                now->cnt++;
                result = now;
                break;
            }
        }
        splay(result,NULL);
    }

    void remove(int key) {
        if(root == NULL) return;
        Node *now = search(key);
        if(now == NULL) return;
        if(now->cnt > 1) {
            now->cnt--;
            updateInfo(now);
            return;
        }
        if(now->childs[0] == NULL && now->childs[1] == NULL) {
            root = NULL;
            return;
        }
        if(now->childs[0] == NULL && now->childs[1] != NULL) {
            root = now->childs[1];
            now->childs[1]->father = NULL;
            return;
        }
        if(now->childs[0] != NULL && now->childs[1] == NULL) {
            root = now->childs[0];
            now->childs[0]->father = NULL;
            return;
        }
        Node *newNode = searchMin(now->childs[1]);
        newNode->father = NULL;
        newNode->childs[0] = now->childs[0];
        newNode->childs[0]->father = newNode;
        root = newNode;
        updateInfo(newNode);
    }

    int lessThan(int key) {
        if(root == NULL) return -1;
        Node *now = search(key);
        if(now != NULL) {
            return size(now->childs[0]);
        }
        if(root->val < key) {
            return root->cnt + size(root->childs[0]);
        }else {
            return size(root->childs[0]);
        }
    }

    int findKth(int rank) {
        if(root == NULL || rank > root->size) return -1;
        Node *now = root;
        while(true) {
            if(rank >= size(now->childs[0]) + 1 && rank <= size(now->childs[0]) + now->cnt) {
                break;
            }else if(rank <= size(now->childs[0])) {
                now = now->childs[0];
            }else {
                rank -= size(now->childs[0]) + now->cnt;
                now = now->childs[1];
            }
        }
        splay(now,NULL);
        return now->val;
    }

    int getPrecursor(int key) {
        Node *now = search(key);
        if(now != NULL) {
            Node *precursor = searchMax(now->childs[0]);
            return precursor->val;
        }
        if(root->val > key) {
            Node *precursor = searchMax(root->childs[0]);
            return precursor->val;
        }
        return root->val;
    }

    int getSuccessor(int key) {
        Node *now = search(key);
        if(now != NULL) {
            Node *successor = searchMin(now->childs[1]);
            return successor->val;
        }
        if(root->val < key) {
            Node *successor = searchMin(root->childs[1]);
            return successor->val;
        }
        return root->val;
    }

    void updateInfo(Node *now) {
        now->size = size(now->childs[0]) + size(now->childs[1]) + now->cnt;
    }

    int size(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    void print() {
        print(root);
    }

    void print(Node *now) {
        if(now == NULL) return;
        print(now->childs[0]);
        cout << now->val << endl;
        print(now->childs[1]);
    }

    int size() {
        return size(root);
    }

};

struct SegmentTree {
    struct Node {
        int left,right;
        Node *leftChild,*rightChild;
        Splay *splay;
        Node() : left(-1) , right(-1) , leftChild(NULL) , rightChild(NULL) , splay(NULL) { }
        Node(int left,int right) : left(left) , right(right) , leftChild(NULL) , rightChild(NULL) {
            splay = new Splay();
        }

        bool isLeafNode() {
            return left == right;
        }

    };

    Node *root;

    SegmentTree(int size) {
        root = new Node(0,size - 1);
        build(root);
    }

    void build(Node *now) {
        if(now->isLeafNode()) {
            return;
        }
        int mid = (now->left + now->right) >> 1;
        now->leftChild = new Node(now->left,mid);
        build(now->leftChild);
        now->rightChild = new Node(mid + 1,now->right);
        build(now->rightChild);
    }

    void update(int pos,int val) {
        update(root,pos,val);
    }

    void update(Node *now,int pos,int val) {
        now->splay->insert(val);
        if(now->isLeafNode()) {
            return;
        }
        int mid = (now->left + now->right) >> 1;
        if(pos <= mid) {
            update(now->leftChild,pos,val);
        }else {
            update(now->rightChild,pos,val);
        }
    }

    void remove(int pos,int val) {
        remove(root,pos,val);
    }

    void remove(Node *now,int pos,int val) {
        now->splay->remove(val);
        if(now->isLeafNode()) {
            return;
        }
        int mid = (now->left + now->right) >> 1;
        if(pos <= mid) {
            remove(now->leftChild,pos,val);
        }else {
            remove(now->rightChild,pos,val);
        }
    }

    int queryLessThan(int left,int right,int value) {
        return queryLessThan(root,left,right,value);
    }

    int queryLessThan(Node *now,int left,int right,int value) {
        if(now->left == left && now->right == right) {
            return now->splay->lessThan(value);
        }
        int mid = (now->left + now->right) >> 1;
        if(right <= mid) {
            return queryLessThan(now->leftChild,left,right,value);
        }else {
            if(left > mid) {
                return queryLessThan(now->rightChild,left,right,value);
            }else {
                return queryLessThan(now->leftChild,left,mid,value) + queryLessThan(now->rightChild,mid + 1,right,value);
            }
        }
    }
};

int main() {
    int n = read<int>(),m = read<int>();
    SegmentTree stree(n);
    int *values = new int[n];
    for(int i = 0;i < n;i++) {
        values[i] = read<int>();
        stree.update(i,values[i]);
    }
    char *buffer = new char[2];
    while(m--) {
        scanf("%s",buffer);
        switch(buffer[0]) {
            case 'Q': {
                int left = read<int>(),right = read<int>(),rank = read<int>();
                left--; right--;
                int result = 0,begin = 0,end = MAX_VAL_RANGE;
                while(begin <= end) {
                    int mid = (begin + end) >> 1,checkValue = stree.queryLessThan(left,right,mid);
                    if(checkValue <= rank - 1) {
                        result = mid;
                        begin = mid + 1;
                    }else {
                        end = mid - 1;
                    }
                }
                printf("%d\n",result);
                break;
            }
            case 'C': {
                int pos = read<int>(),value = read<int>();
                pos--;
                stree.remove(pos,values[pos]);
                stree.update(pos,value);
                values[pos] = value;
                break;
            }
        }
    }
    return 0;
}
