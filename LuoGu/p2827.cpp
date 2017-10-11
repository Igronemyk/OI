#include <cstdio>
#include <functional>
#include <algorithm>

using namespace std;

template<typename T>
inline T read(){
    T result = 0;bool f = true;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f = !f;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

const int INF = 0x3f3f3f3f;

struct Queue{
    int *value,head,tail;
    Queue(int size){
        value = new int[size];
        head = 0;
        tail = 0;
    }

    void push(int val){
        value[tail++] = val;
    }

    int front(){
        return head == tail ? -INF : value[head];
    }

    void pop(){
        if(head != tail) head++;
    }
};

int getMaxValue(Queue &que1,Queue &que2,Queue &que3){
    int maxValue = max(que1.front(),max(que2.front(),que3.front()));
    if(que1.front() == maxValue) que1.pop();
    else if(que2.front() == maxValue) que2.pop();
    else if(que3.front() == maxValue) que3.pop();
    return maxValue;
}

int main(){
    int n = read<int>(),m = read<int>(),q = read<int>(),u = read<int>(),v = read<int>(),t = read<int>();
    Queue que1(n),que2(m),que3(m);
    for(int i = 0;i < n;i++) que1.push(read<int>());
    sort(que1.value,que1.value + n,greater<int>());
    for(int i = 0;i < m;i++){
        long long nowLength = getMaxValue(que1,que2,que3) * 1LL + i * q;
        long long length1 = nowLength * u / v;
        long long length2 = nowLength - length1;
        que2.push(static_cast<int>(length1 - (i + 1) * q));
        que3.push(static_cast<int>(length2 - (i + 1) * q));
        if((i + 1) % t == 0){
            printf("%lld ",nowLength);
        }
    }
    printf("\n");
    for(int i = 0;i < n + m;i++){
        long long maxValue = getMaxValue(que1,que2,que3) * 1LL + m * q;
        if((i + 1) % t == 0){
            printf("%lld ",maxValue);
        }
    }
    printf("\n");
    return 0;
}

