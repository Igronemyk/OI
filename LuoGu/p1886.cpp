#include <cstdio>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c -'0';c = getchar();}
    return result * f;
}

template<typename T>
struct Queue {
    T *values;
    int head,tail;
    Queue(int size) {
        values = new T[size];
        head = 0;
        tail = 0;
    }

    T front() {
        return values[head];
    }

    T back() {
        return values[tail - 1];
    }

    void pop_front() {
        head++;
    }

    void pop_back() {
        tail--;
    }

    void push_back(T val) {
        values[tail++] = val;
    }

    int size() {
        return tail - head;
    }

    bool isEmpty() {
        return head == tail;
    }

};

struct Info {
    int value,index;
    Info() : value(-1) , index(-1) { }
    Info(int value,int index) : value(value) , index(index) { }
};

int main() {
    int n = read<int>(),k = read<int>();
    Queue<int> minResult(n - k + 1),maxResult(n - k + 1);
    Queue<Info> minQue(n),maxQue(n);
    for(int i = 0;i < k - 1;i++) {
        int tmpValue = read<int>();
        while(!minQue.isEmpty() && minQue.back().value >= tmpValue) minQue.pop_back();
        minQue.push_back(Info(tmpValue,i));
        while(!maxQue.isEmpty() && maxQue.back().value <= tmpValue) maxQue.pop_back();
        maxQue.push_back(Info(tmpValue,i));
    }
    for(int i = k - 1;i < n;i++) {
        int tmpValue = read<int>();
        while(!minQue.isEmpty() && minQue.back().value >= tmpValue) minQue.pop_back();
        minQue.push_back(Info(tmpValue,i));
        while(!minQue.isEmpty() && i - minQue.front().index + 1 > k) minQue.pop_front();
        while(!maxQue.isEmpty() && maxQue.back().value <= tmpValue) maxQue.pop_back();
        maxQue.push_back(Info(tmpValue,i));
        while(!maxQue.isEmpty() && i - maxQue.front().index + 1 > k) maxQue.pop_front();
        minResult.push_back(minQue.front().value);
        maxResult.push_back(maxQue.front().value);
    }
    for(int i = 0;i < n - k + 1;i++) {
        printf("%d ",minResult.front());
        minResult.pop_front();
    }
    printf("\n");
    for(int i = 0;i < n - k + 1;i++) {
        printf("%d ",maxResult.front());
        maxResult.pop_front();
    }
    printf("\n");
    return 0;
}
