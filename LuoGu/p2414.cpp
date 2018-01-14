#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstddef>
#include <queue>

using namespace std;

const int MAX_CHARSET_SIZE = 26;
const int FIRST_CHAR = 'a';
const int BUFFER_SIZE = 100001;

struct Info {
    int x,y;
};

struct Graph {
    struct Edge {
        int next,to;
    };
    Edge *edges;
    int tot,*heads;

    Graph(int edgeSize,int nodeSize) {
        edges = new Edge[edgeSize];
        tot = 0;
        heads = new int[nodeSize];
        memset(heads,-1,sizeof(int) * nodeSize);
    }

    void addEdge(int u,int v) {
        edges[tot].to = v;
        edges[tot].next = heads[u];
        heads[u] = tot++;
    }

};

template<typename T>
struct BIT {
    T *values;
    int size;

    BIT(int size) : size(size) {
        values = new T[size + 1];
        memset(values,0,sizeof(T) * (size + 1));
    }

    void add(int pos,T val) {
        for(int i = pos;i <= size;i += lowbit(i)) {
            values[i] += val;
        }
    }

    T sum(int pos) {
        T result = 0;
        while(pos) {
            result += values[pos];
            pos -= lowbit(pos);
        }
        return result;
    }

    int lowbit(int value) {
        return value & -value;
    }
};

struct AdjList {
    struct Node {
        int next,to,sign;
    };
    Node *nodes;
    int tot,*heads;

    AdjList(int nodeSize,int headSize) {
        nodes = new Node[nodeSize];
        tot = 0;
        heads = new int[headSize];
        memset(heads,-1,sizeof(int) * headSize);
    }

    void addNode(int u,int v,int sign) {
        nodes[tot].to = v;
        nodes[tot].next = heads[u];
        nodes[tot].sign = sign;
        heads[u] = tot++;
    }

};

void dfs(int now,Graph &graph,int *dfn,int *size,int &nowTime) {
    dfn[now] = nowTime++;
    size[now] = 1;
    for(int i = graph.heads[now];i != -1;i = graph.edges[i].next) {
        Graph::Edge &tmpEdge = graph.edges[i];
        dfs(tmpEdge.to,graph,dfn,size,nowTime);
        size[now] += size[tmpEdge.to];
    }
}

struct ACAM {
    struct Node {
        Node *father,*fail,*childs[MAX_CHARSET_SIZE];
        int sign;
        int endSign;

        Node(int sign,Node *father) : father(father) , fail(NULL) , sign(sign) , endSign(-1) {
            memset(childs,static_cast<int>(NULL),sizeof(Node *) * MAX_CHARSET_SIZE);
        }

        bool hasChild(int index) {
            return childs[index] != NULL;
        }

    };

    Node *root;
    int size,nowPrintSign,*printSignMap;

    Node *newNode(Node *father) {
        return new Node(size++,father);
    }

    ACAM() : size(0) , nowPrintSign(0) {
        root = newNode(NULL);
        printSignMap = new int[BUFFER_SIZE];
    }

    void build(char *str) {
        int length = strlen(str);
        Node *now = root;
        for(int i = 0;i < length;i++) {
            switch(str[i]) {
                case 'B': {
                    now = now->father;
                    break;
                }
                case 'P': {
                    now->endSign = nowPrintSign;
                    printSignMap[nowPrintSign++] = now->sign;
                    break;
                }
                default: {
                    now = insert(now,str[i]);
                    break;
                }
            }
        }
    }

    Node *insert(Node *now,char value) {
        int index = value - FIRST_CHAR;
        if(!now->hasChild(index)) {
            now->childs[index] = newNode(now);
        }
        return now->childs[index];
    }

    void getFail(Graph &graph) {
        queue<Node *> que;
        que.push(root);
        while(!que.empty()) {
            Node *tmpNode = que.front();
            que.pop();
            for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
                if(!tmpNode->hasChild(i)) continue;
                Node *nowNode = tmpNode->childs[i],*doing = tmpNode->fail;
                while(doing != NULL && !doing->hasChild(i)) {
                    doing = doing->fail;
                }
                if(doing == NULL) {
                    nowNode->fail = root;
                }else {
                    nowNode->fail = doing->childs[i];
                }
                graph.addEdge(nowNode->fail->sign,nowNode->sign);
                que.push(nowNode);
            }
        }
    }

    void getResult(Info *infos,int *result,int infoSize) {
        Graph graph(size,size);
        AdjList querys(infoSize,nowPrintSign);
        for(int i = 0;i < infoSize;i++) {
            Info &tmpInfo = infos[i];
            querys.addNode(tmpInfo.y,tmpInfo.x,i);
        }
        getFail(graph);
        int *dfn = new int[size],*treeSize = new int[size];
        bool *visit = new bool[size];
        memset(visit,false,sizeof(bool) * size);
        int nowTime = 1;
        BIT<int> bitree(size);
        ::dfs(0,graph,dfn,treeSize,nowTime);
        dfs(root,dfn,treeSize,result,querys,bitree,visit);
    }

    void dfs(Node *now,int *dfn,int *size,int *result,AdjList &querys,BIT<int> &bitree,bool *visit) {
        visit[now->sign] = true;
        bitree.add(dfn[now->sign],1);
        if(now->endSign != -1) {
            for(int i = querys.heads[now->endSign];i != -1;i = querys.nodes[i].next) {
                AdjList::Node &tmpNode = querys.nodes[i];
                int signTo = printSignMap[tmpNode.to];
                //printf("Get %d,%d,%d %d %d %d\n",tmpNode.sign,signTo,dfn[signTo],size[signTo],bitree.sum(dfn[signTo] + size[signTo] - 1),bitree.sum(dfn[signTo] - 1));
                result[tmpNode.sign] = bitree.sum(dfn[signTo] + size[signTo] - 1) - bitree.sum(dfn[signTo] - 1);
            }
        }
        for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
            if(!now->hasChild(i)) continue;
            if(visit[now->childs[i]->sign]) continue;
            if(now->childs[i]->sign <= now->sign) continue;
            dfs(now->childs[i],dfn,size,result,querys,bitree,visit);
        }
        bitree.add(dfn[now->sign],-1);
    }


};


int main() {
    ACAM acAutoMachine;
    char *buffer = new char[BUFFER_SIZE];
    scanf("%s",buffer);
    acAutoMachine.build(buffer);
    int m;
    scanf("%d",&m);
    Info *infos = new Info[m];
    for(int i = 0;i < m;i++) {
        scanf("%d%d",&infos[i].x,&infos[i].y);
        infos[i].x--;
        infos[i].y--;
    }
    int *result = new int[m];
    acAutoMachine.getResult(infos,result,m);
    for(int i = 0;i < m;i++) {
        printf("%d\n",result[i]);
    }
    return 0;
}
