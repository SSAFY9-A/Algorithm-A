#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/*
    1. ���δ� ���� ���� ���츮���� ����
    2. ���δ� ������ �ö� �� �ֵ��� �ݵ�� ���� ���� -> ���� �������� ����/���� �� ����
        --> ���̰� ���� ��, ���� ����, �밢���� ���� X
    3. ���� �� '�� �� ��'�� ���� �ִ� K ���̸�ŭ ���� ��� ����
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
int max_length; // ���� (���� �� ���� ����)

struct PEAK {
    int y, x;
};
vector<PEAK> peaks; // ���� ���� ���츮 ��ǥ ����
int max_peak; // ���� ���� ���츮 ����

int dx[4] = { 0, 1, 0, -1 }; // �ϵ�����
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

void dfs(int level, int y, int x) { // level = ���� ���� ����
    visited[y][x] = true;
    //cout << "[" << level << "] (" << y << ", " << x << ")\n";
    if (max_length < level) max_length = level; // ���� ���� ������Ʈ

    // Ž��
    int cy, cx;
    for (int i = 0; i < 4; i++) { // 4�������� ����
        cy = y + dy[i];
        cx = x + dx[i];
        if (isInRange(cy, cx) && !visited[cy][cx]) { // ���� ������ �湮���� �ʾҴٸ�
            if (!cut && arr[cy][cx] >= arr[y][x] && arr[cy][cx] - K < arr[y][x]) { // ���� �ȱ�Ұ�, ���������鼭, ��Ƽ� ������ �� ������
                //cout << "(" << cy << ", " << cx << ") cut\n";
                cut = true;
                int origin = arr[cy][cx]; // ���� ���� ����
                arr[cy][cx] = arr[y][x] - 1; // ���� ��ġ���� 1����
                dfs(level + 1, cy, cx);
                arr[cy][cx] = origin; // ���� ���̷� ����
                cut = false;
            }
            else if (arr[cy][cx] < arr[y][x]) { // ���� ���̺��� ���� ��
                dfs(level + 1, cy, cx); // �� ��ô
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
            if (arr[i][j] > max_peak) { // ���� ���� ���츮 ������Ʈ
                peaks.clear();  // ���츮 vector �ʱ�ȭ
                max_peak = arr[i][j];
            }
            if (arr[i][j] == max_peak) { // ���� ���� ���츮 ��ǥ ����
                peaks.push_back({ i, j });
            }
        }

        for (int i = 0; i < peaks.size(); i++) { // ��� ���� ���� ���츮���� ����
            dfs(1, peaks[i].y, peaks[i].x);
        }

        cout << '#' << test_case << ' ' << max_length << '\n';
    }

    return 0;
}