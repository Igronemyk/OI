#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_CHILD_SIZE = 2;
const int MAX_DEPTH = 24;
const int MAX_TRIE_NODE_SIZE = 2e7;
const int MAXN = 600010;
const int BUFFER_SIZE = 2;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct TrieNode {
    int ch[MAX_CHILD_SIZE],cnt;

    TrieNode() : cnt(0) {
        ch[0] = 0;
        ch[1] = 0;
    }
} tn[MAX_TRIE_NODE_SIZE];

int trieSize = 0;

struct Trie {
    int root;

    Trie() : root(0) { }

    Trie(int root) : root(newNode(root)) { }

    int newNode() {
        return newNode(0);
    }

    int newNode(int sign) {
        tn[++trieSize] = tn[sign];
        return trieSize;
    }

    void insert(int value) {
        int now = root;
        tn[now].cnt++;
        for(int i = MAX_DEPTH;i >= 0;i--) {
            int index = (value >> i) & 1;
            tn[now].ch[index] = newNode(tn[now].ch[index]);
            now = tn[now].ch[index];
            tn[now].cnt++;
        }
    }

    int getMaxXorValue(int prev,int value) {
        int now = root,result = 0,checkValue = 0;
        for(int i = MAX_DEPTH;i >= 0;i--) {
            int index = !((value >> i) & 1);
            int cnt = tn[tn[now].ch[index]].cnt - tn[tn[prev].ch[index]].cnt;
            if(cnt > 0) {
                now = tn[now].ch[index];
                prev = tn[prev].ch[index];
                result |= (1 << i);
                checkValue |= (index << i);
            }else {
                now = tn[now].ch[!index];
                prev = tn[prev].ch[!index];
                checkValue |= ((!index) << i);
            }
        }
        return result;
    }
};

Trie tries[MAXN];

int getRoot(int sign) {
    if(sign < 0) return 0;
    return tries[sign].root;
}

int main() {
    int N = read<int>(),M = read<int>();
    tries[0] = Trie(0);
    tries[0].insert(0);
    int nowXorValue = 0;
    for(int i = 1;i <= N;i++) {
        int tmpValue = read<int>();
        nowXorValue ^= tmpValue;
        tries[i] = Trie(getRoot(i - 1));
        tries[i].insert(nowXorValue);
    }
    int nowIndex = N + 1;
    char *buffer = new char[BUFFER_SIZE];
    while(M--) {
        scanf("%s",buffer);
        if(buffer[0] == 'A') {
            int x = read<int>();
            tries[nowIndex] = Trie(getRoot(nowIndex - 1));
            nowXorValue ^= x;
            tries[nowIndex].insert(nowXorValue);
            nowIndex++;
        }else if(buffer[0] == 'Q') {
            int l = read<int>(),r = read<int>(),x = read<int>();
            x ^= nowXorValue;
            l--; r--;
            printf("%d\n",tries[r].getMaxXorValue(getRoot(l - 1),x));
        }
    }
    return 0;
}
