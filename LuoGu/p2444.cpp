#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <cstddef>
#include <queue>

using namespace std;

const int MAX_CHILD_SIZE = 2;
const char FIRST_CHAR = '0';
const int BUFFER_SIZE = 30001;

struct ACAM {
    struct Node {
        Node *childs[MAX_CHILD_SIZE],*fail;
        bool isDangerous;
        int sign;

        Node(int sign) : sign(sign) {
            memset(childs,static_cast<int>(NULL),sizeof(Node *) * MAX_CHILD_SIZE);
            fail = NULL;
            isDangerous = false;
        }

        bool hasChild(int index) {
            return childs[index] != NULL;
        }

    };

    Node *root;
    int size;

    ACAM() : size(0) {
        root = new Node(size++);
    }

    void insert(char *str) {
        int length = strlen(str);
        Node *now = root;
        for(int i = 0;i < length;i++) {
            int index = str[i] - FIRST_CHAR;
            if(!now->hasChild(index)) {
                now->childs[index] = new Node(size++);
            }
            now = now->childs[index];
        }
        now->isDangerous = true;
    }

    void getFail() {
        queue<Node *> que;
        for(int i = 0;i < MAX_CHILD_SIZE;i++) {
            if(root->hasChild(i)) {
                root->childs[i]->fail = root;
                que.push(root->childs[i]);
            }else {
                root->childs[i] = root;
            }
        }
        while(!que.empty()) {
            Node *tmpNode = que.front();
            que.pop();
            for(int i = 0;i < MAX_CHILD_SIZE;i++) {
                if(tmpNode->hasChild(i)) {
                    tmpNode->childs[i]->fail = tmpNode->fail->childs[i];
                    if(tmpNode->childs[i]->fail->isDangerous) {
                        tmpNode->childs[i]->isDangerous = true;
                    }
                    que.push(tmpNode->childs[i]);
                }else {
                    tmpNode->childs[i] = tmpNode->fail->childs[i];
                }
            }
        }
    }

    bool getResult() {
        bool *nowVisit = new bool[size],*hasVisited = new bool[size];
        memset(nowVisit,false,sizeof(bool) * size);
        memset(hasVisited,false,sizeof(bool) * size);
        bool isFound = false;
        dfs(root,nowVisit,hasVisited,isFound);
        return isFound;
    }

    void dfs(Node *now,bool *nowVisit,bool *hasVisited,bool &isFound) {
        nowVisit[now->sign] = true;
        hasVisited[now->sign] = true;
        for(int i = 0;i < MAX_CHILD_SIZE;i++) {
            Node *doing = now->childs[i];
            if(nowVisit[doing->sign]) {
                isFound = true;
                return;
            }else if(!doing->isDangerous && !hasVisited[doing->sign]) {
                dfs(doing,nowVisit,hasVisited,isFound);
                if(isFound) {
                    return;
                }
            }
        }
        nowVisit[now->sign] = false;
    }



};

int main() {
    ACAM acAutoMachine;
    char *buffer = new char[BUFFER_SIZE];
    int n;
    scanf("%d",&n);
    while(n--) {
        scanf("%s",buffer);
        acAutoMachine.insert(buffer);
    }
    acAutoMachine.getFail();
    bool result = acAutoMachine.getResult();
    if(result) {
        printf("TAK\n");
    }else {
        printf("NIE\n");
    }
    return 0;
}
