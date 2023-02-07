#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
 
using namespace std;
class node {
public:
    int y;
    int x;
    node(int _y, int _x) : y(_y), x(_x) {}
};
 
vector<vector<int>> map;
int N;
int side_core = 0;
vector<node> cores;
int max_level = 0;
 
int max_connected_core = -1;
int need_line = 21e8;
 
bool isSide(int y, int x)
{
    if (y == 0 || y == N - 1 || x == 0 || x == N - 1) {
        return true;
    }
    return false;
}
 
int direct[4][2] = {
    {-1, 0},
    { 1, 0},
    { 0,-1},
    { 0, 1}
};
 
bool makeConnected(node core, int off_y, int off_x)
{
    int dy = core.y + off_y;
    int dx = core.x + off_x;
    while (1) {
        if (dy >= 0 && dy < N && dx >= 0 && dx < N) {
            if (map[dy][dx] == 0) {
                map[dy][dx] = 2;
                dy += off_y;
                dx += off_x;
            }
            else {
                // 간곳인 연결이 안된다
                return false;
            }
                 
        }
        else {
            return true;
        }
    }
}
 
int getConnectedCoreNum()
{
    int c_cnt = 0;
    // 윗줄
    for (int i = 0; i < N; ++i) {
        if (map[0][i] == 2)
            c_cnt++;
    }
 
    // 가장 윗줄, 아랫줄 제외한 좌/우 줄
    for (int i = 1; i < N - 1; ++i) {
        if (map[i][0] == 2)
            c_cnt++;
        if (map[i][N - 1] == 2)
            c_cnt++;
    }
 
    // 가장 아랫줄
    for (int i = 0; i < N; ++i) {
        if (map[N - 1][i] == 2)
            c_cnt++;
    }
    return c_cnt;
}
 
int getNeedLine()
{
    int n_line = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (map[i][j] == 2)
                n_line++;
        }
    }
    return n_line;
}
 
void recur(int level)
{
    // 현재 연결된 코어수  + 
    if (getConnectedCoreNum() + (cores.size() - level) < max_connected_core && max_connected_core != -1) {
        return;
    }
 
    if (level == max_level) {
        // 연결된 코어 숫자가 더 많으면
        // 연결 코어 수 최대값 업데이트
        // 그 때 필요한 연결 수 업데이트
        int cur_conntected_core = getConnectedCoreNum();
        if (max_connected_core < cur_conntected_core) {
            max_connected_core = cur_conntected_core;
            need_line = getNeedLine();
        }
        else if (max_connected_core == cur_conntected_core) {
            // 만약 현재 연결 코어수와 같으면
            // 필요한 연결 수 선이 적으면 업데이트
            int cur_need_line = getNeedLine();
            if (cur_need_line < need_line)
                need_line = cur_need_line;
        }
        //cout << need_line << '\n';
        return;
    }
 
     
    recur(level + 1);
 
    // 연결 하는 경우
    for (int i = 0; i < 4; ++i) {
        vector<vector<int>> copy_map = map; // 복구를 위한 현재갑 저장. -> 메모리 낭비긴 한데 일단 구현.
        bool isConnected = makeConnected(cores[level], direct[i][0], direct[i][1]); // 표시
        if (isConnected == false) { // 만약에 간곳이 연결 안되고 막혔으면 map 복구하고 backtracking; -> 이게 연결 안하는것까지 처리함.
            map = copy_map;
            continue;
        }
        recur(level + 1);
        map = copy_map; // 복구
    }
 
 
}
 
int main(int argc, char** argv)
{
    int test_case;
    int T;
    /*
    1
    5
    1 1 1 1 1
    1 1 0 0 1
    0 0 0 1 1
    0 0 0 1 1
    1 0 1 1 1
    */
    //freopen("sample_input.txt", "r", stdin);
    cin >> T;
    //T = 3;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        // 0. 입력 받기 
        // N 와 map 정보.
        cin >> N;
        for (int i = 0; i < N; ++i) {
            vector<int> vec;
            for (int j = 0; j < N; ++j) {
                int v;
                cin >> v;
                // 코어노드라면
                if (v == 1) {
                    // 사이드에 있느 애면 미리 셈. 
                    if (isSide(i, j))
                        side_core++;
                    else
                        cores.push_back(node(i, j));
                }
                vec.push_back(v);
            }
            map.push_back(vec);
        }
 
        // cores에는 사이드가 아닌 녀석들만 들어있다
        max_level = cores.size();
        //cout << max_level << '\n';
        recur(0);
 
        cout << "#" << test_case << " " << need_line << '\n';
     
 
        // 초기화
        map.clear();
        side_core = 0;
        cores.clear();
        max_level = 0;
 
        max_connected_core = -1;
        need_line = 21e8;
 
    }
    return 0;
}
