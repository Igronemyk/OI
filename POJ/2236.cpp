#include <iostream>
#include <utility>
#include <string>

using namespace std;

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
};

int myPow(int a,int b){
    int result = 1,base = a;
    while(b){
        if(b & 1) result *= base;
        base *= base;
        b >>= 1;
    }
    return result;
}

int main(){
    int N,d;
    cin >> N >> d;
    DisjointSet ds(N);
    pair<int,int> *nodes = new pair<int,int>[N];
    bool **canConnect = new bool*[N];
    bool *visit = new bool[N];
    fill(visit,visit + N,false);
    d *= d;
    for(int i = 0;i < N;i++){
        canConnect[i] = new bool[N];
        fill(canConnect[i],canConnect[i] + N,false);
        int x,y;
        cin >> x >> y;
        nodes[i] = make_pair(x,y);
    }
    for(int i = 0;i < N;i++){
        for(int j = i;j < N;j++){
            if(myPow(nodes[i].first - nodes[j].first,2) + myPow(nodes[i].second - nodes[j].second,2) <= d){
                canConnect[i][j] = true;
                canConnect[j][i] = true;
            }
        }
    }
    char opt;
    while(cin >> opt){
        if(opt == 'O'){
            int pos;
            cin >> pos;
            pos--;
            visit[pos] = true;
            for(int i = 0;i < N;i++){
                if(i == pos) continue;
                if(!visit[i]) continue;
                if(canConnect[pos][i]) ds.merge(i,pos);
            }
        }else{
            int pos1,pos2;
            cin >> pos1 >> pos2;
            pos1--;pos2--;
            cout << (ds.getFather(pos1) == ds.getFather(pos2) ? "SUCCESS" : "FAIL") << endl;
        }
    }
    return 0;
}
