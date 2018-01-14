#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstddef>

using namespace std;

const int INF = 0x3f3f3f3f;
const int BUFFER_SIZE = 10;
const int MAX_VAL_CNT = 4000001;
const char * OPT_INSERT = "INSERT";
const char * OPT_DELETE = "DELETE";
const char * OPT_MAKE_SAME = "MAKE-SAME";
const char * OPT_REVERSE = "REVERSE";
const char * OPT_GET_SUM = "GET-SUM";
const char * OPT_MAX_SUM = "MAX-SUM";

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int getOperatorSign(char *str) {
    if(strcmp(str,OPT_INSERT) == 0) {
        return 0;
    }
    if(strcmp(str,OPT_DELETE) == 0) {
        return 1;
    }
    if(strcmp(str,OPT_MAKE_SAME) == 0) {
        return 2;
    }
    if(strcmp(str,OPT_REVERSE) == 0) {
        return 3;
    }
    if(strcmp(str,OPT_GET_SUM) == 0) {
        return 4;
    }
    if(strcmp(str,OPT_MAX_SUM) == 0) {
        return 5;
    }
    return -1;
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

        ~Node() {
            if(childs[0] != NULL) {
                delete childs[0];
            }
            if(childs[1] != NULL) {
                delete childs[1];
            }
        }
    };

    Node *root;

    Splay() {
        root = NULL;
    }

    static void updateInfo(Node *now) {
        now->size = getSize(now->childs[0]) + getSize(now->childs[1]) + 1;
        now->leftMaxValue = max(getLeftMaxValue(now->childs[0]),getSumValue(now->childs[0]) + now->value + getLeftMaxValue(now->childs[1]));
        now->rightMaxValue = max(getRightMaxValue(now->childs[1]),getSumValue(now->childs[1]) + now->value + getRightMaxValue(now->childs[0]));
        now->maxValue = max(max(getMaxValue(now->childs[0]),getMaxValue(now->childs[1])),getRightMaxValue(now->childs[0]) + now->value + getLeftMaxValue(now->childs[1]));//TODO
        now->sumValue = getSumValue(now->childs[0]) + getSumValue(now->childs[1]) + now->value;
    }

    static int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    static int getChangeValue(Node *now) {
        if(now == NULL) return INF;
        return now->changeValue;
    }

    static int getLeftMaxValue(Node *now) {
        if(now == NULL) return 0;
        return now->leftMaxValue;
    }

    static int getRightMaxValue(Node *now) {
        if(now == NULL) return 0;
        return now->rightMaxValue;
    }

    static int getMaxValue(Node *now) {
        if(now == NULL) return -INF;
        return now->maxValue;
    }

    static int getSumValue(Node *now) {
        if(now == NULL) return 0;
        return now->sumValue;
    }

    void rotate(Node *now) {
        Node *father = now->father,*anc = father->father;
        pushDown(father);
        pushDown(now);
        if(anc != NULL) {
            anc->childs[anc->childs[1] == father] = now;
        }
        now->father = anc;
        father->father = now;
        int direction = father->childs[0] == now;
        father->childs[!direction] = now->childs[direction];
        now->childs[direction] = father;
        if(father->childs[!direction] != NULL) {
            father->childs[!direction]->father = father;
        }
        if(now->father == NULL) {
            root = now;
        }
        updateInfo(father);
        updateInfo(now);
    }

    void splay(Node *now) {
        splay(now,NULL);
    }

    void splay(Node *now,Node *dist) {
        if(now == NULL || now == dist) return;
        while(now->father != dist) {
            Node *father = now->father,*anc = father->father;
            if(anc != dist) {
                if((anc->childs[0] == father) ^(father->childs[0] == now)) {
                    rotate(now);
                }else {
                    rotate(father);
                }
            }
            rotate(now);
        }
    }

    static void pushDown(Node *now) {
        if(now->changeValue != INF) {
            now->rev = false;
            updateChangeTag(now->childs[0],now->changeValue);
            updateChangeTag(now->childs[1],now->changeValue);
            now->changeValue = INF;
        }
        if(now->rev) {
            now->rev = false;
            updateReverseTag(now->childs[0]);
            updateReverseTag(now->childs[1]);
        }
        updateInfo(now);
    }

    static void updateReverseTag(Node *now) {
        if(now == NULL) return;
        if(now->changeValue != INF) return;
        now->rev = !now->rev;
        swap(now->childs[0],now->childs[1]);
        swap(now->leftMaxValue,now->rightMaxValue);
    }

    static void updateChangeTag(Node *now,int tag) {
        if(now == NULL) return;
        now->changeValue = tag;
        now->value = tag;
        int calSumValue = now->size * tag;
        now->sumValue = calSumValue;
        if(tag >= 0) {
            now->leftMaxValue = calSumValue;
            now->rightMaxValue = calSumValue;
            now->maxValue = calSumValue;
        }else {
            now->leftMaxValue = 0;
            now->rightMaxValue = 0;
            now->maxValue = tag;
        }
    }

    Node *getKth(int rank) {
        Node *now = root,*prev = NULL;
        while(now != NULL) {
            prev = now;
            int leftChildSize = getSize(now->childs[0]);
            if(leftChildSize < rank) {
                rank -= leftChildSize + 1;
                now = now->childs[1];
            }else if(leftChildSize > rank) {
                now = now->childs[0];
            }else {
                break;
            }
        }
        splay(prev);
        return now;
    }

    Node * splayRange(int left,int right) {
        Node *leftNode = getKth(left - 1),*rightNode = getKth(right + 1);
        splay(leftNode);
        splay(rightNode,leftNode);
        return root->childs[1]->childs[0];
    }


    void insert(int x,int *values,int size) {
        splayRange(x + 1,x);
        root->childs[1]->childs[0] = buildTree(root->childs[1],0,size - 1,values);
        splay(root->childs[1]->childs[0]);
    }

    void remove(int start,int length) {
        Node *deletedNode = splayRange(start,start + length - 1);
        root->childs[1]->childs[0] = NULL;
        delete deletedNode;
    }

    void change(int start,int length,int value) {
        Node *distNode = splayRange(start,start + length - 1);
        updateChangeTag(distNode,value);
        splay(distNode);
    }

    void reverse(int start,int length) {
        Node *distNode = splayRange(start,start + length - 1);
        updateReverseTag(distNode);
        splay(distNode);
    }

    int getSum(int start,int length) {
        Node *distNode = splayRange(start,start + length - 1);
        int result = getSumValue(distNode);
        splay(distNode);
        return result;
    }

    int getMaxSum() {
        return getMaxValue(root);
    }

    static Node *buildTree(int left,int right,int *values) {
        return buildTree(NULL,left,right,values);
    }

    static Node * buildTree(Node *father,int left,int right,int *values) {
        if(left > right) return NULL;
        int mid = (left + right) >> 1;
        Node *now = new Node(father,values[mid]);
        if(left == right) {
            return now;
        }
        now->childs[0] = buildTree(now,left,mid - 1,values);
        now->childs[1] = buildTree(now,mid + 1,right,values);
        updateInfo(now);
        return now;
    }

    ~Splay() {
        delete root;
    }

    void print() {
        print(root,0);
        printf("\n");
    }

    void print(Node *now,int depth) {
        if(now == NULL) return;
        pushDown(now);
        print(now->childs[0],depth + 2);
        for(int i = 0;i < depth;i++) {
            printf(" ");
        }
        printf("%d\n",now->value,now->leftMaxValue,now->rightMaxValue,now->maxValue);
        print(now->childs[1],depth + 2);
    }

};

