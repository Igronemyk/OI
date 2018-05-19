#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1e4 + 10;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct LCT {
    int ch[MAXN][2],fa[MAXN],n;
    bool rev[MAXN];

    void init(int n) {
        this->n = n;
        memset(ch,0,sizeof(ch));
        memset(fa,0,sizeof(fa));
        memset(rev,0,sizeof(rev));
    }

    bool isRoot(int now) {
        if(now == 0) return true;
        return ch[fa[now]][0] != now && ch[fa[now]][1] != now;
    }

    void rotate(int now) {
        int father = fa[now],anc = fa[father];
        if(!isRoot(father)) {
            ch[anc][ch[anc][1] == father] = now;
        }
        fa[father] = now;
        fa[now] = anc;
        int dir = ch[father][0] == now;
        ch[father][!dir] = ch[now][dir];
        ch[now][dir] = father;
        if(ch[father][!dir] != 0) {
            fa[ch[father][!dir]] = father;
        }
    }

    void updateRevTag(int now) {
        if(now == 0) return;
        rev[now] = !rev[now];
        swap(ch[now][0],ch[now][1]);
    }

    void pushDown(int now) {
        if(now == 0) return;
        if(!rev[now]) return;
        updateRevTag(ch[now][0]);
        updateRevTag(ch[now][1]);
        rev[now] = false;
    }

    void notifyAll(int now) {
        if(now == 0) return;
        if(!isRoot(now)) notifyAll(fa[now]);
        pushDown(now);
    }

    void splay(int now) {
        if(now == 0) return;
        notifyAll(now);
        while(!isRoot(now)) {
            int father = fa[now],anc = fa[father];
            if(!isRoot(father)) {
                if((ch[father][0] == now) ^ (ch[anc][0] == father)) {
                    rotate(now);
                }else {
                    rotate(father);
                }
            }
            rotate(now);
        }
    }

    void access(int pos) {
        int prev = 0;
        for(int now = pos;now != 0;now = fa[now]) {
            splay(now);
            ch[now][1] = prev;
            prev = now;
        }
    }

    void makeRoot(int now) {
        access(now);
        splay(now);
        updateRevTag(now);
    }

    void split(int u,int v) {
        makeRoot(u);
        access(v);
        splay(v);
    }

    int getFather(int now) {
        splay(now);
        pushDown(now);
        while(ch[now][0] != 0) {
            now = ch[now][0];
            pushDown(now);
        }
        splay(now);
        return now;
    }

    bool isLinked(int u,int v) {
        split(u,v);
        return getFather(u) == getFather(v);
    }
    
    void link(int u,int v) {
        makeRoot(u);
        makeRoot(v);
        fa[v] = u;
    }

    void cut(int u,int v) {
        split(u,v);
        ch[v][0] = 0;
        fa[u] = 0;
    }
} lct;

int main() {
    int n = read<int>(),m = read<int>();
    lct.init(n);
    char *buffer = new char[8];
    while(m--) {
        scanf("%s",buffer);
        if(buffer[0] == 'C') {
            int u = read<int>(),v = read<int>();
            lct.link(u,v);
        }else if(buffer[0] == 'D') {
            int u = read<int>(),v = read<int>();
            lct.cut(u,v);
        }else {
            int u = read<int>(),v = read<int>();
            printf(lct.isLinked(u,v) ? "Yes\n" : "No\n");
        }
    }
    return 0;
}
