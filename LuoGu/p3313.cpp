#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <utility>

using namespace std;

const int MAX_SEGMENT_NODE_SIZE = 1e6;

struct SegmentNode {
    int ch[2],maxValue,sumValue;
} sn[MAX_SEGMENT_NODE_SIZE];

struct SgementTree {
    int root,left,right;

    SegmentTree() {
        root = 0;
    }
};

int main() {

    return 0;
}
