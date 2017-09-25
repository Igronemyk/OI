#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const int INF = 0x3f3f3f3f;

int nowLength = INF;
string result;

struct Trie{
    struct Node{
        Node **childs;
        int val;
        Node() : val(0) {
            childs = new Node*[10];
            for(int i = 0;i < 10;i++) childs[i] = NULL;
        }
    };
    Node *root;
    Trie(){
        root = new Node();
    }

    void insert(string s){
        Node *doing = root;
        for(string::iterator it = s.begin();it != s.end();it++){
            int value = *it - '0';
            if(doing->childs[value] == NULL) doing->childs[value] = new Node();
            doing = doing->childs[value];
            doing->val++;
        }
    }

    void del(string s){
        Node *doing = root;
        for(string::iterator it = s.begin();it != s.end();it++){
            int value = *it - '0';
            doing = doing->childs[value];
            doing->val--;
        }
    }

    void check(string s){
        Node *doing = root;
        for(string::iterator it = s.begin();it != s.end() && (it - s.begin() + 1 < nowLength);it++){
            int value = *it - '0';
            doing = doing->childs[value];
            if(doing->val == 0){
                nowLength = it - s.begin() + 1;
                result = s.substr(0,it - s.begin() + 1);
                break;
            }
        }
    }

};

int main(){
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    Trie tree;
    string *strs = new string[n];
    for(int i = 0;i < n;i++){
        cin >> strs[i];
        int tmpSize = static_cast<int>(strs[i].size());
        for(int j = 0;j < tmpSize;j++){
            tree.insert(strs[i].substr(j,tmpSize - j));
        }
    }
    for(int i = 0;i < n;i++){
        nowLength = INF;
        int tmpSize = static_cast<int>(strs[i].size());
        for(int j = 0;j < tmpSize;j++){
            tree.del(strs[i].substr(j,tmpSize - j));
        }
        for(int j = 0;j < tmpSize;j++){
            tree.check(strs[i].substr(j,tmpSize - j));
        }
        for(int j = 0;j < tmpSize;j++){
            tree.insert(strs[i].substr(j,tmpSize - j));
        }
        cout << result << endl;
    }
    return 0;
}
