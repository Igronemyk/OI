#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

long long upperPow(long long value,int k) {
    long long nowValue = k;
    while(nowValue < value) {
        nowValue *= k;
    }
    return nowValue;
}

struct Node {
    long long value;
    int depth;

    Node() : value(-1) , depth(-1) { }
    Node(long long value,int depth) : value(value) , depth(depth) { }

    bool operator < (const Node &otherNode) const {
        if(value != otherNode.value) {
            return value > otherNode.value;
        }else {
            return depth > otherNode.depth;
        }
    }
};

int main() {
    int n = read<int>(),k = read<int>();
    priority_queue<Node> pq;
    long long upValue = (n - 1) % (k - 1) == 0 ? 0 : (k - 1 - (n - 1) % (k - 1));
    while(upValue) {
        pq.push(Node(0,0));
        upValue--;
    }
    for(int i = 0;i < n;i++) {
        long long value = read<long long>();
        pq.push(Node(value,0));
    }
    long long result = 0;
    while(pq.size() > 1) {
        long long weight = 0;
        int maxDepth = 0;
        for(int i = 0;i < k;i++) {
            Node tmpNode = pq.top();
            pq.pop();
            weight += tmpNode.value;
            maxDepth = max(maxDepth,tmpNode.depth);
        }
        pq.push(Node(weight,maxDepth + 1));
        result += weight;
    }
    printf("%lld\n%d\n",result,pq.top().depth);
    return 0;
}
