/*
target
-------------
/////河流/////
--------------
begin...

也可以用动态规划来实现

按照每个人的速度，从小到大排序，
dp[N] = dp[N - 2] + a[1] + a[0] + a[N] + a[1];
其中a[1]表示01二人一起到河对面，花费a[1]
a[0]表示0（走的快的那个人）拿着手灯回去
a[N]表示N,N-1二人一起走到河对面，话费a[N]
a[1]表示1拿着手灯走回去
至此，问题变为dp[N-2]

仔细一想，上面的策略其实是一种贪心策略！因为每次根本就没有多种选择，只有一种“！！！最优选择！！！”
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


const int N = 4;
int costMap[] = {1,2,5,10};
int visit = 0;
vector<string> paths;
vector<string> minPath;
int min_cost = 1000000;
int new_state = 0;
int total_cnt = 0;

int goOtherSide(int state, int i) {
    return state ^ (1 << i);
}

bool iCanGo(int state, int i, int Light) {
    return !!(state & (1 << i)) == !!(state & (1 << Light));    
}

void dfs(int state, long visit, int cost);

void single_select(int state, long visit, int cost, const string& cmd) {
//有两种策略
//策略1:某一个人自己过去，N选1
//策略2:某两个人，一起过去，N选2
  for (int i = 0; i < N; i++) {
        if (!iCanGo(state, i, N)) { //第i人手中没有灯
            continue;
        }

        for (int j = i + 1; j < N; j++) { //两个人一起过去
            if (!iCanGo(state, j, N)) { //第j人手中没有灯
                continue;
            }

            new_state = goOtherSide(state, i);
            new_state = goOtherSide(new_state, j);
            new_state = goOtherSide(new_state, N);

            if (visit & (1 << new_state)) {
                continue;
            }

            stringstream ss;
            ss << i << "+" << j << " " << cmd;
            paths.push_back(ss.str());
            dfs(new_state, visit | (1 << new_state), cost + max(costMap[i],costMap[j]));
            paths.pop_back();
        }

        //如果最大的两个跟手灯在同一边；并且对面有人；则此次的策略很明显！
        //如果i是最大的两个之一，则不合法(最慢的两个，必须一起过去)，直接跳过。
        if (i >= N - 2) {
            continue;
        }

        new_state = goOtherSide(state, i);
        new_state = goOtherSide(new_state, N);
        if (visit & (1 << new_state)) {
            continue;
        }

        stringstream ss;
        ss << i << " " << cmd;
        paths.push_back(ss.str());
        dfs(new_state, visit | (1 << new_state), cost + costMap[i]);
        paths.pop_back();
    }
}

void dfs(int state, long visit, int cost) {
    if (state == (1 << (N + 1)) - 1) {
        if (cost < min_cost) {
            min_cost = cost;
            minPath = paths;
            
            cout << "minCost:" << min_cost << endl;
            for (auto x : minPath) {
                cout << x << endl;
            }
            cout << "-------\n";
        }
        cout << "total_cnt:" << ++total_cnt << endl;
        return;
    }

    //当前局面有哪几种选择
    if (state & (1 << N)) { //手灯在上面，人需要往下走
        single_select(state, visit, cost, "Down");
    } 
    else {
        single_select(state, visit, cost, "Up");
    }
}

int main() {
    dfs(0, 0, 0);
    cout << "minCost:" << min_cost << endl;
    for (auto x : minPath) {
        cout << x << endl;
    }
    return 0;
}