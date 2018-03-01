#pragma GCC optimize(2)
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

struct Splay {
    struct Node {
        Node *father,*childs[2];
        int val,cnt,size;
        Node() : father(NULL) ,val(-1) , cnt(-1) , size(-1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }
        Node(Node *father,int val) : father(father) , val(val) , cnt(1) , size(1) {
            childs[0] = NULL;
            childs[1] = NULL;
        }
    };

    Node *root;

    Splay() : root(NULL) { }


    void rotate(Node *now,int direction) {
        Node *fa = now->father,*anc = fa->father;
        now->father = anc;
        fa->father = now;
        if(anc != NULL) {
            anc->childs[anc->childs[1] == fa] = now;
        }
        fa->childs[!direction] = now->childs[direction];
        if(fa->childs[!direction] != NULL) {
            fa->childs[!direction]->father = fa;
        }
        now->childs[direction] = fa;
        if(root == fa) {
            root = now;
        }
        updateInfo(fa);
        updateInfo(now);
    }

    void splay(Node *now,Node *dist) {
        if(now == NULL || now == dist) return;
        while(now->father != dist) {
            if(now->father->father == dist) {
                rotate(now,now->father->childs[0] == now);
            }else {
                Node *fa = now->father,*anc = fa->father;
                if(anc->childs[0] == fa) {
                    if(fa->childs[0] == now) {
                        rotate(fa,1);
                        rotate(now,1);
                    }else {
                        rotate(now,0);
                        rotate(now,1);
                    }
                }else {
                    if(fa->childs[0] == now) {
                        rotate(now,1);
                        rotate(now,0);
                    }else {
                        rotate(fa,0);
                        rotate(now,0);
                    }
                }
            }
        }
    }

    Node * search(int key) {
        if(root == NULL) return NULL;
        Node *now = root,*result = NULL;
        while(true) {
            if(now->val > key) {
                if(now->childs[0] != NULL) {
                    now = now->childs[0];
                }else {
                    break;
                }
            }else if(now->val < key) {
                if(now->childs[1] != NULL) {
                    now = now->childs[1];
                }else {
                    break;
                }
            }else {
                result = now;
                break;
            }
        }
        splay(now,NULL);
        return result;
    }

    Node * searchMin(Node *now) {
        Node *father = now->father;
        while(now->childs[0] != NULL) {
            now = now->childs[0];
        }
        splay(now,father);
        return now;
    }

    Node *searchMax(Node *now) {
        Node *father = now->father;
        while(now->childs[1] != NULL) {
            now = now->childs[1];
        }
        splay(now,father);
        return now;
    }

    void insert(int key) {
        if(root == NULL) {
            root = new Node(NULL,key);
            return;
        }
        Node *now = root,*result = NULL;
        while(true) {
            if(now->val > key) {
                if(now->childs[0] == NULL) {
                    now->childs[0] = new Node(now,key);
                    result = now->childs[0];
                    break;
                }else {
                    now = now->childs[0];
                }
            }else if(now->val < key) {
                if(now->childs[1] == NULL) {
                    now->childs[1] = new Node(now,key);
                    result = now->childs[1];
                    break;
                }else {
                    now = now->childs[1];
                }
            }else {
                now->cnt++;
                result = now;
                break;
            }
        }
        splay(result,NULL);
    }

    void remove(int key) {
        if(root == NULL) return;
        Node *now = search(key);
        if(now == NULL) return;
        if(now->cnt > 1) {
            now->cnt--;
            updateInfo(now);
            return;
        }
        if(now->childs[0] == NULL && now->childs[1] == NULL) {
            root = NULL;
            return;
        }
        if(now->childs[0] == NULL && now->childs[1] != NULL) {
            root = now->childs[1];
            now->childs[1]->father = NULL;
            return;
        }
        if(now->childs[0] != NULL && now->childs[1] == NULL) {
            root = now->childs[0];
            now->childs[0]->father = NULL;
            return;
        }
        Node *newNode = searchMin(now->childs[1]);
        newNode->father = NULL;
        newNode->childs[0] = now->childs[0];
        newNode->childs[0]->father = newNode;
        root = newNode;
        updateInfo(newNode);
    }

