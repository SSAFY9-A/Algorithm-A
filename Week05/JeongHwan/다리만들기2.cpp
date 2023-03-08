/*
다리 만들기2

헤헤헿 너무 쉽당

MST
섬사이의 다리 최소 길이 구하기

입력 받고
1. 이차원 맵 탐색, 1이면 flood fill 섬 번호 붙이기, 이차원 체크 배열 O(N)
2. 이차원 맵 탐색 후 모든 방향으로 다리 만들어 보기 O(4N)
3. MST(NlogN)

*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
struct Edge {
	int a;
	int b;
	int cost;
};
struct node {
	int y, x;
};

int N, M;
int map[100][100];
int check[100][100];
int direct[4][2] = { -1,0,1,0,0,-1,0,1 };
int cnt_sum;//섬 개수
vector<Edge>v;
int parent[51];

void ff(int sy, int sx)
{
	//섬을 찾았다.
	cnt_sum++;
	check[sy][sx] = cnt_sum;
	queue<node>q;
	q.push({ sy,sx });

	while (!q.empty())
	{
		node now = q.front(); q.pop();
		for (int t = 0; t < 4; t++)
		{
			int dy = now.y + direct[t][0];
			int dx = now.x + direct[t][1];

			if (dy < 0 || dx < 0 || dy >= N || dx >= M) continue;
			if (check[dy][dx] > 0 || map[dy][dx] == 0) continue;

			check[dy][dx] = cnt_sum;
			q.push({ dy,dx });
		}
	}
	return;
}

void getEdge(int sy, int sx)
{
	int a = check[sy][sx];
	int dy;
	int dx;
	int dist;
	for(int t=0; t<4; t++)
	{
		dy = sy;
		dx = sx;
		dist = 0;
		while (true)
		{
			dy += direct[t][0];
			dx += direct[t][1];
			if (dy < 0 || dx < 0 || dy >= N || dx >= M) break;
			if (check[dy][dx] == a) break;
			//다른 섬을 찾았다.
			if (check[dy][dx] != 0)
			{
				//붙어 있거나 한칸 떨어져 있을때
				if (dist <= 1) break;
				v.push_back({ a, check[dy][dx], dist});
				break;
			}
			dist++;
		}
	}
	return;
}

int Find(int a)
{
	if (parent[a] == a) return a;
	return parent[a] = Find(parent[a]);
}

void Union(int a, int b)
{
	int pa = Find(a);
	int pb = Find(b);

	if (pa == pb) return;
	if (pa <= pb) parent[pb] = pa;
	else parent[pa] = pb;
}

bool cmp(Edge left, Edge right)
{
	if (left.cost < right.cost) return true;
	if (left.cost > right.cost) return false;
	return false;
}

int kruskal(void)
{
	//간선 정렬
	sort(v.begin(), v.end(), cmp);
	int cnt_edge = 0;
	int sum = 0; //MST 비용
	for (int t = 0; t < v.size(); t++)
	{
		Edge now = v[t];
		//cycle 만드러지면 제외
		if (Find(now.a) == Find(now.b)) continue;

		Union(now.a, now.b);
		sum += now.cost, cnt_edge++;
	}
	if (cnt_edge == cnt_sum-1) return sum;
	else return -1;
}

int main(void)
{
	//입력
	cin >> N >> M;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < M; x++)
			cin >> map[y][x];

	//탐색 섬 찾기
	for (int y = 0; y < N; y++)
		for (int x = 0; x < M; x++)
		{
			if (check[y][x] == 0 && map[y][x] == 1) ff(y, x);
		}


	//탐색 간선 찾기
	for (int y = 0; y < N; y++)
		for (int x = 0; x < M; x++)
		{
			if (map[y][x] == 1) getEdge(y, x);
		}

	//MST
	for (int y = 1; y < 51; y++)
		parent[y] = y;
	int ans = kruskal();

	cout << ans;
}
