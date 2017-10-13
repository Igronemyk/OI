#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

template<typename T>
inline T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Data{
    int left,right,sign;
    Data() : left(-1) , right(-1) , sign(-1) {}
    Data(int left,int right,int sign) : left(left) , right(right) ,sign(sign) {}
    bool operator < (const Data otherData) const{
        return this->right != otherData.right ? this->right > otherData.right : this->left < otherData.left;
    }
};

Data datas[MAXN];
int result[MAXN],value[MAXN];

int lowbit(int val){
    return val & -val;
}

void update(int pos,int val){
    for(int i = pos;i <= MAXN;i += lowbit(i)){
        value[i] += val;
    }
}

int getSum(int pos){
    int result = 0;
    for(int i = pos;i > 0;i -= lowbit(i)){
        result += value[i];
    }
    return result;
}

int main(){
    int N;
    while((N = read<int>()) != 0){
        memset(result,0,sizeof(result));
        memset(value,0,sizeof(value));
        for(int i = 0;i < N;i++){
            int S = read<int>(),E = read<int>();
            S++;E++;
            datas[i].left = S;
            datas[i].right = E;
            datas[i].sign = i;
        }
        sort(datas,datas + N);
        int prevLeft = -1,prevRight = -1,sameData = 0;
        for(int i = 0;i < N;i++){
            if(prevLeft == datas[i].left && prevRight == datas[i].right){
                sameData++;
            }else{
                sameData = 0;
                prevLeft = datas[i].left;
                prevRight = datas[i].right;
            }
            result[datas[i].sign] = getSum(datas[i].left) - sameData;
            update(datas[i].left,1);
        }
        for(int i = 0;i < N;i++){
            printf("%d ",result[i]);
        }
        printf("\n");
    }
    return 0;
}
