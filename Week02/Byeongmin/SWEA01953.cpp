#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 50
#define MAX_M 50
#define MAX_L 20

int N, M, R, C, L;
int arr[MAX_N][MAX_M];
int visited[MAX_N][MAX_M];
int cnt;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

vector<int> pipes[8] = {
    {},
    {0, 1, 2, 3},
    {0, 2},
    {1, 3},
    {0, 1},
    {1, 2},
    {2, 3},
    {0, 3}
};

struct NODE{
    int y,x;
};

void init() {
    memset(arr, 0, sizeof(arr));
    memset(visited, 0, sizeof(visited));
    cnt = 0;
}

void bfs(NODE start) {
    queue<NODE> q;

    q.push(start);
    visited[start.y][start.x] = 1;

    int ny, nx;
    while(!q.empty()) {
        NODE now = q.front();q.pop();
        int pipe = arr[now.y][now.x];

        for(int i=0;i<pipes[pipe].size();i++) {
            // next node
            ny = now.y + dy[pipes[pipe][i]];
            nx = now.x + dx[pipes[pipe][i]];

            // check if next node is in range and not visited and next node is connected to current node
            if(ny >= 0 && ny < N && nx >= 0 && nx < M && !visited[ny][nx] && arr[ny][nx] != 0) {
                for(int j=0;j<pipes[arr[ny][nx]].size();j++) {
                    if(pipes[arr[ny][nx]][j] == (pipes[pipe][i] + 2) % 4) {
                        q.push({ny, nx});
                        visited[ny][nx] = visited[now.y][now.x] + 1;
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    int T;
    cin >> T;

    for(int t=1;t<=T;t++) {
        init();

        cin >> N >> M >> R >> C >> L;
        NODE start = {R, C};
        for(int i=0;i<N;i++) for(int j=0;j<M;j++) {
            cin >> arr[i][j];
        }

        bfs(start);
        
        for(int i=0;i<N;i++)for(int j=0;j<M;j++) if(visited[i][j] && visited[i][j] <= L) cnt++;

        cout << '#' << t << ' ' << cnt << '\n';
    }

    return 0;
}