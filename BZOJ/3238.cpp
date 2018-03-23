#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

const int MAX_CHARSET_SIZE = 128;
const char FIRST_CHAR = '\0';
const int BUFFER_SIZE = 500000;

struct SuffixArray {
    char *str;
    int *rank,*height,*sa,length;

    SuffixArray(char *str,int length) : str(str) , length(length) {
        rank = new int[length];
        height = new int[length];
        sa = new int[length];
        buildSA();
    }

    void buildSA() {
        int nowRange = MAX_CHARSET_SIZE - 1,*x = rank,*y = height,*cnt = new int[max(MAX_CHARSET_SIZE,length)];
        for(int i = 0;i < length;i++) {
            cnt[x[i] = str[i] - FIRST_CHAR]++;
        }
        for(int i = 1;i <= nowRange;i++) {
            cnt[i] += cnt[i - 1];
        }
        for(int i = length - 1;i >= 0;i--) {
            sa[--cnt[x[i]]] = i;
        }
        for(int nowLen = 1;nowLen <= length;nowLen <<= 1) {
            int nowPos = 0;
            for(int i = length - nowLen;i < length;i++) {
                y[nowPos++] = i;
            }
            for(int i = 0;i < length;i++) {
                if(sa[i] >= nowLen) {
                    y[nowPos++] = sa[i] - nowLen;
                }
            }
            memset(cnt,0,sizeof(int) * (nowRange + 1));
            for(int i = 0;i < length;i++) {
                cnt[x[i]]++;
            }
            for(int i = 1;i <= nowRange;i++) {
                cnt[i] += cnt[i - 1];
            }
            for(int i = length - 1;i >= 0;i--) {
                sa[--cnt[x[y[i]]]] = y[i];
            }
            swap(x,y);
            x[sa[0]] = 0;
            for(int i = 1;i < length;i++) {
                x[sa[i]] = x[sa[i - 1]];
                if(sa[i] + nowLen >= length && sa[i - 1] + nowLen >= length) {
                    if(y[sa[i]] != y[sa[i - 1]]) {
                        x[sa[i]]++;
                    }
                    continue;
                }
                if(y[sa[i]] != y[sa[i - 1]] || ((sa[i] + nowLen >= length) ^ (sa[i - 1] + nowLen >= length)) || (y[sa[i] + nowLen] != y[sa[i - 1] + nowLen])) {
                    x[sa[i]]++;
                }
            }
            nowRange = x[sa[length - 1]];
            if(nowRange >= length - 1) break;
        }
        for(int i = 0;i < length;i++) {
            rank[sa[i]] = i;
        }
        int tmpHeight = 0;
        for(int i = 0;i < length;i++) {
            if(rank[i] == 0) {
                height[rank[i]] = 0;
                tmpHeight = 0;
                continue;
            }
            if(tmpHeight > 0) {
                tmpHeight--;
            }
            int tmpPos = sa[rank[i] - 1];
            while(tmpPos + tmpHeight < length && i + tmpHeight < length && str[i + tmpHeight] == str[tmpPos + tmpHeight]) {
                tmpHeight++;
            }
            height[rank[i]] = tmpHeight;
        }
        delete[] cnt;
    }

};

int main() {
    char *buffer = new char[BUFFER_SIZE + 1];
    scanf("%s",buffer);
    int length = strlen(buffer);
    SuffixArray sa(buffer,length);
    for(int i = 0;i < length;i++) {
        printf("%d ",sa.height[i]);
    }
    printf("\n");
    return 0;
}
