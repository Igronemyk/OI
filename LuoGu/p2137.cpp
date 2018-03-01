#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstddef>
#include <climits>

using namespace std;

const int INF = INT_MAX;

namespace Graph {

}

namespace SegmentTree {

    const int MAX_SEGMENT_NODE_SIZE = 1e7;
    int ch[MAX_SEGMENT_NODE_SIZE][2],cnt[MAX_SEGMENT_NODE_SIZE],segmentSize = 0;

    int newNode(int sign) {
        ++segmentSize;
        ch[segmentSize][0] = ch[sign][0];
        ch[segmentSize][1] = ch[sign][1];
        cnt[segmentSize] = cnt[sign];
        return segmentSize;
    }

    void insert() {

    }
}

int main() {
    return 0;
}
