#include<iostream>
#include<cstring>
#include<vector>
#include<string>
using namespace std;

/* �ð� ���⵵ ���

    4���� ���� + ���� X ==> 5���� ����� ��
    �ִ� core = 12 ==> O(5^12) = �� 2�� ==> 2��
    50�� �׽�Ʈ���̽� 2�� --> TC 1���� 0.04��
    ��Ʈ��ŷ ���� �ɶ�...
    1. �����ڸ� �� �ʿ� X
    2. ���� ���� �� ���� core���� �ִ� ���� core���� ������ X

*/

// Conditions
#define MAX_N 12
#define MAX_core 12

// variables
struct CORE {
    int y, x;
};
vector<CORE> cores; // ������ �ʿ��� core��
bool arr[MAX_N][MAX_N];
bool board[MAX_N][MAX_N]; // ������ ���� ���Ѻ� cell ��
int N;
int skip, min_skip; // ���� ���� core ��
int line, min_line; // ���� ������ ����
int dx[4] = { 0, 1, 0, -1 }; // 0 1 2 3
int dy[4] = { -1, 0, 1, 0 }; // �ϵ�����

// functions
void init() { // �ʱ�ȭ
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

bool connect(CORE core, int d) { // d �������� core ����. ����� return true
    int cy = core.y + dy[d];
    int cx = core.x + dx[d];

    // �ϴ� �Ǵ������� Ȯ��
    while (cx >= 0 && cx < N && cy >= 0 && cy < N) { // �����ڸ����� Ȯ��
        if (board[cy][cx]) return false; // core �Ǵ� line ������ return false
        cy += dy[d];
        cx += dx[d];
    }

    cy = core.y + dy[d];
    cx = core.x + dx[d];
    // ���� ������ ���
    while (cx >= 0 && cx < N && cy >= 0 && cy < N) { // board�� �� ����
        line++;
        board[cy][cx] = 1;
        cy += dy[d];
        cx += dx[d];
    }

    return true;
}

void disconnect(CORE core, int d) { // d �������� ����� �� ����
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
    if (skip > min_skip) return; // �̹� �����غ� core ������ ���� �� return

    if (idx == cores.size()) { // ������ ���� ��
        //debug_print();
        if (min_skip > skip) { // �� ���� core �������� ��
            min_skip = skip;
            min_line = line;
        } else if (min_skip == skip && min_line > line) min_line = line; // �ھ� ���� ������ line�� ���� ��

        return;
    }

    // 4���� ����
    for (int d = 0; d < 4; d++) {
        if (connect(cores[idx], d)) {
            dfs(idx+1);
            disconnect(cores[idx], d);
        }
    }

    // ���� X
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
            if (arr[i][j] && i > 0 && i < N-1 && j > 0 && j < N-1) { // ���� core�鸸 ����
                cores.push_back({ i, j });
            }
        }

        dfs(0); // 0�� index core���� ����

        cout << '#' << test_case << ' ' << min_line << '\n';
    }
    return 0;
}