int main() {
    char *buffer = new char[BUFFER_SIZE];
    int N = read<int>(),M = read<int>();
    Splay splay;
    int *values = new int[MAX_VAL_CNT];
    for(int i = 1;i <= N;i++) {
        values[i] = read<int>();
    }
    values[0] = 0;
    values[N + 1] = 0;
    splay.root = Splay::buildTree(0,N + 1,values);
    while(M--) {
        scanf("%s",buffer);
        int opt = getOperatorSign(buffer);
        switch(opt) {
            case 0: {
                int pos = read<int>(),tot = read<int>();
                for(int i = 0;i < tot;i++) {
                    values[i] = read<int>();
                }
                splay.insert(pos,values,tot);
                break;
            }
            case 1: {
                int pos = read<int>(),tot = read<int>();
                splay.remove(pos,tot);
                break;
            }
            case 2: {
                int pos = read<int>(),tot = read<int>(),c = read<int>();
                splay.change(pos,tot,c);
                break;
            }
            case 3: {
                int pos = read<int>(),tot = read<int>();
                splay.reverse(pos,tot);
                break;
            }
            case 4: {
                int pos = read<int>(),tot = read<int>();
                printf("%d\n",splay.getSum(pos,tot));
                break;
            }
            case 5: {
                printf("%d\n",splay.getMaxSum());
                splay.print();
                printf("%d\n",splay.getMaxSum());
            }
        }
        /*
        printf("-----Debug Info Start-----\n");
        splay.print();
        printf("%d\n",splay.getMaxSum());
        printf("-----Debug Info End-----\n");
        */
    }
    return 0;
}
