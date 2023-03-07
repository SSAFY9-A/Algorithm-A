// 2023-03-07
// 시작 : 11:12 
// 끝 : 

// [내용]
/*
    혁셈블리 해석
    1. 현재 위치의 명령어를 해석하고
    2. 이동방향에 따라 다음 문자로 이동해야 한다.

    - 초기위치 : 가장 왼쪽 위, 이동방향 오른쪽
    - 명령을 처리하다 보면 이동방향이 상,하,좌,우로 이동
    - 만약 범위를 벗어나면 반대편에 있는 위치로 이동
    - 메모리가 단 하나 있따. 0~15 사이의 정수 하나 저장가능.
    - 처음에는 0이 저장되어 있음.

    * 사용 명령은 문제 표 참고
*/

// [입력]
/*
3        // T : 테스트 케이스
2 6        // R : 맵 세로 크기 , C : 맵 가로 크기
6>--v.    // 맵 정보 -> string 으로 처리하면 될듯
.^--_@
*/

// [출력]
/*
    #1 YES // #tc 가능하면 "YES" 아니면 "NO"
*/

// [전략]
/*
    일단 dfs 써야됨.
    왜냐하면 같은 위치라도 어디방향으로 가는지에 따라 결과가 달라져서
    bfs는 안될듯.

    그냥 시작 위치에서 dfs로 명령대로 쭉 진행.
    기저 조건은 @ 만나면 가능하다! -> dfs 완전 끝.

    backtring -> dat를 사용하면 될듯. 맵 크기와 같도록
    이 때, dat는 각 셀마다 vector로 되어있는데 이 벡터에는
    이 위치를 방문했을 때,방문 방향이 담겨 있다.
    만약 방문 방향이 같으면 더이상 가지 않는다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int direct[4][2] = {
    {-1,0}, // 상
    {1,0},  // 하
    {0,-1}, // 좌
    {0,1}   // 우
};

class History {
public:
    int dir;
    int memory;
    History(int _d, int _m) {
        dir = _d;
        memory = _m;
    }

    bool operator == (History a) const {
        if (dir == a.dir && memory == a.memory)
            return true;
        return false;
    }
};

class Log {
public:
    vector<History> history_list;
    Log() {};
};

class node {
public:
    int y;
    int x;
    int dir;
    int memory;
    node(int _y = 0, int _x = 0, int _d = 3, int _m = 0) {
        y = _y;
        x = _x;
        dir = _d;
        memory = _m;
    }
};

int H, W;
vector<string> cmd_map;
vector<vector<Log>> dat;
node start_pos;
node end_pos;
bool can_end_flag = false;
bool is_there_end_pos = false;

void init()
{
    cmd_map.clear();
    dat.clear();
    can_end_flag = false;
    is_there_end_pos = false;
}

void input()
{
    start_pos = node(0,0,3,0);
    cin >> H >> W;
    dat = vector<vector<Log>>(H, vector<Log>(W));
    cmd_map = vector<string>(H);
    for (int i = 0; i < H; ++i) {
        string buf;
        cin >> buf;
        cmd_map[i] = buf;

        if (is_there_end_pos == false) {
            for (int j = 0; j < W; ++j) {
                if (buf[j] == '@') {
                    end_pos = node(i,j,0,0); // 마지막 위치 기록
                    is_there_end_pos = true;
                    break;
                }
            }
        }
    }
}

void getNextDirProcessCmd(node& now, vector<int>& dir_vec) {
    //int direct[4][2] = {
    //{-1,0}, // 상 0
    //{1,0},  // 하 1
    //{0,-1}, // 좌 2
    //{0,1}   // 우 3
    //};

    if (cmd_map[now.y][now.x] == '<') {    // 왼쪽으로 방향 바꿔
        dir_vec.push_back(2);
    }
    else if (cmd_map[now.y][now.x] == '>') { // 오르쪽으로 방향 바꿔
        dir_vec.push_back(3);
    }
    else if (cmd_map[now.y][now.x] == '^') { // 위쪽 방향
        dir_vec.push_back(0);
    }
    else if (cmd_map[now.y][now.x] == 'v') { // 아래쪽 방향
        dir_vec.push_back(1);
    }
    else if (cmd_map[now.y][now.x] == '_') {
        if (now.memory == 0) { // 오른쪽
            dir_vec.push_back(3);
        }
        else { // 왼쪽
            dir_vec.push_back(2);
        }
    }
    else if (cmd_map[now.y][now.x] == '|') {
        if (now.memory == 0) { // 아래쪽
            dir_vec.push_back(1);
        }
        else { // 위쪽
            dir_vec.push_back(0);
        }
    }
    else if (cmd_map[now.y][now.x] == '?') {
        dir_vec.push_back(0);
        dir_vec.push_back(1);
        dir_vec.push_back(2);
        dir_vec.push_back(3);
    }
    else if (cmd_map[now.y][now.x] == '.') {
        dir_vec.push_back(now.dir); // 현재 방향 유지
    }
    else if (cmd_map[now.y][now.x] == '@') {
        //cout << "도착했다고!\n";
        // 끝
    }
    else if (cmd_map[now.y][now.x] >= '0' && cmd_map[now.y][now.x] <= '9') {
        // 방향 유지 및 메모리에 그 값 저장
        dir_vec.push_back(now.dir);
        now.memory = cmd_map[now.y][now.x] - '0';
    }
    else if (cmd_map[now.y][now.x] == '+') {
        dir_vec.push_back(now.dir);
        int mem_buf = now.memory + 1;
        mem_buf = (mem_buf) % 16;
        now.memory = mem_buf;
    }
    else if (cmd_map[now.y][now.x] == '-') {
        dir_vec.push_back(now.dir);
        int mem_buf = now.memory - 1;
        if (mem_buf < 0)
            mem_buf = 15;
        now.memory = mem_buf;
    }
}

bool isHistory(node now, int dir)
{
    History me = History(dir, now.memory);
    for (int i = 0; i < dat[now.y][now.x].history_list.size(); ++i) {
        if (me == dat[now.y][now.x].history_list[i]) {
            return true;
        }
    }
    return false;
}

void inMap(int& y, int& x)
{
    if (y < 0)
        y = H - 1;
    else if (y >= H)
        y = 0;

    if (x < 0)
        x = W - 1;
    else if (x >= W)
        x = 0;
}

void recur(node now)
{
    if (can_end_flag == true)
        return;

    //cout << now.memory << "\n";
    if (cmd_map[now.y][now.x] == '@') {
        can_end_flag = true;
        return;
    }

    // 여길 지나오면 now에 방향, 메모리값 등이 변경되있고
    // 이제 설정된 방향대로 나아가면 됨.
    vector<int> dir_vec;
    getNextDirProcessCmd(now, dir_vec);

    int de = 1;

    for (int i = 0; i < dir_vec.size(); ++i) {
        int dir = dir_vec[i]; // 다음 방향

        int dy = now.y + direct[dir][0];
        int dx = now.x + direct[dir][1];

        // 내 현재 위치에서 "dir" 방향으로 memory 값을 가지고 갈건데
        // 혹시 dat에 이미 그렇게 간 기록이 있따? 그럼 컨티뉴
        if (isHistory(now, dir))
            continue;

            // 처음 그 메모리값, 방향을 가지고 왔으면 일단 "현재 위치"에 방향과 메모리 값을 추가
        dat[now.y][now.x].history_list.push_back(History(dir, now.memory));


        // 이제 갈 방향의 위치를 보쟈 범위를 벗어났으면 반대로 돌려야되니깐
        inMap(dy, dx); // -> 이 함수를 통과하면 자동으로 값이 잘 설정되어있다.

        // 이제 그 방향으로 가자
        node next(dy, dx, dir, now.memory);
        recur(next);
    }





    // dat에는 현재 위치에서 내가 "간" 방향이 저장
    // 지금도 now가 "갈" 방향이랑 dat를 비교해야됨.
    // "도착"한 방향을 중요하지 않다.

    // 나의 위치에서 방향 바꿔야하면
    // 방향 바꾸고

    // 혹시 바꾼 방향이 dat에 있는 방향과 같으면 주의! 위치는 "현재"위치이다.
    // 혹시 바꾼 방향이 dat에 있는 "메모리" 값과 같으면!
    // 리턴

    // 가자

    // 방향 그대로? -> 명령내용 처리하고 그대로 전진.
    // 그 방향으로 갈 위치.






}

bool canReachable()
{
    bool can_reach = false;


    // 위
    int dy = end_pos.y + direct[0][0];
    int dx = end_pos.x + direct[0][1];
    inMap(dy, dx);
    if (cmd_map[dy][dx] == '>' ||
        cmd_map[dy][dx] == '<' ||
        cmd_map[dy][dx] == '^' ||
        cmd_map[dy][dx] == '_') {
        can_reach = false;
    }
    else {
        return true;
    }



    // 아래
    dy = end_pos.y + direct[1][0];
    dx = end_pos.x + direct[1][1];
    inMap(dy, dx);
    if (cmd_map[dy][dx] == '>' ||
        cmd_map[dy][dx] == '<' ||
        cmd_map[dy][dx] == 'v' ||
        cmd_map[dy][dx] == '_') {
        can_reach = false;
    }
    else {
        return true;
    }


    // 좌
    dy = end_pos.y + direct[2][0];
    dx = end_pos.x + direct[2][1];
    inMap(dy, dx);
    inMap(dy, dx);
    if (cmd_map[dy][dx] == '<' ||
        cmd_map[dy][dx] == '^' ||
        cmd_map[dy][dx] == 'v' ||
        cmd_map[dy][dx] == '|') {
        can_reach = false;
    }
    else {
        return true;
    }

    // 우
    dy = end_pos.y + direct[3][0];
    dx = end_pos.x + direct[3][1];
    inMap(dy, dx);
    if (cmd_map[dy][dx] == '>' ||
        cmd_map[dy][dx] == '^' ||
        cmd_map[dy][dx] == 'v' ||
        cmd_map[dy][dx] == '|') {
        can_reach = false;
    }
    else {
        return true;
    }
    return false;
}

void solve()
{
    if (is_there_end_pos == false)
        return;

    if (canReachable() == false)
        return;

    recur(start_pos);
}

int main()
{
    int tc;
    int T;
    //freopen("input.txt", "r", stdin);
    cin >> T;
    //T = 1;
    for (tc = 1; tc <= T; ++tc) {

        // reset
        init();

        // input
        input();

        /*if (tc == 40) {
            for (int i = 0; i < H; ++i) {
                cout << cmd_map[i] << '\n';
            }

            break;
        }*/


        // solve
        solve();

        // output
        if (can_end_flag == true) {
            cout << "#" << tc << " " << "YES\n";
        }
        else {
            cout << "#" << tc << " " << "NO\n";
        }
        
    }

    return 0;
}
