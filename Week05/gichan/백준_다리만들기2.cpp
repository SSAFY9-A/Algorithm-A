// 2023-03-04
// 시작 : 16:37
// 끝 : 18:32

// [전략]
/*
	1. 일단 다리를 다 연결 해봐야하고

	2. 모든 섬이 연결되면그 최소 수를 구해야한다.

	3. 각 섬에서 각 섬으로 갈 수 있는 방법의 코스트 값을 찾고

	4. 엣지 정보를 만들어서

	5. 크루스칼을 돌리면 문제가 풀린다.
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class node {
public:
	int y;
	int x;
	node(int _y, int _x) {
		y = _y;
		x = _x;
	}
};

class edge {
public:
	int n1;
	int n2;
	int cost;
	edge(int _n1, int _n2, int _c) {
		n1 = _n1;
		n2 = _n2;
		cost = _c;
	}

	// cost가 작을수록 우선순위가 높다.
	bool operator < (edge a) const {
		if (cost < a.cost)
			return false;
		if (cost > a.cost)
			return true;
		return false;
	}
};


int N, M;
vector<vector<int>> map_original;
int direct[4][2] = {
	{-1, 0},
	{ 1, 0},
	{ 0,-1},
	{ 0, 1}
};

int parent[7] = { 0, }; // 최대 섬 개수
int MIN_cost = 0;

void input()
{
	cin >> N >> M;
	map_original = vector<vector<int>>(N, vector<int>(M,0));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> map_original[i][j];
		}
	}

	for (int i = 0; i < 7; ++i) {
		parent[i] = i;
	}
}

bool goodToGo(int y, int x, vector<vector<int>>& map, vector<vector<node>>& coast_list, int &id)
{
	// 맵의 범위 내이고
	// map_original의 "땅" 이고
	// map에서 방문한적 없어어야 한다.
	if (y >= 0 && y < N && x >= 0 && x < M) {

		if (map_original[y][x] == 1) {
			if (map[y][x] == 0) {
				return true;
			}
		}
		else { // 맵 안인데 해안가이다?
			coast_list[id - 1].push_back(node(y,x));
		}

	}
	return false;
}

void bfs(node start, vector<vector<int>>& map, int& id, vector<vector<node>>& coast_list)
{
	queue<node> q;
	q.push(start);

	map[start.y][start.x] = id;// map이 방문 표시 배열일것임.

	while (!q.empty()) {
		node now = q.front();
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int dy = now.y + direct[i][0];
			int dx = now.x + direct[i][1];
			
			// 방문한적 없으면서
			// 섬이면서
			// 내가 안가본 곳잉냐?
			if (goodToGo(dy, dx, map, coast_list, id)) {
				map[dy][dx] = id;// 가자
				q.push(node(dy,dx));
			}
		
		}
	}

}

void markAndCountIsland(vector<vector<int>>& map, int& num_of_island, vector<vector<node>>& coast_list)
{
	int id = 1;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			// 섬이 있는데 내가 못찾은 섬이다?
			if (map_original[i][j] == 1 && map[i][j] == 0) {
				coast_list.push_back(vector<node>());
				bfs(node(i,j), map, id, coast_list);
				id++; // 다음섬 아이디 증가

			}
		}
	}
	num_of_island = id-1;
}

bool isMap(int y, int x)
{
	if (y >= 0 && y < N && x >= 0 && x < M)
		return true;
	return false;
}

void pushEdgeIfPossible(int dir, int id, vector<vector<int>>& map, node start, priority_queue<edge>& pq)
{
	int y = start.y;
	int x = start.x;


	int cost = 1;
	while (1) {
		int dy = y + direct[dir][0];
		int dx = x + direct[dir][1];
		
		//cout << dy << ',' << dx << ", " << dir << '\n';
		
		cost++;
		if (isMap(dy, dx)) {
			if (map[dy][dx] != 0) {
				if (map[dy][dx] != id) { // 어떤 섬을 발견했다.
					if (cost-1 > 1) { // 1보다 크면 연결
						
						//cout << id << "섬, 시작위치 : [" << start.y << "," << start.x << "], 끝 위치 : [" << dy << "," << dx << "], 거리:" << cost-1 << '\n';
						// 내 id와 map[dy][dx]와 cost - 1로 엣지 정보 생성
						edge new_edge(id, map[dy][dx], cost-1);
						pq.push(new_edge);
						return;
					}
					else {
						return;
					}
				}
				else {
					return;
				}
			}
			else if (map[dy][dx] == 0) {
				
				y = dy;
				x = dx;
			}
		}
		else {
			return;
		}
	}
}

void makeEdge(int id, vector<vector<int>>& map, node start, priority_queue<edge>& pq)
{
	// 상하좌우로 가본다
	for (int i = 0; i < 4; ++i) {
		int dy = start.y + direct[i][0];
		int dx = start.x + direct[i][1];
		
		// 가려고 하는곳이 맵 안쪽인가
		if (isMap(dy, dx)) {
			// 내가가려고 하는 방향이 "내섬"이 아닌가
			if (map[dy][dx] != id) {
				// 내가 가려고 하는 방향의 바로"뒤"에 내 "섬이 있는가.
				int ry = start.y - direct[i][0];
				int rx = start.x - direct[i][1];
				if (isMap(ry, rx) == true) {
					if (map[ry][rx] == id) {
						// 그럼 이 지점에서는 i 방향으로 쭈욱 이어 봐도 된다.
						pushEdgeIfPossible(i, id, map, start, pq);
					}
				}


			}
			
		}
	}
}


void findEdge(int id, vector<vector<int>>& map, vector<vector<node>>& coast_list, priority_queue<edge>& pq)
{
	// id-1 인덱스의 coast_list을 보면서 
	// 선을 다 이어보자
	for (int i = 0; i < coast_list[id - 1].size(); ++i) {
		node& coast = coast_list[id - 1][i];

		
		// coast에서 상,하,좌,우로 전부 이어보자
		makeEdge(id, map, coast, pq);

	}


}

int Find(int now)
{
	if (now == parent[now])
		return now;
	return parent[now] = Find(parent[now]);
}

void Union(int P, int C)
{
	int pp = Find(P);
	int cp = Find(C);
	if (pp == cp)
		return;
	parent[cp] = pp;
}

int kruskal(priority_queue<edge>& pq)
{
	int sum = 0;
	while (!pq.empty()) {
		edge now = pq.top();
		pq.pop();

		// 부모같으면 하지말고
		if (Find(now.n1) == Find(now.n2))
			continue;


		sum += now.cost;

		Union(now.n1, now.n2);

	}
	if (sum == 0) {
		return -1;
	}
	else {
		return sum;
	}

}

void solve()
{
	// 1. 일단 섬이 몇개인지 알고 각 섬에 id를 부여 해서 그 id값을 map에 쓴다
	vector<vector<int>> map = vector<vector<int>>(N, vector<int>(M, 0));
	vector<vector<node>> coast_list; //coast_list[index] -> index는 id-1 값임. value로 들어있는 node들은 그 id섬의 해안가.

	int num_of_island = 0;

	markAndCountIsland(map, num_of_island, coast_list);

	
	// 3. 여기까지 오면 map에 각 섬의 id로 전부 표시가 되어있다.
	// 그러면 id 1번부터 "해안가"를 찾아서 전부 "직선"으로 연결해 보면서
	// 다른 id를 가지는 섬으로 갈 수 있는 엣지 정보를 추가
	priority_queue<edge> pq;
	for (int i = 1; i <= num_of_island; ++i) {
		findEdge(i, map, coast_list, pq);
		//break;
		
	}
	
	// 4. 엣지정보가 pq에 들어있으니 이제 크루스칼을 돌리자
	MIN_cost = kruskal(pq);

	// 5. 마지막으로 전부 "연결"이 되었는지를 검사해야한다.
	int prev_p = Find(1);
	for (int i = 2; i <= num_of_island; ++i) {
		if (prev_p != Find(i)) {
			MIN_cost = -1;
		}
	}
}

int main()
{
	// input
	input();

	// solve
	solve();


	// output
	cout << MIN_cost;
	return 0;
}

/*
6 6
1 1 1 0 0 0
1 1 0 1 1 1
0 0 0 0 0 0
1 1 0 0 1 1
1 1 0 0 1 0
0 0 0 0 1 0
*/
