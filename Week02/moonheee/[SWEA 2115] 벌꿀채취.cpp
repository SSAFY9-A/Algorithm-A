// 벌통에 상관없이 꿀을 최대한 많이 딸 수에 가까울 수록 돈을 더 많이 벌 수 있다.
// C에 가까운 수는 무조건 포함시켜야 한다.
// sort는 NlogN을 보장한다. (N * N) => 100log(100)
// 벌통은 항상 N 이하로만 주어진다.
// 꿀의 양을 vector에 넣고 sort 시킨다. (내림차순) 1. 꿀의 양 2. y 3. x
// 안된다. 개별적으로 꿀을 양을 넣는다면 C가 10보다 항상 크기 때문에 연속된 값의 비교가 힘들어진다.
// 그렇다면 연속된 값을 계산해서 넣는다면 어떻게 될까?
// 한 줄(N)을 받고 M을 연속으로 골라서 각각의 제곱해서 더한 뒤 벡터에 넣는다. N - M가지 연산 * N 줄 ( 9 * 10 )
// 이 중에 겹치지 않고 2개를 고르면 되지 않을까?
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int max_cost; // 두 일꾼이 얻을 수 있는 최대 수익
int N, M, C; // 맵, 벌통 수, 최대양

// 자료구조
struct Node
{
	int y;
	int x;
	int cost;

	bool operator < (Node B) const
	{
		if (cost > B.cost)
			return true;
		if (cost < B.cost)
			return false;
		if (y < B.y)
			return true;
		if (y > B.y)
			return false;
		if (x < B.x)
			return true;
		if (x > B.y)
			return false;
		return false;
	}
};
vector<Node> v;

int tmp[10];
int cost_m = 0;
int cost = 0;
int c_sum = 0;
void dfs(int level, int start)
{
	if (level >= start + M)
	{
		if (cost > cost_m)
			cost_m = cost;
		return;
	}
	// 고르는 경우
	if (c_sum + tmp[level] <= C)
	{
		c_sum += tmp[level];
		cost += (tmp[level] * tmp[level]);
		dfs(level + 1, start);
		c_sum -= tmp[level];
		cost -= (tmp[level] * tmp[level]);
	}
	// 안고르는 경우
	dfs(level + 1, start);
	return;
}

void init()
{
	max_cost = 0;
	cin >> N >> M >> C;
	v.clear();
	for (int y = 0; y < N; y++)
	{
		// 한줄 입력받기
		for (int x = 0; x < N; x++)
			cin >> tmp[x];
		// v 채우기
		for (int idx = 0; idx < N - M + 1; idx++)
		{
			// M의 숫자들 중에 C를 넘지 안되 가장 많이 벌 수 있는 수 고르기
			// 꿀통은 idx부터 idx+M까지이다.
			cost_m = 0;
			c_sum = 0;
			dfs(idx, idx);
			v.push_back({ y, idx, cost_m });
		}
	}
	// 꿀벌이 많은 순 우선 / y 낮은 순 / x 낮은 순 (y, x는 겹치는 걸 비교하기 위해서 정렬)
	sort(v.begin(), v.end());
	return;
}

void select_max()
{
	// 2개를 고릅니다. 대신 꿀통이 겹치지 않게 고릅니다.
	// N >= M * 2 이라면 같은 y에서 두개 고를 수 있습니다.
	int choice = 0;
	max_cost = 0;
	if (N >= M * 2)
	{
		int idx = 0;
		Node first = v[idx];
		max_cost += first.cost;
		idx++;
		int size = v.size();
		// 두번째 고르기
		while (idx < size && abs(((first.y * N) + first.x) - ((v[idx].y * N) + v[idx].x)) < M)
			idx++;
		max_cost += v[idx].cost;
	}
	else
	{
		int idx = 0;
		Node first = v[idx];
		max_cost += first.cost;
		idx++;
		int size = v.size();
		// 없지는 않겠짘ㅋㅋ
		// 두번째 고르기
		while (idx < size && first.y == v[idx].y)
			idx++;
		max_cost += v[idx].cost;
	}
	return;
}

int main()
{
	int T;
	cin >> T;

	for (int i_t = 0; i_t < T; i_t++)
	{
		// v정렬 완료
		init();
		select_max();
		cout << "#" << i_t + 1 << " " << max_cost << "\n";
	}
}
