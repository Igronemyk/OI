#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstddef>

using namespace std;

const int MAX_VAL_RANGE = 800010;
const int BUFFER_SIZE = 7;
const char * OPT_TOP = "Top";
const char * OPT_BOTTOM = "Bottom";
const char * OPT_INSERT = "Insert";
const char * OPT_ASK = "Ask";
const char * OPT_QUERY = "Query";

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int getOperation(char *str) {
    if(strcmp(str,OPT_TOP) == 0) {
        return 0;
    }
    if(strcmp(str,OPT_BOTTOM) == 0) {
        return 1;
    }
    if(strcmp(str,OPT_INSERT) == 0) {
        return 2;
    }
    if(strcmp(str,OPT_ASK) == 0) {
        return 3;
    }
    if(strcmp(str,OPT_QUERY) == 0) {
        return 4;
    }
    return -1;
}

struct Splay {
    struct Node {
         Node *father,*childs[2];
         int sign,value,size;

         Node(Node *father,int sign,int value) : father(father) , sign(sign) , value(value) , size(1) {
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
        now->size = getSize(now->childs[0]) + getSize(now->childs[1]) + 1;
    }

    int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
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

    void insert(int sign,int value) {
        if(root == NULL) {
            root = new Node(NULL,sign,value);
            return;
        }
        Node *now = root,*result = NULL;
        while(now != NULL) {
            if(now->sign > sign) {
                if(now->childs[0] != NULL) {
                    now = now->childs[0];
                }else {
                    now->childs[0] = new Node(now,sign,value);
                    result = now->childs[0];
                    break;
                }
            }else {
                if(now->childs[1] != NULL) {
                    now = now->childs[1];
                }else {
                    now->childs[1] = new Node(now,sign,value);
                    result = now->childs[1];
                    break;
                }
            }
        }
        splay(result);
    }

    Node *find(int sign) {
        Node *now = root,*prev = NULL;
        while(now != NULL) {
            prev = now;
            if(now->sign > sign) {
                now = now->childs[0];
            }else if(now->sign < sign) {
                now = now->childs[1];
            }else {
                break;
            }
        }
        splay(prev);
        return now;
    }

    Node *findKth(int rank) {
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

    void remove(int sign) {
        Node *now = find(sign);
        if(now == NULL) return;
        if(now->childs[0] == NULL && now->childs[1] == NULL) {
            root = NULL;
            delete now;
            return;
        }
        if(now->childs[0] != NULL && now->childs[1] == NULL) {
            root = now->childs[0];
            root->father = NULL;
            now->clearChild();
            delete now;
            return;
        }
        if(now->childs[0] == NULL && now->childs[1] != NULL) {
            root = now->childs[1];
            root->father = NULL;
            now->clearChild();
            delete now;
            return;
        }
        Node *newNode = searchMin(now->childs[1]);
        newNode->father = NULL;
        newNode->childs[0] = now->childs[0];
        newNode->childs[0]->father = newNode;
        root = newNode;
        now->clearChild();
        delete now;
        updateInfo(newNode);
    }

    void changeSign(int sign,int newSign) {
        Node *now = find(sign);
        if(now == NULL) return;
        int value = now->value;
        remove(sign);
        insert(newSign,value);
    }

    pair<pair<int,int>,pair<int,int> > movePos(int sign,int pos) {
        Node *now = find(sign);
        int nowValue = now->value,nowSign = now->sign;
        if(pos == -1) {
            Node *pre = searchMax(now->childs[0]);
            int preValue = pre->value,preSign = pre->sign;
            pre->value = nowValue;
            now->value = preValue;
            return make_pair(make_pair(nowValue,preSign),make_pair(preValue,nowSign));
        }else {
            Node *suc = searchMin(now->childs[1]);
            int sucValue = suc->value,sucSign = suc->sign;
            suc->value = nowValue;
            now->value = sucValue;
            return make_pair(make_pair(nowValue,sucSign),make_pair(sucValue,nowSign));
        }
    }

    int getRank(int sign) {
        Node *now = find(sign);
        return getSize(now->childs[0]);
    }

    int getValue(int rank) {
        Node *now = findKth(rank);
        return now->value;
    }

    void print() {
        print(root);
        printf("\n");
    }

    void print(Node *now) {
        if(now == NULL) return;
        print(now->childs[0]);
        printf("%d ",now->value);
        print(now->childs[1]);
    }

};

int main() {
    int n = read<int>(),m = read<int>();
    Splay splay;
    int leftSign = 0,rightSign = n - 1;
    int *mapValueToSign = new int[MAX_VAL_RANGE];
    for(int i = 0;i < n;i++) {
        int tmpValue = read<int>();
        splay.insert(i,tmpValue);
        mapValueToSign[tmpValue] = i;
    }
    char *buffer = new char[BUFFER_SIZE];
    while(m--) {
        scanf("%s",buffer);
        int opt = getOperation(buffer);
        switch(opt) {
            case 0: {
                int value = read<int>();
                int sign = mapValueToSign[value];
                splay.changeSign(sign,--leftSign);
                mapValueToSign[value] = leftSign;
                break;
            }
            case 1: {
                int value = read<int>();
                int sign = mapValueToSign[value];
                splay.changeSign(sign,++rightSign);
                mapValueToSign[value] = rightSign;
                break;
            }
            case 2: {
                int value = read<int>(),pos = read<int>();
                if(pos == 0) break;
                pair<pair<int,int>,pair<int,int> > result = splay.movePos(mapValueToSign[value],pos);
                mapValueToSign[result.first.first] = result.first.second;
                mapValueToSign[result.second.first] = result.second.second;
                break;
            }
            case 3: {
                int value = read<int>();
                printf("%d\n",splay.getRank(mapValueToSign[value]));
                break;
            }
            case 4: {
                int value = read<int>();
                printf("%d\n",splay.getValue(value - 1));
                break;
            }
        }
    }
    delete[] buffer;
    delete[] mapValueToSign;
    return 0;
}
