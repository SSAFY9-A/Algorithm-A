#include<iostream>
#include<cstring>
#include<vector>
#include<string>
using namespace std;

/* 시간 복잡도 계산

    4방향 연결 + 연결 X ==> 5가지 경우의 수
    최대 core = 12 ==> O(5^12) = 약 2억 ==> 2초
    50개 테스트케이스 2초 --> TC 1개당 0.04초
    백트래킹 으로 될라나...
    1. 가장자리 할 필요 X
    2. 연결 안할 때 남은 core수가 최대 연결 core보다 적으면 X

*/

// Conditions
#define MAX_N 12
#define MAX_core 12

// variables
struct CORE {
    int y, x;
};
vector<CORE> cores; // 연결이 필요한 core들
bool arr[MAX_N][MAX_N];
bool board[MAX_N][MAX_N]; // 실제로 연결 시켜볼 cell 판
int N;
int skip, min_skip; // 연결 안한 core 수
int line, min_line; // 사용된 전선의 길이
int dx[4] = { 0, 1, 0, -1 }; // 0 1 2 3
int dy[4] = { -1, 0, 1, 0 }; // 북동남서

// functions
void init() { // 초기화
    memset(arr, 0, sizeof(arr));
    memset(board, 0, sizeof(board));
    cores.clear();
    skip = 0;
    min_skip = MAX_core;
    line = 0;
    min_line = MAX_N * MAX_N;
}

void debug_print() {
    cout << '\n';
    cout << "[line] " << line << '\n' << "[skip] " << skip << '\n';
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i][j]) cout << "# ";
            else cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
}

bool connect(CORE core, int d) { // d 방향으로 core 연결. 연결시 return true
    int cy = core.y + dy[d];
    int cx = core.x + dx[d];

    // 일단 되는지부터 확인
    while (cx >= 0 && cx < N && cy >= 0 && cy < N) { // 가장자리까지 확인
        if (board[cy][cx]) return false; // core 또는 line 있으면 return false
        cy += dy[d];
        cx += dx[d];
    }

    cy = core.y + dy[d];
    cx = core.x + dx[d];
    // 연결 가능한 경우
    while (cx >= 0 && cx < N && cy >= 0 && cy < N) { // board에 선 연결
        line++;
        board[cy][cx] = 1;
        cy += dy[d];
        cx += dx[d];
    }

    return true;
}

void disconnect(CORE core, int d) { // d 방향으로 연결된 선 삭제
    int cy = core.y + dy[d];
    int cx = core.x + dx[d];

    while (cx >= 0 && cx < N && cy >= 0 && cy < N) {
        line--;
        board[cy][cx] = 0;
        cy += dy[d];
        cx += dx[d];
    }
}

void dfs(int idx) {
    if (skip > min_skip) return; // 이미 연결해본 core 수보다 적을 때 return

    if (idx == cores.size()) { // 끝까지 왔을 때
        //debug_print();
        if (min_skip > skip) { // 더 많은 core 연결했을 때
            min_skip = skip;
            min_line = line;
        } else if (min_skip == skip && min_line > line) min_line = line; // 코어 수는 같지만 line은 적을 때

        return;
    }

    // 4방향 연결
    for (int d = 0; d < 4; d++) {
        if (connect(cores[idx], d)) {
            dfs(idx+1);
            disconnect(cores[idx], d);
        }
    }

    // 연결 X
    skip++;
    dfs(idx + 1);
    skip--;
}

int main(int argc, char** argv)
{
    // test case
    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        // initialize
        init();

        // input
        cin >> N;
        for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
            board[i][j] = arr[i][j];
            if (arr[i][j] && i > 0 && i < N-1 && j > 0 && j < N-1) { // 안쪽 core들만 저장
                cores.push_back({ i, j });
            }
        }

        dfs(0); // 0번 index core부터 시작

        cout << '#' << test_case << ' ' << min_line << '\n';
    }
    return 0;
}