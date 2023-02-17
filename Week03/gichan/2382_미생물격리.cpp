// 2023-02-17
// 시작 : 23:50
// 끝 : 01/18 01:03
 
// [내용]
/*
    NxN 맵 있어
 
    가장자리에는 약품처리 -> 벽 역할
 
    각 군집 정보는
    y,x(좌표가 0 부터 시작하네) , 미생물 수, 이동방향(상,하,좌,우)
 
    각 군집은 1시간마다 이동방향의 다음셀로 이동.
 
    그러다가 약품 처리된 곳 만나면 미생물 수 반띵나고 방향이 반대로 바뀜
    미생물 수가 홀수인경우 그냥 몫을 취해.
    즉, 1마리 남았을 때, /2 하면 0되고 그 군집 사라짐.
 
    만약 군집들이 합쳐지면 미생물 수 합쳐지고
    방향은 미생물수가 많은 군집의 방향.
 
    M시간동안 미생물 격리
    M시간 이후 남아있는 미생물 "수"의 총합 구해
    주의해 군집수 아니고 그냥 미생물"수" 야
    */
 
// [입력]
/*
    10          // T : 테스트 케이스
    7 2 9       // N : 셀의 개수, M : 격리 시간, K 미생물 군집 갯수
    1 1 7 1     // K개의 미생물 정보가 들어옴
    2 1 7 1     // y,x, 미생물수, 이동방향
    5 1 5 4
    3 2 8 4 
    4 3 14 1
    3 4 3 3 
    1 5 8 2 
    3 5 100 1
    5 5 1 1
*/
 
// [출력]
/*
    #1 145  // #tc 살아남은 미생물수총합
*/
 
// [전략]
/*
    군집 클래스 만들어
    클래스는 각 군집의
    y,x, 미생물수 방향 가지고 있고
    방향은
    // (상: 1, 하 : 2, 좌 : 3, 우 : 4) --> 1씩 뺴서 인덱스호 ㅏ할거임
 
    M번 포문 반복해서 미생물 움직여
    일단 미생물 움직여 놓고
     
    벽에 부딪힌 애들 반으로 줄여서 방향 바꾸기
 
    한 좌표에 모인애들 합치고 방향 바꾸기
     
    순으로 진행.
 
*/
 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
 
using namespace std;
 
int direct[4][2] = {
    {-1, 0},
    { 1, 0},
    { 0,-1},
    { 0, 1}
};
 
class Crowd {
public:
    int y;
    int x;
    int population;
    int y_dir;
    int x_dir;
    Crowd(int _y, int _x, int _p, int _yd, int _xd) {
        y = _y;
        x = _x;
        population = _p;
        y_dir = _yd;
        x_dir = _xd;
    }
 
    bool operator < (Crowd a) const {
        // 작은놈 먼저 나오도록
        // 내가 원하는 상황 폴스로
        if (population < a.population)
            return false;
        if (population > a.population)
            return true;
        return false; // 마지막 무지성 폴스
    }
};
 
// N : 맵크기
// M : 격리시간
// K : 군집 개수
int N, M, K;
 
int map[100][100] = { 0, }; // 겹쳤는지 안겹쳤는지 알기 위해.
vector<Crowd> Crowd_list;
 
 
void moveCrowd()
{
    for (int i = 0; i < Crowd_list.size(); ++i) {
        // 헷갈리니깐 걍 각 변수에 할당해서 하자
        int dy = Crowd_list[i].y + Crowd_list[i].y_dir;
        int dx = Crowd_list[i].x + Crowd_list[i].x_dir;
 
        Crowd_list[i].y = dy;
        Crowd_list[i].x = dx;
 
        // 맵에서 표시 -> 추후 겹친애들 판단하기 위해
        // 즉, map에 있는 숫자가 거기에 있는 군집수
        map[dy][dx]++;
    }
}
 
