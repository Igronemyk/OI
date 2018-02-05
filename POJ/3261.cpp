#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct SuffixArray {
    int *str;
    int length;
    int *sa,*rank,*height;
    SuffixArray(int *str,int length) : str(str) , length(length) {
        sa = new int[length];
        rank = new int[length];
        height = new int[length];
        buildSA();
    }

    void buildSA() {
        pair<int,pair<int,int> > *tmp1 = new pair<int,pair<int,int> >[length];
        pair<pair<int,int>,pair<int,int> > *tmp2 = new pair<pair<int,int>,pair<int,int> >[length];
        for(int i = 0;i < length;i++) {
            tmp1[i] = make_pair(str[i],make_pair(length - i - 1,i));
        }
        sort(tmp1,tmp1 + length);
        for(int i = 0;i < length;i++) {
            sa[i] = tmp1[i].second.second;
        }
        rank[sa[0]] = 0;
        for(int i = 1;i < length;i++) {
            rank[sa[i]] = rank[sa[i - 1]];
            if(str[sa[i]] != str[sa[i - 1]]) {
                rank[sa[i]]++;
            }
        }
        for(int nowLen = 1;nowLen <= length;nowLen <<= 1) {
            for(int i = 0;i < length;i++) {
                tmp2[i] = make_pair(make_pair(rank[i],(i + nowLen < length ? rank[i + nowLen] : 0)),make_pair(length - i - 1,i));
            }
            sort(tmp2,tmp2 + length);
            for(int i = 0;i < length;i++) {
                sa[i] = tmp2[i].second.second;
            }
            rank[sa[0]] = 0;
            for(int i = 1;i < length;i++) {
                rank[sa[i]] = rank[sa[i - 1]];
                if(tmp2[i].first != tmp2[i - 1].first) {
                    rank[sa[i]]++;
                }
            }
            if(rank[sa[length - 1]] == length - 1) break;
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
        delete[] tmp1;
        delete[] tmp2;
    }

    ~SuffixArray() {
        delete[] sa;
        delete[] rank;
        delete[] height;
    }
};

int main() {
    int N = read<int>(),K = read<int>(),*values = new int[N];
    for(int i = 0;i < N;i++) {
        values[i] = read<int>();
    }
    SuffixArray sa(values,N);
    int left = 1,right = N,result = -1;
    while(left <= right) {
        int mid = (left + right) >> 1,cnt = 1,maxCnt = 1;
        for(int i = 0;i < N;i++) {
            if(sa.height[i] >= mid) {
                cnt++;
                maxCnt = max(cnt,maxCnt);
            }else {
                cnt = 1;
            }
        }
        if(maxCnt >= K) {
            result = max(result,mid);
            left = mid + 1;
        }else {
            right = mid - 1;
        }
    }
    printf("%d\n",result);
    return 0;
}
