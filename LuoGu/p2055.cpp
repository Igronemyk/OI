#include <cstdio>
#include <cstring>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c -}
    return
}

const int MAXN = 60;

namespace Adj {
    struct Edge {
        int next,to;
    } edges[MAXN * MAXN];
    int tot,heads[MAXN];

    void init() {
        tot = 0;
        memset(heads,-1,sizeof(heads));
    }

    void addEdge(int u,int v) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }
}

bool *match,*visit;


int main() {
    int T = read<int>();
    while(T--) {
        init();
        int n = read<int>();
        bool *isSchoolStudent = new bool[n],*isAtSchool = new bool[n];
        for(int i = 0;i < n;i++) {
            isSchoolStudent[i] = read<int>();
        }
        int needValue = 0;
        for(int i = 0;i < n;i++) {
            isAtSchool[i] = read<int>();
            isAtSchool[i] = !isAtSchool[i];
            if(isSchoolStudent[i] && isAtSchool[i]) {
                addEdge(i,i);
            }
            if(!isSchoolStudent[i] || (isSchoolStudent[i] && isAtSchool[i])) {
                needValue++;
            }
        }
        for(int i = 0;i < n;i++) {
            for(int j = 0;j < n;j++) {
                bool tmpValue = read<int>();
                if(tmpValue && isSchoolStudent[j]) {
                    addEdge(i,j);
                }
            }
        }

    }
    return 0;
}
