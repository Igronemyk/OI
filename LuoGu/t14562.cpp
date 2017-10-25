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

template<typename T>
struct Queue {
    T *values;
    int size,head,tail;
    Queue(int size) : size(size) , head(0) , tail(0) {
        values = new T[size];
    }

    T front() {
        return values[head];
    }

    void pop() {
        head++;
    }

    void push(T val) {
        values[tail++] = val;
    }

    bool isEmpty() {
        return head == tail;
    }

};

/*
struct BCS {

};
*/

struct Data {
    int value,sign;
    Data() : value(-1) , sign(-1) { }
    Data(int value,int sign) : value(value) , sign(sign) { }
    bool operator < (const Data otherData) const {
        return this->value > otherData.value;
    }
};

int main() {
    int n = read<int>(),*values = new int[n];
    Queue<Data> que(n);
    for(int i = 0;i < n;i++) {
        values[i] = read<int>();
        que.push(Data(values[i],i));
    }
    sort(que.values,que.values + que.size);
    bool *isSelected = new bool[n];
    memset(isSelected,false,sizeof(bool) * n);
    while(!que.isEmpty()) {
        Data tmpData = que.front();
        que.pop();
        if(isSelected[tmpData.sign]) {
            continue;
        }
        int leftSelectSign = tmpData.sign + 1;
        while(leftSelectSign >= 0 && isSelected[leftSelectSign]) {
            leftSelectSign--;
        }
        int rightSelectSign = tmpData.sign - 1;
        while(rightSelectSign < n && isSelected[rightSelectSign]) {
            rightSelectSign++;
        }
        if(rightSelectSign == n) {

        }else if(leftSelectSign == -1) {

        }
    }
    return 0;
}
