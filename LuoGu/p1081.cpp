#include <cstdio>
#include <utility>
#include <iostream>
#include <climits>

using namespace std;

const long long INF = INT_MAX;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

/*
template<typename T>
T myAbs(T value) {
    return (value < 0) ? -value : value;
}
*/

long long myAbs(long long a) {
    return a < 0 ? - a : a;
}

struct Data {
    long long firstValue,firstTo,secondValue,secondTo,height;
    Data() : firstValue(INF),firstTo(-1),secondValue(INF),secondTo(-1),height(-1) {}
};

Data *datas;

pair<long long,long long> getValue(int X,int S) {
    long long nowStatus = 0,nowLen = 0,nowPos = S,ALen = 0,BLen = 0;
    while(true) {
        long long selectPos = -1,len = -1;
        if(nowStatus == 0) {
            if(nowLen + datas[nowPos].secondValue <= X) {
                selectPos = datas[nowPos].secondTo;
                len = datas[nowPos].secondValue;
            }
        }else if(nowStatus == 1) {
            if(nowLen + datas[nowPos].firstValue <= X) {
                selectPos = datas[nowPos].firstTo;
                len = datas[nowPos].firstValue;
            }
        }
        if(selectPos == -1) break;
        //printf("SeletPos %d,len %d,nowLen %d,nowStatus %d\n",selectPos,len,nowLen,nowStatus);
        nowLen += len;
        nowPos = selectPos;
        if(nowStatus == 0) {
            ALen += len;
            nowStatus = 1;
        }else {
            BLen += len;
            nowStatus = 0;
        }
    }
    return make_pair(ALen,BLen);
}

int main() {
    int N = read<int>();
    datas = new Data[N];
    for(int i = 0;i < N;i++) {
        long long height = read<int>();
        datas[i].height = height;
        for(int j = 0;j < i;j++) {
            if((myAbs(height - datas[j].height) < datas[j].firstValue) || (myAbs(height - datas[j].height) == datas[j].firstValue && datas[datas[j].firstTo].height > height)) {
                datas[j].secondValue = datas[j].firstValue;
                datas[j].secondTo = datas[j].firstTo;
                datas[j].firstValue = myAbs(height - datas[j].height);
                datas[j].firstTo = i;
            }else if((myAbs(height - datas[j].height < datas[j].secondValue)) || (myAbs(height - datas[j].height) == datas[j].secondValue && datas[datas[j].secondTo].height > height)) {
                datas[j].secondValue = myAbs(height - datas[j].height);
                datas[j].secondTo = i;
            }
        }
    }
    /*
    for(int i = 0;i < N;i++) {
        printf("Data info for %d:\n",i);
        printf("%d %d %d %d %d\n",datas[i].firstValue,datas[i].firstTo,datas[i].secondValue,datas[i].secondTo,datas[i].height);
    }
    */
    int X0 = read<int>(),M = read<int>();
    pair<long long,long long> tmpValue = getValue(X0,0);
    long double resultValue = (tmpValue.second == 0) ? INF : (tmpValue.first * 1.00 / tmpValue.second);
    int result = 0;
    for(int i = 1;i < N;i++) {
        pair<long long,long long> value = getValue(X0,i);
        long double tmpResult = (value.second == 0) ? INF : (value.first * 1.00 / value.second);
        cout << "While in " << i << " the result is " << tmpResult << endl;
        if(tmpResult < resultValue) {
            resultValue = tmpResult;
            result = i;
        }else if(tmpResult == resultValue && datas[i].height > datas[result].height) {
            result = i;
        }
    }
    printf("%d\n",result + 1);
    while(M--) {
        int Si = read<int>(),Xi = read<int>();
        Si--;
        pair<long long,long long> value = getValue(Xi,Si);
        printf("%lld %lld\n",value.first,value.second);
    }
    return 0;
}
/*
3411661 35382998

*/
