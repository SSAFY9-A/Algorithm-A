#include <iostream>
#include <vector>
#include <limits>
using namespace std;
int map[12][12]; // 0: 비여있는 공간 / 1: core / 2: 전선
int count_core[13]; // index : 연결된 core 수 / value : core수에 해당되는 최소 전선 길이
int count2; // 현재 노드의 전선의 길이
int min_count; // max core에 연결된 최소 전선 길이 (가지 치기)
int max_core; // 최대 core (가지 치기)
int core; // 현재 연결된 core의 수
int N; // 맵의 가로, 세로
vector<pair<int, int>> v; // dfs의 node
// dfs의 방향 배열
int direct[4][2] =
{
	1, 0, // 아래벽에 연결
	-1, 0, // 위쪽벽에 연결
	0, 1, // 오른쪽벽에 연결
	0, -1 // 왼쪽 벽에 연결
};

// 1. map 초기화
// 2. dfs node 벡터 초기화 (벽에 있는 core는 넣지 않는다)
void input()
{
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
			cin >> map[y][x];
	int flag;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
		{
			if (map[y][x] && y != 0 && x != 0)
			{
				flag = 0;
				for (int idx = 0; idx < 4; idx++)
				{
					int dy = y + direct[idx][0];
					int dx = x + direct[idx][1];
					if (dy >= 0 && dx >= 0 && dy < N && dx < N)
						if (map[dy][dx] != 1)
							flag = 1;
				}
				if (flag)
					v.push_back(make_pair(y, x));
			}
		}
	return;
}

// node(벡터의 now번째)에서 direct_idx가 가리키는 벽으로 연결이 가능한지 체크
// 반환값 0 , 1
int is_valid(int now, int direct_idx)
{
	int dy = v[now].first + direct[direct_idx][0];
	int dx = v[now].second + direct[direct_idx][1];
	while (dy >= 0 && dx >= 0 && dy < N && dx < N)
	{
		// 전선(3)과 node(1)을 만났다면 0 반환
		if (map[dy][dx])
			return 0;
		dy += direct[direct_idx][0];
		dx += direct[direct_idx][1];
	}
	return 1;
}

// node(벡터의 now번째)에서 direct_idx가 가리키는 벽으로 전선 연결
// map에 전선(3)을 채워넣음
int set_map(int now, int direct_idx)
{
	int result = 0;
	int dy = v[now].first + direct[direct_idx][0];
	int dx = v[now].second + direct[direct_idx][1];
	while (dy >= 0 && dx >= 0 && dy < N && dx < N)
	{
		map[dy][dx] = 3;
		result++;
		dy += direct[direct_idx][0];
		dx += direct[direct_idx][1];
	}
	return result;
}

// node(벡터의 now번째)에서 direct_idx가 가리키는 벽으로 전선 해제
// map에 전선이 였던 공간을 0으로 채워넣음
int reset_map(int now, int direct_idx)
{
	int result = 0;
	int dy = v[now].first + direct[direct_idx][0];
	int dx = v[now].second + direct[direct_idx][1];
	while (dy >= 0 && dx >= 0 && dy < N && dx < N)
	{
		map[dy][dx] = 0;
		result++;
		dy += direct[direct_idx][0];
		dx += direct[direct_idx][1];
	}
	return result;
}

void dfs(int now)
{
	// 기저 조건
	if (now >= v.size())
	{
		// 최대 core만큼 찾거나 더 많은 core를 찾았을 때
		if (core >= max_core)
		{
			// 더 많은 core를 찾았을 때
			if (core != max_core)
			{
				// max_core 갱신
				max_core = core;
				// max_core에 연결된 최소 전선 길이 갱신
				min_count = count_core[max_core];
			}
			// 같은 core를 연결하고 더 작은 전선 길이를 찾았을 때
			if (count2 < count_core[core])
			{
				count_core[core] = count2;
				min_count = count2;
			}
		}
		return;
	}

	// 분기점 (4개의 벽방향)
	for (int idx = 0; idx < 4; idx++)
	{
		if (is_valid(now, idx))
		{
			// 전선 연결
			core++;
			count2 += set_map(now, idx);
			// 가지 치기 (이미 전선을 너무 많이 사용한 경우 분기 하지 않음)
			// 밑의 return에서 탐색 종료
			if (count2 < min_count)
				dfs(now + 1);
			// 전선 초기화
			core--;
			count2 -= reset_map(now, idx);
		}
	}
	// core를 전선에 연결하지 않는 분기점
	// 가지 치기 (현재 너무 많은 core가 연결되지 않아서 앞으로 다 연결해도
	// max_core가 되지 않는 경우)
	if (max_core && now - core + 1 < v.size() - max_core)
		dfs(now + 1);
	return;
}

int main()
{
	int T;
	cin >> T;

	for (int i_t = 0; i_t < T; i_t++)
	{
		// 테스트별 초기화
		cin >> N;
		count2 = 0;
		core = 0;
		max_core = 0;
		min_count = numeric_limits<int>::max();
		v.clear();
		for (int idx = 0; idx < 13; idx++)
			count_core[idx] = numeric_limits<int>::max();
		input();
		// 좋은 시작 노드가 있을까?
		dfs(0);
		cout << "#" << i_t + 1 << " " << count_core[max_core] << "\n";
	}
	return 0;
}

// 1차 49/50
// 2차 49/50