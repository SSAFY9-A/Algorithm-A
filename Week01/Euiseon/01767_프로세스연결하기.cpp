#include <iostream>
#include <vector>
#include <limits.h>
#include <cstring>
using namespace std;

int N;
int map[13][13];
int clone[13][13];
int lineCnt;
int completed;
int maxCore = INT_MIN;
int minLine = INT_MAX;
struct NODE {
    int y;
    int x;
};
vector<NODE>v;
int isRange(int y, int x) {
    if (y < 0 || x < 0 || y >= N || x >= N)
        return 0;
    return 1;
}
int dir[4][2] = { -1,0,0,1,1,0,0,-1 };
int isEdge(int y, int x) {
    if (y == 0 || x == 0 || y == N - 1 || x == N - 1)
        return 1;
    return 0;
}
int isPossible(int y, int x, int dy, int dx) {
    while (1) { //끝까지 전선을 연결할 수 있는 방향인지 판단
        y += dy;
        x += dx;
        if (isRange(y, x) && clone[y][x] != 0) {
            return 0;
        }
        if (!isRange(y, x)) {
            return 1;
        }
    }
}
void changeMap(int y, int x, int dy, int dx) {
    while (1) {
        y += dy;
        x += dx;
        if (!isRange(y, x)) {
            return;
        }
        clone[y][x] = -1;
        lineCnt++;
    }
}
void restoreMap(int y, int x, int dy, int dx) {
    while (1) {
        y += dy;
        x += dx;
        if (!isRange(y, x)) {
            return;
        }
        clone[y][x] = 0;
        lineCnt--;
    }
}
void dfs(int level) { // level은 배열에 저장한 core 수
    if (level == v.size()) {
        if (completed > maxCore) {
            maxCore = completed;
            minLine = INT_MAX;
        }
        else if (completed == maxCore && minLine > lineCnt) {
            minLine = lineCnt;
        }
        return;
    }

    //branch는 direction
    for (int i = 0; i < 4; i++) {
       int y = v[level].y;
        int x = v[level].x;

        if (!isPossible(y, x, dir[i][0], dir[i][1]))
            continue;
        changeMap(y, x, dir[i][0], dir[i][1]);
        completed++;
        dfs(level + 1);
        completed--;
        restoreMap(y, x, dir[i][0], dir[i][1]);
    }
    dfs(level + 1); // 아무 전선도 연결하지 않을 경우
}
int main() {
    int T;
    cin >> T;
    vector<int>ans;

    for (int t = 0; t < T; t++) {
        cin >> N;
        //입력
        v.clear();
        lineCnt = 0;
        completed = 0;
        maxCore = INT_MIN;
        minLine = INT_MAX;

        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                cin >> map[y][x];
                clone[y][x] = map[y][x];
                if (map[y][x] == 1) { //core일 때
                    if (isEdge(y, x)) { // 가장자리면 skip
                        completed++; // 연결완성된 core count
                    }
                    else {
                        v.push_back({ y,x }); //아니면 dfs돌릴 좌표값 배열에 저장
                    }
                }
            }
        }
        dfs(0);

        if (minLine == INT_MAX)
            ans.push_back(maxCore);
        else ans.push_back(minLine);
    }
    for (int t = 1; t <= T; t++) {
        cout << '#' << t << ' ' << ans[t-1] << '\n';
    }
}

//입력
//0 : road, 1 : core , -1 : visited
//dfs 
//level -> core 개수
//branch -> direction
//backtracking point
//1. 가장자리면 skip