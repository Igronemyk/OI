#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c >= '0' && c <= '9') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Splay {
    struct Node {
        int father,ch[2],value,cnt,size;

        Node() : father(0) , value(0) , cnt(0) , size(0) {
            ch[0] = 0;
            ch[1] = 0;
        }

        Node(int father,int value) : father(father) , value(value) , cnt(1) , size(1) {
            ch[0] = 0;
            ch[1] = 0;
        }
    } n[MAXN];

    int root,size;

    Splay() : root(0) , size(1) { }

    inline int newNode(int father,int value) {
        n[size] = Node(father,value);
        return size++;
    }

    inline void updateInfo(int now) {
        n[now].size = n[n[now].ch[0]].size + n[n[now].ch[1]].size + n[now].cnt;
    }

    void rotate(int now) {
        int father = n[now].father,anc = n[father].father;
        if(anc != 0) {
            n[anc].ch[n[anc].ch[1] == father] = now;
        }
        int direction = n[father].ch[0] == now;
        n[father].father = now;
        n[now].father = anc;
        n[father].ch[!direction] = n[now].ch[direction];
        n[now].ch[direction] = father;
        if(n[father].ch[!direction] != 0) {
            n[n[father].ch[!direction]].father = father;
        }
        updateInfo(father);
        updateInfo(now);
        if(n[now].father == 0) {
            root = now;
        }
    }

    void splay(int now) {
        splay(now,0);
    }

    void splay(int now,int dist) {
        if(now == 0 || now == dist) return;
        while(n[now].father != dist) {
            int father = n[now].father,anc = n[father].father;
            if(anc != dist) {
                if((n[anc].ch[0] == father) ^ (n[father].ch[0] == now)) {
                    rotate(now);
                }else {
                    rotate(father);
                }
            }
            rotate(now);
        }
    }

    void insert(int value) {
        if(root == 0) {
            root = newNode(0,value);
            return;
        }
        int now = root,result = 0;
        while(now != 0) {
            if(n[now].value > value) {
                if(n[now].ch[0] != 0) {
                    now = n[now].ch[0];
                }else {
                    result = newNode(now,value);
                    n[now].ch[0] = result;
                    break;
                }
            }else if(n[now].value < value) {
                if(n[now].ch[1] != 0) {
                    now = n[now].ch[1];
                }else {
                    result = newNode(now,value);
                    n[now].ch[1] = result;
                    break;
                }
            }else {
                n[now].cnt++;
                updateInfo(now);
                result = now;
                break;
            }
        }
        splay(result);
    }

    int find(int value) {
        int now = root,prev = 0;
        while(now != 0) {
            prev = now;
            if(n[now].value > value) {
                now = n[now].ch[0];
            }else if(n[now].value < value) {
                now = n[now].ch[1];
            }else {
                break;
            }
        }
        splay(prev);
        return now;
    }

    int searchMin(int now) {
        int father = n[now].father;
        while(n[now].ch[0] != 0) {
            now = n[now].ch[0];
        }
        splay(now,father);
        return now;
    }

    int searchMax(int now) {
        int father = n[now].father;
        while(n[now].ch[1] != 0) {
            now = n[now].ch[1];
        }
        splay(now,father);
        return now;
    }

    void remove(int value) {
        if(find(value) == 0) return;
        if(n[root].cnt > 1) {
            n[root].cnt--;
            updateInfo(root);
            return;
        }
        int leftChild = n[root].ch[0],rightChild = n[root].ch[1];
        if(leftChild == 0 && rightChild == 0) {
            root = 0;
            return;
        }
        if(leftChild != 0 && rightChild == 0) {
            root = leftChild;
            n[leftChild].father = 0;
            return;
        }
        if(leftChild == 0 && rightChild != 0) {
            root = rightChild;
            n[rightChild].father = 0;
            return;
        }
        int newNode = searchMin(n[root].ch[1]);
        n[newNode].father = 0;
        n[newNode].ch[0] = n[root].ch[0];
        n[n[newNode].ch[0]].father = newNode;
        root = newNode;
        updateInfo(newNode);
    }

    int rank(int value) {
        int now = find(value);
        if(now == 0) return -1;
        return n[n[now].ch[0]].size;
    }

    int findKth(int rank) {
        int now = root,prev = 0;
        while(now != 0) {
            prev = now;
            int leftChildSize = n[n[now].ch[0]].size;
            if(rank >= leftChildSize && rank <= leftChildSize + n[now].cnt - 1) {
                break;
            }else if(rank < leftChildSize) {
                now = n[now].ch[0];
            }else {
                rank -= leftChildSize + n[now].cnt;
                now = n[now].ch[1];
            }
        }
        splay(prev);
        return now;
    }

    int getPrecursor(int value) {
        find(value);
        if(n[root].value >= value) {
            return searchMax(n[root].ch[0]);
        }
        return root;
    }

    int getSuccessor(int value) {
        find(value);
        if(n[root].value <= value) {
            return searchMin(n[root].ch[1]);
        }
        return root;
    }

    int getRankByValue(int value) {
        return rank(value) + 1;
    }

    int getValueByRank(int rank) {
        return n[findKth(rank - 1)].value;
    }

    int getPrecursorVal(int value) {
        return n[getPrecursor(value)].value;
    }

    int getSuccessorVal(int value) {
        return n[getSuccessor(value)].value;
    }


};

int main() {
    Splay splay;
    int n = read<int>();
    while(n--) {
        int opt = read<int>(),x = read<int>();
        switch(opt) {
            case 1: {
                splay.insert(x);
                break;
            }
            case 2: {
                splay.remove(x);
                break;
            }
            case 3: {
                printf("%d\n",splay.getRankByValue(x));
                break;
            }
            case 4: {
                printf("%d\n",splay.getValueByRank(x));
                break;
            }
            case 5: {
                printf("%d\n",splay.getPrecursorVal(x));
                break;
            }
            case 6: {
                printf("%d\n",splay.getSuccessorVal(x));
                break;
            }
        }
    }
    return 0;
}
