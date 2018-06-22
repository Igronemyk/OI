#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
#include <set>

using namespace std;

const int MAXT = 3e5 + 10;
const int INF = INT_MAX;
const int BUFFER_SIZE = 4;

template<typename T>
T read() {
    T result = 0;int f = 1;int c = getchar();
    while(c > '9' || c < '0') {if(c == '-') f *= -1;c = getchar();}
    while(c <= '9' && c >= '0') {result = result * 10 + c - '0';c = getchar();}
    return result * f;
}

struct ValSegmentTree {
    
    int ch[MAXT << 2][2],minV[MAXT << 2],tag[MAXT << 2],root,left,right,sZ;

    int newNode() {
        return newNode(0);
    }

    int newNode(int value) {
        int sign = ++sZ;
        ch[sign][0] = 0;
        ch[sign][1] = 0;
        minV[sign] = value;
        tag[sign] = 0;
        return sign;
    }

    void init(int size) {
        left = 1;
        right = size;
        root = buildTree(left,right);
    }

    void upd(int now) {
        minV[now] = min(minV[ch[now][0]],minV[ch[now][1]]);
    }

    int buildTree(int left,int right) {
        if(left > right) return 0;
        if(left == right) return newNode(left);
        int mid = (left + right) >> 1,now = newNode();
        ch[now][0] = buildTree(left,mid);
        ch[now][1] = buildTree(mid + 1,right);
        upd(now);
        return now;
    }

    void update(int l,int r,int val) {
        update(root,left,right,l,r,val);
    }

    void updateTag(int now,int val) {
        if(now == 0) return;
        tag[now] += val;
        minV[now] += val;
    }

    void pd(int now) {
        if(now == 0) return;
        if(tag[now] == 0) return;
        updateTag(ch[now][0],tag[now]);
        updateTag(ch[now][1],tag[now]);
        tag[now] = 0;
    }

    void update(int now,int left,int right,int l,int r,int val) {
        if(left == l && right == r) {
            minV[now] += val;
            tag[now] += val;
            return;
        }
        pd(now);
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                update(ch[now][0],left,mid,l,r,val);
            }else {
                update(ch[now][0],left,mid,l,mid,val);
                update(ch[now][1],mid + 1,right,mid + 1,r,val);
            }
        }else {
            update(ch[now][1],mid + 1,right,l,r,val);
        }
    }

    int getLeftP(int pos) {
        return getLeftP(root,left,right,pos);
    }

    int getLeftP(int now,int left,int right,int pos) {
        if(minV[now] > 0) return this->right + 1;
        if(left == right) return left;
        pd(now);
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            int result = getLeftP(ch[now][0],left,mid,pos);
            if(result != this->right + 1) return result;
        }
        return getLeftP(ch[now][1],mid + 1,right,pos);
    }

    int getRightP() {
        return getRightP(root,left,right);
    }

    int getRightP(int now,int left,int right) {
        if(minV[now] > 0) return 0;
        if(left == right) return right;
        pd(now);
        int mid = (left + right) >> 1;
        int result = getRightP(ch[now][1],mid + 1,right);
        if(result != 0) return result;
        return getRightP(ch[now][0],left,mid);
    }

} valS;

struct MSegmentTree {
    multiset<int> values[MAXT];
    int ch[MAXT << 2][2],minV[MAXT << 2],minS[MAXT << 2],maxV[MAXT << 2],maxS[MAXT << 2],root,left,right,sZ;
    
    void init(int size) {
        left = 1;
        right = size;
        root = buildTree(left,right);
    }

    int newNode() {
        int sign = ++sZ;
        ch[sign][0] = 0;
        ch[sign][1] = 0;
        minV[sign] = INF;
        minS[sign] = 0;
        maxV[sign] = -INF;
        maxS[sign] = 0;
        return sign;
    }

    void updateValue(int now,int pos) {
        if(values[pos].size() == 0) {
            minV[now] = INF;
            minS[now] = 0;
            maxV[now] = -INF;
            maxS[now] = 0;
            return;
        }
        minV[now] = *values[pos].begin();
        minS[now] = pos;
        maxV[now] = *values[pos].rbegin();
        maxS[now] = pos;
    }

