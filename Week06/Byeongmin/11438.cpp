#include <iostream>
#include <vector>
using namespace std;

#define MAX_N 100001
#define MAX_M 100000

int depth[MAX_N];
vector<int> graph[MAX_N];
int dp[MAX_N][20];

void makeTree(int now, int parent) {
    depth[now] = depth[parent] + 1;

    dp[now][0] = parent;
    int r = 1;
    int i = 2;
    while(i < depth[now]) {
        dp[now][r] = dp[dp[now][r-1]][r-1];
        i*=2;
    }

    for(auto it=graph[now].begin();it!=graph[now].end();++it) {
        if(*it==parent) continue;
        makeTree(*it, now);
    }
}

int Find(int a, int b) {
    // depth a > b 로 만들어 줌
    if(depth[a] < depth[b]) {
        int t = a;
        a = b;
        b = t;
    }

    while(depth[a] != depth[b]) {
        int i = 0;
        while(depth[dp[a][i]] >= depth[b]) ++i;
        if(i) a = dp[a][i-1];
        else a = dp[a][i];
    }

    while(a != b) {
        int i = 0;
        while(dp[a][i]!=dp[b][i]) ++i;
        if(i) {
            a = dp[a][i-1];
            b = dp[b][i-1];
        } else return dp[a][0];
    }

    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M;

    int a, b;
    cin >> N;
    for(int i=1;i<N;++i) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    makeTree(1, 0);

    cin >> M;
    for(int i=0;i<M;++i) {
        cin >> a >> b;
        cout << Find(a, b) << '\n';
    }

    return 0;
}