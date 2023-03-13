// 2023-03-09
// [전략]
/*
	처음에 dfs로 했는데
	시간초과가 난다.

	왜냐 50x50에 문과 거울만 있으면 경우의 수가 엄청 많아진다
	dat로 줄여주려고 해도 잘 안된다 

	왜냐하면 애초에 거울 설치 경우의수가 너무 많기 때문이다.

	bfs로 하고 visited에 [y][x][dir]로 하자
*/

#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class node {
public:
	int y;
	int x;

	node(int _y=-1, int _x=-1) {
		y = _y;
		x = _x;
	}

	bool operator == (node a) const {
		if (y == a.y && x == a.x)
			return true;
		return false;
	}
};

class edge {
public:
	node to;
	int dir;
	int cost;
	edge(node _t, int _d, int _c) {
		to = _t;
		dir = _d;
		cost = _c;
	}

	bool operator < (edge a) const {
		if (cost < a.cost)
			return false;
		if (cost > a.cost)
			return true;
		return false;
	}
};

int direct[4][2] = {
	{-1, 0}, // 상
	{ 0,-1}, // 좌
	{ 1, 0}, // 하
	{ 0, 1}  // 우
};

int N;
vector<string> map;
vector<node> door_pos_list;
node start_pos;
node end_pos;
int MIN_cnt = 21e8;

int visited[50][50][4] = { 0, };
int dist[50][50][4] = { 0, };

void input()
{
	cin >> N;
	for (int i = 0; i < N; ++i) {
		string buf;
		cin >> buf;
		for (int j = 0; j < N; ++j) {
			if (buf[j] == '#') {
				door_pos_list.push_back(node(i,j));
			}
		}
		map.push_back(buf);
	}
}

void dijkstra(node now)
{
	priority_queue<edge> pq;

	// 초기 4방향 넣고
	for (int i = 0; i < 4; ++i) {
		pq.push(edge(node(now.y, now.x), i, 0));
	}

	// 거리 배열
	int MAX = 21e8;
	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 50; ++j) {
			for (int k = 0; k < 4; ++k) {
				dist[i][j][k] = MAX;
			}
		}
	}
	// 거리배열 초기값
	dist[now.y][now.x][0] = 0;
	dist[now.y][now.x][1] = 0;
	dist[now.y][now.x][2] = 0;
	dist[now.y][now.x][3] = 0;
	
	// 우선순위 큐 다 될때까지 돌려보자
	while (!pq.empty()) {
		edge now = pq.top();
		pq.pop();

		// 방문배열 체크
		if (visited[now.to.y][now.to.x][now.dir] == 1)
			continue;
		visited[now.to.y][now.to.x][now.dir] = 1;
		

		// 이제 다음 방향으로 갈거다
		// now.to에 따라 다음 방향이 결정된다
		vector<int> next_dir;
		if (map[now.to.y][now.to.x] == '.') { // 원래 진행 방향으로 그대로 가
			next_dir.push_back(now.dir); // 현재 방향유지
		}
		else if (map[now.to.y][now.to.x] == '!') {
			next_dir.push_back(now.dir); // 원래 방향
			
			int left = now.dir - 1;
			int right = now.dir + 1;

			if (left < 0)
				left = 3;

			right = right % 4;

			next_dir.push_back(left); // 이때는 가중치를 하나 더해줘야함.
			next_dir.push_back(right);
		}
		else if (map[now.to.y][now.to.x] == '#') { // 시작 위치 고려
			next_dir.push_back(now.dir); // 현재 방향유지
		}

		int extra_cost = 0; // 
		for (int i = 0; i < next_dir.size(); ++i) {
			// 거울 안만났으면 0 만났으면 1
			if (i == 0)	
				extra_cost = 0; // 거울 안만난경우고
			else
				extra_cost = 1; // 거울 만난 경우고

			int ndir = next_dir[i];
			int dy = now.to.y + direct[ndir][0];
			int dx = now.to.x + direct[ndir][1];

			// 그럼이제 dy,dx가 다음 갈 곳인데 일단 "갈 수 있는가"를 먼저 확인
			if (dy < 0 || dy >= N || dx < 0 || dx >= N) // 맵 밖이면 끝
				continue;

			// 맵 안이긴 한데 혹시 통과 못하는 벽 *이니?
			if (map[dy][dx] == '*')
				continue;

			// 그 외에는 일단은 다 갈 수 있는 놈들이다.
			// 그럼 이제 거리 배열 보자 이미 더 낮은 값이 써있으면 나와야 한다
			// 나를 통해서 다음으로 갔을 때, 필요한 코스트
			int ncost = dist[now.to.y][now.to.x][now.dir] + extra_cost;

			if (dist[dy][dx][ndir] <= ncost) // 이 경로는 볼 필요없어
			{
				continue;
			}
				

			dist[dy][dx][ndir] = ncost;

			// 이젠 봐야해
			pq.push(edge(node(dy,dx), ndir, ncost));
			
		}
	}

	for (int i = 0; i < 4; ++i) {
		if (MIN_cnt > dist[end_pos.y][end_pos.x][i]) {
			MIN_cnt = dist[end_pos.y][end_pos.x][i];
		}
	}
}

void solve()
{
	start_pos = door_pos_list[0];
	end_pos = door_pos_list[1];
	
	dijkstra(start_pos);
}

int main()
{
	// input
	input();

	// solve
	solve();

	// output
	cout << MIN_cnt;

	return 0;
}
