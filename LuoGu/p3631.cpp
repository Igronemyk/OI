#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXK = 1e5 + 10;
const int MODDER = 1e9;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct BCS {
    int *father,*value,*relate;
    int size;

    BCS(int size) : size(size) {
        father = new int[size];
        value = new int[size];
        relate = new int[size];
        init();
    }

    void init() {
        for(int i = 0;i < size;i++) father[i] = i;
        memset(value,-1,sizeof(int) * size);
        memset(relate,0,sizeof(int) * size);
    }

    int getFather(int now) {
        if(father[now] == now) return now;
        int newFather = getFather(father[now]);
        relate[now] ^= relate[father[now]];
        father[now] = newFather;
        return newFather;
    }

    bool isLinked(int u,int v) {
        return getFather(u) == getFather(v);
    }

    bool merge(int u,int v,int nowRelate) {
        if(isLinked(u,v)) {
            return (relate[u] ^ relate[v]) == nowRelate;
        }
        int rootU = getFather(u),rootV = getFather(v);
        father[rootU] = rootV;
        relate[rootU] = nowRelate ^ relate[u] ^ relate[v];
        if(value[rootU] != -1 && value[rootV] != -1 && (value[rootU] ^ relate[rootU]) != value[rootV]) {
            return false;
        }
        if(value[rootU] != -1) {
            value[rootV] = value[rootU] ^ relate[rootU];
        }
        return true;
    }

    bool setValue(int now,int nowValue) {
        int root = getFather(now);
        nowValue ^= relate[now];
        if(value[root] != -1 && value[root] != nowValue) {
            return false;
        }
        value[root] = nowValue;
        return true;
    }
};

int n,m,k;

struct Info {
    int x,y,value;

    Info() : x(0) , y(0) , value(0) { }

    Info(int x,int y,int value) : x (x) , y(y) , value(value) { }
} infos[MAXK];

int getRowSign(int now) {
    return now - 2;
}

int getColSign(int now) {
    return now - 2 + n - 1;
}

int getExpectedValue(int x,int y) {
    if(!(x & 1) && !(y & 1)) {
        return 1;
    }
    return 0;
}

int getResult(int nowValue) {
    BCS bcset(n + m - 1);
    for(int i = 0;i < k;i++) {
        Info &tmpInfo = infos[i];
        if(tmpInfo.x == 1) {
            bool result = bcset.setValue(getColSign(tmpInfo.y),tmpInfo.value);
            if(!result) return 0;
        }else if(tmpInfo.y == 1) {
            bool result = bcset.setValue(getRowSign(tmpInfo.x),tmpInfo.value);
            if(!result) return 0;
        }else {
            int row = getRowSign(tmpInfo.x),col = getColSign(tmpInfo.y);
            int nowRelate = nowValue ^ getExpectedValue(tmpInfo.x,tmpInfo.y) ^ tmpInfo.value;
            bool result = bcset.merge(row,col,nowRelate);
            if(!result) return 0;
        }
    }
    int result = 1;
    for(int i = 0;i < n + m - 2;i++) {
        if(bcset.getFather(i) == i && bcset.value[i] == -1) {
            result = (result << 1) % MODDER;
        }
    }
    return result;
}

int main() {
    n = read<int>(); m = read<int>(); k = read<int>();
    int setValue = -1,nowIndex = 0;
    for(int i = 0;i < k;i++) {
        int x = read<int>(),y = read<int>();
        if(x == 1 && y == 1) {
            setValue = read<int>();
        }else {
            int value = read<int>();
            infos[nowIndex++] = Info(x,y,value);
        }
    }
    k = nowIndex;
    if(setValue == -1) {
        int result = getResult(0);
        result += getResult(1);
        printf("%d\n",result % MODDER);
    }else {
        printf("%d\n",getResult(setValue));
    }
    return 0;
}

