#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

long long getValue(int *values,int nowLength) {
    int startPos = 14 - nowLength;
    long long result = 0;
    while(startPos <= 15 + nowLength) {
        result = result * 10 + values[startPos++];
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int k,p;
    long long result = 0;
    cin >> k >> p;
    int *values = new int[30],nowLength = 0;
    fill(values,values + 30,0);
    int cntValue = 0;
    while(cntValue < k) {
        values[14]++;
        values[15]++;
        int nowPos = 14;
        while(values[nowPos] > 9) {
            values[nowPos] = 0;
            values[--nowPos]++;
        }
        nowPos = 15;
        while(values[nowPos] > 9) {
            values[nowPos] = 0;
            values[++nowPos]++;
        }
        if(nowPos > 15 + nowLength) {
            nowLength++;
        }
        result = (result + getValue(values,nowLength) % p) % p;
        cntValue++;
    }
    cout << result << endl;
    return 0;
}
