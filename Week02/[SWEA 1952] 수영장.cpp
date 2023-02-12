// d1, m1, m3, y1
// 뒤로 갈 수록 금액이 싸지면 좋은데 확정할 수 없다.
// 조합으로 문제를 풀어야 한다.
// d1과 m1을 고르는 문제는 쉽다.
// *m3를 고르는 문제는 모든 배열을 3번 연속으로 묶어서 m3보다 가격이 높으면 바꾼다.
// y1로 고르는 문제는 위의 과정에서 나온 최소 cost가 y1보다 크다면 y1를 고른다.
// *과정에서 m3를 몇 번 골라야 하나? 최대 4번 고를 수 있다. 4번 고르는 경우는 매우 특수한 경우다.
// 약 12!
#include <iostream>
using namespace std;
int d1, m1, m3, y_1;
int plan[15];
int min_cost;
int cost;
int pivot;

// level 달에 어떤 이용권을 사야할까?
void dfs(int level)
{
	if (level >= 12)
	{
		if (cost < min_cost)
			min_cost = cost;
		return;
	}
	// 3달치를 사는 경우
	if (level < 12 &&
		(plan[level] + plan[level + 1] + plan[level + 2] > m3))
	{
		cost += m3;
		dfs(level + 3);
		cost -= m3;
	}
	// 사지 않는 경우
	cost += plan[level];
	dfs(level + 1);
	cost -= plan[level];
	return;
}

int main()
{
	int T;
	cin >> T;
	for (int i_t = 0; i_t < T; i_t++)
	{
		cin >> d1 >> m1 >> m3 >> y_1;
		min_cost = 3000 * 3600;
		// d1, m1
		// m1 / d1 몫보다 커지면 무조건 m1을 구매한다
		cost = 0;
		pivot = m1 / d1;
		for (int i = 0; i < 12; i++)
		{
			cin >> plan[i];
			if (plan[i] > pivot)
				plan[i] = m1;
			else
				plan[i] = d1 * plan[i];
			cost += plan[i];
		}
		if (min_cost < cost)
			min_cost = cost;

		// m3를 사는 경우
		cost = 0;
		dfs(0);

		// y1을 사는 경우
		if (min_cost > y_1)
			min_cost = y_1;
		cout << "#" << i_t + 1 << " " << min_cost << "\n";
	}
	return 0;
}
