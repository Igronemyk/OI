#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int BUFFER_SIZE = 1;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' ||c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

int main() {
    int N = read<int>(),Q = read<int>(),blockSize = static_cast<int>(sqrt(N)),blockCnt = (N / blockSize) + 1,*l = new int[blockCnt],*r = new int[blockCnt],*belong = new int[N],*values = new int[N];
    int lastBlock = -1,realBlockCnt = 0;
    for(int i = 0;i < N;i++) {
        int tmpValue = read<int>(),belongBlock = i / blockSize;
        if(belongBlock != lastBlock) {
            if(lastBlock != -1) {
                r[lastBlock] = i - 1;
            }
            l[belongBlock] = i;
            lastBlock = belongBlock;
            realBlockCnt++;
        }
        belong[i] = belongBlock;
        values[i] = tmpValue;
    }
    r[lastBlock] = N - 1;
    int *sizes = new int[realBlockCnt];
    for(int i = 0;i < realBlockCnt;i++) {
        sizes[i] = r[i] - l[i] + 1;
    }
    int **sortedValues = new int*[realBlockCnt],*addTags = new int[realBlockCnt];
    memset(addTags,0,sizeof(int) * realBlockCnt);
    for(int i = 0;i < realBlockCnt;i++) {
        sortedValues[i] = new int[sizes[i]];
        memcpy(sortedValues[i],values + l[i],sizeof(int) * sizes[i]);
        sort(sortedValues[i],sortedValues[i] + sizes[i]);
    }
    char *buffer = new char[BUFFER_SIZE + 1];
    while(Q--) {
        scanf("%s",buffer);
        if(buffer[0] == 'M') {
            int L = read<int>(),R = read<int>(),W = read<int>();
            L--; R--;
            if(belong[L] == belong[R]) {
                int block = belong[L];
                for(int i = L;i <= R;i++) {
                    values[i] += W;
                }
                memcpy(sortedValues[block],values + l[block],sizeof(int) * sizes[block]);
                sort(sortedValues[block],sortedValues[block] + sizes[block]);
                continue;
            }
            for(int i = belong[L] + 1;i <= belong[R] - 1;i++) {
                addTags[i] += W;
            }
            {
                int block = belong[L];
                for(int i = L;i <= r[block];i++) {
                    values[i] += W;
                }
                memcpy(sortedValues[block],values + l[block],sizeof(int) * sizes[block]);
                sort(sortedValues[block],sortedValues[block] + sizes[block]);
            }
            {
                int block = belong[R];
                for(int i = l[block];i <= R;i++) {
                    values[i] += W;
                }
                memcpy(sortedValues[block],values + l[block],sizeof(int) * sizes[block]);
                sort(sortedValues[block],sortedValues[block] + sizes[block]);
            }
        }else {
            int L = read<int>(),R = read<int>(),C = read<int>();
            L--; R--;
            if(belong[L] == belong[R]) {
                int result = 0,block = belong[L];
                for(int i = L;i <= R;i++) {
                    if(values[result] + addTags[block] >= C) {
                        result++;
                    }
                }
                printf("%d\n",result);
            }else {
                int result = 0;
                for(int i = belong[L] + 1;i <= belong[R] - 1;i++) {
                    int checkValue = C - addTags[i];
                    result += (sortedValues[i] + sizes[i]) - lower_bound(sortedValues[i],sortedValues[i] + sizes[i],checkValue);
                }
                {
                    int block = belong[L];
                    for(int i = L;i <= r[block];i++) {
                        if(values[i] + addTags[block] >= C) {
                            result++;
                        }
                    }
                }
                {
                    int block = belong[R];
                    for(int i = l[block];i <= R;i++) {
                        if(values[i] + addTags[block] >= C) {
                            result++;
                        }
                    }
                }
                printf("%d\n",result);
            }
        }
    }
    return 0;
}
