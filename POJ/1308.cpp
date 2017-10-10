#include <cstdio>
#include <cstring>

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int MAXN = 101;

struct DisjointSet{
    int *father;
    DisjointSet(int size){
        father = new int[size];
        for(int i = 0;i < size;i++) father[i] = i;
    }

    void reInit(int size){
        for(int i = 0;i < size;i++) father[i] = i;
    }

    int getFather(int u){
        if(father[u] == u) return u;
        return father[u] = getFather(father[u]);
    }

    void merge(int u,int v){
        int faU = getFather(u),faV = getFather(v);
        father[faU] = faV;
    }
};

bool visit[MAXN];

int main(){
    DisjointSet ds(MAXN);
    int firstX = read<int>(),firstY = read<int>(),countValue = 1;
    while(firstX != -1 && firstY != -1){
        memset(visit,false,sizeof(visit));
        bool flag = false;
        ds.reInit(MAXN);
        if(firstX != 0 && firstY != 0) {if(ds.getFather(firstX) != ds.getFather(firstY)) ds.merge(firstX,firstY); else flag = true;}
        if(firstX != 0) visit[firstX] = true;
        if(firstY != 0) visit[firstY] = true;
        int x = firstX,y = firstY,checkPos = firstX;
        if(x != 0 && y != 0){
            x = read<int>();
            y = read<int>();
        }
        while(x != 0 && y != 0){
            if(ds.getFather(x) == ds.getFather(y)){
                flag = true;
            }
            ds.merge(x,y);
            visit[x] = true;
            visit[y] = true;
            x = read<int>();
            y = read<int>();
        }
        if(!flag && checkPos != 0){
            for(int i = 1;i <= MAXN;i++){
                if(visit[i] && ds.getFather(i) != ds.getFather(checkPos)){
                    flag = true;
                    break;
                }
            }
        }
        printf("Case %d ",countValue);
        printf(flag ? "is not a tree.\n" : "is a tree.\n");
        countValue++;
        firstX = read<int>();
        firstY = read<int>();
    }
    return 0;
}
