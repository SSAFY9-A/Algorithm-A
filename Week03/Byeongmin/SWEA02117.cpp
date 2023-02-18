/*
2117. [모의 SW 역량테스트] 홈 방범 서비스
https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V61LqAf8DFAWu&
*/

/*
운영비용 = K * K + (K - 1) * (K - 1)
운영이익 = M * 집
*/

#include <iostream>
#include <cstring>
#include <queue>

#define MAX_N 20
#define MAX_M 10

using namespace std;

struct Node{
    int y, x;
};

int N, M;
int total_houses;
bool arr[MAX_N][MAX_N];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

int max(int a, int b) {
    return a>b?a:b;
}

void init() {
    memset(arr, 0, sizeof(arr));
    total_houses = 0;
}

void input() {
    cin >> N >> M;
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) {
        cin >> arr[i][j];
        if(arr[i][j]) total_houses++;
    }
}

int getCost(int K) {
    return K * K + (K-1) * (K-1);
}

int bfs(Node start) {
    int visited[MAX_N][MAX_N] = {0, };
    int DAT[MAX_N+MAX_N] = {0, };
    queue<Node> q;
    q.push(start);
    visited[start.y][start.x] = 1;
    if(arr[start.y][start.x]) DAT[1] = 1;

    int max_K = 0;

    while(!q.empty()) {
        Node now = q.front(); q.pop();

        int ny, nx;
        for(int d=0;d<4;d++) {
            ny = now.y + dy[d];
            nx = now.x + dx[d];
            if(ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
            if(getCost(visited[now.y][now.x] + 1) > total_houses * M) continue;
            if(visited[ny][nx]) continue;
            q.push({ny, nx});
            // cout << "{" << ny << ", " << nx << "}\n";
            visited[ny][nx] = visited[now.y][now.x] + 1;
            if(arr[ny][nx]) DAT[visited[ny][nx]]++;
            if(max_K < visited[ny][nx]) max_K = visited[ny][nx];
        }
    }

    int result = 0;
    for(int i=1;i<=max_K;i++) {
        DAT[i] += DAT[i-1];
        // cout << DAT[i] << ' ';
    }
    for(int i=1;i<=max_K;i++) {
        if(getCost(i) <= DAT[i] * M) result = DAT[i];
        // cout << "[" << i << "] " << getCost(i) << ", result: " << result << '\n';
    }
    return result;
}

int main() {
    int T;
    cin >> T;
    for(int t=1;t<=T;t++) {
        init();
        input();

        int answer = 0;
        // answer = max(answer, bfs({0, 0}));
        for(int i=0;i<N;i++) for(int j=0;j<N;j++) {
            answer = max(answer, bfs({i, j}));
        }

        cout << '#' << t << ' ' << answer << '\n';
    }

    return 0;
}