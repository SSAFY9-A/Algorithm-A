#include <iostream>
#include <vector>
using namespace std;
int N;
int map[13][13];
int max_core;
int core;
int min_line;
int line;
vector<pair<int, int>> cores;
int direct[4][2] =
{
	-1, 0,
	1, 0,
	0, -1,
	0, 1
};

void init()
{
	cin >> N;
	cores.clear();
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
		{
			cin >> map[y][x];
			if (y != 0 && x != 0 && y != N - 1 && x != N - 1 && map[y][x] == 1)
				cores.push_back(make_pair(y, x));
		}
	max_core = 0;
	core = 0;
	min_line = 50;
	line = 0;
	return;
}

bool is_valid(int d, int y, int x)
{
	int dy = y + direct[d][0];
	int dx = x + direct[d][1];
	while (dy >= 0 && dy < N && dx >= 0 && dx < N)
	{
		if (map[dy][dx])
			return false;
		dy += direct[d][0];
		dx += direct[d][1];
	}
	return true;
}

int set_line(int d, int y, int x)
{
	int line = 0;
	int dy = y + direct[d][0];
	int dx = x + direct[d][1];
	while (dy >= 0 && dy < N && dx >= 0 && dx < N)
	{
		if (map[dy][dx] == 0)
		{
			map[dy][dx] = 3;
			line++;
		}
		dy += direct[d][0];
		dx += direct[d][1];
	}
	return line;
}

int unset_line(int d, int y, int x)
{
	int line = 0;
	int dy = y + direct[d][0];
	int dx = x + direct[d][1];
	while (dy >= 0 && dy < N && dx >= 0 && dx < N)
	{
		if (map[dy][dx] == 3)
		{
			map[dy][dx] = 0;
			line++;
		}
		dy += direct[d][0];
		dx += direct[d][1];
	}
	return line;
}

void dfs(int level)
{
	if (level >= cores.size())
	{
		if (core >= max_core)
		{
			if (core > max_core)
			{
				max_core = core;
				min_line = line;
			}
			if (line < min_line)
				min_line = line;
		}
		return;
	}
	// 상
	if (is_valid(0, cores[level].first, cores[level].second))
	{
		core++;
		line += set_line(0, cores[level].first, cores[level].second);
		dfs(level + 1);
		core--;
		line -= unset_line(0, cores[level].first, cores[level].second);
	}
	// 하
	if (is_valid(1, cores[level].first, cores[level].second))
	{
		core++;
		line += set_line(1, cores[level].first, cores[level].second);
		dfs(level + 1);
		core--;
		line -= unset_line(1, cores[level].first, cores[level].second);
	}
	// 좌
	if (is_valid(2, cores[level].first, cores[level].second))
	{
		core++;
		line += set_line(2, cores[level].first, cores[level].second);
		dfs(level + 1);
		core--;
		line -= unset_line(2, cores[level].first, cores[level].second);
	}
	// 우
	if (is_valid(3, cores[level].first, cores[level].second))
	{
		core++;
		line += set_line(3, cores[level].first, cores[level].second);
		dfs(level + 1);
		core--;
		line -= unset_line(3, cores[level].first, cores[level].second);
	}
	// 연결하지 않는다
	if (level - core < cores.size() - max_core)
		dfs(level + 1);
	return;
}

int main()
{
	int T;
	cin >> T;
	for (int i_t = 0; i_t < T; i_t++)
	{
		init();
		dfs(0);
		cout << "#" << i_t + 1 << " " << min_line << "\n";
	}
	return 0;
}