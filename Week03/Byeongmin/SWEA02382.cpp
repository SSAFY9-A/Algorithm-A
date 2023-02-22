/*
2382. [모의 SW 역량테스트] 미생물 격리
https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl&&
*/

#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 101
#define MAX_K 1001
#define MAX_M 1001

using namespace std;

struct Cell {
    int y, x;
    int num;
    int direction;
    bool moveFlag;

    bool operator < (Cell c) {
        return num < c.num;
    }
};

int N, K, M;
int total_num;
queue<Cell> arr[MAX_N][MAX_N];

const int dx[5] = {0, 0, 0, -1, 1};
const int dy[5] = {0, -1, 1, 0, 0};

void init() {
    total_num = 0;
    for(int i=0;i<N;i++)for(int j=0;j<N;j++) while(!arr[i][j].empty()) arr[i][j].pop();
}

int getOppositeDirection(int d) {
    if(d == 1) return 2;
    else if (d == 2) return 1;
    else if (d == 3) return 4;
    else if (d == 4) return 3;
    return 0;
}

void printDebug() {
    for(int y=0;y<N;y++) {
        for(int x=0;x<N;x++) {
            if(arr[y][x].size()==0) cout << 0 << '\t';
            else cout << arr[y][x].front().num << '\t';
        }
        cout << '\n';
    }
    cout << '\n';
}

void move() {
    for(int i=0;i<N;i++)for(int j=0;j<N;j++) {
        if(arr[i][j].empty() || arr[i][j].front().moveFlag == M%2) continue;

        Cell now = arr[i][j].front();
        arr[i][j].pop();

        now.y += dy[now.direction];
        now.x += dx[now.direction];
        if(now.y == 0 || now.y == N-1 || now.x == 0 || now.x == N-1) {
            now.direction = getOppositeDirection(now.direction);
            total_num -= (now.num - (now.num / 2));
            now.num = now.num / 2;
        }
        now.moveFlag = !now.moveFlag;

        if(now.num != 0) arr[now.y][now.x].push(now);

        // printDebug();
    }
}

void combine() {
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) {
        if(arr[i][j].size() < 2) continue;

        int size = arr[i][j].size();

        int max_num = 0;

        Cell result = {i, j, 0, 0, arr[i][j].front().moveFlag};

        for(int k=0;k<size;k++) {
            Cell now = arr[i][j].front();
            arr[i][j].pop();

            result.num += now.num;

            if(max_num < now.num) {
                max_num = now.num;
                result.direction = now.direction;
            }
        }

        arr[i][j].push(result);
    }
}

int main() {
    int T;
    cin >> T;
    for(int t=1;t<=T;t++) {
        cin >> N >> M >> K;

        init();

        int y, x, num, direction;
        for(int i=0;i<K;i++) {
            cin >> y >> x >> num >> direction;
            arr[y][x].push({y, x, num, direction, bool(M%2)});
            total_num += num;
        }

        //printDebug();

        while(M--) {
            //cout << "[" << M << "]\n";
            move();
            //printDebug();
            combine();
            //printDebug();
        }

        cout << '#' << t << ' ' << total_num << '\n';
    }


    return 0;
}