#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_CHARSET_SIZE = 128;
const char FIRST_CHAR = '\0';
const int BUFFER_SIZE = 100;

struct SuffixArray {
    char *str;
    int length;
    int *sa,*rank,*height;
    SuffixArray(char *str,int length) : str(str) , length(length) {
        sa = new int[length];
        rank = new int[length];
        height = new int[length];
        buildSA();
    }

    void buildSA() {
        int nowRange = MAX_CHARSET_SIZE - 1,*x = rank,*y = height,*cnt = new int[max(length,MAX_CHARSET_SIZE)];
        memset(cnt,0,sizeof(int) * (nowRange + 1));
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
            int tmpPos = 0;
            for(int i = length - nowLen;i < length;i++) {
                y[tmpPos++] = i;
            }
            for(int i = 0;i < length;i++) {
                if(sa[i] >= nowLen) {
                    y[tmpPos++] = sa[i] - nowLen;
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
                if(sa[i - 1] + nowLen >= length && sa[i] + nowLen >= length) {
                    if(y[sa[i]] != y[sa[i - 1]]) {
                        x[sa[i]]++;
                    }
                    continue;
                }
                if(y[sa[i]] != y[sa[i - 1]] || (sa[i] + nowLen >= length && sa[i - 1] + nowLen < length) || (sa[i] + nowLen < length && sa[i - 1] + nowLen >= length) || y[sa[i] + nowLen] != y[sa[i - 1] + nowLen]) {
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

    ~SuffixArray() {
        delete[] sa;
        delete[] rank;
        delete[] height;
    }
};

int main() {
    int N;
    scanf("%d",&N);
    char *buffer = new char[BUFFER_SIZE + 1];
    char *str = new char[N * 3 + 2],*result = new char[N + 1];
    int nowPos = 0;
    for(int i = 0;i < N;i++) {
        scanf("%s",buffer);
        str[nowPos++] = buffer[0];
    }
    str[nowPos++] = '$';
    for(int i = N - 1;i >= 0;i--) {
        str[nowPos++] = str[i];
    }
    SuffixArray sa(str,nowPos);
    int left = 0,right = N + 1;
    for(int nowLength = 0;nowLength < N;nowLength++) {
        if(sa.rank[left] < sa.rank[right]) {
            result[nowLength] = str[left++];
        }else {
            result[nowLength] = str[right++];
        }
    }
    nowPos = 0;
    for(int i = 0;i < N;i++) {
        printf("%c",result[i]);
        ++nowPos;
        if(nowPos == 80) {
            printf("\n");
            nowPos = 0;
        }
    }
    printf("\n");
    return 0;
}
