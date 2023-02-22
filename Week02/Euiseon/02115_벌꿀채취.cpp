// 입력 : N,M,C ->벌통 크기, 가로로 연속된 벌통 개수, 한 사람이 채취할 수 있는 꿀 최대양
// dfs : level 사람, branch : 벌통좌표
// 각 좌표의 연속된 벌통의 수에서 C를 안 넘는 최대값을 구하고 상품가치 계산하여 다음 레벨로 전달
// 두 사람모두 채취를 했으면 최종 상품가치 Max랑 비교
#include <iostream>
#include <limits.h>
#include <math.h>
using namespace std;
int map[10][10];
int visited[10][10];
int N, M, C;
int Max;

// 해당 벌통 라인에서 가장 많은 수익 구하는 변수
int value;
int valueMax;
int amount; // 꿀의 양

void getValue(int y, int x, int idx)
{ // 벌통 라인에서 가장 큰 가치는?
	if (valueMax < value) {
		valueMax = value;
	}
	if (idx == M) {
		return;
	}

	for (int i = idx; i < M; i++) {
		if (amount + map[y][x + i] > C)
			continue;
		amount += map[y][x + i];
		value += pow(map[y][x + i], 2);
		getValue(y, x, i + 1);
		amount -= map[y][x + i];
		value -= pow(map[y][x + i], 2);
	}
}
int isValid(int y, int x) {
	for (int i = 0; i < M; i++) {
		if (visited[y][x + i] == 1)
			return 0;
	}
	return 1;
}
void dfs(int level, int value)
{
	if (level == 2) {
		if (value > Max)
			Max = value;

		return;
	}

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x <= N - M; x++)
		{
			if (!isValid(y, x)) //현재좌표로부터 M범위까지 visited check
				continue;
			valueMax = 0;
			getValue(y, x, 0);
			for (int i = 0; i < M; i++)
			{
				visited[y][x + i] = 1;
			}
			dfs(level + 1, value + valueMax);
			for (int i = 0; i < M; i++)
			{
				visited[y][x + i] = 0;
			}
		}
	}
}
int main()
{
	int T;
	cin >> T;

	for (int t = 0; t < T; t++)
	{
		cin >> N >> M >> C;
		Max = INT_MIN;
		amount = 0;
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				cin >> map[y][x];
			}
		}
		dfs(0, 0);
		cout << '#' << t + 1 << ' ' << Max << '\n';
	}
}