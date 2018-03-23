#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int WSIZE = 10000;
const int TSIZE = 1000000;

int * getNext(char *str,int length) {
    int *next = new int[length + 1];
    next[0] = 0;
    next[1] = 0;
    for(int i = 1;i < length;i++) {
        int j = next[i];
        while(j && str[i] != str[j]) {
            j = next[j];
        }
        next[i + 1] = (str[i] == str[j]) ? j + 1 : 0;
    }
    return next;
}

int kmp(char *root,char *str,int lengthOfRoot,int lengthOfStr) {
    int resultCount = 0,*next = getNext(str,lengthOfStr);
    for(int i = 0,j = 0;i < lengthOfRoot;i++) {
        while(j && root[i] != str[j]) {
            j = next[j];
        }
        if(root[i] == str[j]) {
            j++;
        }
        if(j == lengthOfStr) {
            resultCount++;
        }
    }
    delete[] next;
    return resultCount;
}

int main() {
    int t;
    scanf("%d",&t);
    char *W = new char[WSIZE + 1],*T = new char[TSIZE + 1];
    while(t--) {
        scanf("%s%s",W,T);
        int tLen = strlen(T),wLen = strlen(W);
        printf("%d\n",kmp(T,W,tLen,wLen));
    }
    return 0;
}

