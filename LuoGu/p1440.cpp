#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
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

    void push_back(T val) {
        values[tail++] = val;
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

    void size() {
        return tail - head;
    }

    bool isEmpty() {
        return head == tail;
    }
};

struct Data {
    int val,index;
    Data() : val(-1) , index(-1) { }
    Data(int val,int index) : val(val) , index(index) { }
};

int main() {
    int n = read<int>(),m = read<int>();
    Queue<Data> que(n);
    for(int i = 0;i < n;i++) {
        if(que.isEmpty()) {
            printf("0\n");
        }else {
            printf("%d\n",que.front().val);
        }
        int tmpValue = read<int>();
        while(!que.isEmpty() && que.back().val >= tmpValue) {
            que.pop_back();
        }
        que.push_back(Data(tmpValue,i));
        int beginIndex = i - m + 1;
        if(beginIndex < 0) beginIndex = 0;
        while(!que.isEmpty() && que.front().index < beginIndex) {
            que.pop_front();
        }
    }
    return 0;
}
