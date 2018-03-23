#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_TRIE_NODE_SIZE = 100010;
const int MAX_CHARSET_SIZE = 10;
const char FIRST_CHAR = '0';
const int BUFFER_SIZE = 10;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct TrieNode {
    int trans[MAX_CHARSET_SIZE];
    bool isEnd;

    TrieNode() {
        memset(trans,0,sizeof(int) * MAX_CHARSET_SIZE);
        isEnd = false;
    }
} tn[MAX_TRIE_NODE_SIZE];

int trieSize = 0;

struct Trie {
    int root;

    Trie() : root(newNode()) { }

    int newNode() {
        tn[++trieSize] = TrieNode();
        return trieSize;
    }

    void insert(char *str) {
        int now = root;
        for(int i = 0;str[i];i++) {
            int index = str[i] - FIRST_CHAR;
            if(tn[now].trans[index] == 0) {
                tn[now].trans[index] = newNode();
            }
            now = tn[now].trans[index];
        }
        tn[now].isEnd = true;
    }

    bool check() {
        return dfs(root,false);
    }

    bool dfs(int now,bool isContains) {
        if(now == 0) return true;
        if(tn[now].isEnd && isContains) {
            return false;
        }
        bool flag = true;
        for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
            if(!flag) break;
            flag = dfs(tn[now].trans[i],isContains | tn[now].isEnd);
        }
        return flag;
    }
};

char buffer[BUFFER_SIZE + 1];

int main() {
    int T = read<int>();
    while(T--) {
        trieSize = 0;
        Trie trie;
        int n = read<int>();
        while(n--) {
            scanf("%s",buffer);
            trie.insert(buffer);
        }
        bool flag = trie.check();
        if(flag) {
            printf("YES\n");
        }else {
            printf("NO\n");
        }
    }
    return 0;
}
