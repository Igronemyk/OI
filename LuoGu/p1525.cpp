#include <cstdio>
#include <algorithm>

using namespace std;

template<typename T>
inline T read(){
    T result = 0;bool f = true;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = !f;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

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
        if(faU == faV) return;
        father[faU] = faV;
    }

    bool isLinked(int u,int v){
        return getFather(u) == getFather(v);
    }
};

struct Data{
    int u,v,val;
    Data() : u(-1) , v(-1) , val(-1) {}
    Data(int u,int v,int val) : u(u) , v(v) , val(val) {}
    bool operator < (const Data otherData) const{
        return this->val > otherData.val;
    }
};

int main(){
    int N = read<int>(),M = read<int>();
    DisjointSet ds(2 * N);
    Data *datas = new Data[M];
    for(int i = 0;i < M;i++){
        int u = read<int>() - 1,v = read<int>() - 1,val = read<int>();
        datas[i] = Data(u,v,val);
    }
    sort(datas,datas + M);
    int result = 0;
    for(int i = 0;i < M;i++){
        if(ds.isLinked(datas[i].u,datas[i].v) || ds.isLinked(datas[i].u + N,datas[i].v + N)){
            result = datas[i].val;
            break;
        }else{
            ds.merge(datas[i].u + N,datas[i].v);
            ds.merge(datas[i].u,datas[i].v + N);
        }
    }
    printf("%d\n",result);
    return 0;
}
