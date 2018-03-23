#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <cstdlib>

using namespace std;

const int MAX_SPLAY_NODE_SIZE = 1e6;

template<typename T>
T read()
{
    T result = 0; int f = 1; char c = getchar();
    while (c > '9' || c < '0') { if (c == '-') f *= -1; c = getchar(); }
    while (c <= '9' && c >= '0') { result = result * 10 + c - '0'; c = getchar(); }
    return result * f;
}

struct SplayNode
{
    int father, ch[2], sign, cnt, size;

    SplayNode() : father(0), sign(0), cnt(0), size(0)
    {
        ch[0] = 0;
        ch[1] = 0;
    }

    SplayNode(int sign, int cnt) : father(0), sign(sign), cnt(cnt), size(cnt)
    {
        ch[0] = 0;
        ch[1] = 0;
    }
} sn[MAX_SPLAY_NODE_SIZE];

int splaySize = 0;

struct Splay
{
    int root;

    static int newNode(int sign, int cnt)
    {
        sn[++splaySize] = SplayNode(sign, cnt);
        if (splaySize == MAX_SPLAY_NODE_SIZE)
        {
            printf("Memory Limit Exceed\n");
            exit(0);
        }
        return splaySize;
    }

    Splay(int startSign, int size) : root(newNode(startSign, size)) {}

    void updateInfo(int now)
    {
        sn[now].size = sn[sn[now].ch[0]].size + sn[sn[now].ch[1]].size + sn[now].cnt;
    }

    void rotate(int now)
    {
        int father = sn[now].father, anc = sn[father].father;
        if (anc != 0)
        {
            sn[anc].ch[sn[anc].ch[1] == father] = now;
        }
        int direction = sn[father].ch[0] == now;
        sn[now].father = anc;
        sn[father].father = now;
        sn[father].ch[!direction] = sn[now].ch[direction];
        sn[now].ch[direction] = father;
        if (sn[father].ch[!direction] != 0)
        {
            sn[sn[father].ch[!direction]].father = father;
        }
        if (sn[now].father == 0)
        {
            root = now;
        }
        updateInfo(father);
        updateInfo(now);
    }

    void splay(int now)
    {
        splay(now, 0);
    }

    void splay(int now, int dist)
    {
        if (now == 0 || now == dist) return;
        while (sn[now].father != dist)
        {
            int father = sn[now].father, anc = sn[father].father;
            if (anc != dist)
            {
                if ((sn[father].ch[0] == now) ^ (sn[anc].ch[0] == father))
                {
                    rotate(now);
                }
                else
                {
                    rotate(father);
                }
            }
            rotate(now);
        }
    }

    pair<int, int> split(int now, int k)
    {
        splay(now);
        if (k == 1 && sn[now].cnt == 1) return make_pair(now, 0);
        if (k == 1)
        {
            int newNodeSign = newNode(sn[now].sign + 1, sn[now].cnt - 1);
            sn[now].cnt = 1;
            sn[newNodeSign].ch[0] = now;
            sn[newNodeSign].ch[1] = sn[now].ch[1];
            if (sn[newNodeSign].ch[1] != 0)
            {
                sn[sn[newNodeSign].ch[1]].father = newNodeSign;
            }
            sn[now].ch[1] = 0;
            sn[now].father = newNodeSign;
            updateInfo(now);
            updateInfo(newNodeSign);
            root = newNodeSign;
            return make_pair(now, newNodeSign);
        }
        if (k == sn[now].cnt)
        {
            int newNodeSign = newNode(sn[now].sign + (k - 1),1);
            sn[now].cnt = k - 1;
            sn[newNodeSign].ch[0] = now;
            sn[newNodeSign].ch[1] = sn[now].ch[1];
            if (sn[newNodeSign].ch[1] != 0)
            {
                sn[sn[newNodeSign].ch[1]].father = newNodeSign;
            }
            sn[now].ch[1] = 0;
            sn[now].father = newNodeSign;
            updateInfo(now);
            updateInfo(newNodeSign);
            root = newNodeSign;
            return make_pair(newNodeSign, 0);
        }
        int midNodeSign = newNode(sn[now].sign + (k - 1), 1);
        int rightNodeSign = newNode(sn[now].sign + k, sn[now].cnt - k);
        sn[now].cnt = k - 1;
        sn[now].father = midNodeSign;
        sn[midNodeSign].ch[0] = now;
        sn[midNodeSign].ch[1] = rightNodeSign;
        sn[rightNodeSign].ch[1] = sn[now].ch[1];
        if (sn[rightNodeSign].ch[1] != 0)
        {
            sn[sn[rightNodeSign].ch[1]].father = rightNodeSign;
        }
        sn[now].ch[1] = 0;
        sn[rightNodeSign].father = midNodeSign;
        updateInfo(now);
        updateInfo(rightNodeSign);
        updateInfo(midNodeSign);
        root = midNodeSign;
        return make_pair(midNodeSign, rightNodeSign);
    }

    void changeSign(int now, int newSign)
    {
        splay(now);
        sn[now].sign = newSign;
    }

    int getRank(int now)
    {
        splay(now);
        return sn[sn[now].ch[0]].size + 1;
    }

    int searchMin(int now)
    {
        int father = sn[now].father;
        while (sn[now].ch[0] != 0)
        {
            now = sn[now].ch[0];
        }
        splay(now, father);
        return now;
    }

