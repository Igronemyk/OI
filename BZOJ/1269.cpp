#include <cstdio>
#include <algorithm>
#include <cstring>
#include <utility>
#include <cstddef>
#include <cstdio>

using namespace std;

const int MAX_TREAP_NODE_SIZE = 3e6;
const int BUFFER_SIZE = 2e6;

struct TreapNode {
    int ch[2],priority,size;
    bool rev;
    char value;

    TreapNode() : priority(0) , size(0) , rev(false) , value(0) {
        ch[0] = 0;
        ch[1] = 0;
    }

    TreapNode(char value) : priority(rand()) , rev(false) , value(value) {
        ch[0] = 0;
        ch[1] = 0;
    }
} tn[MAX_TREAP_NODE_SIZE];

int treapSize = 0,gcStk[MAX_TREAP_NODE_SIZE],gcSize = 0;

struct Treap {
    typedef pair<int,int> DRoot;

    int root;

    int newNode(char value) {
        if(gcSize != 0) {
            int sign = gcStk[gcSize--];
            if(tn[sign].ch[0] != 0) {
                gcStk[++gcSize] = tn[sign].ch[0];
            }
            if(tn[sign].ch[1] != 0) {
                gcStk[++gcSize] = tn[sign].ch[1];
            }
            tn[sign] = TreapNode(value);
            return sign;
        }
        tn[++treapSize] = TreapNode(value);
        return treapSize;
    }

    Treap() : root(0) { }

    void updateRevTag(int now) {
        if(now == 0) return;
        tn[now].rev = !tn[now].rev;
    }

    void pushDown(int now) {
        if(now == 0) return;
        if(!tn[now].rev) return;
        updateRevTag(tn[now].ch[0]);
        updateRevTag(tn[now].ch[1]);
        swap(tn[now].ch[0],tn[now].ch[1]);
        updateRevTag(now);
    }

    void updateInfo(int now) {
        tn[now].size = tn[tn[now].ch[0]].size + tn[tn[now].ch[1]].size + 1;
    }

    int merge(int a,int b) {
        if(a == 0) return b;
        if(b == 0) return a;
        pushDown(a);
        pushDown(b);
        if(tn[a].priority > tn[b].priority) {
            tn[a].ch[1] = merge(tn[a].ch[1],b);
            updateInfo(a);
            return a;
        }else {
            tn[b].ch[0] = merge(a,tn[b].ch[0]);
            updateInfo(b);
            return b;
        }
    }

    DRoot split(int now,int k) {
        DRoot result(0,0);
        if(now == 0) return result;
        pushDown(now);
        if(k <= tn[tn[now].ch[0]].size) {
            result = split(tn[now].ch[0],k);
            tn[now].ch[0] = result.second;
            updateInfo(now);
            result.second = now;
        }else {
            result = split(tn[now].ch[1],k - tn[tn[now].ch[0]].size - 1);
            tn[now].ch[1] = result.first;
            updateInfo(now);
            result.first = now;
        }
        return result;
    }

    void insert(int pos,char *values,int size) {
        DRoot tmp = split(root,pos);
        int newNodeSign = buildTree(0,size - 1,values);
        root = merge(tmp.first,merge(newNodeSign,tmp.second));
    }

    void reverse(int pos,int size) {
        DRoot tmp1 = split(root,pos),tmp2 = split(tmp1.second,size);
        updateRevTag(tmp2.first);
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
    }

    void remove(int pos,int size) {
        DRoot tmp1 = split(root,pos),tmp2 = split(tmp1.second,size);
        gcStk[++gcSize] = tmp2.first;
        root = merge(tmp1.first,tmp2.second);
    }

    void print(int pos,int size) {
        DRoot tmp1 = split(root,pos),tmp2 = split(tmp1.second,size);
        print(tmp2.first);
        root = merge(tmp1.first,merge(tmp2.first,tmp2.second));
        printf("\n");
    }

    int buildTree(int left,int right,char *values) {
        if(left > right) return 0;
        int mid = (left + right) >> 1;
        int now = newNode(values[mid]);
        tn[now].ch[0] = buildTree(left,mid - 1,values);
        tn[now].ch[1] = buildTree(mid + 1,right,values);
        updateInfo(now);
        return now;
    }

    void print(int now) {
        if(now == 0) return;
        print(tn[now].ch[0]);
        printf("%c",tn[now].value);
        print(tn[now].ch[1]);
    }

};

void getStr(char *buffer,int size) {
    for(int i = 0;i < size;i++) {
        buffer[i] = getchar();
        while(buffer[i] > 126 || buffer[i] < 32) {
            buffer[i] = getchar();
        }
    }
}


int main() {
    int T;
    char *buffer = new char[BUFFER_SIZE];
    scanf("%d",&T);
    Treap treap;
    int nowPos = 0;
    while(T--) {
        scanf("%s",buffer);
        switch(buffer[0]) {
            case 'M': {
                int k;
                scanf("%d",&k);
                nowPos = k;
                break;
            }
            case 'I': {
                int size;
                scanf("%d",&size);
                getStr(buffer,size);
                treap.insert(nowPos,buffer,size);
                break;
            }
            case 'D': {
                int size;
                scanf("%d",&size);
                treap.remove(nowPos,size);
                break;
            }
            case 'R': {
                int size;
                scanf("%d",&size);
                treap.reverse(nowPos,size);
                break;
            }
            case 'G': {
                int size = 1;
                treap.print(nowPos,size);
                break;
            }
            case 'P': {
                nowPos--;
                break;
            }
            case 'N': {
                nowPos++;
                break;
            }
        }
    }
    return 0;
}
