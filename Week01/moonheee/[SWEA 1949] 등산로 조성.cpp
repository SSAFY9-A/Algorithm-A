#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int map[8][8]; // input의 map
int max_hight; // 시작점의 높이 = 가장 높은 높이
vector<pair<int, int>> node; // 시작점 = 가장 높은 좌표들

int max_line; // 현재 가장 긴 등산로 길이
int line; // 현재 등산로 길이
int dat_k; // 현재 공사 유무
int dat[8][8]; // 현재 지나온 등산로 유무

int K; // 등산로 깊이
int N; // 맵 크기
int direct[4][2] =
{
	1, 0, // 하
	-1, 0, // 상
	0, 1, // 우
	0, -1 // 좌
};

// 현재 위치에서 다음으로 갈 y, x 고르기
void dfs(int y, int x)
{
	// 아무것도 고르지 못했다면 max와 비교하기
	int flag = 1;
	for (int idx = 0; idx < 4; idx++)
	{
		int dy = y + direct[idx][0];
		int dx = x + direct[idx][1];

		// map을 벗어나는 좌표는 탐색하지 않는다.
		if (dy >= 0 && dx >= 0 && dy < N && dx < N
			&& dat[dy][dx] == 0)
		{
			// 다음 좌표의 높이가 낮은 경우 탐색
			if (map[dy][dx] < map[y][x])
			{
				dat[dy][dx] = 1;
				line++;
				dfs(dy, dx);
				flag = 0;
				dat[dy][dx] = 0;
				line--;
			}
			// 다음 좌표의 높이가 같거나 높을 때 탐색
			// 한번만 깎기
			// 다음 map이 높을 때만 사용하기
			// K 깊이로 깎을 수 있는지 확인하기
			else if (map[dy][dx] >= map[y][x] && dat_k && map[dy][dx] - K < map[y][x])
			{
				dat[dy][dx] = 1;
				line++;
				// 최소한의 높이로 갂기
				int diff = map[dy][dx] - map[y][x] + 1;
				map[dy][dx] -= diff;
				dat_k = 0;
				dfs(dy, dx);
				// 복구
				flag = 0;
				dat[dy][dx] = 0;
				map[dy][dx] += diff;
				line--;
				dat_k = 1;
			}
		}
	}
	// 아무것도 고르지 못했다면 max와 비교하기
	if (flag)
	{
		if (line > max_line)
			max_line = line;
	}
	return;
}

int main()
{
	int T;
	cin >> T;
	for (int i_t = 0; i_t < T; i_t++)
	{
		max_hight = 0;
		node.clear();
		cin >> N >> K;
		// map 입력
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
			{
				cin >> map[y][x];
				if (map[y][x] > max_hight)
					max_hight = map[y][x];
			}
		// 시작점 셋팅
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				if (map[y][x] == max_hight)
					node.push_back(make_pair(y, x));

		// 시작점 만큼 반복
		int size = node.size();
		max_line = -1;
		for (int i_s = 0; i_s < size; i_s++)
		{
			line = 1;
			dat_k = 1;
			memset(dat, 0, sizeof(dat));
			dat[node[i_s].first][node[i_s].second] = 1;
			dfs(node[i_s].first, node[i_s].second);
		}
		cout << "#" << i_t + 1 << " " << max_line << "\n";
	}
	return 0;
}
