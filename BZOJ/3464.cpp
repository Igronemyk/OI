#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>
#include <vector>
#include <set>
#include <climits>

using namespace std;

const int MAXM = 5e5 + 10;
const int MAXN = 1e5 + 10;
const int BUFFER_SIZE = 10;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct LCT {
    int ch[MAXM][2],fa[MAXM],siz[MAXM],sig[MAXM],sigSiz[MAXM],w[MAXM],sumW[MAXM],lazy[MAXM],maxW[MAXN],maxWSign[MAXN];
    bool rev[MAXM];
    LCT() {
        memset(ch,0,sizeof(ch));
        memset(fa,0,sizeof(fa));
        memset(sig,0,sizeof(sig));
        memset(sigSiz,0,sizeof(sigSiz));
        memset(w,0,sizeof(w));
        memset(sumW,0,sizeof(sumW));
        memset(lazy,-1,sizeof(lazy));
        memset(maxW,0,sizeof(maxW));
        memset(rev,0,sizeof(rev));
        memset(maxWSign,0,sizeof(maxWSign));
    }

    int nodeSize;


    void init(int nodeSize) {
        this->nodeSize = nodeSize;
        fill(siz,siz + MAXM,1);
        fill(siz,siz + nodeSize + 1,0);
    }


    void upd(int now) {
        sumW[now] = sumW[ch[now][0]] + sumW[ch[now][1]] + w[now];
        siz[now] = siz[ch[now][0]] + siz[ch[now][1]] + (now > nodeSize);
        sigSiz[now] = sigSiz[ch[now][0]] + sigSiz[ch[now][1]] + (sig[now] != 0);
        maxW[now] = max((now > nodeSize ? w[now] : 0),max(maxW[ch[now][0]],maxW[ch[now][1]]));
        maxWSign[now] = 0;
        if(maxW[now] != 0) {
            if(maxW[now] == w[now]) {
                maxWSign[now] = now;
            }else if(maxW[now] == maxW[ch[now][0]]) {
                maxWSign[now] = ch[now][0];
            }else if(maxW[now] == maxW[ch[now][1]]) {
                maxWSign[now] = ch[now][1];
            }
        }
    }

    bool isRoot(int now) {
        if(now == 0) return true;
        if(fa[now] == 0) return true;
        return ch[fa[now]][0] != now && ch[fa[now]][1] != now;
    }

    void rot(int now) {
        int father = fa[now],anc = fa[father];
        if(!isRoot(father)) {
            ch[anc][ch[anc][1] == father] = now;
        }
        fa[now] = anc;
        fa[father] = now;
        int dir = ch[father][0] == now;
        ch[father][!dir] = ch[now][dir];
        ch[now][dir] = father;
        if(ch[father][!dir] != 0) {
            fa[ch[father][!dir]] = father;
        }
        upd(father);
        upd(now);
    }

    void updLazy(int now,int newLazy) {
        if(now == 0) return;
        lazy[now] = newLazy;
        if(newLazy != 0) {
            sigSiz[now] = siz[now];
        }else {
            sigSiz[now] = 0;
        }
        if(now > nodeSize) {
            sig[now] = newLazy;
        }
    }

    void updRev(int now) {
        if(now == 0) return;
        rev[now] = !rev[now];
        swap(ch[now][0],ch[now][1]);
    }

    void pd(int now) {
        if(now == 0) return;
        if(lazy[now] != -1) {
            updLazy(ch[now][0],lazy[now]);
            updLazy(ch[now][1],lazy[now]);
            lazy[now] = -1;
        }
        if(rev[now]) {
            updRev(ch[now][0]);
            updRev(ch[now][1]);
            rev[now] = false;
        }
    }

    void notifyAll(int now) {
        if(now == 0) return;
        if(!isRoot(now)) notifyAll(fa[now]);
        pd(now);
    }
    
    void splay(int now) {
        if(now == 0) return; 
        notifyAll(now);
        while(!isRoot(now)) {
            int father = fa[now],anc = fa[father];
            if(!isRoot(father)) {
                if((ch[anc][0] == father) ^ (ch[father][0] == now)) {
                    rot(now);
                }else {
                    rot(father);
                }
            }
            rot(now);
        }
    }

    void access(int now) {
        int prev = 0;
        for(;now != 0;now = fa[now]) {
            splay(now);
            ch[now][1] = prev;
            upd(now);
            prev = now;
        }
    }

    void makeRoot(int now) {
        access(now);
        splay(now);
        updRev(now);
    }

    int getFather(int now) {
        if(now == 0) return 0;
        access(now);
        splay(now);
        pd(now);
        while(ch[now][0] != 0) {
            now = ch[now][0];
            pd(now);
        }
        return now;
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }

    void split(int u,int v) {
        makeRoot(u);
        access(v);
        splay(v);
    }

    int check(int u,int v) {
        if(!isLinked(u,v)) return 0;
        split(u,v);
        if(sigSiz[v] != 0) {
            return 2;
        }else {
            return 1;
        }
    }

    void link(int u,int v) {
        makeRoot(u);
        fa[u] = v;
    }

    void cut(int u,int v) {
        split(u,v);
        if(ch[v][0] == u && ch[u][1] == 0) {
            ch[v][0] = 0;
            fa[u] = 0;
            upd(v);
        }
    }

    void setSign(int u,int v,int sign) {
        split(u,v);
        updLazy(v,sign);
    }

    void changeWeight(int sign,int weight) {
        makeRoot(sign);
        w[sign] = weight;
        upd(sign);
    }

    int getMax(int u,int v) {
        split(u,v);
        return maxW[v];
    }

    int getMaxSign(int u,int v) {
        split(u,v);
        return maxWSign[v];
    }

    int getSign(int now) {
        makeRoot(now);
        pd(now);
        return sig[now];
    }


    int getSum(int u,int v) {
        split(u,v);
        return sumW[v];
    }

} lct;


