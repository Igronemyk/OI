#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int BUFFER_SIZE = 1e6 + 1;

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
    char *str = new char[BUFFER_SIZE];
    scanf("%s",str);
    int length = strlen(str);
    SuffixArray sa(str,length);
    for(int i = 0;i < length;i++) {
        printf("%d ",sa.sa[i] + 1);
    }
    printf("\n");
    delete[] str;
    return 0;
}
