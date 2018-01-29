#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;

const int MAX_LCT_NODE_SIZE = 300010;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c >= '0' && c <= '9') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct LCTNode {
    int father,ch[2];
    int weight,addTag,maxWeight;
    bool rev;

    LCTNode() : weight(0) , addTag(0) , maxWeight(0) , rev(false) {
        ch[0] = 0;
        ch[1] = 0;
    }

    void clear() {
        father = 0;
        ch[0] = 0;
        ch[1] = 0;
        weight = 0;
        addTag = 0;
        maxWeight = 0;
        rev = false;
    }
} ln[MAX_LCT_NODE_SIZE];

struct LCT {

    bool isRoot(int now) {
        return ln[ln[now].father].ch[0] != now && ln[ln[now].father].ch[1] != now;
    }

    void updateInfo(int now) {
        ln[now].maxWeight = max(max(ln[ln[now].ch[0]].maxWeight,ln[ln[now].ch[1]].maxWeight),ln[now].weight);
    }

    void pushDown(int now) {
        if(now == 0) return;
        if(ln[now].addTag != 0) {
            updateAddTag(ln[now].ch[0],ln[now].addTag);
            updateAddTag(ln[now].ch[1],ln[now].addTag);
            ln[now].addTag = 0;
        }
        if(ln[now].rev) {
            updateRevTag(ln[now].ch[0]);
            updateRevTag(ln[now].ch[1]);
            ln[now].rev = false;
        }
    }

    void updateAddTag(int now,int tag) {
        if(now == 0) return;
        ln[now].addTag += tag;
        ln[now].weight += tag;
        ln[now].maxWeight += tag;
    }

    void updateRevTag(int now) {
        if(now == 0) return;
        ln[now].rev = !ln[now].rev;
        swap(ln[now].ch[0],ln[now].ch[1]);
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

    int findRoot(int pos) {
        access(pos);
        splay(pos);
        while(ln[pos].ch[0] != 0) {
            pos = ln[pos].ch[0];
        }
        return pos;
    }

    bool isLinked(int u,int v) {
        return findRoot(u) == findRoot(v);
    }

    void split(int u,int v) {
        makeRoot(u);
        access(v);
        splay(v);
    }

    void link(int u,int v) {
        if(isLinked(u,v)) {
            printf("-1\n");
            return;
        }
        makeRoot(u);
        ln[u].father = v;
    }

    void cut(int u,int v) {
        if(u == v || !isLinked(u,v)) {
            printf("-1\n");
            return;
        }
        split(u,v);
        ln[ln[v].ch[0]].father = 0;
        ln[v].ch[0] = 0;
        updateInfo(v);
    }

    void update(int u,int v,int w) {
        if(!isLinked(u,v)) {
            printf("-1\n");
            return;
        }
        split(u,v);
        updateAddTag(v,w);
    }

    int getMaxWeight(int u,int v) {
        if(!isLinked(u,v)) {
            return -1;
        }
        split(u,v);
        return ln[v].maxWeight;
    }

};

int main() {
    int N;
    LCT lct;
    while(~scanf("%d",&N)) {
        for(int i = 1;i <= N;i++) {
            ln[i].clear();
        }
        for(int i = 1;i <= N - 1;i++) {
            int u = read<int>(),v = read<int>();
            lct.link(u,v);
        }
        for(int i = 1;i <= N;i++) {
            int weight = read<int>();
            lct.update(i,i,weight);
        }
        int Q = read<int>();
        while(Q--) {
            int opt = read<int>();
            switch(opt) {
                case 1: {
                    int x = read<int>(),y = read<int>();
                    lct.link(x,y);
                    break;
                }
                case 2: {
                    int x = read<int>(),y = read<int>();
                    lct.cut(x,y);
                    break;
                }
                case 3: {
                    int w = read<int>(),x = read<int>(),y = read<int>();
                    lct.update(x,y,w);
                    break;
                }
                case 4: {
                    int x = read<int>(),y = read<int>();
                    printf("%d\n",lct.getMaxWeight(x,y));
                    break;
                }
            }
        }
        printf("\n");
    }
    return 0;
}
