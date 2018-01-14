#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

const int MAX_STR_LEN = 300001;
const int MAX_CHARSET_SIZE = 26;
const int FIRST_CHAR = 'a';

struct PAM {
    struct State {
        State **trans,*fail;
        int len,size;
        State() : trans(NULL) , fail(NULL) , len(-2) , size(-1) { }
        State(int len) : fail(NULL) , len(len) , size(0) {
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
        states = new State*[size + 2];
        str = new char[size + 1];
        init();
    }

    void init() {
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

    void insert(char *str,int length) {
        for(int i = 0;i < length;i++) {
            insert(str[i]);
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
        last->size++;
    }

    State * createState(int len) {
        states[nowSize++] = new State(len);
        states[nowSize - 1]->fail = even;
        return states[nowSize - 1];
    }

    long long getResult() {
        long long result = 0;
        for(int i = nowSize - 1;i >= 0;i--) {
            states[i]->fail->size += states[i]->size;
            result = max(result,states[i]->size * 1LL * states[i]->len);
        }
        return result;
    }

};

int main() {
    char *str = new char[MAX_STR_LEN + 3];
    scanf("%s",str);
    int length = strlen(str);
    PAM pam(length);
    pam.insert(str,length);
    printf("%lld\n",pam.getResult());
    return 0;
}
