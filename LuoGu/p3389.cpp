#include <cstdio>
#include <cmath>

using namespace std;

template<typename T>
T read(){
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-')f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

bool check(double value){
    return !(fabs(value) < 0.00000001);
}

int main(){
    int n = read<int>();
    double **values = new double*[n];
    for(int i = 0;i < n;i++){
        values[i] = new double[n + 1];
        for(int j = 0;j <= n;j++){
            values[i][j] = read<int>();
        }
    }
    for(int doing = 0;doing < n - 1;doing++){
        /*
        int maxValue = doing;
        for(int i = doing + 1;i < n;i++) if(values[i][doing] > values[maxValue][doing]) maxValue = i;
        if(maxValue != doing){
            for(int i = doing;i <= n;i++){
                int tmpValue = values[doing][i];
                values[doing][i] = values[maxValue][i];
                values[maxValue][i] = tmpValue;
            }
        }
        */
        for(int i = doing + 1;i < n;i++){
            double weight = values[i][doing] / values[doing][doing];
            for(int j = doing;j <= n;j++){
                values[i][j] -= weight * values[doing][j];
            }
        }
    }
    if(!check(values[n - 1][n - 1]) || !check(values[n - 1][n])){
        printf("No Solution\n");
    }else{
        double *result = new double[n];
        result[n - 1] = values[n - 1][n] / values[n - 1][n - 1];
        for(int i = n - 2;i >= 0;i--){
            double tmpValue = 0;
            for(int j = n - 1;j > i;j--) tmpValue += values[i][j] * result[j];
            result[i] = (values[i][n] - tmpValue) / values[i][i];
        }
        for(int i = 0;i < n;i++) printf("%.2f\n",result[i]);
    }
    return 0;
}
