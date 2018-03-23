#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>

using namespace std;

const int MAX_EVENT_SIZE = 2010;
const int MIN_VAL_RANGE = 0;
const int MAX_VAL_RANGE = 50010;

struct SegmentTree {
    struct Node {
        Node *ch[2];
        int sum,lazy,left,right;

        Node(int left,int right) : sum(0) , lazy(0) , left(left) ,right(right) {
            ch[0] = NULL;
            ch[1] = NULL;
        }

        int getLen() {
            return right - left + 1;
        }
    };

    Node *root;

    SegmentTree(int left,int right) {
        root = build(left,right);
    }

    Node *build(int left,int right) {
        Node *now = new Node(left,right);
        if(left == right) {
            return now;
        }
        int mid = (left + right) >> 1;
        now->ch[0] = build(left,mid);
        now->ch[1] = build(mid + 1,right);
        return now;
    }

    int getSum(Node *now) {
        if(now == NULL) return 0;
        return now->sum;
    }

    void updateInfo(Node *now) {
        if(now->lazy != 0) {
            now->sum = now->getLen();
            return;
        }
        now->sum = getSum(now->ch[0]) + getSum(now->ch[1]);
    }

    void update(int left,int right,int value) {
        update(root,left,right,value);
    }

    void update(Node *now,int left,int right,int value) {
        if(now->left == left && now->right == right) {
            now->lazy += value;
            updateInfo(now);
            return;
        }
        int mid = (now->left + now->right) >> 1;
        if(left <= mid) {
            if(right <= mid) {
                update(now->ch[0],left,right,value);
            }else {
                update(now->ch[0],left,mid,value);
                update(now->ch[1],mid + 1,right,value);
            }
        }else {
            update(now->ch[1],left,right,value);
        }
        updateInfo(now);
    }

    int getValue() {
        return root->sum;
    }

    void clear() {
        clear(root);
    }

    void clear(Node *now) {
        if(now == NULL) return;
        clear(now->ch[0]);
        now->sum = 0;
        now->lazy = 0;
        clear(now->ch[1]);
    }

};

struct Event {
    int sign,left,right,flag;

    Event() : sign(-1) , left(-1) , right(-1) , flag(-1) { }

    Event(int sign,int left,int right,int flag) : sign(sign) , left(left) , right(right) , flag(flag) { }

    bool operator < (const Event &otherEvent) const {
        return sign < otherEvent.sign;
    }
};

int main() {
    int x1,x2,y1,y2;
    Event *events = new Event[MAX_EVENT_SIZE];
    int eventPos = 0,countEnd = 0;
    SegmentTree stree(MIN_VAL_RANGE,MAX_VAL_RANGE);
    while(~scanf("%d%d%d%d",&x1,&y1,&x2,&y2)) {
        if(x1 == -1 && x2 == -1 && y1 == -1 && y2 == -1) {
            countEnd++;
            if(countEnd == 2) {
                break;
            }
            stree.clear();
            sort(events,events + eventPos);
            int nowPos = 0;
            long long result = 0;
            for(int i = MIN_VAL_RANGE;i <= MAX_VAL_RANGE;i++) {
                while(nowPos < eventPos && events[nowPos].sign == i) {
                    Event &tmpEvent = events[nowPos];
                    stree.update(tmpEvent.left,tmpEvent.right,tmpEvent.flag);
                    nowPos++;
                }
                result += stree.getValue();
            }
            printf("%lld\n",result);
            eventPos = 0;
        }else {
            countEnd = 0;
            events[eventPos++] = Event(x1,y1 + 1,y2,1);
            events[eventPos++] = Event(x2,y1 + 1,y2,-1);
        }

    }
    return 0;
}
