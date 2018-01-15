#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstddef>

using namespace std;

const int INF = 0x3f3f3f3f;
const int BUFFER_SIZE = 13;
const char *OPT_INSERT = "INSERT";
const char *OPT_MIN_GAP = "MIN_GAP";
const char *OPT_MIN_SORT_GAP = "MIN_SORT_GAP";

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int getOperation(char *str) {
    if(strcmp(str,OPT_INSERT) == 0) {
        return 0;
    }
    if(strcmp(str,OPT_MIN_GAP) == 0) {
        return 1;
    }
    if(strcmp(str,OPT_MIN_SORT_GAP) == 0) {
        return 2;
    }
    return -1;
}

struct Splay {
    struct Node {
        Node *father,*childs[2];
        int value,cnt,size;

        Node(Node *father,int value) : father(father) , value(value) , cnt(1) , size(1) {
            clearChild();
        }

        ~Node() {
            if(childs[0] != NULL) {
                delete childs[0];
            }
            if(childs[1] != NULL) {
                delete childs[1];
            }
        }

        void clearChild() {
            childs[0] = NULL;
            childs[1] = NULL;
        }
    };

    Node *root;

    Splay() : root(NULL) { }

    ~Splay() {
        if(root != NULL) {
            delete root;
        }
    }

    void updateInfo(Node *now) {
        now->size = getSize(now->childs[0]) + getSize(now->childs[1]) + now->cnt;
    }

    int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    /*
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
            father->childs[!direction]->father = father;
        }
        updateInfo(father);
        updateInfo(now);
        if(now->father == NULL) {
            root = now;
        }
    }

    void splay(Node *now) {
        splay(now,NULL);
    }

    void splay(Node *now,Node *dist) {
        if(now == NULL || now == dist) return;
        while(now->father != dist) {
            Node *father = now->father,*anc = father->father;
            if(anc != dist) {
                if((anc->childs[0] == father) ^ (father->childs[0] == now)) {
                    rotate(now);
                }else {
                    rotate(father);
                }
            }
            rotate(now);
        }
    }*/

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
            father->childs[!direction]->father= father;
        }
        updateInfo(father);
        updateInfo(now);
        if(now->father == NULL) {
            root = now;
        }
    }

    void splay(Node *now) {
        splay(now,NULL);
    }

    void splay(Node *now,Node *dist) {
        if(now == NULL || now == dist) return;
        while(now->father != dist) {
            Node *father = now->father,*anc = father->father;
            if(anc != dist) {
                if((anc->childs[0] == father) ^ (father->childs[0] == now)) {
                    rotate(now);
                }else {
                    rotate(father);
                }
            }
            rotate(now);
        }
    }

    void insert(int value) {
        if(root == NULL) {
            root = new Node(NULL,value);
            return;
        }
        Node *now = root,*result = NULL;
        while(now != NULL) {
            if(now->value > value) {
                if(now->childs[0] != NULL) {
                    now = now->childs[0];
                }else {
                    now->childs[0] = new Node(now,value);
                    result = now->childs[0];
                    break;
                }
            }else if(now->value < value) {
                if(now->childs[1] != NULL) {
                    now = now->childs[1];
                }else {
                    now->childs[1] = new Node(now,value);
                    result = now->childs[1];
                    break;
                }
            }else {
                now->cnt++;
                result = now;
                updateInfo(now);
                break;
            }
        }
        splay(result);
    }

    Node *searchMin(Node *now) {
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

    Node *find(int value) {
        Node *now = root,*prev = NULL;
        while(now != NULL) {
            prev = now;
            if(now->value > value) {
                if(now->childs[0] != NULL) {
                    now = now->childs[0];
                }else {
                    now = NULL;
                    break;
                }
            }else if(now->value < value) {
                if(now->childs[1] != NULL) {
                    now = now->childs[1];
                }else {
                    now = NULL;
                    break;
                }
            }else {
                break;
            }
        }
        splay(prev);
        return now;
    }

    void remove(int value) {
        Node *now = find(value);
        if(now == NULL) return;
        if(now->cnt > 1) {
            now->cnt--;
            return;
        }
        if(now->childs[0] == NULL && now->childs[1] == NULL) {
            root = NULL;
            delete now;
            now = NULL;
            return;
        }
        if(now->childs[0] != NULL && now->childs[1] == NULL) {
            root = now->childs[0];
            root->father = NULL;
            now->clearChild();
            delete now;
            now = NULL;
            return;
        }
        if(now->childs[0] == NULL && now->childs[1] != NULL) {
            root = now->childs[1];
            root->father = NULL;
            now->clearChild();
            delete now;
            now = NULL;
            return;
        }
        Node *newNode = searchMin(now->childs[1]);
        newNode->childs[0] = now->childs[0];
        newNode->father = NULL;
        newNode->childs[0]->father = newNode;
        root = newNode;
        now->clearChild();
        delete now;
        now = NULL;
        updateInfo(newNode);
    }

    int insertAndGetValue(int value) {
        insert(value);
        if(root->cnt > 1) {
            return 0;
        }
        Node *pre = searchMax(root->childs[0]),*suc = searchMin(root->childs[1]);
        return min(value - pre->value,suc->value - value);
    }

    int getMinValue() {
        Node *now = searchMin(root);
        return now->value;
    }
};

int main() {
    int N = read<int>(),M = read<int>(),*initValues = new int[N],*endValues = new int[N],*sortValues = new int[N];
    Splay minValues,allValues;
    for(int i = 0;i < N;i++) {
        int tmpValue = read<int>();
        initValues[i] = tmpValue;
        endValues[i] = tmpValue;
        sortValues[i] = tmpValue;
        allValues.insert(tmpValue);
    }
    sort(sortValues,sortValues + N);
    allValues.insert(-INF);
    allValues.insert(INF);
    int minValue = INF,minAllValue = INF;
    for(int i = 0;i < N - 1;i++) {
        minValues.insert(abs(initValues[i + 1] - initValues[i]));
        minValue = min(minValue,abs(initValues[i + 1] - initValues[i]));
        minAllValue = min(minAllValue,abs(sortValues[i + 1] - sortValues[i]));
    }
    char *buffer = new char[BUFFER_SIZE];
    while(M--) {
        scanf("%s",buffer);
        int opt = getOperation(buffer);
        switch(opt) {
            case 0: {
                int pos = read<int>(),value = read<int>();
                pos--;
                minAllValue = min(minAllValue,allValues.insertAndGetValue(value));
                int oldValue = endValues[pos];
                minValues.insert(abs(oldValue - value));
                if(pos != N - 1) {
                    minValues.remove(abs(oldValue - initValues[pos + 1]));
                    minValues.insert(abs(value - initValues[pos + 1]));
                }
                minValue = minValues.getMinValue();
                endValues[pos] = value;
                break;
            }
            case 1: {
                printf("%d\n",minValue);
                break;
            }
            case 2: {
                printf("%d\n",minAllValue);
                break;
            }
        }
    }
    delete[] buffer;
    delete[] initValues;
    delete[] endValues;
    delete[] sortValues;
    return 0;
}
