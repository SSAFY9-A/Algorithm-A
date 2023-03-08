#include<iostream>
#include<queue>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
//섬의 개수 6이하.. 맵 10*10
int N, M;
int map[10][10];

int parent[7];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
int via[10][10];
int CNT;

struct node {
	int y, x;
};
struct edge {
	int from;
	int to;
	int dist;
};
vector<edge>v;
bool cmp(edge a, edge b)
{
	return a.dist < b.dist;
}

int Find(int a)
{
	if (a == parent[a]) return a;
	return parent[a] = Find(parent[a]);
}

void Union(int a, int b)
{
	int pa = Find(a);
	int pb = Find(b);
	if (pa == pb) return;
	parent[pb] = pa;
}
int kruskal()
{
	sort(v.begin(), v.end(), cmp);
	int sum = 0;
	int cnt = 0;

	for (int i = 0; i < v.size(); i++)
	{
		edge now = v[i];
		if (Find(now.from) == Find(now.to)) continue;
		sum += now.dist;
		cnt++;
		Union(now.from, now.to);
	}
	//cout << cnt << "," << sum;
	if (cnt == CNT-1) return sum;
	return -1;
	
}
void pushVector(int y, int x, int d)
{
	int value = via[y][x];
	int Max_index = max(N,M);
	int cnt = 0;
	int flag = 0;

	for (int i = 1; i < Max_index; i++)
	{
		int cy = y + dy[d]*i;
		int cx = x + dx[d]*i;
		if (cy < 0 || cx < 0 || cy >= N || cx >= M) break;
		if (via[cy][cx] == value) break;
		if (map[cy][cx] == 0) cnt++;
		if (map[cy][cx] != 0 && via[cy][cx] != value) {
			//길이가 2이상이고, 시작과 도착 value가 달라야함. (섬이 다른 것임)
			if (cnt >=2)
			{
				v.push_back({value, via[cy][cx] ,cnt });
			}
			break;
		}
	}
	return;
}
void Bridge()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] == 0)continue;
			for (int d = 0; d < 4; d++)
			{
				pushVector(i, j, d);
			}
		}
	}

}
void ConnectIsland(int y, int x)
{
	queue<node>q;
	q.push({ y,x });
	via[y][x] = CNT;
	while (!q.empty())
	{
		node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int cy = now.y + dy[i];
			int cx = now.x + dx[i];
			if (cx < 0 || cy < 0 || cx >= M || cy >= N) continue;
			if (via[cy][cx] != 0) continue;
			if (map[cy][cx] == 0)continue;
			via[cy][cx] = CNT;
			q.push({ cy,cx });
		}
	}
}
void CountIsland()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] == 1 && via[i][j] == 0)
			{
				CNT++;
				//섬끼리 구분
				ConnectIsland(i, j);

			}
		}
	}
}
void printMap()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cout << via[i][j] << " ";
		cout << endl;
	}

}
int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];

	//일단 섬 몇개 있는지 확인. 섬의 개수=CNT
	CountIsland();

	//printMap();

	//섬끼리 연결 가능하다면 v vector에 다 넣어줌
	Bridge();

	//MST
	for (int i = 0; i <= CNT; i++)
		parent[i] = i;
	cout<<kruskal();

}
