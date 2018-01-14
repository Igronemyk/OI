#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int MAX_CHARSET_SIZE = 26;
const char START_CHAR = 'a';
const int MAX_STR_LEN = 1000001;

struct SAM {
    int *fail,*size,**trans,*maxLen,stateSize,strMaxSize,last;

    SAM(int strMaxSize) : stateSize(1) , strMaxSize(strMaxSize) {
        int stateMaxSize = strMaxSize * 2;
        fail = new int[stateMaxSize];
        memset(fail,0,sizeof(int) * stateMaxSize);
        size = new int[stateMaxSize];
        memset(size,0,sizeof(int) * stateMaxSize);
        trans = new int*[stateMaxSize];
        maxLen = new int[stateMaxSize];
        memset(maxLen,0,sizeof(int) * stateMaxSize);
        last = createState(0);
    }

    void insert(char c) {
        int index = c - START_CHAR;
        int newState = createState(maxLen[last] + 1),lastCheck = last;
        last = newState;
        size[newState]++;
        while(lastCheck && !trans[lastCheck][index]) {
            trans[lastCheck][index] = newState;
            lastCheck = fail[lastCheck];
        }
        if(!lastCheck) {
            fail[newState] = 1;
            return;
        }
        int tmpState = trans[lastCheck][index];
        if(maxLen[lastCheck] + 1 == maxLen[tmpState]) {
            fail[newState] = tmpState;
            return;
        }
        int midState = createState(maxLen[lastCheck] + 1);
        memcpy(trans[midState],trans[tmpState],sizeof(int) * MAX_CHARSET_SIZE);
        fail[midState] = fail[tmpState];
        fail[tmpState] = midState;
        fail[newState] = midState;
        while(lastCheck && trans[lastCheck][index] == tmpState) {
            trans[lastCheck][index] = midState;
            lastCheck = fail[lastCheck];
        }
    }

    long long getResult() {
        long long result = 0;
        int *countMax = new int[strMaxSize + 1],*sortedSize = new int[stateSize - 2];
        memset(countMax,0,sizeof(int) * (strMaxSize + 1));
        for(int i = 2;i < stateSize;i++) {
            countMax[maxLen[i]]++;
        }
        for(int i = 1;i <= strMaxSize;i++) {
            countMax[i] += countMax[i - 1];
        }
        for(int i = 2;i < stateSize;i++) {
            sortedSize[--countMax[maxLen[i]]] = i;
        }
        for(int i = stateSize - 3;i >= 0;i--) {
            int pos = sortedSize[i];
            if(fail[pos] > 1) {
                size[fail[pos]] += size[pos];
            }
            if(size[pos] > 1) {
                result = max(result,size[pos] * 1LL * maxLen[pos]);
            }
        }
        return result;
    }

    int createState(int maxLength) {
        int newState = stateSize++;
        trans[newState] = new int[MAX_CHARSET_SIZE];
        memset(trans[newState],0,sizeof(int) * MAX_CHARSET_SIZE);
        maxLen[newState] = maxLength;
        return newState;
    }

};

int main() {
    char *str = new char[MAX_STR_LEN];
    scanf("%s",str);
    int length = strlen(str);
    SAM sam(length);
    for(int i = 0;i < length;i++) {
        sam.insert(str[i]);
    }
    printf("%lld\n",sam.getResult());
    return 0;
}
