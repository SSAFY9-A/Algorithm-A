#include<iostream>
#include<cstring>
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

// variables
bool arr[MAX_N][MAX_N];
bool board[MAX_N][MAX_N]; // ������ ���� ���Ѻ� cell ��
int N, num_core;
int max_connection, connection, skip; // ����� core ��
int line, min_line; // ���� ������ ����

int dx[4] = {0, 1, 0, -1}; // 0 1 2 3
int dy[4] = {-1, 0, 1, 0}; // �ϵ�����

// functions
void init() { // �ʱ�ȭ
    memset(arr, 0, sizeof(arr));
    memset(board, 0, sizeof(board));
    max_connection = 0;
    connection = 0;
    skip = 0;
    min_line = MAX_N*MAX_N;
    line= 0;
}

bool connect(int y, int x, int d) { // [3] d �������� core ����. ����� return true
    int cy = y;
    int cx = x;

    // �ϴ� �Ǵ������� Ȯ��
    while(cx >= 0 && cx < N && cy >= 0 && cy < N) { // �����ڸ����� Ȯ��
        cy += dy[d];
        cx += dx[d];
        if(board[cy][cx]) return false; // core �Ǵ� line ������ return false
    }

    // ���� ������ ���
    while(cx >= 0 && cx < N && cy >= 0 && cy < N) { // board�� �� ����
        line++;
        board[cy][cx] = 1;
        cy += dy[d];
        cx += dx[d];
    }

    return true;
}

void disconnect(int y, int x, int d) { // d �������� ����� �� ����
    int cy = y + dy[d];
    int cx = x + dx[d];

    while(cx >= 0 && cx < N && cy >= 0 && cy < N) {
        line--;
        board[cy][cx] = 0;
        cy += dy[d];
        cx += dx[d];
    }
}

void dfs(int y, int x) {
    if(y == N-2 && x == N-2) { // ������ ����
        if(max_connection < connection) {
            max_connection = connection;
            min_line = line;
        } else if(max_connection == connection && min_line > line) min_line = line;
        return;
    }

    for(int j=x+1;j<N-1;j++) { // [2] ���� core ���� ���� ���� (���� �࿡��)
        // 4 �������� �� ����
        for(int d=0;d<4;d++) {
            if(connect(y, j, d)) { // ���� �Ǹ� �� ����
                connection++;
                dfs(y, j); // ���� core�� �Ѿ
                disconnect(y, j, d); // �� ����
                connection--;
            }
        }

        // ���� X
    }

    for(int i=y+1;i<N-1;i++) for(int j=1;j<N-1;j++) { // [2] ���� ����� 1�� ������
        // 4 �������� �� ����

        // ���� X
    }
}

int main(int argc, char** argv)
{
    // test case
	int test_case;
	int T;
	
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case){
        // initialize
        init();

        // input
        cin >> N >> num_core;
        for(int i=0;i<N;i++) for(int j=0;j<N;j++){
            cin >> arr[i][j];
            board[i][j] = arr[i][j];
        }

        dfs(1, 0); // [1] (1, 1)���� �����ڸ��� ������ ��� core���� 4���� connect �õ�

        cout << '#' << test_case << ' ' << min_line << '\n';
	}
	return 0;
}