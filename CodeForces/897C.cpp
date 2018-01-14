#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;


const string f0 = "What are you doing at the end of the world? Are you busy? Will you save us?";
const string frontStr = "What are you doing while sending \"";
const string midStr = "\"? Are you busy? Will you send \"";
const string endStr = "\"?";
const int F0_LEN = 75;
const int FRONT_LEN = 34;
const int MID_LEN = 32;
const int END_LEN = 2;;
const int MAX_LEN_N = 53;

long long lengthValue[MAX_LEN_N + 1];

char dfs(int nowDepth,long long nowValue) {
     if(nowDepth == 0) {
        if(nowValue > F0_LEN) {
            return '.';
        }else {
            return f0[nowValue - 1];
        }
    }
    if(nowValue <= FRONT_LEN) {
        return frontStr[nowValue - 1];
    }
    nowValue -= FRONT_LEN;
    if(nowDepth > MAX_LEN_N || nowValue <= lengthValue[nowDepth - 1]) {
        return dfs(nowDepth - 1,nowValue);
    }
    nowValue -= lengthValue[nowDepth - 1];
    if(nowValue <= MID_LEN) {
        return midStr[nowValue - 1];
    }
    nowValue -= MID_LEN;
    if(nowDepth > MAX_LEN_N || nowValue <= lengthValue[nowDepth - 1]) {
        return dfs(nowDepth - 1,nowValue);
    }
    nowValue -= lengthValue[nowDepth - 1];
    if(nowValue <= END_LEN) {
        return endStr[nowValue - 1];
    }
    return '.';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q;
    cin >> q;
    lengthValue[0] = 75;
    for(int i = 1;i <= MAX_LEN_N;i++) {
        lengthValue[i] = lengthValue[i - 1] * 2 + 68;
    }
    while(q--) {
        int n;
        cin >> n;
        long long k;
        cin >> k;
        cout << dfs(n,k);
    }
    cout << endl;
    return 0;
}