    int rank(int key) {
        Node *now = search(key);
        if(root->val >= key) {
            return size(root->childs[0]);
        }
        return size(root->childs[0]) + 1;
    }

    static void updateInfo(Node *now) {
        now->size = size(now->childs[0]) + size(now->childs[1]) + now->cnt;
    }

    static int size(Node *now) {
        if(now == NULL) return 0;
        return now->size;
    }

    static Node *buildTree(int left,int right) {
        return buildTree(NULL,left,right);
    }

    static Node * buildTree(Node *father,int left,int right) {
        if(left > right) return NULL;
        int mid = (left + right) >> 1;
        Node *now = new Node(father,mid);
        if(left == right) {
            return now;
        }
        now->childs[0] = buildTree(now,left,mid - 1);
        now->childs[1] = buildTree(now,mid + 1,right);
        updateInfo(now);
        return now;
    }

};


struct SegmentTree {
    struct Node {
        Node *ch[2];
        Splay *splay;

        Node() : splay(new Splay()) {
            ch[0] = NULL;
            ch[1] = NULL;
        }
    };

    Node *root;
    int left,right;

    SegmentTree(int n) : left(1) , right(n) {
        root = new Node();
        build(root,left,right);
    }

    void build(Node *now,int left,int right) {
        now->splay->root = Splay::buildTree(left,right);
        if(left == right) return;
        int mid = (left + right) >> 1;
        now->ch[0] = new Node();
        build(now->ch[0],left,mid);
        now->ch[1] = new Node();
        build(now->ch[1],mid + 1,right);
    }

    int queryLessThan(int l,int r,int value) {
        return queryLessThan(root,left,right,l,r,value);
    }

    int queryLessThan(Node *now,int left,int right,int l,int r,int value) {
        if(left == l && right == r) {
            return now->splay->rank(value);
        }
        int mid = (left + right) >> 1;
        if(l <= mid) {
            if(r <= mid) {
                return queryLessThan(now->ch[0],left,mid,l,r,value);
            }else {
                return queryLessThan(now->ch[0],left,mid,l,mid,value) + queryLessThan(now->ch[1],mid + 1,right,mid + 1,r,value);
            }
        }else {
            return queryLessThan(now->ch[1],mid + 1,right,l,r,value);
        }
    }

    void change(int pos,int oldValue,int newValue) {
        change(root,left,right,pos,oldValue,newValue);
    }

    void change(Node *now,int left,int right,int pos,int oldValue,int newValue) {
        now->splay->remove(oldValue);
        now->splay->insert(newValue);
        if(left == right) {
            return;
        }
        int mid = (left + right) >> 1;
        if(pos <= mid) {
            change(now->ch[0],left,mid,pos,oldValue,newValue);
        }else {
            change(now->ch[1],mid + 1,right,pos,oldValue,newValue);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,q;
    long long result = 0;
    cin >> n >> q;
    SegmentTree stree(n);
    int *values = new int[n + 1];
    for(int i = 1;i <= n;i++) {
        values[i] = i;
    }
    while(q--) {
        int left,right;
        cin >> left >> right;
        if(left == right) {
            cout << result << endl;
            continue;
        }else if(left > right) {
            swap(left,right);
        }
        if(left + 1 <= right - 1) {
            int queryLeft = left + 1,queryRight = right - 1,queryLength = queryRight - queryLeft + 1;
            int lessThanLeft = stree.queryLessThan(queryLeft,queryRight,values[left]),lessThanRight = stree.queryLessThan(queryLeft,queryRight,values[right]);
            int moreThanLeft = queryLength - lessThanLeft,moreThanRight = queryLength - lessThanRight;
            result -= lessThanLeft;
            result += moreThanLeft;
            result -= moreThanRight;
            result += lessThanRight;
        }
        stree.change(left,values[left],values[right]);
        stree.change(right,values[right],values[left]);
        if(values[left] < values[right]) {
            result++;
        }else {
            result--;
        }
        swap(values[left],values[right]);
        cout << result << endl;
    }
    return 0;
}
