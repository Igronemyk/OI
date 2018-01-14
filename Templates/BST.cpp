#include <cstdio>
#include <cstddef>
#include <algorithm>
#include <cstring>

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

template<typename K,typename V>
struct BST {
    struct Node {
        K key;
        V val;
        Node *left,*right;
        int size,cnt;
        Node(K key,V val) : key(key) , val(val) , left(NULL) , right(NULL) , size(1) , cnt(1) { }

        bool hasLeftChild() {
            return left != NULL;
        }

        bool hasRightChild() {
            return right != NULL;
        }

    };

    Node *root;

    BST() {
        root = NULL;
    }

    V get(const K &key) {
        return get(root,key)->val;
    }

    void remove(const K &key) {
        remove(root,key);
    }

    void insert(const K &key,const V &val) {
        insert(root,key,val);
    }

    int size(const K &key) {
        return size(get(root,key));
    }

    int getRank(const K &key) {
        return getRank(root,key);
    }

    K getByRank(int rank) {
        return getByRank(root,rank)->key;
    }

    K getPrecursor(const K &key) {
        return getPrecursor(root,key);
    }

    K getSuccessor(const K &key) {
        return getSuccessor(root,key);
    }


    Node * get(const K &key) {
        Node *now = root;
        while(now != NULL) {
            if(key > now->key) {
                now = now->left;
            }else if(key < now->key) {
                now = now->right;
            }else {
                break;
            }
        }
        return now;
    }


    /*
    //deleted
    Node * get(Node *now,const K &key) {

        if(now->key > key) {
            return get(now->left,key);
        }else if(now->key < key) {
            return get(now->right,key);
        }else {
            return now;
        }
    }
    */


    void remove(const K &key) {
        Node *now = get(key);
        if(now == NULL) return;
        if(now->cnt > 1) {
            now->cnt--;
        }else if() {

        }
    }

    //deleted
    void remove(Node *&now,const K &key) {
        if(now == NULL) return;
        if(now->key > key) {
            remove(now->left,key);
        }else if(now->key < key) {
            remove(now->right,key);
        }else {
            if(now->cnt > 1) {
                now->cnt--;
            }else if(!now->hasLeftChild() && !now->hasRightChild()) {
                now = NULL;
            }else if(now->hasLeftChild() && !now->hasRightChild()) {
                now = now->left;
            }else if(!now->hasLeftChild() && now->hasRightChild()) {
                now = now->right;
            }else {
                Node *tmp = now;
                now = getMin(tmp->right);
                remove(tmp->right,now->key);
                now->left = tmp->left;
                now->right = tmp->right;
            }
        }
        if(now != NULL) updateSize(now);
    }

    void insert(Node *&now,const K &key,const V &val) {
        if(now == NULL) {
            now = new Node(key,val);
            return;
        }
        if(now->key > key) {
            insert(now->left,key,val);
        }else if(now->key < key) {
            insert(now->right,key,val);
        }else {
            now->cnt++;
        }
        updateSize(now);
    }

    Node * getMin(Node *now) {
        if(!now->hasLeftChild()) return now;
        return getMin(now->left);
    }

    int size(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    int size(Node *now,const K &key) {
        if(now == NULL) return 0;
        if(now->key > key) {
            return size(now->left,key);
        }else if(now->key < key) {
            return size(now->right,key);
        }else {
            return now->size;
        }
    }

    int getRank(Node *now,const K &key) {
        if(now == NULL) return -1;
        int leftChildSize = 0;
        if(now->hasLeftChild()) leftChildSize = now->left->size;
        if(now->key > key) {
            return getRank(now->left,key);
        }else if(now->key < key) {
            return getRank(now->right,key) + leftChildSize + now->cnt;
        }else {
            return leftChildSize + 1;
        }
    }

    Node * getByRank(Node *now,int rank) {
        if(now == NULL) return NULL;
        int leftChildSize = 0;
        if(now->hasLeftChild()) leftChildSize = now->left->size;
        if(rank >= leftChildSize + 1 && rank <= now->cnt + leftChildSize) {
            return now;
        }else if(leftChildSize >= rank) {
            return getByRank(now->left,rank);
        }else {
            return getByRank(now->right,rank - leftChildSize - now->cnt);
        }
    }

    K getPrecursor(Node *now,const K &key) {
        if(now == NULL) return -INF;
        if(now->key < key) {
            K result = now->key;
            if(now->hasRightChild()) {
                result = max(result,getPrecursor(now->right,key));
            }
            return result;
        }else {
            if(now->hasLeftChild()) {
                return getPrecursor(now->left,key);
            }
        }
        return -INF;
    }

    K getSuccessor(Node *now,const K &key) {
        if(now == NULL) return INF;
        if(now->key > key) {
            K result = now->key;
            if(now->hasLeftChild()) {
                result = min(result,getSuccessor(now->left,key));
            }
            return result;
        }else {
            if(now->hasRightChild()) {
                return getSuccessor(now->right,key);
            }
        }
        return INF;
    }

    void updateSize(Node *now) {
        now->size = size(now->left) + size(now->right) + now->cnt;
    }

};

int main() {
    int n = quick_read<>::scan<int>();
    BST<int,int> bst;
    while(n--) {
        int opt = quick_read<>::scan<int>(),x = quick_read<>::scan<int>();
        switch(opt) {
            case 1: {
                bst.insert(x,1);
                break;
            }
            case 2: {
                bst.remove(x);
                break;
            }
            case 3: {
                printf("%d\n",bst.getRank(x));
                break;
            }
            case 4: {
                printf("%d\n",bst.getByRank(x));
                break;
            }
            case 5: {
                printf("%d\n",bst.getPrecursor(x));
                break;
            }
            case 6: {
                printf("%d\n",bst.getSuccessor(x));
                break;
            }
        }
    }
    return 0;
}
