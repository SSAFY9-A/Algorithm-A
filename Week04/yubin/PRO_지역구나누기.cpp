#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;

int N;
int map[8][8];
int parent[8];
int via[8];
int path[8]; //나눈 그룹 확인
int MIN = 21e8;
vector<int>cost;

int Find(int now)
{
    if (now == parent[now]) return now;
    return parent[now] = Find(parent[now]);
}
void Union(int a, int b)
{
    int pa = Find(a);
    int pb = Find(b);
    if (pa == pb) return;
    parent[pb] = pa;
}

//여기만 짜면 될듯!!
int checkAB(vector<int>a)
{
    //Union확인->내일ㄱ
    int sz = a.size();
    for (int i = 0; i < sz - 1; i++)
        for (int j = i + 1; j < sz; j++)
            if (map[a[i]][a[j]] == 1)
            {
                Union(a[i], a[j]);
            }
    int originFind = Find(a[0]);
    for (int i = 0; i < sz; i++)
        if (Find(a[i]) != originFind)
            return 0;
    return 1;
}
int SUM(vector<int>a)
{
    int sz = a.size();
    int s = 0;
    for (int i = 0; i < sz; i++)
        s += cost[a[i]];
    return s;
}
void divAB()
{
    vector<int>A;
    vector<int>B;
    int sumA, sumB;
     
    for (int i = 0; i < N; i++)
    {
        //via로 AB마을 나눔. 
        if (via[i] == 0)
            B.push_back(i);
        else
            A.push_back(i);
    }
   
    if (checkAB(A) * checkAB(B) == 1)
    {
        sumA = SUM(A);
        sumB = SUM(B);
        if (MIN > abs(sumA - sumB))
            MIN = abs(sumA - sumB);
    }
    
    

}

void dfs(int now, int level)
{
    if (now == level)
    {
        for (int i = 0; i < N; i++)
            parent[i] = i;
        divAB();
        return;
    }
    for (int i = 0; i < N; i++)
    {
        if (via[i] == 1) continue;
        if (now > 0 && path[now - 1] >= i) continue;
        via[i] = 1;
        path[now] = i;
        dfs(now + 1, level);
        path[now] = 0;
        via[i] = 0;
    }
}

void start()
{
    for (int i = 1; i <= N / 2; i++)
        dfs(0, i);
}

void init()
{
    MIN = 21e8;
    for (int i = 0; i < N; i++)
        parent[i] = i;
    cost.clear();
    memset(via, 0, sizeof(via));
    memset(path, 0, sizeof(path));
}

int main()
{
    int T;
    int input;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        cin >> N;
        init();
     
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> map[i][j];
        for (int i = 0; i < N; i++)
        {
            cin >> input;
            cost.push_back(input);
        }
        start();
        cout << "#"<<tc<<" "<<MIN<<'\n';
    }
}

