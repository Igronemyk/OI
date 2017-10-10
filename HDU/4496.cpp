#include <cstdio>
#include <utility>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
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
        father[faU] = faV;
    }

    bool isLink(int u,int v){
        return this->getFather(u) == this->getFather(v);
    }
};

int main(){
    int N,M;
    while(~scanf("%d%d",&N,&M)){
        pair<int,int> *querys = new pair<int,int>[M];
        DisjointSet ds(N);
        for(int i = 0;i < M;i++){
            int u = read<int>(),v = read<int>();
            querys[i] = make_pair(u,v);
        }
        int nowValue = N;
        int *result = new int[M];
        for(int i = M - 1;i >= 0;i--){
            result[i] = nowValue;
            int city1 = querys[i].first,city2 = querys[i].second;
            if(!ds.isLink(city1,city2)){
                ds.merge(city1,city2);
                nowValue--;
            }
        }
        for(int i = 0;i < M;i++) printf("%d\n",result[i]);
    }
    return 0;
}
