#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>

using namespace std;

const int MAX_CHILD_SIZE = 26;

int k,length;
bool found;

struct Trie {
    struct Node {
        Node *childs[MAX_CHILD_SIZE];
        int countEnd;

        Node() {
            for(int i = 0;i < MAX_CHILD_SIZE;i++) childs[i] = NULL;
            countEnd = 0;
        }

        bool hasChild(int index) {
            return childs[index] != NULL;
        }

    };
    Node *root;

    Trie() {
        root = new Node();
    }

    void insert(char *str,int length) {
        Node *doing = root;
        for(int i = 0;i < length;i++) {
            int tmpIndex = str[i] - 'a';
            if(!doing->hasChild(tmpIndex)) {
                doing->childs[tmpIndex] = new Node();
            }
            doing = doing->childs[tmpIndex];
        }
        doing->countEnd++;
    }

    void dfs(int depth,Node *doing,char *result) {
        if(doing->countEnd == k) {
            found = true;
        }
        if(depth == length) return;
        for(int i = 0;i < MAX_CHILD_SIZE;i++) {
            if(doing->hasChild(i)) {
                result[depth] = i + 'a';
                dfs(depth + 1,doing->childs[i],result);
                if(found) return;
            }
        }
    }

};

int main() {
    scanf("%d%d",&k,&length);
    char *tmpStr = new char[length + 1];
    Trie trie;
    for(int doing = 0;doing < k;doing++) {
        scanf("%s",tmpStr);
        for(int i = 0;i < length;i++) {
            for(int j = i + 1;j < length;j++) {
                int tmpChar = tmpStr[i];
                tmpStr[i] = tmpStr[j];
                tmpStr[j] = tmpChar;
                trie.insert(tmpStr,length);
                tmpChar = tmpStr[i];
                tmpStr[i] = tmpStr[j];
                tmpStr[j] = tmpChar;
            }
        }
    }
    trie.dfs(0,trie.root,tmpStr);
    if(found) {
        printf("%s\n",tmpStr);
    }else {
        printf("-1\n");
    }
    return 0;
}
