#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_LEN = 110010;

int manacher(char *str,char *newStr,int *RL) {
    memset(newStr,0,sizeof(char) * ((MAX_LEN + 1) * 2));
    int oldLen = strlen(str);
    newStr[0] = '#';
    int outputIndex = 1;
    for(int i = 0;i < oldLen;i++) {
        newStr[outputIndex++] = str[i];
        newStr[outputIndex++] = '#';
    }
    int maxRight = -1,pos = -1,result = 0,len = outputIndex;
    memset(RL,0,sizeof(int) * outputIndex);
    for(int i = 0;i < len;i++) {
        if(i < maxRight) {
            RL[i] = min(RL[2 * pos - i],maxRight - i);
        }else {
            RL[i] = 1;
        }
        while(i - RL[i] >= 0 && i + RL[i] < len && newStr[i - RL[i]] == newStr[i + RL[i]]) {
            RL[i]++;
        }
        if(i + RL[i] - 1 > maxRight) {
            maxRight = i + RL[i] - 1;
            pos = i;
        }
        result = max(result,RL[i] - 1);
    }
    return result;
}

int main() {
    char *str = new char[MAX_LEN],*newStr = new char[(MAX_LEN + 1) * 2];
    int *RL = new int[(MAX_LEN + 1) * 2];
    while(~scanf("%s",str)) {
        printf("%d\n",manacher(str,newStr,RL));
    }
    return 0;
}
