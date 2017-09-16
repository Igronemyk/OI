#include <cstdio>
#include <algorithm>

using namespace std;
/*
int solve(int n){
    int result = 0;
    bool **value = new bool*[n];
    for(int i = 0;i < n;i++){
        value[i] = new bool[n];
    }
    for(int i = 0;i < (1 << n);i++){
        int sumAdd = 0,sumDel = 0;
        for(int j = 0;j < n;j++){
            value[0][j] = (i & (1 << j));
            value[0][j] ? sumAdd++ : sumDel++;
        }
        for(int j = 1;j < n;j++){
            for(int k = 0;k < n - j;k++){
                value[j][k] = !(value[j - 1][k] ^ value[j - 1][k + 1]);
                value[j][k] ? sumAdd++ : sumDel++;
            }
        }
        if(sumAdd == sumDel) result++;
    }
    return result;
}

int main(){
    for(int i = 1;i <= 24;i++){
        printf("%d ",solve(i));
    }
    return 0;
}
*/
int main(){
    int result[] = {1,0,0,4,6,0,0,12,40,0,0,171,410,0,0,1896,5160,0,0,32757,59984,0,0,431095,822229};
    int n;
    while(~scanf("%d",&n)){
        if(n == 0) break;
        printf("%d %d\n",n,result[n]);
    }
    return 0;
}
//1 0 0 4 6 0 0 12 40 0 0 171 410 0 0 1896 5160 0 0 32757 59984 0 0 431095 822229

