#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_TRIE_NODE_SIZE = 3200010;
const int MAX_CHARSET_SIZE = 2;
const int MAX_BIT_SIZE = 32;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct TrieNode {
    int ch[2],cnt;
} tn[MAX_TRIE_NODE_SIZE];

int trieSize = 0;

struct Trie {
    int root;

    static int newNode() {
        ++trieSize;
        tn[trieSize].ch[0] = 0;
        tn[trieSize].ch[1] = 0;
        tn[trieSize].cnt = 0;
        return trieSize;
    }

    Trie() {
        root = newNode();
    }

    void insert(long long value) {
        int now = root;
        for(int i = MAX_BIT_SIZE;i >= 0;i--) {
            int index = ((1LL << i) & value) != 0;
            if(tn[now].ch[index] == 0) {
                tn[now].ch[index] = newNode();
            }
            now = tn[now].ch[index];
        }
    }

    long long getMaxXorValue(long long value) {
        long long result = 0;
        int now = root;
        for(int i = MAX_BIT_SIZE;i >= 0;i--) {
            int index = ((1LL << i) & value) != 0;
            if(tn[now].ch[!index] != 0) {
                now = tn[now].ch[!index];
                if(index == 0) {
                    result |= (1LL << i);
                }
            }else {
                now = tn[now].ch[index];
                if(index == 1) {
                    result |= (1LL << i);
                }
            }
        }
        return result;
    }

};

int main() {
    int T = read<int>();
    for(int nowCase = 1;nowCase <= T;nowCase++) {
        printf("Case #%d:\n",nowCase);
        trieSize = 0;
        Trie trie;
        int N = read<int>(),M = read<int>();
        for(int i = 0;i < N;i++) {
            long long tmpValue = read<long long>();
            trie.insert(tmpValue);
        }
        while(M--) {
            long long tmpValue = read<long long>();
            printf("%lld\n",trie.getMaxXorValue(tmpValue));
        }
    }
    return 0;
}
