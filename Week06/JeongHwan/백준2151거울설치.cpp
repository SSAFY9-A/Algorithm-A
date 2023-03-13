/*
거울 설치
거울의 최소 개수
# 문
. 빈칸

check 배열,들어온 방향
dist 배열m , 들어온 방향
 오히려 비효육적임
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_N 50

struct Node {
	int y, x, dir, cost;
};

int N;
int direct[4][2] = { -1,0,1,0,0,-1,0,1 }; //상하좌우
char map[MAX_N][MAX_N+1];
Node heap[4 * MAX_N * MAX_N];
int h_size = 0;
int sy, sx, ey, ex;
int dist[4][MAX_N][MAX_N];
bool find;


bool cmp(int a, int b)
{
	if (heap[a].cost < heap[b].cost) return true;
	if (heap[b].cost < heap[b].cost) return false;
	return false;
}

void h_push(Node n)
{
	heap[h_size] = n;
	int cur = h_size;
	while (cur > 0 && cmp(cur, (cur - 1) / 2))
	{
		Node tmp = heap[(cur - 1) / 2];
		heap[(cur - 1) / 2] = heap[cur];
		heap[cur] = tmp;
		cur = (cur - 1) / 2;
	}
	h_size++;
}
void h_pop(void)
{
	h_size--;
	heap[0] = heap[h_size];
	int cur = 0;
	while (cur * 2 + 1 < h_size)
	{
		int child;
		if (cur * 2 + 2 == h_size)
		{
			child = cur * 2 + 1;
		}
		else
		{
			child = heap[cur * 2 + 1].cost < heap[cur * 2 + 2].cost ? cur * 2 + 1 : cur * 2 + 2;
		}
		if (cmp(cur, child))
		{
			break;
		}
		Node tmp = heap[cur];
		heap[cur] = heap[child];
		heap[child] = tmp;

		cur = child;
	}
	return;
}

int dijkstra(void)
{
	for(int z=0; z<4; z++)
		for (int y = 0; y < MAX_N; y++)
			for (int x = 0; x < MAX_N; x++)
				dist[z][y][x] = 21e8;
	for (int t = 0; t < 4; t++)
	{
		h_push({ sy, sx, t, 0 });
		dist[t][sy][sx] = 0;
	}
	while (h_size != 0)
	{
		Node now = heap[0]; h_pop();

		if (dist[now.dir][now.y][now.x] < now.cost) continue;

		if (map[now.y][now.x] == '.' || map[now.y][now.x] == '#')
		{
			int dy = now.y + direct[now.dir][0];
			int dx = now.x + direct[now.dir][1];
			if (dy < 0 || dx < 0 || dy >= N || dx >= N)continue;
			if (map[dy][dx] == '*') continue;
			dist[now.dir][dy][dx] = now.cost;
			h_push({ dy,dx,now.dir,now.cost });
		}
		else if (map[now.y][now.x] == '!')
		{
			for (int t = now.dir; t < now.dir + 4; t++)
			{
				
				int u = t % 4;
				if (u + now.dir == 1 || u + now.dir == 5) continue;
				int dy = now.y + direct[u][0];
				int dx = now.x + direct[u][1];
				if (dy < 0 || dx < 0 || dy >= N || dx >= N) continue;
				if (map[dy][dx] == '*')continue;
				int ncost;
				if (u == now.dir) ncost = now.cost;
				else ncost = now.cost + 1;
				if (dist[u][dy][dx] <= ncost) continue;
				dist[u][dy][dx] = ncost;
				h_push({ dy,dx,u,ncost });
			}
		}

	}

	int MIN = 21e8;
	for (int t = 0; t < 4; t++)
	{
		if (MIN > dist[t][ey][ex])
			MIN = dist[t][ey][ex];
	}
	return MIN;
}

int main(void)
{

	scanf("%d", &N);
	for (int y = 0; y < N; y++)
	{
		scanf("%s", &map[y]);
		for(int x=0; x<N; x++)
		{
			if (map[y][x] == '#')
			{
				if (!find)
				{
					sy = y;
					sx = x;
					find = true;
				}
				else
				{
					ey = y;
					ex = x;
				}
			}
		}
	}

	printf("%d", dijkstra());

}
