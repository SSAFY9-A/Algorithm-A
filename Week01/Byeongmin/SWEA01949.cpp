#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/*
    1. 등산로는 가장 높은 봉우리에서 시작
    2. 등산로는 산으로 올라갈 수 있도록 반드시 높은 지형 -> 낮은 지형으로 가로/세로 로 연결
        --> 높이가 같은 곳, 낮은 지형, 대각선은 연결 X
    3. 등산로 중 '딱 한 곳'을 정해 최대 K 깊이만큼 지형 깎기 가능
*/

// Conditions
#define MAX_N 8
#define MAX_K 5
#define MAX_val 20
#define MAX_peak 5

// variables
int N, K;
bool cut;
int arr[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int max_length; // 정답 (가장 긴 등산로 길이)

struct PEAK {
    int y, x;
};
vector<PEAK> peaks; // 가장 높은 봉우리 좌표 저장
int max_peak; // 가장 높은 봉우리 높이

int dx[4] = { 0, 1, 0, -1 }; // 북동남서
int dy[4] = { -1, 0, 1, 0 };

// functions
void init() {
    memset(arr, 0, sizeof(arr));
    memset(visited, 0, sizeof(visited));
    cut = false;
    max_length = 0;
    max_peak = 0;
}

bool isInRange(int y, int x) {
    if (y >= 0 && y < N && x >= 0 && x < N) return true;
    return false;
}

void dfs(int level, int y, int x) { // level = 현재 등산로 길이
    visited[y][x] = true;
    //cout << "[" << level << "] (" << y << ", " << x << ")\n";
    if (max_length < level) max_length = level; // 등산로 길이 업데이트

    // 탐색
    int cy, cx;
    for (int i = 0; i < 4; i++) { // 4방향으로 간다
        cy = y + dy[i];
        cx = x + dx[i];
        if (isInRange(cy, cx) && !visited[cy][cx]) { // 범위 내에서 방문하지 않았다면
            if (!cut && arr[cy][cx] >= arr[y][x] && arr[cy][cx] - K < arr[y][x]) { // 아직 안깎았고, 못지나가면서, 깎아서 지나갈 수 있으면
                //cout << "(" << cy << ", " << cx << ") cut\n";
                cut = true;
                int origin = arr[cy][cx]; // 원래 높이 저장
                arr[cy][cx] = arr[y][x] - 1; // 현재 위치보다 1적게
                dfs(level + 1, cy, cx);
                arr[cy][cx] = origin; // 원래 높이로 복원
                cut = false;
            }
            else if (arr[cy][cx] < arr[y][x]) { // 현재 높이보다 낮을 때
                dfs(level + 1, cy, cx); // 길 개척
            }
        }
    }
    visited[y][x] = false;
}

int main() {
    int test_case, T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case) {
        init();

        cin >> N >> K;
        for (int i = 0; i < N; i++)for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
            if (arr[i][j] > max_peak) { // 가장 높은 봉우리 업데이트
                peaks.clear();  // 봉우리 vector 초기화
                max_peak = arr[i][j];
            }
            if (arr[i][j] == max_peak) { // 가장 높은 봉우리 좌표 저장
                peaks.push_back({ i, j });
            }
        }

        for (int i = 0; i < peaks.size(); i++) { // 모든 가장 높은 봉우리에서 시작
            dfs(1, peaks[i].y, peaks[i].x);
        }

        cout << '#' << test_case << ' ' << max_length << '\n';
    }

    return 0;
}