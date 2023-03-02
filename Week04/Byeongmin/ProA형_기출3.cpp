#include <iostream>
#include <cstring>
#include <queue>
#define MAX_N 8

using namespace std;

int N, min_diff;
bool arr[MAX_N][MAX_N];
int people[MAX_N];
int groups[MAX_N];

void init() {
    memset(groups, 0, sizeof(groups));
    min_diff = 200;
}

bool bfs(int A, int B) {
    if(A == 0 || B == 0) return false;

    queue<int> q;
    bool visited[MAX_N] = {0, };
    int sums[2] = {A, B};

    int idx = 0;

    for(int g=0;g<2;g++) {
        int group = groups[idx];
        int sum = people[idx];
        q.push(idx);
        visited[idx] = true;

        while(!q.empty()) {
            int now = q.front(); q.pop();

            for(int i=0;i<N;i++) {
                if(arr[now][i] && !visited[i] && group == groups[i]) {
                    q.push(i);
                    sum += people[i];
                    visited[i] = true;
                }
            }
        }

        if(sum != sums[group]) return false;
        
        while(groups[idx] == group) idx++;
    }
    return true;
}

void dfs(int level, int A, int B) {
    if(level == N) {
        if(bfs(A, B)) {
            int result = A - B;
            if(result < 0) result *= -1;
            if(min_diff > result) min_diff = result;
        }
        return;
    }

    groups[level] = 0;
    dfs(level+1, A+people[level], B);
    groups[level] = 1;
    dfs(level+1, A, B+people[level]);
}

int main() {
    int T;
    cin >> T;
    for(int t=1;t<=T;t++) {
        cin >> N;
        init();

        for(int i=0;i<N;i++) for(int j=0;j<N;j++) cin >> arr[i][j];
        for(int i=0;i<N;i++) cin >> people[i];

        dfs(0, 0, 0);

        cout << "#" << t << " " << min_diff << '\n';
    }

    return 0;
}