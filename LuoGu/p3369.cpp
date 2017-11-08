#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

template <std::size_t bufferSize = 1U << 15>
class quick_read {
public:
    static std::size_t buffer_size() {
        return bufferSize;
    }

    static int getchar() {
        if (S == T)
        {
            S = buffer;
            T = buffer + std::fread(buffer, 1, buffer_size(), stdin);
            if (S == T)
            {
                return EOF;
            }
        }
        return *S++;
    }

    template <typename Integer>
    static Integer scan() {
        char c = getchar();
        Integer result = 0;
        int f = 1;
        while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
        while(c <= '9' && c >= '0') {result = result * 10 + c- '0';c = getchar();}
        return result * f;
    }
private:
    static char buffer[bufferSize];
    static char *S;
    static char *T;
};

template <std::size_t bufferSize>
char quick_read<bufferSize>::buffer[bufferSize];

template <std::size_t bufferSize>
char *quick_read<bufferSize>::S = NULL;

template <std::size_t bufferSize>
char *quick_read<bufferSize>::T = NULL;

struct Treap {
    struct Node {
        int weight,priority,countSelf,countChilds;
        Node *leftChild,*rightChild;
        Node() : weight(-1) , priority(-1) , countSelf(-1) , countChilds(-1) , leftChild(NULL) , rightChild(NULL) { }
        Node(int weight,int priority) : weight(weight) , priority(priority) , countSelf(1) , countChilds(1) , leftChild(NULL) , rightChild(NULL) { }

        bool hasLeftChild() {
            return leftChild != NULL;
        }

        bool hasRightChild() {
            return rightChild != NULL;
        }
    };
    Node *root;

    Treap() {
        srand(12345);
        root = NULL;
    }

    void insert(int val) {
        insert(root,val);
    }

    void remove(int val) {
        remove(root,val);
    }

    int getRankByVal(int val) {
        return getRankByVal(root,val);
    }

    int getValByRank(int rank) {
        return getValByRank(root,rank);
    }

    int getPrecursorByVal(int val) {
        return getPrecursorByVal(root,val);
    }

    int getSuccessorByVal(int val) {
        return getSuccessorByVal(root,val);
    }

    void insert(Node *&now,int val) {
        if(now == NULL) {
            int randPriority = rand();
            now = new Node(val,randPriority);
            return;
        }
        if(now->weight == val) {
            now->countSelf++;
            updateInfo(now);
            return;
        }
        if(now->weight > val) {
            insert(now->leftChild,val);
            if(now->leftChild->priority > now->priority) {
                rightRotate(now);
            }else {
                updateInfo(now);
            }
        }else if(now->weight < val) {
            insert(now->rightChild,val);
            if(now->rightChild->priority > now->priority) {
                leftRotate(now);
            }else {
                updateInfo(now);
            }
        }
    }

    void remove(Node *&now,int val) {
        if(now == NULL) return;
        if(now->weight == val) {
            if(now->countSelf > 1) {
                now->countSelf--;
            }else {
                if(!now->hasLeftChild() && !now->hasRightChild()) {
                    now = NULL;
                }else if(now->hasLeftChild() && !now->hasRightChild()) {
                    now = now->leftChild;
                }else if(!now->hasLeftChild() && now->hasRightChild()) {
                    now = now->rightChild;
                }else if(now->hasLeftChild() && now->hasLeftChild()){
                    if(now->leftChild->priority > now->rightChild->priority) {
                        rightRotate(now);
                        remove(now->rightChild,val);
                    }else {
                        leftRotate(now);
                        remove(now->leftChild,val);
                    }
                }
            }
            if(now != NULL) updateInfo(now);
        }else if(now->weight > val) {
            remove(now->leftChild,val);
            updateInfo(now);
        }else if(now->weight < val) {
            remove(now->rightChild,val);
            updateInfo(now);
        }
    }

    int getRankByVal(Node *now,int val) {
        if(now == NULL) return 1;
        int leftChildCount = 0;
        if(now->hasLeftChild()) leftChildCount = now->leftChild->countChilds;
        if(now->weight == val) {
            return leftChildCount + 1;
        }
        if(now->weight > val) {
            return getRankByVal(now->leftChild,val);
        }
        if(now->weight < val) {
            return leftChildCount + getRankByVal(now->rightChild,val) + now->countSelf;
        }
        return 1;
    }

    int getValByRank(Node *now,int rank) {
        if(now == NULL || rank < 0 || rank > now->countChilds) return -INF;
        int leftChildCount = 0;
        if(now->hasLeftChild()) leftChildCount = now->leftChild->countChilds;
        if(rank >= leftChildCount + 1 && rank <= now->countSelf + leftChildCount) return now->weight;
        if(leftChildCount >= rank) {
            return getValByRank(now->leftChild,rank);
        }else {
            return getValByRank(now->rightChild,rank - leftChildCount - now->countSelf);
        }
    }

    int getPrecursorByVal(Node *now,int val) {
        if(now == NULL) return -INF;
        if(now->weight < val) {
            int ans = now->weight;
            if(now->hasRightChild()) ans = max(ans,getPrecursorByVal(now->rightChild,val));
            return ans;
        }else {
            if(now->hasLeftChild()) return getPrecursorByVal(now->leftChild,val);
        }
        return -INF;
    }

    int getSuccessorByVal(Node *now,int val) {
        if(now == NULL) return INF;
        if(now->weight > val) {
            int ans = now->weight;
            if(now->hasLeftChild()) ans = min(ans,getSuccessorByVal(now->leftChild,val));
            return ans;
        }else {
            if(now->hasRightChild()) return getSuccessorByVal(now->rightChild,val);
        }
        return INF;
    }

    void leftRotate(Node *&now) {
        Node *tmpNode = now->rightChild;
        now->rightChild = tmpNode->leftChild;
        tmpNode->leftChild = now;
        updateInfo(now);
        updateInfo(tmpNode);
        now = tmpNode;
    }

    void rightRotate(Node *&now) {
        Node *tmpNode = now->leftChild;
        now->leftChild = tmpNode->rightChild;
        tmpNode->rightChild = now;
        updateInfo(now);
        updateInfo(tmpNode);
        now = tmpNode;
    }

    void updateInfo(Node *&now) {
        now->countChilds = now->countSelf;
        if(now->hasLeftChild()) {
            now->countChilds += now->leftChild->countChilds;
        }
        if(now->hasRightChild()) {
            now->countChilds += now->rightChild->countChilds;
        }
    }

};

int main() {
    Treap treap;
    int n = quick_read<>::scan<int>();
    while(n--) {
        int opt = quick_read<>::scan<int>(),x = quick_read<>::scan<int>();
        switch(opt) {
            case 1: {
                treap.insert(x);
                break;
            }
            case 2: {
                treap.remove(x);
                break;
            }
            case 3: {
                printf("%d\n",treap.getRankByVal(x));
                break;
            }
            case 4: {
                printf("%d\n",treap.getValByRank(x));
                break;
            }
            case 5: {
                printf("%d\n",treap.getPrecursorByVal(x));
                break;
            }
            case 6: {
                printf("%d\n",treap.getSuccessorByVal(x));
                break;
            }
        }
    }
    return 0;
}
