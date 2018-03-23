#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const double EPS = 1e-10;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}


bool gauss(double **values,int size) {
    for(int i = 0;i < size;i++) {
        int nowSelect = i;
        for(int j = i + 1;j < size;j++) {
            if(fabs(values[j][i]) > fabs(values[nowSelect][i])) {
                nowSelect = j;
            }
        }
        if(fabs(values[nowSelect][i]) <= EPS) {
            return false;
        }
        if(nowSelect != i) {
            swap(values[nowSelect],values[i]);
        }
        for(int j = 0;j < size;j++) {
            if(i == j) continue;
            double tmpValue = values[j][i] / values[i][i];
            for(int k = size;k >= i;k--) {
                values[j][k] -= values[i][k] * tmpValue;
            }
        }
    }
    return true;
}

int main() {
    int n = read<int>();
    double **values = new double*[n];
    for(int i = 0;i < n;i++){
        values[i] = new double[n + 1];
        for(int j = 0;j <= n;j++){
            values[i][j] = read<int>();
        }
    }
    bool result = gauss(values,n);
    if(!result) {
        printf("No Solution\n");
    }else {
        for(int i = 0;i < n;i++) {
            printf("%.2lf\n",values[i][n] / values[i][i]);
        }
    }
    return 0;
}
