#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <cmath>
#include <utility>

using namespace std;

const int BUFFER_SIZE = 13;
const int MAX_PRINT_CNT = 10;
const int MAX_PLAYER_SIZE = 1e6;
const int MAX_CHARSET_SIZE = 26;
const int FIRST_CHAR = 'A';


template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

template<typename T>
T read(char *str,int pos) {
    T result = 0;
    for(;str[pos] >= '0' && str[pos] <= '9';pos++) {
        result = result * 10 + str[pos] - '0';
    }
    return result;
}

struct Trie {
    struct Node {
        Node *childs[MAX_CHARSET_SIZE];
        int sign;

        Node() : sign(-1) {
            memset(childs,static_cast<int>(NULL),sizeof(Node *) * MAX_CHARSET_SIZE);
        }

        bool hasChild(int index) {
            return childs[index] != NULL;
        }

    };

    Node *root;
    int sign;

    Trie() : sign(0) {
        root = new Node();
    }

    int insert(char *str) {
        Node *now = root;
        for(int i = 0;str[i];i++) {
            int index = str[i] - FIRST_CHAR;
            if(!now->hasChild(index)) {
                now->childs[index] = new Node();
            }
            now = now->childs[index];
        }
        if(now->sign == -1) now->sign = sign++;
        return now->sign;
    }

};

struct Treap {
    struct Node {
        Node *childs[2];
        int sign,priority,size,uploadTime;
        long long value;

        Node() : sign(-1) , priority(-1) , size(-1) , uploadTime(-1) , value(-1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }

        Node(long long value,int uploadTime,int sign) : sign(sign) , priority(rand()) , size(1) , uploadTime(uploadTime) , value(value) {
            childs[0] = NULL;
            childs[1] = NULL;
        }
    };

    typedef pair<Node *,Node *> DRoot;

    Node *root;

    Treap() : root(NULL) { }

    static int getSize(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    static void updateInfo(Node *now) {
        if(now == NULL) return;
        now->size = getSize(now->childs[0]) + getSize(now->childs[1]) + 1;
    }

    static Node *merge(Node *a,Node *b) {
        if(a == NULL) return b;
        if(b == NULL) return a;
        if(a->priority > b->priority) {
            a->childs[1] = merge(a->childs[1],b);
            updateInfo(a);
            return a;
        }else {
            b->childs[0] = merge(a,b->childs[0]);
            updateInfo(b);
            return b;
        }
    }

    static DRoot split(Node *now,int k) {
        DRoot result(NULL,NULL);
        if(now == NULL) return result;
        if(k <= getSize(now->childs[0])) {
            result = split(now->childs[0],k);
            now->childs[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(now->childs[1],k - getSize(now->childs[0]) - 1);
            now->childs[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    static bool comp(long long value,int uploadTime,long long otherValue,int otherUploadTime) {
        if(value != otherValue) {
            return value > otherValue;
        }else {
            return uploadTime < otherUploadTime;
        }
    }

    int lowerCount(long long value,int uploadTime) {
        int result = 0;
        Node *now = root;
        while(now != NULL) {
            if(comp(now->value,now->uploadTime,value,uploadTime)) {
                result += getSize(now->childs[0]) + 1;
                now = now->childs[1];
            }else {
                now = now->childs[0];
            }
        }
        return result;
    }

    int rank(long long value,int uploadTime) {
        return lowerCount(value,uploadTime) + 1;
    }

    void insert(long long value,int uploadTime,int sign) {
        int cnt = lowerCount(value,uploadTime);
        DRoot tmp = split(root,cnt);
        Node *newNode = new Node(value,uploadTime,sign);
        root = merge(tmp.first,merge(newNode,tmp.second));
    }

    void remove(long long value,int uploadTime) {
        int cnt = lowerCount(value,uploadTime);
        DRoot tmp = split(root,cnt);
        root = merge(tmp.first,split(tmp.second,1).second);
    }

    void printResult(int rank,char **players) {
        rank--;
        DRoot tmp1 = split(root,rank);
        int cnt = min(tmp1.second->size,MAX_PRINT_CNT);
        DRoot tmp2 = split(tmp1.second,cnt);
        int nowPrinted = 0;
        print(tmp2.first,players,cnt,nowPrinted);
        printf("\n");
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
    }

    void print(Node *now,char **players,int readyToPrint,int &nowPrinted) {
        if(now == NULL) return;
        print(now->childs[0],players,readyToPrint,nowPrinted);
        printf("%s",players[now->sign]);
        nowPrinted++;
        if(readyToPrint != nowPrinted) printf(" ");
        print(now->childs[1],players,readyToPrint,nowPrinted);
    }

};

int main() {
    srand(123456);
    int n = read<int>(),*uploadTimes = new int[n];
    long long *scores = new long long[n];
    Trie trie;
    Treap treap;
    char *buffer = new char[BUFFER_SIZE],**players = new char*[n];
    fill(players,players + n,static_cast<char *>(NULL));
    int uploadTime = 0;
    while(n--) {
        memset(buffer,0,sizeof(char) * BUFFER_SIZE);
        scanf("%s",buffer);
        int length = strlen(buffer);
        switch(buffer[0]) {
            case '+': {
                long long score;
                scanf("%lld",&score);
                int sign = trie.insert(buffer + 1);
                treap.insert(score,uploadTime,sign);
                if(players[sign] == NULL) {
                    players[sign] = new char[BUFFER_SIZE];
                    memset(players[sign],0,sizeof(char) * BUFFER_SIZE);
                    memcpy(players[sign],buffer + 1,sizeof(char) * (length - 1));
                }else {
                    treap.remove(scores[sign],uploadTimes[sign]);
                }
                scores[sign] = score;
                uploadTimes[sign] = uploadTime++;
                break;
            }
            case '?': {
                if(buffer[1] >= '0' && buffer[1] <= '9') {
                    int tmpRank = read<int>(buffer,1);
                    treap.printResult(tmpRank,players);
                }else {
                    int sign = trie.insert(buffer + 1);
                    printf("%d\n",treap.rank(scores[sign],uploadTimes[sign]));
                }
                break;
            }
        }
    }
    return 0;
}
