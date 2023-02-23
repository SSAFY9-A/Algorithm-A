#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;
int N;
int map[10][10];
int stair[2][2];
int path[10];//사람은 10명 이하 
int Min = 21e8;
struct node
{
    int dista;
    int distb;
};
vector<node>v;

int abs(int a, int b)
{
    if (a > b) return a - b;
    return b - a;
}
bool cmp(node left, node right)
{
    return left.dista < right.dista;
}
bool cmpb(node left, node right)
{
    return left.distb < right.distb;
}
void start()
{
    int k = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (map[i][j] > 1)
            {
                stair[k][0] = i;
                stair[k][1] = j;
                k++;
            }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (map[i][j] == 1)
            {
                int numA = abs(i, stair[0][0]) + abs(j, stair[0][1]);
                int numB = abs(i, stair[1][0]) + abs(j, stair[1][1]);
                v.push_back({numA,numB });
            }
        }
    }

}
void calculator()
{
    vector<int> arrA;
    vector<int> arrB;
    vector<node>SortB;
    int check = 0;
    int num;
    int bsz = 0;
    int asz = 0;
    int Amax=0;
    int Bmax = 0;
    int Max = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (path[i] == 0)
        {
            asz = arrA.size();
            num = v[i].dista + map[stair[0][0]][stair[0][1]] + 1;
            if (asz > 2 && arrA[asz - 3] > v[i].dista)
                num = num - v[i].dista + arrA[asz - 3]-1;
             arrA.push_back(num);
             Amax = num;
        }
        else  SortB.push_back(v[i]);

    }
    sort(SortB.begin(), SortB.end(), cmpb);
   //B정렬
    for (int i = 0; i < SortB.size(); i++)
    {
        bsz = arrB.size();
        num = SortB[i].distb + map[stair[1][0]][stair[1][1]] + 1;
        if (bsz > 2 && arrB[bsz - 3] > SortB[i].distb)
            num = num - SortB[i].distb + arrB[bsz - 3]-1;
        //여기서 큰 거 확인해야함. 
        arrB.push_back(num);
        Bmax = num;
    }

    Max = Amax;
    if (Amax < Bmax) Max = Bmax;
   if (Min > Max) Min =Max;

}

//계단에 들어가는 순서,,,
void dfs(int now)
{
    if (now == v.size())
    {
        calculator();
        return;
    }
    path[now] = 0;
    dfs(now + 1);
    path[now] = 1;
    dfs(now + 1);
}

int main()
{
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        cin >> N;
        memset(path, 0, sizeof(path));
        Min = 21e8;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                cin >> map[i][j];

        start();
        sort(v.begin(), v.end(), cmp);

        dfs(0);
        cout << "#" << tc << " "<<Min<<endl;
        v.clear();
    }
}
