#include<iostream>
#include<cstring>
using namespace std;

#define MAX_N 20
#define MAX_TYPE 101
 
int N, cnt, answer, y_start, x_start;
int cafe[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
bool DAT[MAX_TYPE];

int dx[4] = {1, -1, -1, 1};
int dy[4] = {1, 1, -1, -1};

void init() {
    memset(visited, 0, sizeof(visited));
    memset(DAT, 0, sizeof(DAT));
    cnt = 0;
    answer = -1;
 
    cin >> N;
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) cin >> cafe[i][j];
}
 
void dfs(int y, int x, int dir) {
    if(y_start == y && x_start == x && visited[y][x]) {
        if(cnt > answer) {
            //cout << "(" << y_start+1 << ", " << char(x_start+'A') << ") " << cnt << '\n';
            answer = cnt;
        }
        return;
    }
    if(visited[y][x]) return;
    if(DAT[cafe[y][x]]) return;
    if(dir == 4) return;
 
 
    visited[y][x] = true;
    DAT[cafe[y][x]] = true;
    cnt++;
 
    int cy, cx;
    // same driection
    cy = y+dy[dir];
    cx = x+dx[dir];
    if(cy>=0&&cy<N&&cx>=0&&cx<N) dfs(cy, cx, dir);
 
    // next direction
    cy = y+dy[dir+1];
    cx = x+dx[dir+1];
    if(cy>=0&&cy<N&&cx>=0&&cx<N) dfs(cy, cx, dir+1);
 
    cnt--;
    DAT[cafe[y][x]] = false;
    visited[y][x] = false;
 
}
 
int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin>>T;
    for(test_case = 1; test_case <= T; ++test_case) {
        init();
 
        for(int i=0;i<N-1;i++) for(int j=0;j<N-1;j++) {
            y_start = i;
            x_start = j;
 
            dfs(i, j, 0);
        }
 
        cout << '#' << test_case << ' ' << answer << '\n';
    }
    return 0;
}