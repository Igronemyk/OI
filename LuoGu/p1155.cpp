#include <cstdio>
#include <stack>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct Stack {
    int *value,size,tail;
    Stack(int size) : size(size) {
        value = new int[size];
        tail = 0;
    }

    void push(int val) {
        value[tail++] = val;
    }

    void pop() {
        tail--;
    }

    int top() {
        return value[tail - 1];
    }

    bool isEmpty() {
        return tail == 0;
    }
};

struct Queue {
    int *value,size,head,tail;
    Queue(int size) : size(size) {
        value = new int[size];
        head = 0;
        tail = 0;
    }

    void push(int val) {
        value[tail++] = val;
    }

    void pop() {
        head++;
    }

    int front() {
        return value[head];
    }

    bool isEmpty() {
        return head == tail;
    }
};

Stack stk1(1010),stk2(1010);
int result[2010];
int *values,n;


bool dfs(int nowPos,int nowDoing,int nowOptPos) {
    if(nowPos == n) {
        while(true) {
            if(!stk1.isEmpty() && stk1.top() == nowDoing) {
                result[nowOptPos++] = 1;
                nowDoing++;
                stk1.pop();
            }else if(!stk2.isEmpty() && stk2.top() == nowDoing) {
                result[nowOptPos++] = 3;
                nowDoing++;
                stk2.pop();
            }else {
                break;
            }
        }
        return true;
    }
    if(stk1.isEmpty() || stk1.top() > values[nowPos]) {
        int tmpNowOptPos = nowOptPos,tmpNowDoing = nowDoing;
        result[tmpNowOptPos++] = 0;
        stk1.push(values[nowPos]);
        while(!stk1.isEmpty() && stk1.top() == tmpNowDoing) {
            result[tmpNowOptPos++] = 1;
            tmpNowDoing++;
            stk1.pop();
        }
        bool result = dfs(nowPos + 1,tmpNowDoing,tmpNowOptPos);
        if(result) return true;
        while(tmpNowDoing - 1 >= nowDoing) {
            stk1.push(tmpNowDoing - 1);
            tmpNowDoing--;
        }
        if(!stk1.isEmpty() && stk1.top() == values[nowPos]) stk1.pop();
    }
    if(stk2.isEmpty() || stk2.top() > values[nowPos]) {
        int tmpNowOptPos = nowOptPos,tmpNowDoing = nowDoing;
        while(!stk2.isEmpty() && stk2.top() == tmpNowDoing) {
            result[tmpNowOptPos++] = 3;
            tmpNowDoing++;
            stk2.pop();
        }
        result[tmpNowOptPos++] = 2;
        stk2.push(values[nowPos]);
        bool result = dfs(nowPos + 1,tmpNowDoing,tmpNowOptPos);
        if(result) return true;
        stk2.pop();
        while(tmpNowDoing - 1 >= nowDoing) {
            stk2.push(tmpNowDoing - 1);
            tmpNowDoing--;
        }
    }
    return false;
}

int main() {
    n = read<int>();
    if(n <= 10) {
        values = new int[n];
        for(int i = 0;i < n;i++) {
            values[i] = read<int>();
        }
        bool solved = dfs(0,1,0);
        if(solved) {
            for(int i = 0;i < 2 * n;i++) {
                printf("%c ",result[i] + 'a');
            }
            printf("\n");
        }else {
            printf("0\n");
        }
    }else {
        Stack s1(n),s2(n);
        Queue ans(n * 2 + 1);
        bool flag = true;
        int nowDoing = 1;
        for(int i = 0;i < n;i++) {
            int tmpValue = read<int>();
            if(s1.isEmpty()) {
                s1.push(tmpValue);
                ans.push(0);
            }else if(s1.top() > tmpValue) {
                s1.push(tmpValue);
                ans.push(0);
            }else {
                while(true) {
                    if(!s2.isEmpty() &&s2.top() == nowDoing) {
                        ans.push(3);
                        nowDoing++;
                        s2.pop();
                    }else {
                        break;
                    }
                }
                if(s2.isEmpty()) {
                    s2.push(tmpValue);
                    ans.push(2);
                }else if(s2.top() > tmpValue) {
                    s2.push(tmpValue);
                    ans.push(2);
                }else {
                    flag = false;
                    break;
                }
            }
            while(true) {
                if(!s1.isEmpty() && s1.top() == nowDoing) {
                    ans.push(1);
                    nowDoing++;
                    s1.pop();
                }else {
                    break;
                }
            }
        }
        while(true) {
            if(!s1.isEmpty() && s1.top() == nowDoing) {
                ans.push(1);
                nowDoing++;
                s1.pop();
            }else if(!s2.isEmpty() && s2.top() == nowDoing) {
                ans.push(3);
                nowDoing++;
                s2.pop();
            }else {
                if(nowDoing != n + 1) flag = false;
                break;
            }
        }
        if(flag) {
            while(!ans.isEmpty()) {
                printf("%c ",ans.front() + 'a');
                ans.pop();
            }
            printf("\n");
        }else {
            printf("0\n");
        }
    }
    return 0;
}