    int searchMax(int now)
    {
        int father = sn[now].father;
        while (sn[now].ch[1] != 0)
        {
            now = sn[now].ch[1];
        }
        splay(now, father);
        return now;
    }

    pair<int, int> getKth(int k)
    {
        pair<int, int> result(0, 0);
        int now = root;
        while (now != 0)
        {
            if (k < sn[sn[now].ch[0]].size + 1)
            {
                now = sn[now].ch[0];
            }
            else if (k >= sn[sn[now].ch[0]].size + 1 && k <= sn[sn[now].ch[0]].size + sn[now].cnt)
            {
                result = split(now, k - sn[sn[now].ch[0]].size);
                break;
            }
            else
            {
                k -= sn[sn[now].ch[0]].size + sn[now].cnt;
                now = sn[now].ch[1];
            }
        }
        return result;
    }

    void remove(int now)
    {
        splay(now);
        bool hasLc = sn[now].ch[0] != 0, hasRc = sn[now].ch[1] != 0;
        if (!hasLc && !hasRc)
        {
            root = 0;
            sn[now].ch[0] = 0;
            sn[now].ch[1] = 0;
            updateInfo(now);
            return;
        }
        else if (hasLc && !hasRc)
        {
            root = sn[now].ch[0];
            sn[root].father = 0;
            sn[now].ch[0] = 0;
            sn[now].ch[1] = 0;
            updateInfo(now);
            return;
        }
        else if (!hasLc && hasRc)
        {
            root = sn[now].ch[1];
            sn[root].father = 0;
            sn[now].ch[0] = 0;
            sn[now].ch[1] = 0;
            updateInfo(now);
            return;
        }
        int pre = searchMax(sn[now].ch[0]);
        sn[pre].father = 0;
        sn[pre].ch[1] = sn[now].ch[1];
        if (sn[now].ch[1] != 0)
        {
            sn[sn[now].ch[1]].father = pre;
        }
        root = pre;
        sn[now].ch[0] = 0;
        sn[now].ch[1] = 0;
        updateInfo(pre);
        updateInfo(now);
    }

    void insertLast(int now)
    {
        int insertPos = searchMax(root);
        sn[insertPos].ch[1] = now;
        sn[now].father = insertPos;
        updateInfo(insertPos);
        splay(now);
    }

    void insertFirst(int now)
    {
        int insertPos = searchMin(root);
        sn[insertPos].ch[0] = now;
        sn[now].father = insertPos;
        updateInfo(insertPos);
        splay(now);
    }

    void print()
    {
        print(root);
        printf("\n");
    }

    void print(int now)
    {
        if (now == 0) return;
        print(sn[now].ch[0]);
        printf("(%d,%d,%d,%d,%d,%d) ", sn[now].father, sn[now].ch[0], sn[now].ch[1], now, sn[now].sign, sn[now].cnt);
        print(sn[now].ch[1]);
    }

};

int main()
{
    int n = read<int>(), m = read<int>();
    Splay splay(1, n);
    map<int, int> signs;
    signs[1] = 1;
    int lastAns = 0;
    while (m--)
    {
        int opt = read<int>();
        switch (opt)
        {
            case 1:
            {
                int x = read<int>() - lastAns, y = read<int>() - lastAns;
                map<int, int>::iterator it = signs.upper_bound(x);
                it--;
                int nowSign = it->second;
                pair<int, int> tmpResult = splay.split(nowSign, x - it->first + 1);
                signs.erase(x);
                signs[y] = tmpResult.first;
                if (tmpResult.second != 0)
                {
                    signs[x + 1] = tmpResult.second;
                }
                lastAns = splay.getRank(tmpResult.first);
                splay.changeSign(tmpResult.first, y);
                printf("%d\n", lastAns);
                break;
            }
            case 2:
            {
                int x = read<int>() - lastAns;
                map<int, int>::iterator it = signs.upper_bound(x);
                it--;
                int nowSign = it->second;
                pair<int, int> tmpResult = splay.split(nowSign, x - it->first + 1);
                signs[x] = tmpResult.first;
                if (tmpResult.second != 0)
                {
                    signs[x + 1] = tmpResult.second;
                }
                lastAns = splay.getRank(tmpResult.first);
                splay.remove(tmpResult.first);
                splay.insertFirst(tmpResult.first);
                printf("%d\n", lastAns);
                break;
            }
            case 3:
            {
                int x = read<int>() - lastAns;
                map<int, int>::iterator it = signs.upper_bound(x);
                it--;
                int nowSign = it->second;
                pair<int, int> tmpResult = splay.split(nowSign, x - it->first + 1);
                signs[x] = tmpResult.first;
                if (tmpResult.second != 0)
                {
                    signs[x + 1] = tmpResult.second;
                }
                lastAns = splay.getRank(tmpResult.first);
                splay.remove(tmpResult.first);
                splay.insertLast(tmpResult.first);
                printf("%d\n", lastAns);
                break;
            }
            case 4:
            {
                int k = read<int>() - lastAns;
                pair<int, int> tmpResult = splay.getKth(k);
                signs[sn[tmpResult.first].sign] = tmpResult.first;
                if (tmpResult.second != 0)
                {
                    signs[sn[tmpResult.second].sign] = tmpResult.second;
                }
                lastAns = sn[tmpResult.first].sign;
                printf("%d\n", lastAns);
                break;
            }
        }
    }
    return 0;
}