void boundaryCheck()
{
    for (int i = 0; i < Crowd_list.size(); ++i) {
        int cur_y = Crowd_list[i].y;
        int cur_x = Crowd_list[i].x;
 
        // 가장자리 체크 x,y 좌표중 하나라도 가장자리면 가장자리임
        if (cur_y == 0 || cur_y == N - 1 || cur_x == 0 || cur_x == N - 1) {
            // 미생물 반띵하고
            Crowd_list[i].population = Crowd_list[i].population / 2;
 
            // 방향 반대로 -> 각 오프셋값에 -1 곱하면 반대됨.
            Crowd_list[i].y_dir *= -1;
            Crowd_list[i].x_dir *= -1;
        }
    }
 
    // 죽은애들은 그냥 없애주자
    while (1) {
        bool break_flag = true;
        for (int i = 0; i < Crowd_list.size(); ++i) {
            if (Crowd_list[i].population == 0) {
                Crowd_list.erase(Crowd_list.begin() + i);
                break_flag = false;
                break;
            }
        }
        if (break_flag)
            break;
    }
 
}
 
void findAndMergeCrowd(int y, int x)
{
    priority_queue<Crowd> same_crowds;
    // break_flag가 false인 한
    // 계속 같은 위치 군집 찾느다.
    while (1) {
        bool break_flag = true;
        for (int i = 0; i < Crowd_list.size(); ++i) {
            if (Crowd_list[i].y == y && Crowd_list[i].x == x) {
                same_crowds.push(Crowd_list[i]);
                Crowd_list.erase(Crowd_list.begin() + i); // 지운다.
                break_flag = false;
                break;
            }
        }
        if (break_flag) // 더이상 찾을 놈이 없다 -> 탈출하자.
            break;
    }
 
    Crowd new_crowd(y,x,0,0,0); // 합친놈들 저장할 군집객체
    while (!same_crowds.empty()) {
        Crowd now = same_crowds.top();
        same_crowds.pop();
        new_crowd.population += now.population; // 미생물수 누적해서 더해주고
 
        // 어차피 가장 마지막에 나오는 놈이
        // 가장 큰 인구수를 가졌기때무네
        // 가장 마지막에 업데이트 되면 그게 올바르방향이 됨.
        new_crowd.y_dir = now.y_dir; // 방향 업데이트
        new_crowd.x_dir = now.x_dir;
    }
 
    // 이렇게 만들어진 새로운 군집을 군집리스트에 추가
    Crowd_list.push_back(new_crowd);
}
 
void mergeCrowd()
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (map[i][j] >= 2) { // 이러면 겹친거임.
                findAndMergeCrowd(i,j);
            }
        }
    }
}
 
int getAlivePop()
{
    int sum = 0;
    for (int i = 0; i < Crowd_list.size(); ++i) {
        sum += Crowd_list[i].population;
    }
    return sum;
}
 
void init()
{
    memset(map, 0, sizeof(map));
    Crowd_list.clear();
}
 
int main()
{
    int tc;
    int T;
    //freopen("input.txt","r",stdin);
    cin >> T;
    for (tc = 1; tc <= T; ++tc) {
        // reset
        init();
 
        // input
        cin >> N >> M >> K;
        // 초기 미생물 정보 받기.
        for (int i = 0; i < K; ++i) {
            int y, x, population, dir;
            cin >> y >> x >> population >> dir;
            dir--; // -> dir 배열에서 맞은 방향 인덱스로 만들기 위함.
            Crowd_list.push_back(Crowd(y, x, population, direct[dir][0], direct[dir][1]));
        }
 
        // solve
        for (int i = 0; i < M; ++i) {
            moveCrowd(); // 각 군집들 이동시켜
 
            boundaryCheck(); // 사이드에 있는 애들 수 반띵하고 방향 바꿔
 
            // 겹친애들 합쳐줘
            mergeCrowd();
 
            // 겹치거 체크하는 맵배열 초기화
            memset(map,0,sizeof(map));
        }
        int alive_pop = getAlivePop();
        // output
        cout << "#" << tc << " " << alive_pop << '\n';
    }
    return 0;
}
