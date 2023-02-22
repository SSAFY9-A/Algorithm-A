// 2023-02-15
// 시작 : 22:35
// 끝 : 23:15
 
// [내용]
/*
    홈방범 회사가 손해를 보지 않고
    최대 서비스 가능한 집의 수 구하기
*/
 
// [입력]
/*
    10                  // T : 테스트 케이스
    8 3                 // N : 맵크기, M : 하나의 집이 제공 가능 비용
    0 0 0 0 0 1 0 0     // Nxn 맵
    0 1 0 1 0 0 0 1
    0 0 0 0 0 0 0 0
    0 0 0 1 0 1 0 0
    0 0 1 1 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 1 0 1 0
    1 0 0 0 0 0 0 0
*/
 
// [출력]
/*
    #test_case 서비스를 제공 받는 집들 수
*/
 
// [전략]
/*
    집들의 위치에서 각각 BFS를 시작한다
 
    언제까지? 
 
    회사가 손해를 보지 않을 떄 까지
 
    그걸 반복해서 서비스 제공 가능 최대 집수 구한다.
 
     
    위 전략은 틀렸다
    샘플 테스트 케이스 2번 같은 경우에 고장남.
    제일 확실하게는 그냥 모든 노드에서 돌려보는건데
    그 떄 탈출 조건을 운영 비용이 모든 집들이 비용을 다 지불해도
    감당안되면 그냥 탈출하면 됨.
*/
 
 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
 
using namespace std;
 
class node {
public:
    int y;
    int x;
    node(int _y, int _x) : y(_y), x(_x) {}
};
 
/*
N : 맵 크기
M : 집마다 제공 가능한 비용
*/
int N, M;
int map[20][20] = { 0, };
vector<node> client_pos;
int MAX_client_num = 0;
 
void print(int visited[][20])
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << visited[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "================ \n";
}
 
 
void bfs(node start)
{
    queue<node> q;
    q.push(start);
 
    int visited[20][20] = { 0, };
    visited[start.y][start.x] = 1;
 
    int direct[4][2] = {
        {-1, 0},
        { 1, 0},
        { 0,-1},
        { 0, 1}
    };
    // K * K + (K - 1) * (K - 1)
    int K = 1;
    int client_cnt = 0; // 
    int total_payback_cost = client_pos.size();
    // 시작점은 따로 세고 들어가야함
    if (map[start.y][start.x] == 1)
        client_cnt++;
    while (!q.empty()) {
 
        int need_cost = K * K + (K - 1) * (K - 1);
        int payback_cost = client_cnt * M;
 
        // K를 더 넓히면 손해를 본다.
        bool good = false;
        if (need_cost <= payback_cost) {
            good = true;
        }
 
        /*cout << "운영 비용 : " << need_cost << ", 이익 비용 : " << payback_cost << '\n';
        print(visited);*/
         
        // 현재 서비스 제공 받는 고객수가 많으면 업데이트.
        if (MAX_client_num < client_cnt) {
            if (good) {
                MAX_client_num = client_cnt;
            }
        }
 
        // 중간에 탈출 조건
        if (need_cost > total_payback_cost * M) {
            break;
        }
 
        int cursize = q.size();
        for (int i = 0; i < cursize; ++i) {
            node now = q.front();
            q.pop();
 
            for (int i = 0; i < 4; ++i) {
                int dy = now.y + direct[i][0];
                int dx = now.x + direct[i][1];
             
                // 범위 검사
                if (dy >= 0 && dy < N && dx >= 0 && dx < N) {
                    // 방문한적 없고
                    if (visited[dy][dx] == 0) {
                        visited[dy][dx] = 1;
                        if (map[dy][dx] == 1) // 서비스 지역에 고객 있으면 카운팅
                            client_cnt++;
                        q.push(node(dy,dx));
                    }
                }
            }
        }
 
        K++; // 서비스 범위 증가됐다!
    }
     
}
 
void init()
{
    memset(map, 0, sizeof(map));
    client_pos.clear();
    MAX_client_num = 0;
}
 
int main()
{
    int test_case;
    int T;
    //freopen("input.txt", "r", stdin);
    cin >> T;
    //T = 1;
 
    for (test_case = 1; test_case <= T; ++test_case) {
        // reset
        init();
 
        // input
        cin >> N >> M; // 맵크기, 집당 페이백
        for (int i = 0; i < N; ++i) { // 맵 정보
            for (int j = 0; j < N; ++j) {
                cin >> map[i][j];
                if (map[i][j] == 1) {
                    client_pos.push_back(node(i,j));
                }
            }
        }
 
        // solve
        // 각 집들의 위치를 시작점으로 bfs 돌리면서
        // 제공 가능한 최대 집들 수 찾기.
        //cout << client_pos.size() << '\n';
        /*for (int i = 0; i < client_pos.size(); ++i) {
            bfs(client_pos[i]);
        }*/
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                bfs(node(i, j));
            }
        }
 
 
        // output
        cout << "#" << test_case << " " << MAX_client_num << '\n';
         
         
         
    }
 
    return 0;
}
