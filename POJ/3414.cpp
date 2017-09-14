#include <cstdio>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

struct State{
    int now1,now2,depth,opt;
    State *prev;
    State() : now1(-1),now2(-1),depth(-1),opt(-1),prev(NULL) {}
    State(int now1,int now2,int depth,State *prev,int opt) : now1(now1),now2(now2),depth(depth),prev(prev),opt(opt) {}
};

int main(){
    int A,B,C;
    while(~scanf("%d%d%d",&A,&B,&C)){
        bool **visit = new bool*[A + 1];
        for(int i = 0;i <= A;i++){
            visit[i] = new bool[B + 1];
            fill(visit[i],visit[i] + B + 1,false);
        }
        queue<State *> que;
        State *startState = new State(0,0,0,NULL,-1);
        que.push(startState);
        visit[0][0] = true;
        bool solved = false;
        State *result;
        while(!que.empty()){
            State *tmp = que.front();
            que.pop();
            if(tmp->now1 == C || tmp->now2 == C){
                solved = true;
                result = tmp;
                break;
            }
            if(!visit[A][tmp->now2]){
                visit[A][tmp->now2] = true;
                State *stNow = new State(A,tmp->now2,tmp->depth + 1,tmp,1);
                que.push(stNow);
            }
            if(!visit[tmp->now1][B]){
                visit[tmp->now1][B] = true;
                State *stNow = new State(tmp->now1,B,tmp->depth + 1,tmp,2);
                que.push(stNow);
            }
            if(!visit[tmp->now1][0]){
                visit[tmp->now1][0] = true;
                State *stNow = new State(tmp->now1,0,tmp->depth + 1,tmp,3);
                que.push(stNow);
            }
            if(!visit[0][tmp->now2]){
                visit[0][tmp->now2] = true;
                State *stNow = new State(0,tmp->now2,tmp->depth + 1,tmp,4);
                que.push(stNow);
            }
            if(tmp->now1 > B - tmp->now2){
                if(!visit[tmp->now1 - B + tmp->now2][B]){
                    visit[tmp->now1 - B + tmp->now2][B] = true;
                    State *stNow = new State(tmp->now1 - B + tmp->now2,B,tmp->depth + 1,tmp,5);
                    que.push(stNow);
                }
            }else{
                if(!visit[0][tmp->now2 + tmp->now1]){
                    visit[0][tmp->now2 + tmp->now1] = true;
                    State *stNow = new State(0,tmp->now2 + tmp->now1,tmp->depth + 1,tmp,6);
                    que.push(stNow);
                }
            }
            if(tmp->now2 > A - tmp->now1){
                if(!visit[A][tmp->now2 - A + tmp->now1]){
                    visit[A][tmp->now2 - A + tmp->now1] = true;
                    State *stNow = new State(A,tmp->now2 - A + tmp->now1,tmp->depth + 1,tmp,7);
                    que.push(stNow);
                }
            }else{
                if(!visit[tmp->now1 + tmp->now2][0]){
                    visit[tmp->now1 +tmp->now2][0] = true;
                    State *stNow = new State(tmp->now1 + tmp->now2,0,tmp->depth + 1,tmp,8);
                    que.push(stNow);
                }
            }
        }
        //if(solved) printf("%d\n",result->depth);
        if(solved){
            printf("%d\n",result->depth);
            State *start = result;
            stack<int> st;
            while(start->opt != -1){
                st.push(start->opt);
                start = start->prev;
            }
            while(!st.empty()){
                int opt = st.top();
                st.pop();
                switch(opt){
                    case 1: {
                        printf("FILL(1)\n");
                        break;
                    }
                    case 2: {
                        printf("FILL(2)\n");
                        break;
                    }
                    case 3: {
                        printf("DROP(2)\n");
                        break;
                    }
                    case 4: {
                        printf("DROP(1)\n");
                        break;
                    }
                    case 5:
                    case 6: {
                        printf("POUR(1,2)\n");
                        break;
                    }
                    case 7:
                    case 8: {
                        printf("POUR(2,1)\n");
                        break;
                    }
                }
            }
        }else{
            printf("impossible\n");
        }
    }
    return 0;
}
