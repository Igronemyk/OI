#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
using namespace std;

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
    return resultCount;
}

int main() {
    char *root = new char[1000010],*s = new char[1000010];
    int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%s%s",s,root);
        int len1 = strlen(root),len2 = strlen(s);
        printf("%d\n",kmp(root,s,len1,len2));
    }
    return 0;
}
