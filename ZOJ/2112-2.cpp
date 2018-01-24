#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 50010;
const int INF = 0x3f3f3f3f;
const int MAX_OPT_NUM = 100000;
const int BUFFER_SIZE = 2;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if( c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct BIT {
    int values[MAXN + 1];

    void update(int pos,int val) {
        for(int i = pos;i <= MAXN;i += lowbit(i)) {
            values[i] += val;
        }
    }

    int getSum(int pos) {
        int result = 0;
        while(pos) {
            result += values[pos];
            pos -= lowbit(pos);
        }
        return result;
    }

    int lowbit(int val) {
        return val & -val;
    }

    void clear() {
        memset(values,0,sizeof(values));
    }

} bitree;

struct Operator {
    int type,left,right,val,id,cnt;
    Operator() : type(0) , left(0) , right(0) , val(0) , id(0) , cnt(0) { }
    Operator(int type,int left,int right,int val,int id,int cnt) : type(type) , left(left) , right(right) , val(val) , id(id) , cnt(cnt) { }
} opts[MAX_OPT_NUM],opts1[MAX_OPT_NUM],opts2[MAX_OPT_NUM];

int result[MAX_OPT_NUM + 1],values[MAXN + 1];
char buffer[BUFFER_SIZE];

void cdq(int left,int right,int leftRange,int rightRange) {
    if(left > right) return;
    if(leftRange == rightRange) {
        for(int i = left;i <= right;i++) {
            if(opts[i].type == 3) {
                result[opts[i].id] = leftRange;
            }
        }
        return;
    }
    int midRange = (leftRange + rightRange) >> 1,count1 = 0,count2 = 0;
    for(int i = left;i <= right;i++) {
        Operator &tmpOpt = opts[i];
        switch(tmpOpt.type) {
            case 1: {
                if(tmpOpt.val <= midRange) {
                    bitree.update(tmpOpt.left,1);
                    opts1[count1++] = tmpOpt;
                }else {
                    opts2[count2++] = tmpOpt;
                }
                break;
            }
            case 2: {
                if(tmpOpt.val <= midRange) {
                    bitree.update(tmpOpt.left,-1);
                    opts1[count1++] = tmpOpt;
                }else {
                    opts2[count2++] = tmpOpt;
                }
                break;
            }
            case 3: {
                int cnt = bitree.getSum(tmpOpt.right) - bitree.getSum(tmpOpt.left - 1);
                if(tmpOpt.cnt - cnt <= 0) {
                    opts1[count1++] = tmpOpt;
                }else {
                    tmpOpt.cnt -= cnt;
                    opts2[count2++] = tmpOpt;
                }
                break;
            }
        }
    }
    for(int i = left;i <= right;i++) {
        Operator &tmpOpt = opts[i];
        switch(tmpOpt.type) {
            case 1: {
                if(tmpOpt.val <= midRange) {
                    bitree.update(tmpOpt.left,-1);
                }
                break;
            }
            case 2: {
                if(tmpOpt.val <= midRange) {
                    bitree.update(tmpOpt.left,1);
                }
                break;
            }
        }
    }
    for(int i = 0;i < count1;i++) {
        opts[left + i] = opts1[i];
    }
    for(int i = 0;i < count2;i++) {
        opts[left + count1 + i] = opts2[i];
    }
    cdq(left,left + count1 - 1,leftRange,midRange);
    cdq(left + count1,right,midRange + 1,rightRange);
}

int main() {
    int T = read<int>();
    while(T--) {
        bitree.clear();
        int N = read<int>(),M = read<int>(),countOpt = 0;
        for(int i = 1;i <= N;i++) {
            int tmpValue = read<int>();
            values[i] = tmpValue;
            opts[countOpt++] = Operator(1,i,-1,tmpValue,-1,-1);
        }
        int countQueryOpt = 0;
        while(M--) {
            scanf("%s",buffer);
            if(buffer[0] == 'Q') {
                int left = read<int>(),right = read<int>(),k = read<int>();
                opts[countOpt++] = Operator(3,left,right,-1,countQueryOpt++,k);
            }else {
                int pos = read<int>(),value = read<int>();
                opts[countOpt++] = Operator(2,pos,-1,values[pos],-1,-1);
                opts[countOpt++] = Operator(1,pos,-1,value,-1,-1);
                values[pos] = value;
            }
        }
        cdq(0,countOpt - 1,0,INF);
        for(int i = 0;i < countQueryOpt;i++) {
            printf("%d\n",result[i]);
        }
    }
    return 0;
}
