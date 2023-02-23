#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
// dfs로 조합 본다. level은 모든 사람이고, branch는 1번계단 2번계단
// vector를 stair1, stair2 를 만들고 각각 넣어준다 해당하는 계단에
// 계단 위치를 먼저 구하고 모든 사람의 stair1 그리고 stair2 과 거리를
// person struct에 넣어준다.
// dfs 마지막에서 두 stair vector를 정렬하고 두 벡터를 각각
// queue pool에 담아서 확인... pool이 3이되면 비교.. 이런식으로
// 각 사람이 다 내려갈때까지 걸리는 시간중 max값을 구하고
// 끝날때 다른 조합에서의 최솟값과 비교하여 업데이트 해준다.
struct Stair
{
    int y, x;
    int length;
};
struct Person
{
    int toStair1;
    int toStair2;
};
vector<Stair> stairs;
vector<Person> p;
vector<Person> stair[2]; // 계단 1,2을 선택한사람

int person[10];        // vector로 계단을 선택해나가면 거리에 따라서
// 정렬을 해버리면 원래 순서랑 달라져버리니 dfs 조합을 못짬 따라서 배열생성
int N;
int Size; // 총 몇명?
int ans;
int map[10][10]; // 입력받기용
bool cmp1(Person o1, Person o2) { return o1.toStair1 < o2.toStair1; }
bool cmp2(Person o1, Person o2) { return o1.toStair2 < o2.toStair2; }
void dfs(int now)
{
    if (now == p.size())
    { // 모든 사람 조합 확인
        stair[0].clear();
        stair[1].clear();
        for (int i = 0; i < Size; i++)
        { // 각 사람들의 계단 선택에따라 vector 분배 -> 거리에 따른 정렬 위함
            if (person[i] == 1)
                stair[0].push_back(p[i]);
            else
                stair[1].push_back(p[i]);
        }
        sort(stair[0].begin(), stair[0].end(), cmp1);
        sort(stair[1].begin(), stair[1].end(), cmp2);
        // stair1 선택한 사람부터
        int Max = 0; //현재조합에서 가장 Max;
        for (int s = 0; s < 2; s++)
        {
            int dit; //계단까지 거리
            int len = stairs[s].length;
            queue<int> pool; // 3명까지 수용가능
            for (int i = 0; i < stair[s].size(); i++)
            {
                if (s == 0) dit = stair[s][i].toStair1;
                else dit = stair[s][i].toStair2;
                int ret;
                int Time = dit + len+1; //거리 +계단 길이 -> 아직 못나온상태 +1을 해줘야 나온다

                if (pool.size() >= 3)
                {
                    int e = pool.front();
                    pool.pop();
                    if (Time - e < len) // 계단길이보다 작은 시간 차이라면
                        ret = e + len;
                    else
                        ret = Time;
                }
                else
                    ret = Time;
                if (ret >= ans) // 정답보다 큰 경우가 있을경우는 의미없음
                    return;
                if (ret > Max) // 이번 조합에서의 Max
                    Max = ret;
                pool.push(ret);
            }
        }
        if (Max < ans)
            ans = Max;
        return;
    }
    person[now] = 1; // 1번계단
    dfs(now + 1);
    person[now] = 2; // 2번 계단
    dfs(now + 1);
}
int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        cin >> N;
        p.clear();
        stairs.clear();
        ans = 21e8;
        Size = 0;
        for (int y = 0; y < N; y++)
        {
            for (int x = 0; x < N; x++)
            {
                cin >> map[y][x];
                if (map[y][x] > 1)
                {
                    stairs.push_back({ y, x, map[y][x] });
                }
            }
        }
        for (int y = 0; y < N; y++)
        {
            for (int x = 0; x < N; x++)
            {
                if (map[y][x] == 1)
                {
                    Size++;
                    int to1 = abs(y - stairs[0].y) + abs(x - stairs[0].x);
                    int to2 = abs(y - stairs[1].y) + abs(x - stairs[1].x);
                    p.push_back({ to1, to2 });
                }
            }
        }
        dfs(0);
        cout << '#'<<t+1<<' '<<ans<<'\n';
    }
    return 0;
}
