#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>
#include <cassert>
#include <cstddef>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

template<typename T,size_t L>
struct MyAllocator {
    struct Data {
        char v[sizeof(T)];
    };

    Data *now;
    int tot;

    MyAllocator() : now(NULL) , tot(0) { }

    inline T *allocate() {
        if(now == NULL || tot == L) {
            now = new Data[L];
            tot = 0;
        }
        T *result = new (now->v) T();
        now++;
        tot++;
        return result;
    }
};

int n = 0;

struct CirEdge {
    int u,v,w,length;
};

struct LCTEdge {
    int w;
    CirEdge *cir;
};

MyAllocator<CirEdge,500010> cirEdgeAllocator;
MyAllocator<LCTEdge,500010> lctEdgeAllocator;

struct LCT {

    static CirEdge *getCir(LCTEdge *e) {
        if(e == NULL) return NULL;
        return e->cir;
    }

    struct LCTInfo {
        bool hasCir;
        int length;
        LCTEdge *head,*tail;
        int headLen,tailLen;

        LCTInfo() : hasCir(false) , length(0) , head(NULL) , tail(NULL) , headLen(0) , tailLen(0) { } 
    
        inline void rev() {
            swap(head,tail);
            swap(headLen,tailLen);
        }

        inline void updateCir(bool value) {
            hasCir = value;
        }

        friend inline LCTInfo operator + (const LCTInfo &a,const LCTInfo &b) {
            assert(a.tail == b.head);
            LCTEdge *link = a.tail;
            LCTInfo info;
            info.hasCir = a.hasCir || link->cir != NULL || b.hasCir;
            info.head = a.head;
            info.tail = b.tail;
            if(getCir(link) == NULL || (getCir(a.head) == getCir(link) && getCir(b.tail) == getCir(link))) {
                info.headLen = a.headLen;
                info.tailLen = b.tailLen;
                info.length = a.length + link->w + b.length;
            }else if(getCir(a.head) == getCir(link)) {
                info.headLen = a.length + link->w + b.headLen;
                info.length = b.length;
                info.tailLen = b.tailLen;
            }else if(getCir(b.tail) == getCir(link)) {
                info.headLen = a.headLen;
                info.length = a.length;
                info.tailLen = a.tailLen + link->w + b.length;
            }else {
                int midLength = a.tailLen + link->w + b.headLen;
                info.headLen = a.headLen;
                info.length = a.length + min(midLength,link->cir->length - midLength) + b.length;
                info.tailLen = b.tailLen;
            }
            return info;
        }
    };
    struct LCTNode {
        LCTNode *fa,*ch[2];
        LCTEdge *prev,*next;
        bool lazyTag,revTag;
        CirEdge *lazy;
        LCTInfo info;

        LCTNode() : fa(NULL) , prev(NULL) , next(NULL) , lazyTag(false) , revTag(false), lazy(NULL) , info(LCTInfo()) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    
        inline void rev() {
            revTag = !revTag;
            swap(ch[0],ch[1]);
            swap(prev,next);
            info.rev();
        }

        inline void addLazy(CirEdge *lazy) {
            lazyTag = true;
            this->lazy = lazy;
            info.updateCir(lazy != NULL && (ch[0] != NULL || ch[1] != NULL));
            if(ch[0] != NULL) prev->cir = lazy;
            if(ch[1] != NULL) next->cir = lazy;
        }

        inline void pushDown() {
            if(revTag) {
                if(ch[0] != NULL) ch[0]->rev();
                if(ch[1] != NULL) ch[1]->rev();
                revTag = false;
            }
            if(lazyTag) {
                if(ch[0] != NULL) ch[0]->addLazy(lazy);
                if(ch[1] != NULL) ch[1]->addLazy(lazy);
                lazyTag = false;
            }
        }

        inline bool isRoot() {
            return fa == NULL || (fa->ch[0] != this && fa->ch[1] != this);
        }

        void update() {
            info = LCTInfo();
            info.head = prev;
            info.tail = next;
            if(ch[0] != NULL) {
                info = ch[0]->info + info;
            }
            if(ch[1] != NULL) {
                info = info + ch[1]->info;
            }
        }
    } *nodes;

    int size;

    LCT(int size) : size(size) {
        nodes = new LCTNode[size + 1];
    }

    void rotate(LCTNode *now) {
        LCTNode *father = now->fa,*anc = father->fa;
        if(!father->isRoot()) {
            anc->ch[anc->ch[1] == father] = now;
        }
        int dir = father->ch[0] == now;
        now->fa = anc;
        father->fa = now;
        father->ch[!dir] = now->ch[dir];
        now->ch[dir] = father;
        if(father->ch[!dir] != NULL) {
            father->ch[!dir]->fa = father;
        }
        father->update();
    }

