#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define MAX_R 20
#define MAX_C 20

// < > ^ v
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Node{
    int y, x;
    int direction;
    int memory;
};

int R, C;
char arr[MAX_R][MAX_C+1];
bool visited[MAX_R][MAX_C][4][16];
bool exits;

void init() {
    memset(arr, 0, sizeof(arr));
    memset(visited, 0, sizeof(visited));
}

bool checkExit(){
    for(int i=0;i<R;i++)for(int j=0;j<C;j++) if(arr[i][j] == '@') return true;
    return false;
}

void printDebug(Node n){
    cout << "(" << n.y << ", " << n.x << ") [" << n.direction << " " << n.memory << "]\n";
    for(int i=0;i<R;i++) {
        for(int j=0;j<C;j++) {
            if(i == n.y && j == n.x) cout << "X ";
            else cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
    int t;
    cin >> t;
}

bool go(Node start) {
    if(!exits) return false;

    queue<Node> q;
    q.push(start);

    while(!q.empty()) {
        Node now = q.front();
        int y = now.y;
        int x = now.x;
        int direction = now.direction;
        int memory = now.memory;
        q.pop();

        // printDebug(now);

        if(arr[y][x] == '@') return true;

        if(visited[y][x][direction][memory]) continue;
        visited[y][x][direction][memory] = true;

        if(arr[y][x] == '<') direction = 0;
        else if (arr[y][x] == '>') direction = 1;
        else if (arr[y][x] == '^') direction = 2;
        else if (arr[y][x] == 'v') direction = 3;
        else if (arr[y][x] == '_') {
            if(memory) direction = 0;
            else direction = 1;
        }
        else if (arr[y][x] == '|') {
            if(memory) direction = 2;
            else direction = 3;
        }
        else if (arr[y][x] >= '0' && arr[y][x] <= '9') memory = arr[y][x] - '0';
        else if (arr[y][x] == '+') memory = (memory+1)%16;
        else if (arr[y][x] == '-') memory = (memory+15)%16;
        else if (arr[y][x] == '?') for(int d=1;d<4;d++) {
            int nd = (direction + d) % 4;
            int ny = y + dy[nd];
            int nx = x + dx[nd];

            if(ny == -1) ny += R;
            if(ny == R) ny = 0;
            if(nx == -1) nx += C;
            if(nx == C) nx = 0;

            if(!visited[ny][nx][nd][direction]) q.push({ny, nx, nd, memory});
        }
        y += dy[direction];
        x += dx[direction];

        if(y == -1) y += R;
        if(y == R) y = 0;
        if(x == -1) x += C;
        if(x == C) x = 0;

        if(!visited[y][x][direction][memory]) q.push({y, x, direction, memory});
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    for(int t=1;t<=T;t++) {
        init();
        cin >> R >> C;
        for(int i=0;i<R;i++) cin >> arr[i];
        exits = checkExit();

        cout << "#" << t << " ";
        if(go({0, 0, 1, 0})) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}