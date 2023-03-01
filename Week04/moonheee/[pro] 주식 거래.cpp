#include <iostream>
#include <cstring>
using namespace std;

int cost;
int Ms, Ma;
int N, L;
int arr[15][16];	// 종목의 종류 0 ~ N - 1 / 기간 0 ~ L
int selected[15];		// 주식을 산 개수

int max_cost;

void init()
{
	cin >> Ms >> Ma;
	cin >> N >> L;
	for (int i_n = 0; i_n < N; i_n++)
		for (int i_l = 0; i_l <= L; i_l++)
			cin >> arr[i_n][i_l];
	cost = Ms;
	memset(selected, 0, sizeof(selected));
	return;
}

void dfs(int i_l, int level, int tmp_cost)
{
	if (level >= N)
	{
		int tmp = 0;
		int tmp2 = 0;
		for (int i_n = 0; i_n < N; i_n++)
		{
			tmp += arr[i_n][i_l + 1] * selected[i_n];
			tmp2 += arr[i_n][i_l] * selected[i_n];
		}
		if (max_cost < (cost - tmp2) + tmp)
			max_cost = (cost - tmp2) + tmp;
		return;
	}
	if (arr[level][i_l + 1] - arr[level][i_l] <= 0)
		dfs(i_l, level + 1, tmp_cost);
	else
	{
		int max_branch = tmp_cost / arr[level][i_l];
		for (int i_b = max_branch; i_b >= 0; i_b--)
		{
			selected[level] = i_b;
			dfs(i_l, level + 1, tmp_cost - (arr[level][i_l] * selected[level]));
			selected[level] = 0;
		}
	}
	return;
}

void sol()
{
	// i_l 기간에 사야할 종목 고르기
	for (int i_l = 0; i_l < L; i_l++)
	{
		// 현재 내 투자금을 계산한다 (가지고 있는 현금 + 추가 투자금)
		if (i_l != 0)
			cost += Ma;
		// 초기화
		max_cost = 0;
		dfs(i_l, 0, cost);
		// 그냥 미래가 됬다 치고 이익금을 통장에 집어 넣는다
		if (max_cost > 0)
			cost = max_cost;
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
		sol();
		cout << "#" << i_t + 1 << " " << (cost + Ma)  - (Ms + Ma * L) << "\n";
	}
	return 0;
}