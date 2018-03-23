#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int MAX_CHARSET_SIZE = 26;
const char FIRST_CHAR = 'a';
const int BUFFER_SIZE = 1e6;

template<typename T>
T read() {
    T result = 0;int f = 1;char c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct ACAM {
    struct Node {
        Node *trans[MAX_CHARSET_SIZE],*fail;
        bool isCounted;
        vector<int> signs;
        Node() {
            fill(trans,trans + MAX_CHARSET_SIZE,static_cast<Node *>(NULL));
            fail = NULL;
            isCounted = false;
        }
    };

    Node *root;

    ACAM() {
        root = new Node();
    }

    void insert(char *str,int sign) {
        Node *now = root;
        for(int i = 0;str[i];i++) {
            int index = str[i] - FIRST_CHAR;
            if(now->trans[index] == NULL) {
                now->trans[index] = new Node();
            }
            now = now->trans[index];
        }
        now->signs.push_back(sign);
    }

    void build() {
        queue<Node *> que;
        root->fail = root;
        for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
            if(root->trans[i] == NULL) {
                root->trans[i] = root;
            }else {
                que.push(root->trans[i]);
                root->trans[i]->fail = root;
            }
        }
        while(!que.empty()) {
            Node *tmp = que.front();
            que.pop();
            for(int i = 0;i < MAX_CHARSET_SIZE;i++) {
                if(tmp->trans[i] == NULL) {
                    tmp->trans[i] = tmp->fail->trans[i];
                }else {
                    tmp->trans[i]->fail = tmp->fail->trans[i];
                    tmp->trans[i]->signs.insert(tmp->trans[i]->signs.end(),tmp->trans[i]->fail->signs.begin(),tmp->trans[i]->fail->signs.end());
                    que.push(tmp->trans[i]);
                }
            }
        }
    }

    int query(char *str,int size) {
        Node *now = root;
        int result = 0;
        bool *visit = new bool[size];
        memset(visit,false,sizeof(bool) * size);
        for(int i = 0;str[i];i++) {
            int index = str[i] - FIRST_CHAR;
            now = now->trans[index];
            if(!now->isCounted) {
                now->isCounted = true;
                for(vector<int>::iterator it = now->signs.begin();it != now->signs.end();it++) {
                    if(!visit[*it]) {
                        result++;
                        visit[*it] = true;
                    }
                }
            }
        }
        return result;
    }
};

int main() {
    char *data = new char[BUFFER_SIZE + 1];
    scanf("%s",data);
    int n = read<int>();
    char *buffer = new char[BUFFER_SIZE + 1];
    ACAM acam;
    for(int i = 0;i < n;i++) {
        scanf("%s",buffer);
        acam.insert(buffer,i);
    }
    acam.build();
    printf("%d\n",acam.query(data,n));
    return 0;
}
