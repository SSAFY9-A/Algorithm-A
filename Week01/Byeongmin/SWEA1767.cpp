#include<iostream>
#include<cstring>
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

// variables
bool arr[MAX_N][MAX_N];
bool board[MAX_N][MAX_N]; // 실제로 연결 시켜볼 cell 판
int N, num_core;
int max_connection, connection, skip; // 연결된 core 수
int line, min_line; // 사용된 전선의 길이

int dx[4] = {0, 1, 0, -1}; // 0 1 2 3
int dy[4] = {-1, 0, 1, 0}; // 북동남서

// functions
void init() { // 초기화
    memset(arr, 0, sizeof(arr));
    memset(board, 0, sizeof(board));
    max_connection = 0;
    connection = 0;
    skip = 0;
    min_line = MAX_N*MAX_N;
    line= 0;
}

bool connect(int y, int x, int d) { // [3] d 방향으로 core 연결. 연결시 return true
    int cy = y;
    int cx = x;

    // 일단 되는지부터 확인
    while(cx >= 0 && cx < N && cy >= 0 && cy < N) { // 가장자리까지 확인
        cy += dy[d];
        cx += dx[d];
        if(board[cy][cx]) return false; // core 또는 line 있으면 return false
    }

    // 연결 가능한 경우
    while(cx >= 0 && cx < N && cy >= 0 && cy < N) { // board에 선 연결
        line++;
        board[cy][cx] = 1;
        cy += dy[d];
        cx += dx[d];
    }

    return true;
}

void disconnect(int y, int x, int d) { // d 방향으로 연결된 선 삭제
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
    if(y == N-2 && x == N-2) { // 끝까지 오면
        if(max_connection < connection) {
            max_connection = connection;
            min_line = line;
        } else if(max_connection == connection && min_line > line) min_line = line;
        return;
    }

    for(int j=x+1;j<N-1;j++) { // [2] 이전 core 다음 부터 시작 (같은 행에서)
        // 4 방향으로 선 연결
        for(int d=0;d<4;d++) {
            if(connect(y, j, d)) { // 연결 되면 선 연결
                connection++;
                dfs(y, j); // 다음 core로 넘어감
                disconnect(y, j, d); // 선 제거
                connection--;
            }
        }

        // 연결 X
    }

    for(int i=y+1;i<N-1;i++) for(int j=1;j<N-1;j++) { // [2] 다음 행부터 1번 열부터
        // 4 방향으로 선 연결

        // 연결 X
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

        dfs(1, 0); // [1] (1, 1)부터 가장자리를 제외한 모든 core에서 4방향 connect 시도

        cout << '#' << test_case << ' ' << min_line << '\n';
	}
	return 0;
}