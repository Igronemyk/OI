#include <cstdio>

using namespace std;

const int MODDER = 1e9 + 9;

//2000000018
//2147483647

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
        long long key;
        int value;
        int sumValue;

        Node() : father(NULL) , key(-1) , value(-1) , sumValue(-1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

        Node(Node *father,long long key,int value) : father(father) , key(key) , value(value) , sumValue(value) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

    };

    Node *root;

    Splay() : root(NULL) { }

    void rotate(Node *now) {
        Node *father = now->father,*anc = father->father;
        if(anc != NULL) {
            anc->childs[anc->childs[1] == father] = now;
        }
        int direction = father->childs[0] == now;
        now->father = anc;
        father->father = now;
        father->childs[!direction] = now->childs[direction];
        if(father->childs[!direction] != NULL) {
            father->childs[!direction]->father = father;
        }
        now->childs[direction] = father;
        if(root == father) {
            root = now;
        }
        updateInfo(father);
        updateInfo(now);
    }

    void splay(Node *now) {
        splay(now,NULL);
    }

    void splay(Node *now,Node *dist) {
        if(now == NULL || now->father == dist) return;
        while(now->father != dist) {
            Node *father = now->father,*anc = father->father;
            if(anc != NULL) {
                if((father->childs[0] == now) ^ (anc->childs[0] == father)) {
                    rotate(now);
                }else {
                    rotate(father);
                }
            }
            rotate(now);
        }
    }

    void updateInfo(Node *now) {
        if(now == NULL) return;
        now->sumValue = (((getSumValue(now->childs[0]) + getSumValue(now->childs[1])) % MODDER) + now->value) % MODDER;
    }

    int getSumValue(Node *now) {
        if(now == NULL) return 0;
        return now->sumValue;
    }

    void insert(long long key,int value) {
        if(root == NULL) {
            root = new Node(NULL,key,value);
            return;
        }
        Node *now = root,*result = NULL;
        while(now != NULL) {
            if(now->key > key) {
                if(now->childs[0] != NULL) {
                    now = now->childs[0];
                }else {
                    now->childs[0] = new Node(now,key,value);
                    result = now->childs[0];
                    break;
                }
            }else if(now->key < key) {
                if(now->childs[1] != NULL) {
                    now = now->childs[1];
                }else {
                    now->childs[1] = new Node(now,key,value);
                    result = now->childs[1];
                    break;
                }
            }else {
                now->value = (now->value + value) % MODDER;
                updateInfo(now);
                result = now;
                break;
            }
        }
        splay(result);
    }

    Node *search(long long key) {
        if(root == NULL) return NULL;
        Node *now = root,*result = NULL;
        while(true) {
            if(now->key > key) {
                if(now->childs[0] != NULL) {
                    now = now->childs[0];
                }else {
                    break;
                }
            }else if(now->key < key) {
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
        splay(now);
        return result;
    }

    int getResult(long long key) {
        Node *pos = search(key);
        if(pos != NULL) {
            return getSumValue(pos->childs[0]);
        }else {
            if(root == NULL) {
                return 0;
            }
            if(root->key > key) {
                return getSumValue(root->childs[0]);
            }else {
                return (root->value + getSumValue(root->childs[0])) % MODDER;
            }
        }
    }

};

int main() {
    int N = read<int>();
    long long indexValue = 0;
    Splay splay;
    for(int i = 0;i < N;i++) {
        int tmpValue = read<int>();
        indexValue += tmpValue;
        int tmpResult = (splay.getResult(indexValue + 1) + (indexValue >= 0 ? 1 : 0)) % MODDER;
        if(i == N - 1) {
            printf("%d\n",tmpResult);
        }
        splay.insert(indexValue,tmpResult);
    }
    return 0;
}
