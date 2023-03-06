#include <iostream>
using namespace std;

int min_count;
int map[10][10];
int dat[6];			// 남은 색종이의 개수
int cnt;			// 사용한 색종이 수

void init()
{
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
			cin >> map[y][x];
	for (int i = 1; i <= 5; i++)
		dat[i] = 5;
	min_count = 5 + 5 + 5 + 5 + 6;
	cnt = 0;
	return;
}

int get_max_size(int y, int x)
{
	int max_size = 0;
	for (int k = 0; k < 5; k++)
	{
		// 행 확인
		for (int dx = x; dx <= x + k; dx++)
		{
			if (y + k > 9 || dx > 9)
				return max_size;
			if (map[y + k][dx] != 1)
				return max_size;
		}
		// 열 확인
		for (int dy = y; dy <= y + k; dy++)
		{
			if (x + k > 9 || dy > 9)
				return max_size;
			if (map[dy][x + k] != 1)
				return max_size;
		}
		// 모두 1로 잘 덮혀있다면
		max_size = k + 1;
	}
	return max_size;
}

void set_p(int y, int x, int size)
{
	for (int dy = y; dy < y + size; dy++)
		for (int dx = x; dx < x + size; dx++)
			map[dy][dx] = 0;
	dat[size]--;
	cnt++;
	return;
}

void unset_p(int y, int x, int size)
{
	for (int dy = y; dy < y + size; dy++)
		for (int dx = x; dx < x + size; dx++)
			map[dy][dx] = 1;
	dat[size]++;
	cnt--;
	return;
}

pair<int, int> find_next(int y, int x)
{
	for (int i = y * 10 + x; i < 100; i++)
		if (map[i / 10][i % 10] == 1)
			return make_pair(i / 10, i % 10);
	return make_pair(-1, -1);
}

// y, x좌표에 어떤 색종이를 붙일지 고민하는 함수
void dfs(int y, int x)
{
	// 기저 조건 : 모든 1에 색종이를 덮었을 때
	// 기저 조건 : 더 이상 붙일 색종이가 없을 때
	// 붙일 수 있는 색종이 종류 구하기
	int max_size = get_max_size(y, x);
	for (int size = max_size; size >= 1; size--)
	{
		// size 크기의 색종이가 없다면
		if (dat[size] == 0)
			continue;
		if (cnt > min_count)
			continue;
		// i * i 크기의 색종이를 붙인다.
		set_p(y, x, size);
		// 현재 가까운? 1을 찾아서 이동
		pair<int, int> next = find_next(y, x);
		if (next.first == -1)
		{
			// 모든 1에 색종이가 다 채워졌다
			if (cnt < min_count)
				min_count = cnt;
		}
		else
			dfs(next.first, next.second);
		// 복구
		unset_p(y, x, size);
	}
	// 색종이를 붙일 수 없다면 아래 return으로 종료
	return;
}

void sol()
{
	// 모든 1은 색종이가 붙여져야 합니다.
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
			if (map[y][x] == 1)
			{
				dfs(y, x);
				return;
			}
	// map에 1이 없다면
	min_count = 0;
	return;
}

int main()
{
	init();
	sol();
	// 모든 경우가 붙일 수 없다면
	if (min_count == 5 + 5 + 5 + 5 + 6)
		cout << -1 << "\n";
	else
		cout << min_count << "\n";
	return 0;
}