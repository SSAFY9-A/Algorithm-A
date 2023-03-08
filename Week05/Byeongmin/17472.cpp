#include <iostream>
#include <queue>
#include <vector>

#define MAX_N 10
#define MAX_M 10
#define MAX_C 9 // Max Country + 3

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
int parent[MAX_C];
priority_queue<Edge> pq;
int country = 2;
int answer = 0;

void printDebug() {
    cout << '\n';
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) cout << arr[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}

void sepCountry() {
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
    for(int i=0;i<N;i++)for(int j=0;j<M;j++) {
        if(arr[i][j]) {
            for(int d=0;d<4;d++) {
                int length = 0;
                int ny = i + dy[d];
                int nx = j + dx[d];

                while (true) {
                    if(ny < 0 || ny >= N || nx < 0 || nx >= M) break;
                    if(arr[ny][nx] > 0) {
                        if(length <= 1) break;
                        if(arr[ny][nx] == arr[i][j]) break;
                        //cout << "(" << i << ", " << j << ") -> (" << ny << ", " << nx << ")\n";
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

int Find(int a) {
    if(parent[a] == a) return a;
    else return Find(parent[a]);
}

void Union(int a, int b) {
    int pa = Find(a);
    int pb = Find(b);

    parent[pb] = pa;
}

bool connectBridge() {
    int num_bridges = 0;

    while(num_bridges < country - 3) {
        if(pq.empty()) return false;

        Edge e = pq.top();
        pq.pop();

        if(Find(e.from) == Find(e.to)) continue;
        
        answer += e.length;
        Union(e.to, e.from);
        num_bridges++;
    }
    return true;
}

int main() {
    cin >> N >> M;
    for(int i=0;i<N;i++)for(int j=0;j<M;j++) cin >> arr[i][j];

    for(int i=0;i<MAX_C;i++) parent[i] = i;

    sepCountry();

    getBridge();

    if(connectBridge()) {
        cout << answer;
    } else cout << -1;

    return 0;
}