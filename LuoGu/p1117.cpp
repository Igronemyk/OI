#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_CHARSET_SIZE = 26;
const char FIRST_CHAR = 'a';
const int BUFFER_SIZE = 3e4 + 1;
const int MAX_RANGE = 3e4 + 1;

int log2Value[MAX_RANGE];

struct SuffixArray {
    char *str;
    int length;
    int *sa,*rank,*height,**values;
    SuffixArray(char *str,int length) : str(str) , length(length) {
        sa = new int[length];
        rank = new int[length];
        height = new int[length];
        buildSA();
        buildST();
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

    void buildST() {
        int depth = log2Value[length];
        values = new int*[length];
        for(int i = 0;i < length;i++) {
            values[i] = new int[depth + 1];
            values[i][0] = height[i];
        }
        for(int nowDepth = 1;nowDepth <= depth;nowDepth++) {
            for(int startPos = 0;startPos + (1 << nowDepth) - 1 < length;startPos++) {
                values[startPos][nowDepth] = min(values[startPos][nowDepth - 1],values[startPos + (1 << (nowDepth - 1))][nowDepth - 1]);
                printf("mn[%d][%d]=%d\n",startPos + 1,nowDepth,values[startPos][nowDepth]);
            }
        }
    }

    int lcp(int left,int right) {
        printf("Old cal %d,%d\n",left,right);
        if(left >= length || right >= length) return 0;
        left = rank[left];
        right = rank[right];
        if(left > right) swap(left,right);
        left++;
        printf("Caling %d,%d\n",left,right);
        int logValue = log2Value[right - left + 1];
        printf("k=%d\n",logValue);
        int result = max(values[left][logValue],values[right - (1 << logValue) + 1][logValue]);
        printf("Return %d\n",result);
        return result;
    }

    ~SuffixArray() {
        delete[] sa;
        delete[] rank;
        delete[] height;
        for(int i = 0;i < log2Value[length];i++) {
            delete[] values[i];
        }
        delete[] values;
    }

    void printDebug() {
        printf("SA:\n");
        for(int i = 0;i < length;i++) {
            printf("%d ",sa[i]);
        }
        printf("\n");
        printf("Rank:\n");
        for(int i = 0;i < length;i++) {
            printf("%d ",rank[i]);
        }
        printf("\n");
        printf("Height:\n");
        for(int i = 0;i < length;i++) {
            printf("%d ",height[i]);
        }
        printf("\n");
    }
};

int main() {
    for(int i = 2;i < MAX_RANGE;i++) {
        log2Value[i] = log2Value[i >> 1] + 1;
    }
    int T;
    scanf("%d",&T);
    char *str = new char[BUFFER_SIZE];
    while(T--) {
        scanf("%s",str);
        int length = strlen(str);
        int *stValue = new int[length],*edValue = new int[length];
        memset(stValue,0,sizeof(int) * length);
        memset(edValue,0,sizeof(int) * length);
        SuffixArray suffix(str,length);
        printf("SuffixInfo:\n");
        suffix.printDebug();
        reverse(str,str + length);
        SuffixArray prefix(str,length);
        reverse(str,str + length);
        printf("%s\n",str);
        printf("PrefixInfo:\n");
        prefix.printDebug();
        for(int nowLen = 1;nowLen <= length / 2;nowLen++) {
            printf("Doing %d\n",nowLen);
            for(int firstPos = nowLen - 1,secondPos = firstPos + nowLen;secondPos < length;firstPos += nowLen,secondPos += nowLen) {
                int lcp = min(suffix.lcp(firstPos,secondPos),nowLen),lcs = min(prefix.lcp(length - 1 - firstPos + 1,length - 1 - secondPos + 1),nowLen - 1);
                int canAdd = lcp + lcs - nowLen + 1;
                printf("Checking %d,%d,%d,%d,%d\n",firstPos + 1,secondPos + 1,lcp,lcs,canAdd);
                if(lcp + lcs >= nowLen) {
                    stValue[max(firstPos - lcs,0)]++;
                    if(firstPos - lcs + canAdd < length) {
                        stValue[firstPos - lcs + canAdd]--;
                    }
                    edValue[max(secondPos + lcp - canAdd,0)]++;
                    if(secondPos + lcp < length) {
                        edValue[secondPos + lcp]--;
                    }
                }
            }
        }
        for(int i = 1;i < length;i++) {
            stValue[i] += stValue[i - 1];
            edValue[i] += edValue[i - 1];
        }
        long long result = 0;
        for(int i = 0;i < length - 1;i++) {
            result += edValue[i] * 1LL * stValue[i + 1];
        }
        printf("%lld\n",result);
        delete[] stValue;
        delete[] edValue;
    }
    delete[] str;
    return 0;
}