    void notifyAll(LCTNode *now) {
        if(now == NULL) return;
        if(!now->isRoot()) notifyAll(now->fa);
        now->pushDown();
    }

    void splay(LCTNode *now) {
        if(now == NULL) return;
        notifyAll(now);
        while(!now->isRoot()) {
            LCTNode *father = now->fa,*anc = father->fa;
            if(!father->isRoot()) {
                if((father->ch[0] == now) ^ (anc->ch[0] == father)) {
                    rotate(now);
                }else {
                    rotate(father);
                }
            }
            rotate(now);
        }
        now->update();
    }

    void splay(LCTNode *now,LCTNode *target) {
        if(now == NULL || target == NULL || now == target) return;
        notifyAll(now);
        while(now->fa != target) {
            LCTNode *father = now->fa,*anc = father->fa;
            if(anc != target) {
                if((anc->ch[0] == father) ^ (father->ch[0] == now)) {
                    rotate(now);
                }else {
                    rotate(father);
                }
            }
            rotate(now);
        }
        now->update();
    }

    void access(LCTNode *pos) {
        LCTNode *prev = NULL;
        for(LCTNode *now = pos;now != NULL;now = now->fa) {
            splay(now);
            now->ch[1] = prev;
            if(prev != NULL) {
                now->next = prev->info.head;
            }else {
                now->next = NULL;
            }
            now->update();
            prev = now;
        }
        splay(pos);
    }

    void makeRoot(LCTNode *now) {
        access(now);
        now->rev();
        now->pushDown();
    }

    bool link(int a,int b,int w) {
        if(a == b) return false;
        if(a > b) swap(a,b);
        LCTNode *u = nodes + a,*v = nodes + b;
        makeRoot(v); makeRoot(u);
        if(u->fa == NULL && v->fa == NULL) {
            LCTEdge *e = lctEdgeAllocator.allocate();
            e->w = w;
            e->cir = NULL;
            u->fa = v;
            u->prev = e;
            u->update();
            return true;
        }
        access(v);
        if(v->info.hasCir) {
            return false;
        }
        CirEdge *e = cirEdgeAllocator.allocate();
        e->u = a; e->v = b; e->w = w; e->length = v->info.length + w;
        splay(u,v);
        u->next->cir = e; v->prev->cir = e;
        if(u->ch[1] != NULL) {
            u->ch[1]->addLazy(e);
        }
        u->update();
        v->update();
        return true;
    }

    bool cut(int a,int b,int w) {
        if(a == b) return false;
        if(a > b) swap(a,b);
        LCTNode *u = nodes + a,*v = nodes + b;
        makeRoot(v); access(u);
        if(u->prev != NULL && u->prev->cir != NULL && u->prev->cir->u == a && u->prev->cir->v == b && u->prev->cir->w == w) {
            splay(v,u);
            v->next->cir = NULL; u->prev->cir = NULL;
            if(v->ch[1] != NULL) {
                v->ch[1]->addLazy(NULL);
            }
            v->update();
            u->update();
            return true;
        }
        if(u->ch[0] != v || u->ch[0]->ch[1] != NULL || u->prev->w != w) {
            return false;
        }
        if(!u->prev->cir) {
            v->pushDown();
            u->ch[0] = NULL; v->fa = NULL;
            u->prev = NULL; v->next = NULL;
            u->update();
            v->update();
            return true;
        }
        int cirU = u->prev->cir->u,cirV = u->prev->cir->v,cirW = u->prev->cir->w;
        cut(cirU,cirV,cirW);
        cut(a,b,w);
        link(cirU,cirV,cirW);
        return true;
    }

    int query(int a,int b) {
        LCTNode *u = nodes + a,*v = nodes + b;
        makeRoot(v); makeRoot(u);
        if(u != v && u->fa == NULL && v->fa == NULL) {
            return -1;
        }
        access(v);
        return v->info.length;
    }
};

int main() {
    int n = read<int>(),m = read<int>();
    LCT lct(n);
    char *buffer = new char[10];
    while(m--) {
        scanf("%s",buffer);
        if(buffer[0] == 'l') {
            int u = read<int>(),v = read<int>(),w = read<int>();
            printf(lct.link(u,v,w) ? "ok\n" : "failed\n");
        }else if(buffer[0] == 'c') {
            int u = read<int>(),v = read<int>(),w = read<int>();
            printf(lct.cut(u,v,w) ? "ok\n" : "failed\n");
        }else {
            int u = read<int>(),v = read<int>();
            printf("%d\n",lct.query(u,v));
        }
    }
    return 0;
}
