/*
홍 방범 서비스
N*N 도시, 영역의 크기 K, 운영비용 K * K + (K - 1) * (K - 1),
하나의 집이 비용할 수 있는 비용 M, 손해를 안보고 가장 많은 집에 서비스를 제공하는 영역
을 찾고 서비스를 제공 받는 집들의 수를 출력
flood-fill 알고리즘
brute-force 알고리즘
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;
struct node
{
    int y;
    int x;
};
int N, M;
int map[20][20]; // 맵
int cost[42];   //미리 계산해놓은 k값에 따른 비용, index가 k
int num_house;  //집 숫자
int max_house;  //보안회사가 손해 안보고 서비스를 제공할 수 있는 집들의 최댓값

void init(void)
{
    num_house = 0;
    max_house = -21e8;
}

void ff(int y, int x)
{
    queue<node>q;
    q.push({ y,x });
    int visited[20][20] = { 0, };
    visited[y][x] = 1;
    int direct[4][2] = { -1,0,0,-1,0,1,1,0 };
    int cnt = map[y][x];
    if (cnt * M >= cost[1])
    {
        if (max_house < cnt)
            max_house = cnt;
    }
    while (!q.empty())
    {
        node now = q.front();
        q.pop();
        for (int t = 0; t < 4; t++)
        {
            int dy = now.y + direct[t][0];
            int dx = now.x + direct[t][1];
            //범위 체크
            if (dy < 0 || dx < 0 || dy >= N || dx >= N)continue;
            //중복 체크
            if (visited[dy][dx] > 0)continue;
            //집 숫자 세기
            if (map[dy][dx] == 1) cnt++;
            visited[dy][dx] = visited[now.y][now.x] + 1;
            q.push({ dy,dx });


            if (cnt * M >= cost[visited[dy][dx]])
            {
                if (max_house < cnt)
                    max_house = cnt;
            }

            if (num_house * M < cost[visited[dy][dx]])
                return;
        }
    }
    if (cnt * M >= cost[1])
    {
        if (max_house < cnt)
            max_house = cnt;
    }
}

void bf(void)
{
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            ff(y, x);
}

int main(void)
{
    //freopen("input.txt", "r", stdin);
    for (int t = 1; t < 42; t++)
        cost[t] = t * t + (t - 1) * (t - 1);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        cin >> N >> M;
        init();
        for (int y = 0; y < N; y++)
            for (int x = 0; x < N; x++)
            {
                int i;
                cin >> i;
                map[y][x] = i;
                if (i == 1)
                    num_house++;
            }

        bf();
        if (max_house == -21e8)
            cout << '#' << tc << ' ' << 0 << '\n';
        else
            cout << '#' << tc << ' ' << max_house << '\n';
    }
}