    void upd(int now) {
        if(minV[ch[now][0]] <= minV[ch[now][1]]) {
            minV[now] = minV[ch[now][0]];
            minS[now] = minS[ch[now][0]];
        }else {
            minV[now] = minV[ch[now][1]];
            minS[now] = minS[ch[now][1]];
        }
        if(maxV[ch[now][0]] > maxV[ch[now][1]]) {
            maxV[now] = maxV[ch[now][0]];
            maxS[now] = maxS[ch[now][0]];
        }else {
            maxV[now] = maxV[ch[now][1]];
            maxS[now] = maxS[ch[now][1]];
        }
    }

    int buildTree(int left,int right) {
        if(left > right) return 0;
        if(left == right) {
            values[left].clear();
            return newNode();
        }
        int mid = (left + right) >> 1,now = newNode();
        ch[now][0] = buildTree(left,mid);
        ch[now][1] = buildTree(mid + 1,right);
        upd(now);
        return now;
    }

    void insert(int pos,int value) {
        insert(root,left,right,pos,value);
    }
    

    void insert(int now,int left,int right,int pos,int value) {
        if(left == right) {
            values[left].insert(value);
            updateValue(now,left);
            return;
        }
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            insert(ch[now][0],left,mid,pos,value);
        }else {
            insert(ch[now][1],mid + 1,right,pos,value);
        }
        upd(now);
    }

    bool remove(int pos,int value) {
        return remove(root,left,right,pos,value);
    }

    bool remove(int now,int left,int right,int pos,int value) {
        if(left == right) {
            values[left].erase(values[left].find(pos));
            updateValue(now,left);
            return;
        }
        int mid = (left + right) >> 1;
        bool result;
        if(pos <= mid) {
            result = remove(ch[now][0],left,mid,pos,value);
        }else {
            result = remove(ch[now][1],mid + 1,right,pos,value);
        }
        upd(now);
        return result;
    }

    pair<int,int> getMin(int pos) {
        return getMin(root,left,right,pos);
    }

    pair<int,int> getMin(int now,int left,int right,int pos) {
        if(left > pos) return make_pair(INF,0);
        if(right <= pos) return make_pair(minV[now],minS[now]);
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            return getMin(ch[now][0],left,mid,pos);
        }else {
            pair<int,int> r1 = getMin(ch[now][0],left,mid,pos),r2 = getMin(ch[now][1],mid + 1,right,pos);
            if(r1.first == r2.first) {
               if(r1.second < r2.second) {
                    return r1;
               }else {
                    return r2;
               }
            }else if(r1.first < r2.first) {
                return r1;
            }else {
                return r2;
            }
        }
    }

    pair<int,int> getMax(int pos) {
        return getMax(root,left,right,pos);
    }

    pair<int,int> getMax(int now,int left,int right,int pos) {
        if(right < pos) return make_pair(-INF,0);
        if(left >= pos) return make_pair(maxV[now],maxS[now]);
        int mid = (left + right) >> 1;
        if(pos > mid) {
            return getMax(ch[now][1],mid + 1,right,pos);
        }else {
            pair<int,int> r1 = getMax(ch[now][0],left,mid,pos),r2 = getMax(ch[now][1],mid + 1,right,pos);
            if(r1.first == r2.first) {
                if(r1.second > r2.second) {
                    return r1;
                }else {
                    return r2;
                }
            }else if(r1.first > r2.first) {
                return r1;
            }else {
                return r2;
            }
        }
    }
} now,pre;

int main() {
    int T = read<int>(),Q = read<int>();
    valS.init(T);
    now.init(T);
    pre.init(T);
    char *buffer = new char[BUFFER_SIZE];
    long long result = 0;
    while(Q--) {
        scanf("%s",buffer);
        int t = read<int>(),p = read<int>();
        if(buffer[0] == 'A') {
            int pos = valS.getLeftP(t);
            if(pos == T + 1) {
                valS.update(t,T,-1);
                now.insert(t,p);
                result += p;
            }else {
                pair<int,int> mission = now.getMin(t);
                bool compValue = (mission.first == p) ? (mission.second < t) : (mission.first < p);
                if(compValue) {
                    valS.update(mission.second,T,1);
                    now.remove(mission.second,mission.first);
                    result -= mission.first;
                    pre.insert(mission.second,mission.first);
                    valS.update(t,T,-1);
                    now.insert(t,p);
                    result += p;
                }else {
                    pre.insert(t,p);
                }
            }
        }else {

        }
    }
    return 0;
}
