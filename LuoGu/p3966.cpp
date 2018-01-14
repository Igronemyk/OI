#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <utility>
#include <queue>
#include <sstream>

using namespace std;

const int MAX_CHILD_SIZE = 26;

struct ACAM {

    struct Node {
        Node *childs[MAX_CHILD_SIZE],*fail;
        vector<int> words;

        inline Node() {
            for(int i = 0;i < MAX_CHILD_SIZE;i++) childs[i] = NULL;
            fail = NULL;
        }

        inline bool hasChild(int index) {
            return childs[index] != NULL;
        }

        inline Node * getChild(int index) {
            if(!hasChild(index)) {
                childs[index] = new Node();
            }
            return childs[index];
        }

        inline Node *getChildWithoutCheck(int index) {
            return childs[index];
        }
    };
    Node *root;
    int size;

    inline ACAM(string *strs,int size) : size(size) {
        root = new Node();
        for(int i = 0;i < size;i++) {
            insert(strs[i],i);
        }
        build();
    }

    void insert(const string &s,int sign) {
        Node *doing = root;
        for(string::const_iterator it = s.begin();it != s.end();it++) {
            int index = *it - 'a';
            doing = doing->getChild(index);
            if(it + 1 == s.end()) {
                doing->words.push_back(sign);
            }
        }
    }

    void build() {
        queue<Node *> que;
        que.push(root);
        while(!que.empty()) {
            Node *tmpNode = que.front();
            que.pop();
            for(int i = 0;i < MAX_CHILD_SIZE;i++) {
                if(!tmpNode->hasChild(i)) continue;
                Node *nowNode = tmpNode->getChildWithoutCheck(i),*doing = tmpNode->fail;
                while(doing != NULL && !doing->hasChild(i)) {
                    doing = doing->fail;
                }
                if(doing == NULL) {
                    nowNode->fail = root;
                }else {
                    nowNode->fail = doing->getChildWithoutCheck(i);
                    nowNode->words.insert(nowNode->words.end(),nowNode->fail->words.begin(),nowNode->fail->words.end());
                }
                que.push(nowNode);
            }
        }
    }

    inline void query(const string &s,int *result) {
        Node *doing = root;
        int nowMaxValue = 0;
        memset(result,0,sizeof(int) * size);
        for(string::const_iterator it = s.begin();it != s.end();it++) {
            if(*it == ' ') {
                doing = root;
                continue;
            }
            int index = *it - 'a';
            bool canContinue = true;
            while(!doing->hasChild(index)) {
                if(doing == root) {
                    canContinue = false;
                    break;
                }
                doing = doing->fail;
            }
            if(!canContinue) continue;
            doing = doing->getChildWithoutCheck(index);
            for(vector<int>::iterator it = doing->words.begin();it != doing->words.end();it++) {
                result[*it]++;
                if(nowMaxValue < result[*it]) nowMaxValue = result[*it];
            }
        }
    }

};

int main() {
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    string *strs = new string[N];
    stringstream ss;
    for(int i = 0;i < N;i++) {
        cin >> strs[i];
        ss << strs[i];
        ss << ' ';
    }
    int *result = new int[N];
    string values = ss.str();
    ACAM machine(strs,N);
    machine.query(values,result);
    for(int i = 0;i < N;i++) {
        cout << result[i] << endl;
    }
    return 0;
}
