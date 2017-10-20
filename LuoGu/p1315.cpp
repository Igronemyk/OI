#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Visitor{
    int T,A,B;
    Visitor() : T(-1) , A(-1) , B(-1) { }
    Visitor(int T,int A,int B) : T(T) , A(A) , B(B) { }
};

struct BIT {
    int *values,size;
    BIT(int size) : size(size) {
        values = new int[size + 1];
    }

    void update(int pos,int val) {
        while(pos <= size) {
            values[pos] += val;
            pos += lowbit(pos);
        }
    }

    int sum(int pos) {
        int result = 0;
        while(pos) {
            result += values[pos];
            pos -= lowbit(pos);
        }
        return result;
    }

    int getValue(int pos) {
        return sum(pos) - sum(pos - 1);
    }

    int lowbit(int val) {
        return val & - val;
    }
};

struct VisitNode {
    int weight,pos;
    VisitNode() : weight(-1) , pos(-1) { }
    bool operator < (const VisitNode node) const {
        return this->weight > node.weight;
    }
};

int main() {
    int n = read<int>(),m = read<int>(),k = read<int>();
    if(k == 0) {
        int *values = new int[n],*lastArriveTime = new int[n],*index = new int[n];
        Visitor *visitors = new Visitor[m];
        index[0] = 0;
        memset(lastArriveTime,0,sizeof(int) * n);
        for(int i = 0;i < n - 1;i++) {
            values[i] = read<int>();
            index[i + 1] = index[i] + values[i];
        }
        for(int i = 0;i < m;i++) {
            int T = read<int>(),A = read<int>(),B = read<int>();
            A--;B--;
            visitors[i].T = T;
            visitors[i].A = A;
            visitors[i].B = B;
            lastArriveTime[A] = max(lastArriveTime[A],T);
        }
        int *startTime = new int[n];
        startTime[0] = lastArriveTime[0];
        for(int i = 1;i < n - 1;i++) {
            startTime[i] = max(lastArriveTime[i],startTime[i - 1] + values[i - 1]);
        }
        long long sumValue = 0;
        for(int i = 0;i < m;i++) {
            Visitor &tmpVisitor = visitors[i];
            sumValue += (startTime[tmpVisitor.B - 1] + values[tmpVisitor.B - 1]) - tmpVisitor.T;
        }
        printf("%lld\n",sumValue);
    }else {

    }
    return 0;
}
