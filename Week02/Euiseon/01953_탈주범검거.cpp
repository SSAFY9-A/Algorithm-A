#include <iostream>
#include <queue>

using namespace std;
//masking
int mask[8][4] = {
    {0,0,0,0},
    {1,1,1,1},//1
    {1,0,1,0},//2
    {0,1,0,1},//3
    {1,1,0,0},//4
    {0,1,1,0},//5
    {0,0,1,1},//6
    {1,0,0,1}//7
};
struct Node {
    int y, x;
    int time;
    int type;
};
int dir[4][2] = { -1,0,0,1,1,0,0,-1 }; //위, ->, 아래, <-
int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N, M, R, C, L; // 터널 크기 (N,M),맨홀위치(R,C), 소요 시간(L)
        cin >> N >> M >> R >> C >> L;
        int map[51][51] = { 0 };
        int ans = 0;
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < M; x++) {
                cin >> map[y][x];
            }
        }
        queue<Node>q;
        int type = map[R][C];
        q.push({ R,C,1,type});
        
        map[R][C] = 0;
      
        while (!q.empty()) {
            Node now = q.front();
            q.pop();

            if (now.time > L)
                break;
            
            
            ans++;
            type = now.type;
            for (int i = 0; i < 4; i++) {
                if (mask[type][i] == 0)
                    continue;
                int dy = now.y + dir[i][0];
                int dx = now.x + dir[i][1];
                if (dy < 0 || dx < 0 || dy >= N || dx >= M)
                    continue;
                if (map[dy][dx] == 0)
                    continue;
                if (mask[map[dy][dx]][(i + 2) % 4] == 0) // (i+2)%4 는 다음 노드에서 바라본 방향
                    continue;
                
       
                int nextTime = now.time + 1;
                q.push({ dy,dx,nextTime,map[dy][dx]});
                map[dy][dx] = 0;
            }

        }
        cout << '#' << t + 1 << ' ' << ans << '\n';
    }

    return 0;
}