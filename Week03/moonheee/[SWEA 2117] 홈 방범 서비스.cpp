// BFS로 풀어야 겠다.
// 50개 테케 3초 컷 한 케이스당 0.06초
// 집의 개수 최대 N * N
// M이 주어진다.
// K * K + (K - 1) * (K - 1) / M < 집의 개수
// 가능한 집의 최대의 개수 
// K의 최대 값은 전체 집의 개수를 알면 알 수 있다.
// (N * N) * (N) => 400 * 20 = 8000번...
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int max_count; // 손해를 보지 않고 관리할 수 있는 최대 집 개수

int N, M;
int map[20][20];
int visited[20][20];
int home_total = 0;
int avg_y, avg_x;

int h_count; // 기준점으로 시작해서 관리할 수 있는 최대 집 개수

void init()
{
	cin >> N >> M;
	home_total = 0;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
		{
			cin >> map[y][x];
			if (map[y][x])
			{
				avg_y += y;
				avg_x += x;
				home_total++;
			}
		}
	avg_y /= home_total;
	avg_x /= home_total;
	max_count = 0;
}

int cal_cost(int k)
{
	return (k * k) + (k - 1) * (k - 1);
}

void bfs(pair<int, int> start)
{
	queue<pair<int, int>> q;
	q.push(start);
	memset(visited, 0, sizeof(visited));
	visited[start.first][start.second] = 1;
	int direct[4][2] =
	{
		1, 0,
		0, 1,
		-1, 0,
		0, -1
	};
	int day = 0;
	h_count = 0; // 이익외 되는 집의 개수
	int hh_count = map[start.first][start.second]; // 관리하는 집의 개수

	while (!q.empty())
	{
		day++;

		// 회사에 이익이 있다면 집의 개수 업데이트
		int tmp = cal_cost(day);
		if (cal_cost(day) <= hh_count * M && h_count < hh_count)
			h_count = hh_count;
		// 전체 집을 다 찾았다면 그만 찾자.
		if (hh_count >= home_total)
			break;

		int cursize = q.size();
		for (int i = 0; i < cursize; i++)
		{
			pair<int, int> now = q.front();
			q.pop();

			for (int i_d = 0; i_d < 4; i_d++)
			{
				int dy = now.first + direct[i_d][0];
				int dx = now.second + direct[i_d][1];
				if (dy >= 0 && dy < N && dx >= 0 && dx < N && visited[dy][dx] == 0)
				{
					q.push(make_pair(dy, dx));
					if (map[dy][dx])
						hh_count++;
					visited[dy][dx] = 1;
				}
			}
		}
	}
	return;
}

int main()
{
	int T;
	cin >> T;
	for (int i_t = 0; i_t < T; i_t++)
	{
		init();
		// 어디서 시작하면 가장 많이 관리할 수 있을까?
		bfs(make_pair(avg_y, avg_x));
		max_count = h_count;
		if (max_count == home_total)
		{
			cout << "#" << i_t + 1 << " " << max_count << "\n";
			continue;
		}
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
			{
				bfs(make_pair(y, x));
				if (h_count > max_count)
					max_count = h_count;
				if (max_count == home_total)
					break;
			}
		cout << "#" << i_t + 1 << " " << max_count << "\n";
	}
	return 0;
}