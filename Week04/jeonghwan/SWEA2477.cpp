/*
SW 2477 차량 정비소
N개의 접수 창구, M개의 정비 창구, 접수창구 i의 처리시간 ai, 정비창구 j의 처리시간 bj,
방문한 고객 수 K, 고객번호 k의 도착시간 tk,
고객(고객번호, 도착 시간, 사용한 접수 창구, 사용한 정비 창구, 현재 상태)
창구(창구 번호, 처리시간, 받고 있는 고객 번호, 남은 시간);
 
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
struct person
{
    int num;
    int arrive;
    int n1;
    int n2;
};
struct service
{
    int num;
    int cost;
    person p;
    int delay;
    int status;//1이면 일중 0이면 일 안하는 중
};
int N, M, K, A, B;
vector<service> se1;
vector<service> se2;
queue<person>p1;
queue<person>p2;
int cnt;
int p_cnt;
person tmp = { 0,0,0,0 };
void init(void)
{
    se1.clear();
    se2.clear();
    while (!p1.empty()) p1.pop();
    while (!p2.empty()) p2.pop();
    cnt = 0;
    p_cnt = 0;
}
 
void input(void)
{
    int i;
    cin >> N >> M >> K >> A >> B;
    for (int n = 1; n <= N; n++)
    {
        cin >> i;
        se1.push_back({ n,i,tmp,0,0 });
    }
    for (int m = 1; m <= M; m++)
    {
        cin >> i;
        se2.push_back({ m,i,tmp,0,0 });
    }
    for (int k = 1; k <= K; k++)
    {
        cin >> i;
        p1.push({ k, i, 0, 0});
    }
}
 
void check_se1(void)
{
 
    for (int t = 0; t < se1.size(); t++)
    {
        //접수를 다했으므로
        if (se1[t].status == 0)
        {
            if(se1[t].p.num != 0)
            {
                p2.push(se1[t].p);
                se1[t].p.num = 0;
            }
        }
    }
}
void push_se1(void)
{
    for (int t = 0; t < se1.size(); t++)
    {
        if (se1[t].status == 0)
        {
            if (p1.empty()) return;
            person p = p1.front();
            if (p.arrive == 0)
            {
                p.n1 = se1[t].num;
                se1[t].p = p;
                se1[t].delay = se1[t].cost;
                se1[t].status = 1;
                p1.pop();
            }
            else return;
        }
    }
}
void push_se2(void)
{
    for (int t = 0; t < se2.size(); t++)
    {
        if (se2[t].status == 0)
        {
            if (p2.empty()) return;
            person p = p2.front();
            if (p.arrive == 0)
            {
                p.n2 = se2[t].num;
                se2[t].p = p;
                se2[t].delay = se2[t].cost;
                se2[t].status = 1;
                p2.pop();
                if (p.n1 == A && p.n2 == B)
                    cnt+=p.num;
                p_cnt++;
            }
            else return;
        }
    }
}
 
void update(void)
{
    for (int t = 0; t < se1.size(); t++)
    {
        //일 안하면
        if (se1[t].status == 0) continue;
        se1[t].delay--;
        if (se1[t].delay == 0) se1[t].status = 0;
    }
    for (int t = 0; t < se2.size(); t++)
    {
        //일 안하면
        if (se2[t].status == 0) continue;
        se2[t].delay--;
        if (se2[t].delay == 0) se2[t].status = 0;
    }
    for (int t = 0; t < p1.size(); t++)
    {
        person p = p1.front();
        if (p.arrive > 0)
            p.arrive--;
        p1.pop();
        p1.push(p);
    }
}
 
void sv(void)
{
    // 접수 대기, 정비 대기에 한명이라도 사람이 있으면
    while (true)
    {
        if (p_cnt == K)
            return;
        //se1에서 접수 다받은 사람 정비 대기로 이동
        check_se1();
 
        //se1에서 접수 받을 수 있는 만큼 접수 받기
        push_se1();
 
        //se2에서 정비 받을 수 있는 만큼 정비 받기
        push_se2();
 
        //시간 지나기
        update();
    }
    return;
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
        sv();
        if (cnt == 0) cnt = -1;
        cout << '#' << tc << ' ' << cnt << '\n';
    }
}
