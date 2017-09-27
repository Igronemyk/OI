#include <cstdio>

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Data{
    int A,B,C;
    Data() : A(0), B (0) , C(0) {}
    Data(int A,int B,int C) : A(A) , B(B) , C(C) {}
    int getSum(){
        return this->A + this->B + this->C;
    }
    void setValue(Data otherData){
        this->A = otherData.A;
        this->B = otherData.B;
        this->C = otherData.C;
    }
};

bool isVaild[1000];
Data dp[1000];
int nextValue[] = {-6,-5,-4};

int main(){
    int N = read<int>();
    isVaild[0] = true;
    for(int i = 1;i <= N;i++){
        for(int j = 0;j < 3;j++){
            if(i + nextValue[j] < 0 || !isVaild[i + nextValue[j]]) continue;
            if(!isVaild[i] || dp[i].getSum() < dp[i + nextValue[j]].getSum() + 1){
                if(!isVaild[i]) isVaild[i] = true;
                dp[i].setValue(dp[i + nextValue[j]]);
                switch(j){
                    case 0:{
                        dp[i].A++;
                        break;
                    }
                    case 1:{
                        dp[i].B++;
                        break;
                    }
                    case 2:{
                        dp[i].C++;
                        break;
                    }
                }
            }
        }
    }
    if(!isVaild[N]){
        printf("Data wrong!\n");
    }else{
        printf("A=%d B=%d C=%d\n",dp[N].A,dp[N].B,dp[N].C);
    }
    return 0;
}
