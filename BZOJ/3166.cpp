#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>
#include <set>

using namespace std;

const int MAX_CHILD_SIZE = 2;
const int MAX_DEPTH = 30;
const int MAX_TRIE_NODE_SIZE = 2e6;
const int MAXN = 50010;

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


    Trie copy() {
        return Trie(root);
    }

};

Trie tries[MAXN];

int main() {
    int n = read<int>();
    pair<int,int> *values = new pair<int,int>[n];
    for(int i = 0;i < n;i++) {
        int index = i + 1,tmpValue = read<int>();
        tries[index] = tries[index - 1].copy();
        tries[index].insert(tmpValue);
        values[i].first = tmpValue;
        values[i].second = index;
    }
    sort(values,values + n);
    set<int> nowValues;
    nowValues.insert(-1); nowValues.insert(0); nowValues.insert(n + 1); nowValues.insert(n + 2);
    nowValues.insert(values[n - 1].second);
    int result = 0;
    for(int i = n - 2;i >= 0;i--) {
        pair<int,int> &tmpValue = values[i];
        set<int>::iterator it1 = nowValues.lower_bound(tmpValue.second),it2 = it1;
        it1++; it2--; it2--;
        int left = *it2,right = *it1;
        left = max(left,1); right = min(right,n);
        result = max(result,tries[right].getMaxXorValue(tries[left - 1].root,tmpValue.first));
        nowValues.insert(tmpValue.second);
    }
    printf("%d\n",result);
    return 0;
}
