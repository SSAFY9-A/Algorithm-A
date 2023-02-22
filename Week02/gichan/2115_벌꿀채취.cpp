// 2023-02-14
// 시작 : 23:12
// 끝 : 01:07
 
// [내용]
/*
 
    N x N 벌통에서 꿀 채취할거야
    2명의 일꾼이
    M개로 가로로 꿀 채취 가능.
 
    각일꿀당 꿀 채취 전체양이 C를 넘으면 안됨.
*/
 
// [입력]
/*
     
    10          // T : 테스트 케이스
    4 2 13      // N : 벌통의 크기, M : 선택가능벌통수, C : 꿀채취최대양 
    6 1 9 7     // NxN 벌통꿀 정보
    9 8 5 8
    3 4 5 3
    8 2 6 7
*/
 
// [출력]
/*
    #1 174  // #test_case 최대채취량
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
 
/*
    N: 벌통 한 변 길이
    M: 가로로 선택해야하는 벌통 길이
    C: 한 일꾼당 최대 채취 가능 꿀 량
*/
class node {
public:
    int y;
    int x;
    node(int _y, int _x) : y(_y), x(_x) {}
};
 
int N, M, C; 
int map[10][10] = { 0, };
int MAX_profit = 0;
 
vector<node> worker_position;
 
int C_cnt = 0;
int power_sum_out = 0;
void recur(int level, vector<int>& honey, int profit)
{
    if (C_cnt > C)
        return;
 
    if (level == honey.size()) {
        // 여기서 구해봐
        if (profit > power_sum_out) {
            power_sum_out = profit;
        }
             
        return;
    }
 
    // 뽑는다.
    C_cnt += honey[level];
    int next_profit = honey[level] * honey[level];
    recur(level + 1, honey, profit + next_profit);
    C_cnt -= honey[level];
 
    // 안뽑느다.
    recur(level + 1, honey, profit);
}
 
int getProfit(node start)
{
    vector<int> honey;
    int sum = 0;
    for (int x = start.x; x < start.x + M; ++x) {
        sum += map[start.y][x];
        honey.push_back(map[start.y][x]);
    }
 
    // 1. sum이 C보다 작거나 같으면 그냥 전부 제곱해서 더해 가져가
    int power_sum = 0;
    if (sum <= C) {
        for (int i = 0; i < honey.size(); ++i) {
            power_sum += honey[i] * honey[i];
        }
        return power_sum;
    }
    else {
        // 0개 ~ honey.size()개 까지 다 뽑아봐
        power_sum_out = 0;
        //for (int i = 0; i < honey.size(); ++i) {
        //  cout << honey[i] << " ";
        //}
        //cout << '\n';
        recur(0, honey, 0);
        return power_sum_out;
    }
}
 
void r(int level, node start)
{
    if (level == 2) {
        //for (int i = 0; i < worker_position.size(); ++i) {
        //  cout << "일꾼" << i + 1 << " : " << worker_position[i].y << ", " << worker_position[i].x << '\n';
        //}
        //cout << "=============\n";
        //cout << "일꾼1 : " << worker_position[0].y << ", " << worker_position[0].x << '\n';
        int worker1_profit = getProfit(worker_position[0]);
        //cout << "이익 : " << worker1_profit << '\n';
 
        //cout << "일꾼2 : " << worker_position[1].y << ", " << worker_position[1].x << '\n';;
        int worker2_profit = getProfit(worker_position[1]);
        //cout << "이익 : " << worker2_profit << '\n';
        //cout << "=================\n";
         
        if (worker1_profit + worker2_profit > MAX_profit) {
            MAX_profit = worker1_profit + worker2_profit;
        }
         
        return;
    }
 
    int j = start.x; 
    for (int i = start.y; i < N; ++i) {
        while(1) {
 
            // 현재 줄에서 M칸을 선택해서 인덱스 초과가 안나는가
            if (j + M - 1 <= N - 1) { // M 구간 선택 가능!
                worker_position.push_back(node(i,j));
                r(level + 1, node(i, j + M));
                worker_position.pop_back();
            }
            j++;
            if (j > N) {
                j = 0;
                break;
            }
        }
    }
}
 
void init()
{
    memset(map, 0, sizeof(map));
    MAX_profit = 0;
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
        cin >> N >> M >> C;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> map[i][j];
            }
        }
 
        // solve
        r(0, node(0,0));
         
        // output
        cout << "#" << test_case << " " << MAX_profit << '\n';
 
    }
    return 0;
}
