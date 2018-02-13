#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <utility>
#include <set>
#include <ctime>

using namespace std;

const int MAX_VAL_RANGE = 1e6;
const int BUFFER_SIZE = 2;
template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Treap {
    struct Node {
        Node *ch[2];
        int value,priority,size;

        Node(int value) : value(value) , priority(rand()) , size(1) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    };

    Node *root;

    typedef pair<Node *,Node *> DRoot;

    Treap() {
        root = NULL;
    }

    static int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    static void updateInfo(Node *now) {
        now->size = getSize(now->ch[0]) + getSize(now->ch[1]) + 1;
    }

    static Node *merge(Node *a,Node *b) {
        if(a == NULL) return b;
        if(b == NULL) return a;
        if(a->priority > b->priority) {
            a->ch[1] = merge(a->ch[1],b);
            updateInfo(a);
            return a;
        }else {
            b->ch[0] = merge(a,b->ch[0]);
            updateInfo(b);
            return b;
        }
    }

    static DRoot split(Node *now,int k) {
        DRoot result(NULL,NULL);
        if(now == NULL) return result;
        if(k <= getSize(now->ch[0])) {
            result = split(now->ch[0],k);
            now->ch[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(now->ch[1],k - getSize(now->ch[0]) - 1);
            now->ch[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    int lowerCount(int value) {
        Node *now = root;
        int result = 0;
        while(now != NULL) {
            if(now->value < value) {
                result += getSize(now->ch[0]) + 1;
                now = now->ch[1];
            }else {
                now = now->ch[0];
            }
        }
        return result;
    }

    void insert(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        root = merge(tmp.first,merge(new Node(value),tmp.second));
    }

    void remove(int value) {
        int cnt = lowerCount(value);
        DRoot tmp = split(root,cnt);
        root = merge(tmp.first,split(tmp.second,1).second);
    }
};

int main() {
    srand(123456);
    set<int> *colors = new set<int>[MAX_VAL_RANGE + 10];
    for(int i = 1;i <= MAX_VAL_RANGE;i++) {
        colors[i].insert(0);
    }
    int N = read<int>(),sqrtValue = static_cast<int>(sqrt(N)),M = read<int>(),*values = new int[N + 1],*saveColors = new int[N + 1],*belong = new int[N + 1],*l = new int[N + 1],*r = new int[N + 1];
    Treap *treaps = new Treap[N + 1];
    int prevBlock = 1;
    l[1] = 1;
    for(int i = 1;i <= N;i++) {
        belong[i] = (i - 1) / sqrtValue + 1;
        if(belong[i] != prevBlock) {
            r[prevBlock] = i - 1;
            if(r[prevBlock] < l[prevBlock]) {
                exit(1);
            }
            l[belong[i]] = i;
        }
        int tmpValue = read<int>();
        if(tmpValue > MAX_VAL_RANGE) {
            exit(1);
        }
        values[i] = *(colors[tmpValue].rbegin());
        saveColors[i] = tmpValue;
        treaps[belong[i]].insert(values[i]);
        colors[tmpValue].insert(i);
        prevBlock = belong[i];
    }
    r[prevBlock] = N;
    char *buffer = new char[BUFFER_SIZE];
    while(M--) {
        scanf("%s",buffer);
        if(buffer[0] == 'Q') {
            int left = read<int>(),right = read<int>(),start = belong[left] + 1,end = belong[right] - 1,result = 0;
            for(int i = start;i <= end;i++) {
                result += treaps[i].lowerCount(left);
            }
            if(belong[left] != belong[right]) {
                for(int i = left;i <= r[belong[left]];i++) {
                    if(values[i] < left) {
                        result++;
                    }
                }
                for(int i = l[belong[right]];i <= right;i++) {
                    if(values[i] < left) {
                        result++;
                    }
                }
            }else {
                for(int i = left;i <= right;i++) {
                    if(values[i] < left) {
                        result++;
                    }
                }
            }
            printf("%d\n",result);
        }else {
            int pos = read<int>(),newColor = read<int>(),oldColor = saveColors[pos];
            if(newColor == oldColor) {
                continue;
            }
            saveColors[pos] = newColor;
            {
                set<int>::iterator it = colors[oldColor].lower_bound(pos),prev = it,succ = it;
                prev--; succ++;
                if(succ != colors[oldColor].end()) {
                    treaps[belong[*succ]].remove(values[*succ]);
                    values[*succ] = *prev;
                    treaps[belong[*succ]].insert(values[*succ]);
                }
                colors[oldColor].erase(it);
            }
            {
                treaps[belong[pos]].remove(values[pos]);
                colors[newColor].insert(pos);
                set<int>::iterator it = colors[newColor].lower_bound(pos),prev = it,succ = it;
                prev--; succ++;
                values[pos] = *prev;
                treaps[belong[pos]].insert(values[pos]);
                if(succ != colors[newColor].end()) {
                    treaps[belong[*succ]].remove(values[*succ]);
                    values[*succ] = pos;
                    treaps[belong[*succ]].insert(values[*succ]);
                }
            }
        }
    }
    return 0;
}
