#include <iostream>
#include <queue>
#include <vector>

#define MAX_N 10
#define MAX_M 10

using namespace std;

struct Node {
    int y, x;
};

struct Edge{
    int from, to;
    int length;

    bool operator < (Edge e) const {
        return length > e.length;
    }
};

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int N, M;
int arr[MAX_N][MAX_M];
int parent[MAX_N*MAX_M];
priority_queue<Edge> pq;

void printDebug() {
    cout << '\n';
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) cout << arr[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}

void sepCountry() {
    int country = 2;
    for(int i=0;i<N;i++)for(int j=0;j<M;j++) {
        if(arr[i][j] == 1) {
            queue<Node> q;
            q.push({i, j});
            arr[i][j] = country;
                
            while(!q.empty()) {
                Node now = q.front();q.pop();

                int ny, nx;
                for(int d=0;d<4;d++) {
                    ny = now.y + dy[d];
                    nx = now.x + dx[d];
                    if(ny < 0 || ny >= N || nx < 0 || nx >= M) continue;
                    if(arr[ny][nx] == 1) {
                        arr[ny][nx] = country;
                        q.push({ny, nx});
                    }
                }
            }
            country++;
        }
    }
}

void getBridge() {
    for(int i=0;i<N;i++)for(int j=0;j<N;j++) {
        if(arr[i][j]) {
            for(int d=0;d<4;d++) {
                int length = 1;
                int ny = i;
                int nx = j;

                while (true) {
                    if(ny < 0 || ny >= N || nx < 0 || nx >= M) break;
                    if(arr[ny][nx] > 0) {
                        if(length <= 1) break;
                        if(arr[ny][nx] == arr[i][j]) break;
                        pq.push({arr[ny][nx], arr[i][j], length});
                        break;
                    }
                    length++;
                    ny += dy[d];
                    nx += dx[d];
                }

            }
        }
    }
}

int main() {
    cin >> N >> M;
    for(int i=0;i<N;i++)for(int j=0;j<M;j++) cin >> arr[i][j];

    for(int i=0;i<MAX_N*MAX_M;i++) parent[i] = i;

    sepCountry();

    getBridge();

    return 0;
}