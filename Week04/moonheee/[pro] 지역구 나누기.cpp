// N - 1번째 마을을 기준으로 같은 편을 먹을지 선택합니다.
// 같은면 1, 다르면 0
#include <iostream>
#include <queue>
using namespace std;

int min_dif;
int N;
int adj[8][8];
int p[8];

int selected;	// bit 6543210
int pp[2];		// 지역구별 인원

void init()
{
	cin >> N;
	min_dif = 21e8;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
			cin >> adj[y][x];
	for (int i_n = 0; i_n < N; i_n++)
		cin >> p[i_n];
	return;
}

// 올바르게 골랐는지 확인
bool is_valid()
{
	// 시작은 N - 1번 노드에서 시작
	// BFS를 돌면서 선택이 안된 노드는 돌지 않기
	queue<int> q;
	q.push(N - 1);
	int visited = 1 << (N - 1);

	while (!q.empty())
	{
		int now = q.front();
		q.pop();
		for (int i_n = 0; i_n < N; i_n++)
		{
			// now와 연결되 노드 찾기
			if (adj[now][i_n] == 0)
				continue;
			if (visited & (1 << i_n))
				continue;
			if ((selected & (1 << i_n)) == 0)
				continue;
			q.push(i_n);
			visited |= (1 << i_n);
		}
	}
	if (visited != (selected + (1 << (N - 1))))
		return false;

	// 다른 쪽 진영도 연결되었는지 확인
	int start;
	for (start = 0; start < 3; start++)
		if ((selected & (1 << start)) == 0)
			break;
	if (start == 3)
		return true;
	q.push(start);
	visited = 1 << start;

	while (!q.empty())
	{
		int now = q.front();
		q.pop();
		for (int i_n = 0; i_n < N; i_n++)
		{
			// now와 연결되 노드 찾기
			if (adj[now][i_n] == 0)
				continue;
			if (visited & (1 << i_n))
				continue;
			if ((selected & (1 << i_n)) != 0)
				continue;
			q.push(i_n);
			visited |= (1 << i_n);
		}
	}
	if (visited != (~selected & ((1 << N) - 1)))
		return false;
	return true;
}

int main()
{
	int T;
	cin >> T;
	for (int i_t = 0; i_t < T; i_t++)
	{
		init();
		// 같은 편이지 고르기
		selected = (1 << (N - 1)) - 2;
		while (selected >= 0)
		{
			pp[0] = 0;
			pp[1] = p[N - 1];
			if (is_valid())
			{
				// 유권자 수 계산
				for (int i_n = 0; i_n < N - 1; i_n++)
				{
					if (selected & (1 << i_n))
						pp[1] += p[i_n];
					else
						pp[0] += p[i_n];
				}
				// 유권자 차이 계산
				if (min_dif > abs(pp[0] - pp[1]))
					min_dif = abs(pp[0] - pp[1]);
			}
			selected--;
		}
		cout << "#" << i_t + 1 << " " << min_dif << "\n";
	}
	return 0;
}
