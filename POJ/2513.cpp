#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const long long S1 = 131;
const long long M1 = 275593;
const long long S2 = 133;
const long long M2 = 1e9 + 7;
const int BUFFER_SIZE = 11;
const int MAX_COLOR_SIZE =500001;

struct BCS {
    int *father;
    BCS(int size) {
        father = new int[size];
        for(int i = 0;i < size;i++) father[i] = i;
    }

    int getFather(int pos) {
        if(father[pos] == pos) return pos;
        father[pos] = getFather(father[pos]);
        return father[pos];
    }

    void merge(int u,int v) {
        int faU = getFather(u),faV = getFather(v);
        if(faU == faV) return;
        father[faU] = faV;
    }

};

struct HashTable {
    struct Node {
        int hashVal,cnt,next,sign;
    };
    Node *nodes;
    int tot,*heads;

    HashTable(int nodeSize,int headSize) {
        nodes = new Node[nodeSize];
        tot = 0;
        heads = new int[headSize];
        memset(heads,-1,sizeof(int) * headSize);
    }

    int add(char *str,int length) {
        int firstHash = hash1(str,length),secondHash = hash2(str,length);
        for(int i = heads[firstHash];i != -1;i = nodes[i].next) {
            Node &tmpNode = nodes[i];
            if(tmpNode.hashVal != secondHash) continue;
            tmpNode.cnt++;
            return tmpNode.sign;
        }
        nodes[tot].hashVal = secondHash;
        nodes[tot].cnt = 1;
        nodes[tot].next = heads[firstHash];
        nodes[tot].sign = tot;
        heads[firstHash] = tot++;
        return nodes[tot - 1].sign;
    }

    int hash1(char *str,int length) {
        long long value = 0;
        for(int i = 0;i < length;i++) {
            value = (value * S1 + str[i] - 'a') % M1;
        }
        return static_cast<int>(value);
    }

    int hash2(char *str,int length) {
        long long value = 0;
        for(int i = 0;i < length;i++) {
            value = (value * S2 + str[i] - 'a') % M2;
        }
        return static_cast<int>(value);
    }
};



int main() {
    HashTable table(MAX_COLOR_SIZE,M1);
    char *buffer1 = new char[BUFFER_SIZE],*buffer2 = new char[BUFFER_SIZE];
    BCS bcset(MAX_COLOR_SIZE);
    while(~scanf("%s%s",buffer1,buffer2)) {
        int buffer1Len = strlen(buffer1),buffer2Len = strlen(buffer2);
        int color1 = table.add(buffer1,buffer1Len);
        int color2 = table.add(buffer2,buffer2Len);
        bcset.merge(color1,color2);
    }
    int countEndPoint = 0;
    for(int i = 0;i < table.tot;i++) {
        if(table.nodes[i].cnt & 1) {
            countEndPoint++;
        }
    }
    int father = bcset.getFather(0);
    for(int i = 1;i < table.tot;i++) {
        if(father != bcset.getFather(i)) {
            countEndPoint = -1;
            break;
        }
    }
    if(countEndPoint == 0 || countEndPoint == 2) {
        printf("Possible\n");
    }else {
        printf("Impossible\n");
    }
    return 0;
}
