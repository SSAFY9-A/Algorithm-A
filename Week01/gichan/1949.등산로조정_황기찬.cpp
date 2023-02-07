// 2023-02-06 22:57 
// N 한변의 길이 (3 <= N <= 8)
// K 공사 가능 깊이 K (1 <= K <= 5)
// 지형의 높이 1 ~ 20
// 가장 높은 봉우리는 최대 5개
// K만큼 깍아서 음수로 만들수오 있음.
 
 
// [입력] ===
// 2023-02-06 23:01 ~
// T (테스트 케이스)
// N K
// N*N 지도 정보
/*
10
5 1
9 3 2 3 2
6 3 1 7 5
3 4 8 9 9
2 3 7 7 7
7 6 5 5 8
*/
 
// [출력] ===
// #1 만들 수 있느 ㄴ가장 긴 등산로 길이.
 
 
// 전략
// NxN 맵을 입력 받는다
// 입력 받으면서 N 최대값 찾는다.
// 다리 맵을 돌면서 N 최대값의 y,x 좌표를 vector에 추가한다.
// vector의 요소 를 기준점마다 출발할 때, 최대 길이를 구한다.
 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
 
class node {
public:
    int y;
    int x;
    int k;
    node(int _y, int _x, int _k = 0) : y(_y), x(_x), k(_k) {}
};
 
using namespace std;
vector<vector<int>> map;
vector<node> start_list; // 시작 가능한 최대 높이 지점들 리스트.
vector<node> possible_K_list; // K 값을 적용할 수 있는 위치들 후보.
int N, K, max_H;
int visited[8][8] = { 0, };
int MAX = -21e8;
int cur_cnt = 0;
 
// 상,하,좌,우 방향 배열
int direct[4][2] = {
    {-1, 0},
    { 1, 0},
    { 0,-1},
    { 0, 1}
};
 
void recur(node base)
{
    // 기저 조건 : 딱히 없음. 포문을 뚫고 나가야됨.
    bool end_flag = true;
    for (int i = 0; i < 4; ++i) {
        int dy = base.y + direct[i][0];
        int dx = base.x + direct[i][1];
         
        // 범위 검사
        if (dy >= 0 && dy < N && dx >= 0 && dx < N) {
            // 갈 수 있는지 검사 : (base 보다 값이 작은가)
            if (map[base.y][base.x] > map[dy][dx]) { // 갈수있다.
                // 내가 현재 탐색에서 방문하지 않았던 길이여야함
                // visited 배열 사용
                if (visited[dy][dx] == 0) {
                    end_flag = false; // 이 탐색에서는 현재 막장이 아니니 등산로 더 이어진다.
                    // 이제 그쪽으로 가자!
                    visited[dy][dx] = 1;
                    cur_cnt++;
                    recur(node(dy,dx));
                    visited[dy][dx] = 0;
                    cur_cnt--;
                }
            }
        }
    }
 
    // 끝까지 간 것은 여기서 알 수 있음.
    // 여기서 현재 등산로 길이가 기존 MAX 값 보다 크다면
    // 업데이트 해준다.
    if (cur_cnt > MAX)
        MAX = cur_cnt;
}
 
int isGoodK(int y, int x)
{
    // K는 최대값에도 적용 가능.
    // 내가 주변보다 나랑 같거나 작은 놈들이 있는데
    // K만큼 깎아서 주변 보다 그보다 더 작아질 수 있다면 K 후보로 등록.
    for (int i = 0; i < 4; ++i) {
        int dy = y + direct[i][0];
        int dx = x + direct[i][1];
 
        // 범위 확인
        if (dy >= 0 && dy < N && dx >= 0 && dx < N) {
            // 나보다 작거나 같은 놈들이 있다.
            if (map[y][x] >= map[dy][dx]) {// 무조건 이 상태여야함.
                if (map[y][x] - K < map[dy][dx]) {
                    return map[y][x] - map[dy][dx] + 1; // 즉, K 시작값. [리턴값 ~ K 최대값]
                }
                     
            }
        }
 
    }
    return -1; // K 위치로 부적합.
}
 
void r()
{
    for (int i = 0; i < start_list.size(); ++i) {
        visited[start_list[i].y][start_list[i].x] = 1; // 처음 시작 위치 방문 표시
        cur_cnt++; // 등산로 길이 세기
        recur(start_list[i]);
        visited[start_list[i].y][start_list[i].x] = 0;
        cur_cnt--;
    }
}
void init()
{
    max_H = 0;
    map.clear();
    start_list.clear(); // 시작 가능한 최대 높이 지점들 리스트.
    possible_K_list.clear(); // K 값을 적용할 수 있는 위치들 후보.
    max_H = 0;;
    memset(visited, 0, sizeof(visited));
    MAX = -21e8;
    cur_cnt = 0;
}
void getStartPos()
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (map[i][j] == max_H) { // 최대 높이와 같으면 시작 가능 벡터에 위치정보 추가.
                start_list.push_back(node(i, j));
            }
        }
    }
}
void getMaxH()
{
    max_H = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (map[i][j] > max_H) // 최대값 실시간으로 갱신.
                max_H = map[i][j];
        }
    }
}
 
int main()
{
    int test_case;
    int T;
 
    //freopen("input.txt","r", stdin);
    cin >> T;
    //T = 1;
    for (test_case = 1; test_case <= T; ++test_case) {
         
        // reset
        init();
         
        // input
        cin >> N >> K;
        // map 입력, 동시에 최대 높이 값 찾기
        for (int i = 0; i < N; ++i) {
            vector<int> vec;
            for (int j = 0; j < N; ++j) {
                int v;
                cin >> v;
                vec.push_back(v);
                if (v > max_H) // 최대값 실시간으로 갱신.
                    max_H = v;
            }
            map.push_back(vec);
        }
         
        // start_list 만들기
        getStartPos();
 
        // possible_K_list 만들기
        // K 값을 적용해볼 수 있는 후보 위치 고르기
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int isK = isGoodK(i, j);
                if (isK != -1) { // K 위치로 적합하다.
                    possible_K_list.push_back(node(i,j, isK));
                    //cout << i << ", " << j << " : " << map[i][j] << '\n';
                }
            }
        }
         
         
        // solve
        // K 고려 안하고 한번
        r();
        // K 고려 하고 한번
        // 각 시작 가능 위치마다 dfs를 돌린다.
        vector<vector<int>> map_copy = map;
        for (int i = 0; i < possible_K_list.size(); ++i) {
            int ky = possible_K_list[i].y;
            int kx = possible_K_list[i].x;
            int kstart = possible_K_list[i].k;
            // K 값을 적용할 때, 그대로 하는게 아니라
            // 최대 1 부터 까지 적용 가능
            for (int j = kstart; j <= K; ++j) {
                map[ky][kx] -= j; // K 값 적용
                start_list.clear(); // 이전 시작 위치 제거
                getMaxH();          // 최대 높이를 다시 찾아야돼.
                getStartPos();      // 다시 시작 위치 파악
                cur_cnt = 0;
                r();                // dfs 동작
                map = map_copy;     // 맵 복구
            }
        }
         
        // output
        cout << "#" << test_case << " " << MAX << '\n';
    }
    return 0;
}
