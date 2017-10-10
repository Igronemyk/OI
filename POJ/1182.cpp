#include <cstdio>

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int MAXN = 50000;

struct DisjointSet{
    int *father;
    DisjointSet(int size){
        father = new int[size];
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

    bool isLink(int u,int v){
        return this->getFather(u) == this->getFather(v);
    }
};

int main(){
    int N = read<int>(),K = read<int>();
    DisjointSet ds(3 * MAXN);
    int result = 0;
    for(int i = 0;i < K;i++){
        int D = read<int>(),X = read<int>(),Y = read<int>();
        X--;Y--;
        if(X >= N || Y >= N){
            result++;
            continue;
        }
        if(D == 1){
            if(ds.isLink(X,Y + N) || ds.isLink(X,Y + 2 * N)){
                result++;
            }else{
                ds.merge(X,Y);
                ds.merge(X + N,Y + N);
                ds.merge(X + 2 * N,Y + 2 * N);
            }
        }else{
            if(ds.isLink(X,Y) || ds.isLink(X,Y + 2 * N)){
                result++;
            }else{
                ds.merge(X,Y + N);
                ds.merge(X + N,Y + 2 * N);
                ds.merge(X + 2 * N,Y);
            }
        }
    }
    printf("%d\n",result);
    return 0;
}
