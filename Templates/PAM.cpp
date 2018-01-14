#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

const int MAX_CHARSET_SIZE = 26;
const int FIRST_CHAR = 'a';

struct PAM {
    struct State {
        State **trans,*fail;
        int len;
        State() : trans(NULL) , fail(NULL) , len(-2) { }
        State(int len) : fail(NULL) , len(len) {
            trans = new State*[MAX_CHARSET_SIZE];
            fill(trans,trans + MAX_CHARSET_SIZE,static_cast<State *>(NULL));
        }

        bool hasTrans(int index) {
            return trans[index] != NULL;
        }

    } **states;
    State *even,*odd,*last;
    char *str;
    int nowSize,nowCharSize,size;

    PAM(int size) : size(size) {
        states = new State*[size + 5];
        str = new char[size + 5];
        init();
    }

    void init() {
        fill(states,states + size + 5,static_cast<State *>(NULL));
        fill(str,str + size + 5,0);
        nowSize = 0;
        nowCharSize = 0;
        even = createState(0);
        odd = createState(-1);
        even->fail = odd;
        odd->fail = odd;
        str[0] = 0;
        last = even;
    }

    void insert(string s) {
        for(string::iterator it = s.begin();it != s.end();it++) {
            insert(*it);
        }
    }


    void insert(char c) {
        int index = c - FIRST_CHAR;
        str[++nowCharSize] = c;
        State *lastCheck = last;
        while(str[nowCharSize - lastCheck->len - 1] != str[nowCharSize]) {
            lastCheck = lastCheck->fail;
        }
        if(!lastCheck->hasTrans(index)) {
            State *newState = createState(lastCheck->len + 2);
            State *newFail = lastCheck->fail;
            while(str[nowCharSize - newFail->len - 1] != str[nowCharSize]) {
                newFail = newFail->fail;
            }
            if(newFail->hasTrans(index)) {
                newState->fail = newFail->trans[index];
            }
            lastCheck->trans[index] = newState;
        }
        last = lastCheck->trans[index];
    }

    State * createState(int len) {
        states[nowSize++] = new State(len);
        states[nowSize - 1]->fail = even;
        return states[nowSize - 1];
    }

    int getMaxLen() {
        int maxLen = 0;
        for(int i = 0;i < nowSize;i++) {
            maxLen = max(maxLen,states[i]->len);
        }
        return maxLen;
    }

};

int main() {
    string str;
    cin >> str;
    PAM pam(str.size());
    pam.insert(str);
    cout << pam.getMaxLen() << endl;
    return 0;
}
