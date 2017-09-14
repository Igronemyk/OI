#include <bits/stdc++.h>

using namespace std;

long long Combination(long long n,long long m){
    if(m == 0) return 1;
    if(n == 0) return 0;
    return Combination(n - 1,m - 1) + Combination(n - 1,m);
}

int main(){
    cout << Combination(10009,3);
    return 0;
}
