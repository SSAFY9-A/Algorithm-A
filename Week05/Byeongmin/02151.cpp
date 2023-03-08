#include <iostream>

using namespace std;

#define MAX_N 50

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

struct Node{
    int y, x;
};

int N;
char arr[MAX_N][MAX_N];
int answer = MAX_N;
bool visited[MAX_N][MAX_N];

void dfs(Node door) {

}

int main() {
    cin >> N;

    Node door = {-1, -1};

    for(int i=0;i<N;i++)for(int j=0;j<N;j++) {
        cin >> arr[i][j];
        if(door.y == -1 && arr[i][j] == '#') door = {i, j};
    }

    dfs(door);

    return 0;
}