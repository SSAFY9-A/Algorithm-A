/*
지역구 나누기
마을 N개
지역구 A, B 2개
조건 1. 지역구 A, B에 포함된 유권자 수 차이의 최솟값
	 2. 같은 지역구는 연결되어 있어야함
완전탐색 : 마을 지역구 A, 지역구 B
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace  std;
int N, Pi[8];
int adj[8][8];
int MIN;//유권자수 차이 최솟값
vector<int>region[2];//지역구 A 0 지역구 B1
int parent[8];
int Find(int a)
{
	if (parent[a] == a)
		return a;
	return parent[a] = Find(parent[a]);
}
void Union(int a, int b)
{
	int pa = Find(a);
	int pb = Find(b);
	if (pa == pb) return;
	if (pa <= pb)
		parent[pb] = pa;
	else parent[pa] = pb;
}
void sv(int level,int a, int b)
{
	if (level == N)
	{
		//검증
		for (int t = 0; t < 2; t++)
		{
			if (region[t].size() == 1) continue;
			for (int q = 0; q < 8; q++)
				parent[q] = q;
			for (int y = 0; y < region[t].size(); y++)
			{
				for (int x =0;x<region[t].size(); x++)
				{
					if (adj[region[t][y]][region[t][x]] == 1)
					{
						Union(region[t][y], region[t][x]);
					}
				}
			}
			for (int y = 0; y < region[t].size(); y++)
			{
				if (Find(region[t][y]) != Find(region[t][0]))
					return;
			}
		}
		if (MIN > abs(a - b))
			MIN = abs(a - b);
		return;
	}

	for (int t = 0; t < 2; t++)
	{

		//지역구 추가
		region[t].push_back(level);
		if (t == 0) sv(level + 1, a + Pi[level], b);
		else if (t == 1)sv(level + 1, a , b + Pi[level]);	
		region[t].pop_back();
		

	}
}
int main(void)
{
	int T,i;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		MIN = 21e8;
		region[0].clear();
		region[1].clear();
		cin >> N;
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
			{
				cin >> i;
				adj[y][x] = i;
			}
		for (int t = 0; t < N; t++)
		{
			cin >> i;
			Pi[t] = i;
		}
		
		sv(0,0,0);
		cout << '#' << tc << ' ' << MIN << '\n';
	}
}
