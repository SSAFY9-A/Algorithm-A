/*
[제약 사항]
 
1. 시간 제한 : 최대 50개 테스트 케이스를 모두 통과하는 데 C/C++/Java 모두 3초
 
2. 모든 종류의 이용권 요금은 10 이상 3,000 이하의 정수이다.
 
3. 각 달의 이용 계획은 각 달의 마지막 일자보다 크지 않다.
 
월 1일, 월, 3월 3가지 경우의 수, 1년 
*/
#include <iostream>
using namespace std;
//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)
 
int price[4]; // 1일 이용권, 1달 이용권, 3달 이용권, 1년 이용권 가격
int calender[12]; // 12개월 이용계획
int min_cost; // 1년 수영장 비용 최솟값
int acc_cost; // 1년 수영장 비용 누적값
int next_month[4] = { 1,1,3,12 }; // 이용권당 넘어가야할 다음달
 
void init(void)
{
    for (int x = 0; x < 4; x++)
        cin >> price[x];  // 이용권 가격 입력
    for (int x = 0; x < 12; x++)
        cin >> calender[x];   // 1년 계획 입력
    min_cost = 21e8;
    acc_cost = 0;
}
 
void dfs(int level)
{
    //현재 누적값이 최솟값보다 크면 백트랙킹
    if (acc_cost > min_cost)
        return;
    //level은 개월수 12개월 이면 최솟값 갱신하고 리턴
    if (level >= 12)
    {
        min_cost = acc_cost;
        return;
    }
 
    for (int x = 0; x < 4; x++)
    {
        // 금월 이용계획이 0이면 다음달로
        if (calender[level] == 0)
            dfs(level + 1);
        // 금월 이용계획이 있고 1일만 사용할 경우
        else if( x == 0)
        {
            acc_cost += calender[level] * price[x];
            dfs(level + next_month[x]);
            acc_cost -= calender[level] * price[x];
        }
        // 나머지 경우
        else
        {
            acc_cost += price[x];
            dfs(level + next_month[x]);
            acc_cost -= price[x];
        }
    }
}
 
int main(void)
{
    //freopen("input.txt", "r", stdin);
 
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        init();
        dfs(0);
        cout << '#' << t + 1 << ' ' << min_cost<<'\n';
    }
}
