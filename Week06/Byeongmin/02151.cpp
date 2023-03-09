#include <iostream>
#include <cstring>
using namespace std;

#define MAX_N 50

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

struct Node{
    int y, x;
};

int N;
char arr[MAX_N][MAX_N+1];
int visited[MAX_N][MAX_N][4];
int answer = MAX_N;
Node door = {-1, -1};

void printDebug(int y, int x) {
    cout << '\n';
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++) {
            if(i==y && j==x) cout << 'X';
            else cout << arr[i][j];
        }
        cout << '\n';
    }
    char c;
    cin >> c;
}

void dfs(Node now, int d, int mirror) {
    if(answer <= mirror) return;
    if(visited[now.y][now.x][d] && visited[now.y][now.x][d] >= mirror) return;

    int ny, nx;
    for(int d=0;d<4;d++) {
        ny = now.y + dy[d];
        nx = now.x + dx[d];
    }
}

int main() {
    cin >> N;

    memset(visited, 0, sizeof(visited));

    for(int i=0;i<N;i++) {
        cin >> arr[i];
        for(int j=0;j<N;j++) {
            if(arr[i][j] == '#' && door.y == -1) {
                door = {i, j};
                arr[i][j] = '*';
            }
        }
    }

    for(int d=0;d<4;d++) dfs({door.y, door.x}, d, 0);

    cout << answer;

    return 0;
}