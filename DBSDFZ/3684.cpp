#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int BUFFER_SIZE = 1e5;

struct BigInteger {
    static const int MAX_LEN = 1200;
    static const int NUM = 9;
    static const int LIMIT = 1e9;

    int *values,length;

    BigInteger() {
        init();
    }

    BigInteger(char *str) {
        init();
        int strLen = strlen(str),nowPos = strLen - 1;
        length = strLen / NUM;
        for(int i = 1;i <= length;i++) {
            for(int j = nowPos - NUM + 1;j <= nowPos;j++) {
                values[i] = values[i] * 10 + str[j] - '0';
            }
            nowPos -= NUM;
        }
        if(strLen % NUM != 0) {
            length++;
            for(int i = 0;i <= nowPos;i++) {
                values[length] = values[length] * 10 + str[i] - '0';
            }
        }
    }

    void init() {
        length = 0;
        values = new int[MAX_LEN + 1];
        memset(values,0,sizeof(int) * (MAX_LEN + 1));
    }

    bool operator < (const BigInteger &otherInteger) const {
        if(length != otherInteger.length) return length < otherInteger.length;
        for(int i = length;i >= 1;i--) {
            if(values[i] != otherInteger.values[i]) {
                return values[i] < otherInteger.values[i];
            }
        }
        return false;
    }

    void operator *= (int value) {
        for(int i = 1;i <= length;i++) {
            values[i] *= value;
        }
        int nowPos = 1;
        while(nowPos <= length) {
            if(values[nowPos] >= LIMIT) {
                values[nowPos + 1] += values[nowPos] / LIMIT;
                values[nowPos] %= LIMIT;
            }
            if(nowPos == length && values[nowPos + 1]) {
                length++;
            }
            nowPos++;
        }
    }

    void operator /= (int value) {
        for(int i = length;i >= 1;i--) {
            values[i - 1] += values[i] % value * LIMIT;
            values[i] /= value;
        }
        while(values[length] == 0 && length > 0) {
            length--;
        }
    }

    void operator -= (BigInteger &otherInteger) {
        for(int i = 1;i <= length;i++) {
            values[i] -= otherInteger.values[i];
            if(values[i] < 0) {
                values[i] += LIMIT;
                values[i + 1]--;
            }
        }
        while(values[length] == 0 && length > 0) {
            length--;
        }
    }

    void print() {
        for(int i = length;i >= 1;i--) {
            printf((i == length ? "%d" : "%09d"),values[i]);
        }
        printf("\n");
    }

    bool isZero() {
        if(length <= 1 && values[1] == 0) return true;
        return false;
    }

    bool isOdd() {
        return values[1] & 1;
    }

};

int main() {
    char *buffer = new char[BUFFER_SIZE + 1];
    scanf("%s",buffer);
    BigInteger A(buffer);
    scanf("%s",buffer);
    BigInteger B(buffer);
    int cnt = 0;
    while(!A.isZero() && !B.isZero()) {
        if(A < B) swap(A,B);
        bool isA = A.isOdd(),isB = B.isOdd();
        if(!isA && !isB) {
            cnt++;
            A /= 2;
            B /= 2;
        }else if(isA && isB) {
            A -= B;
        }else {
            if(isA) {
                B /= 2;
            }else {
                A /= 2;
            }
        }
    }
    if(A < B) swap(A,B);
    while(cnt--) {
        A *= 2;
    }
    A.print();
    return 0;
}
