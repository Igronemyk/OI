#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int LCT_MAX_NDOE_SIZE = 100010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct LCTNode {
    int father,ch[2],value,xorValue;
    bool rev;

    void clear() {
        father= 0;
        ch[0] = 0;
        ch[1] = 0;
        value = 0;
        xorValue = 0;
        rev = false;
    }
} ln[LCT_MAX_NDOE_SIZE];

struct LCT {

    bool isRoot(int now) {
        if(ln[now].father == now) return true;
        return ln[ln[now].father].ch[0] != now && ln[ln[now].father].ch[1] != now;
    }

    void updateInfo(int now) {
        ln[now].xorValue = ln[ln[now].ch[0]].xorValue ^ ln[ln[now].ch[1]].xorValue ^ ln[now].value;
    }

    void pushDown(int now) {
        if(now == 0) return;
        if(!ln[now].rev) return;
        updateRevTag(ln[now].ch[0]);
        updateRevTag(ln[now].ch[1]);
        swap(ln[now].ch[0],ln[now].ch[1]);
        updateRevTag(now);
    }

    void updateRevTag(int now) {
        if(now == 0) return;
        ln[now].rev = !ln[now].rev;
    }

    void notifyAll(int now) {
        if(!isRoot(now)) notifyAll(ln[now].father);
        pushDown(now);
    }

    void rotate(int now) {
        int father = ln[now].father,anc = ln[father].father;
        if(!isRoot(father)) {
            ln[anc].ch[ln[anc].ch[1] == father] = now;
        }
        ln[now].father = anc;
        ln[father].father = now;
        int direction = ln[father].ch[0] == now;
        ln[father].ch[!direction] = ln[now].ch[direction];
        ln[now].ch[direction] = father;
        if(ln[father].ch[!direction] != 0) {
            ln[ln[father].ch[!direction]].father = father;
        }
        updateInfo(father);
        updateInfo(now);
    }

    void splay(int now) {
        if(now == 0) return;
        notifyAll(now);
        while(!isRoot(now)) {
            int father = ln[now].father,anc = ln[father].father;
            if(!isRoot(father)) {
                if((ln[anc].ch[0] == father) ^ (ln[father].ch[0] == now)) {
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
        for(int now = pos;now != 0;now = ln[now].father) {
            splay(now);
            ln[now].ch[1] = prev;
            updateInfo(now);
            prev = now;
        }
    }

    void makeRoot(int pos) {
        access(pos);
        splay(pos);
        updateRevTag(pos);
    }

    void split(int u,int v) {
        makeRoot(u);
        access(v);
        splay(v);
    }

    void link(int u,int v) {
        makeRoot(u);
        ln[u].father = v;
    }

    void changeValue(int pos,int newValue) {
        makeRoot(pos);
        ln[pos].value = newValue;
        updateInfo(pos);
    }

    int getXorValue(int u,int v) {
        split(u,v);
        return ln[v].xorValue;
    }
};
int main() {
    int T = read<int>();
    LCT lct;
    while(T--) {
        int N = read<int>(),Q = read<int>();
        for(int i = 1;i <= N;i++) {
            ln[i].clear();
        }
        for(int i = 0;i < N - 1;i++) {
            int u = read<int>(),v = read<int>();
            lct.link(u,v);
        }
        for(int i = 1;i <= N;i++) {
            int tmpValue = read<int>();
            lct.changeValue(i,tmpValue + 1);
        }
        while(Q--) {
            int opt = read<int>(),x = read<int>(),y = read<int>();
            if(opt == 0) {
                lct.changeValue(x,y + 1);
            }else {
                int xorValue = lct.getXorValue(x,y);
                printf("%d\n",xorValue - 1);
            }
        }
    }
    return 0;
}
