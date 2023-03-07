// 각 섬을 floodfill로 이름 정하기
// 각섬들의 최소 거리를 저장
// 각 섬들을 kruskal 로 연결 MST
// 마지막에 다리개수가 섬 개수 -1 이면 통과
#include <iostream>
#include <queue>

using namespace std;
int map[10][10];
int land[10][10];
int length[100][100]; // from to 최소 

int N, M;
int node;
struct Node {
    int y, x;
};
struct Bridge {
    int A;
    int B;
    int dist;
    bool operator < (Bridge o) const {
        return dist > o.dist;
    }
};
int dir[4][2] = { -1,0,0,1,1,0,0,-1 };

void floodfill(int y, int x) {
    queue<Node>q;
    q.push({ y,x });
    while (!q.empty()) {
        Node now = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int dy = now.y + dir[i][0];
            int dx = now.x + dir[i][1];
            if (dy < 0 || dx < 0 || dy >= N || dx >= M)
                continue;
            if (map[dy][dx] != 1)
                continue;
            if (land[dy][dx] != 0)
                continue;
            land[dy][dx] = node;
            q.push({ dy,dx });
        }
    }
}
void getLen() { //해당 섬에서 각 섬의 길이 찾기
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (land[y][x] == 0)
                continue;
            int now = land[y][x];
            for (int i = 0; i < 4; i++) {
                int dy = y;
                int dx = x;
                int dist = 0;
                while (1) {
                    dy += dir[i][0];
                    dx += dir[i][1];
                    if (dy < 0 || dx < 0 || dy >= N || dx >= M)
                        break;
                    int next = land[dy][dx];
                    if (now == next) // 같은 섬이면 나가
                        break;
                    if (next != 0) { // 다른 섬을 만나면
                        if (dist > 1) {
                            if (length[now][next] > dist) { //최소 다리 길이면 업데이트
                                length[now][next] = dist;
                                length[next][now] = dist;
                            }
                        }
                        break;
                    }
                    dist++;
                }
            }
        }
    }
}
int parent[11];
int Find(int now) {
    //cout << now << '\n';
    if (now == parent[now])
        return now;
    return parent[now] = Find(parent[now]);
}
void Union(int A, int B) {
    int pa = Find(A);
    int pb = Find(B);
    if (pa == pb)
        return;
    parent[pb] = pa;
}
int kruskal() {
    priority_queue<Bridge>pq;

    for (int A = 1; A <= node; A++) {
        for (int B = 1; B <=node; B++) {
            if (length[A][B] == 21e8)
                continue;
            pq.push({ A,B,length[A][B] });
        }
    }
    int cnt = 0;
    int sum = 0;
    while (!pq.empty()) {
        Bridge now = pq.top();
        pq.pop();
        if (now.dist <= 1)
            continue;
        if (Find(now.A) == Find(now.B))
            continue;
        cnt++;
        sum += now.dist;
        Union(now.A, now.B);
    }
    if (cnt != node - 1)
        return -1;
    return sum;
}
int main() {
    cin >> N >> M;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            cin >> map[y][x];
            length[y+1][x+1] = 21e8;
        }
    }
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (map[y][x] == 1 && land[y][x] == 0) {
                node++; //node(섬)번호는 1부터
                land[y][x] = node;
                floodfill(y, x); // map을 node 번호로 바꾼다.
            }
        }
    }
    if (node == 0)
        cout << 0;
    for (int i = 0; i < 11; i++) {
        parent[i] = i;
    }
    getLen();//각 섬에서 모든 섬까지 다리 길이 찾기
    int ans = kruskal();
    cout << ans;
    return 0;
}
