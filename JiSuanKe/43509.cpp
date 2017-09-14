#include <bits/stdc++.h>

using namespace std;


double **mem;
int N,k;


bool check(double value){
    return false;
}

double dfs(int qLeft,int pos,double *A,double *B){
    if(mem[qLeft][pos] == -1){
        if(qLeft == 1){
            mem[qLeft][pos] = abs(A[N] - A[pos] - (B[N] - B[pos]));
        }else{
            double maxResult = -1;
            for(int i = 1;i <= N - qLeft + 1;i++){
                double caled = dfs(qLeft - 1,pos + i,A,B) + abs((A[pos + i] - A[pos]) - (B[pos + i] - B[pos]));
                if(maxResult == -1 || caled > maxResult) maxResult = caled;
            }
            mem[qLeft][pos] = maxResult;
        }
    }
    return mem[qLeft][pos];
}

int main(){
    ios::sync_with_stdio(false);
    cin >> N >> k;
    mem = new double*[k + 1];
    for(int i = 0 ;i <= N;i++){
        mem[i] = new double[N + 1];
        fill(mem[i],mem[i] + N + 1,-1);
    }
    double *A = new double[N + 1],*B = new double[N + 1];
    A[0] = 0;
    B[0] = 0;
    for(int i = 1;i <= N;i++){
        double tmpValue;
        cin >> tmpValue;
        A[i] = A[i - 1] + tmpValue;
    }
    for(int i = 1;i <= N;i++){
        double tmpValue;
        cin >> tmpValue;
        B[i] = B[i - 1] + tmpValue;
    }
    double result = dfs(k,0,A,B);
    cout << setprecision(6) << fixed << result << endl;
    return 0;
}