struct Edge {
    int sign,u,v,w;

    Edge() : sign(0) , u(0) , v(0) , w(0) { }

    Edge(int sign,int u,int v,int w) : sign(sign) , u(u) , v(v) , w(w) { }

    bool operator < (const Edge &otherEdge) const {
        if(u != otherEdge.u) return u < otherEdge.u;
        if(v != otherEdge.v) return v < otherEdge.v;
        return w < otherEdge.w;
    }
};

set<Edge> others;
set<Edge> nows;

int from[MAXM],to[MAXM],weights[MAXM];

int main() {
    int n = read<int>(),m = read<int>(),nowSign = n;
    lct.init(n);
    char *buffer = new char[BUFFER_SIZE];
    while(m--) {
        scanf("%s",buffer);
        if(buffer[0] == 'l') {
            int u = read<int>(),v = read<int>(),w = read<int>();
            if(u == v) {
                printf("failed\n");
                continue;
            }
            if(u > v) swap(u,v);
            int sign = ++nowSign;
            from[sign] = u;
            to[sign] = v;
            weights[sign] = w;
            Edge newEdge(sign,u,v,w);
            int linkState = lct.check(u,v);
            if(linkState == 0) {
                lct.changeWeight(sign,w);
                lct.link(u,sign);
                lct.link(sign,v);
                nows.insert(newEdge);
                printf("ok\n");
            }else if(linkState == 1) {
                int maxWeight = lct.getMax(u,v);
                if(w < maxWeight) {
                    int maxSign = lct.getMaxSign(u,v);
                    Edge removeEdge(maxSign,from[maxSign],to[maxSign],weights[maxSign]);
                    nows.erase(removeEdge);
                    others.insert(removeEdge);
                    lct.cut(from[maxSign],maxSign);
                    lct.cut(maxSign,to[maxSign]);
                    lct.changeWeight(sign,w);
                    lct.link(u,sign);
                    lct.link(sign,v);
                    nows.insert(newEdge);
                    lct.setSign(removeEdge.u,removeEdge.v,removeEdge.sign);
                }else {
                    lct.setSign(u,v,sign);
                    others.insert(newEdge);
                }
                printf("ok\n");
            }else if(linkState == 2) {
                printf("failed\n");
            }
        }else if(buffer[0] == 'c') {
            int u = read<int>(),v = read<int>(),w = read<int>();
            if(u == v) {
                printf("failed\n");
                continue;
            }
            if(u > v) swap(u,v);
            {
                set<Edge>::iterator it = others.lower_bound(Edge(-1,u,v,w));
                if(it != others.end() && it->u == u && it->v == v && it->w == w) {
                    others.erase(it);
                    lct.setSign(u,v,0);
                    printf("ok\n");
                    continue;
                }
            }
            {
                set<Edge>::iterator it = nows.lower_bound(Edge(-1,u,v,w));
                if(it != nows.end() && it->u == u && it->v == v && it->w == w) {
                    Edge tmpEdge = *it;
                    int sign = lct.getSign(tmpEdge.sign);
                    if(sign != 0) {
                        Edge removeEdge(sign,from[sign],to[sign],weights[sign]);
                        lct.setSign(from[sign],to[sign],0);
                        others.erase(removeEdge);
                        nows.insert(removeEdge);
                        nows.erase(it);
                        lct.setSign(removeEdge.u,removeEdge.v,0);
                        lct.cut(u,tmpEdge.sign);
                        lct.cut(tmpEdge.sign,v);
                        lct.changeWeight(removeEdge.sign,removeEdge.w);
                        lct.link(removeEdge.u,removeEdge.sign);
                        lct.link(removeEdge.sign,removeEdge.v);
                    }else {
                        nows.erase(it);
                        lct.cut(u,it->sign);
                        lct.cut(it->sign,v);
                    }
                    printf("ok\n");
                }else {
                    printf("failed\n");
                }
            }
        }else if(buffer[0] == 'd') {
            int u = read<int>(),v = read<int>();
            if(u == v) {
                printf("0\n");
            }else if(!lct.isLinked(u,v)) {
                printf("-1\n");
            }else {
                printf("%d\n",lct.getSum(u,v));
            }
        }
    }
    return 0;
}
