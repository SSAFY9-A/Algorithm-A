/*
N*N 정사각형, P 사람들, S 계단 입구, 이동완료시간 : 계단 입구 까지 이동 시간 + 계단 내려가는 시간,
계단 입구 이동 시간 = |사람 세로 위치 - 계단 입구 세로 위치| + | 사람 가로위치 - 계단 입구 가로 위치|
계단 내려가는 시간 도착후 1분후 출발, 계딴 위 동시 최대 3명, 3명이 내려가는 중 한명 완전히 내려가기까지대기
K길이 K분 이동 완료 최소 시간을 구하시오
void input(void)
void init(void)
bf 완전탐색 경우의 수 : 몇 번 계단을 이용할 것인가
func1 bf로 사람이 다 계단에 다 도착했을 때 이동완료시간을 구하여 MIN값과 비교하여 갱신하기
계단 이용시간을 쉽게 구하기 위해 투포인터를 사용
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
struct node
{
    int y, x;
};
int N;//맵 크기
int map[10][10];//맵
int MIN; // 이동완료시간 최솟값
vector<node>p;    //사람들 좌표
vector<int>len_s; //계단 길이
vector<node>s; //계단 좌표
vector<vector<int>>arrive_t; // 계단 도착 시간
 
void init(void)
{
    MIN = 21e8;
    p.clear();
    s.clear();
    len_s.clear();
    arrive_t.clear();
    for (int i = 0; i < 2; ++i) {
        arrive_t.push_back(vector<int>());
    }
}
void input(void)
{
    int i;
    cin >> N;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
        {
            cin >> i;
            map[y][x] = i;
            if (i == 1)
                p.push_back({ y,x });
            if (i > 1)
            {
                len_s.push_back(i);
                s.push_back({ y,x});
            }
        }
}
void func1(void)
{
    int t = 0; //계단 이동 시간
    int p = 0; //계단 이동중인 사람들
    //벡터 복사하기
    vector<vector<int>>copy = arrive_t;
    //벡터 오름차순 sort 하기
    sort(copy[0].begin(), copy[0].end(), less<int>());
    sort(copy[1].begin(), copy[1].end(), less<int>());
    // 계단 이동 시간 구하기
    //초기화
 
    int max[3] = { 0, };
    int cnt = 0;
    int time = 0;
    for (int i = 0; i < copy[0].size(); i++)
    {
        //계단 3개 미만
        if (cnt < 3)
        {
            time = copy[0][i] + 1 + len_s[0];
            //저장
            max[cnt] = time;
            cnt++;
            //내림차순 정렬
            sort(max, max + 3, greater<int>());
        }
        else
        {
            time = copy[0][i] + 1;
            // 아직 계단에 3명 있으면
            if (max[2] > time)
            {
                //시작 시간 변경해서 계산
                time = max[2] + len_s[0];
                //max 변경
                max[2] = time;
                sort(max, max + 3, greater<int>());
            }
            else
            {
                time += len_s[0];
                max[2] = time;
                sort(max, max + 3, greater<int>());
            }
        }
    }
    int a = time;
    //초기화
    max[0] = 0;
    max[1] = 0;
    max[2] = 0;
    cnt = 0;
    time = 0;
    for (int i = 0; i < copy[1].size(); i++)
    {
        //계단 3개 미만
        if (cnt < 3)
        {
            time = copy[1][i] + 1 + len_s[1];
            //저장
            max[cnt] = time;
            cnt++;
            //내림차순 정렬
            sort(max, max + 3, greater<int>());
        }
        else
        {
            time = copy[1][i] + 1;
            // 아직 계단에 3명 있으면
            if (max[2] > time)
            {
                //시작 시간 변경해서 계산
                time = max[2] + len_s[1];
                //max 변경
                max[2] = time;
                sort(max, max + 3, greater<int>());
            }
            else
            {
                time += +len_s[1];
                max[2] = time;
                sort(max, max + 3, greater<int>());
            }
        }
    }
    int b = time;
    if (a < b) a = b;
    if (MIN > a)
        MIN = a;
 
}
void bf(int person)
{
    if (person == p.size())
    {
        func1();
        return;
    }
    for (int t = 0; t < 2; t++)
    {
        // 도착 시간
         
        int time = abs(p[person].y - s[t].y) + abs(p[person].x - s[t].x);
        arrive_t[t].push_back(time);
        bf(person + 1);
        arrive_t[t].pop_back();
    }
}
 
 
 
int main(void)
{
    //freopen("input.txt", "r", stdin);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        init();
        input();
        bf(0);
        cout << '#' << tc << ' ' << MIN << '\n';
    }
 
}
