#include <iostream>
#include <algorithm>

using namespace std;

long long n,sum = 0;

bool check(long long rounds){
    return (n*rounds - sum) >= rounds;
}

int main(){
    cin >> n;
    long long maxValue = 0;
    for(int i = 0;i < n;i++){
        long long tmpValue;
        cin >> tmpValue;
        maxValue = max(maxValue,tmpValue);
        sum += tmpValue;
    }
    long long left = maxValue,right = sum;
    long long result = sum;
    while(left <= right){
        long long mid = (left + right) >> 1;
        if(check(mid)){
            if(mid < result) result = mid;
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
    cout << result << endl;
    return 0;
}
