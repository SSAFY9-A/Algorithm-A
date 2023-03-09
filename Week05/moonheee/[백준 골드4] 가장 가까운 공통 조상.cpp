#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

int V;
int dp[10001][20];
int A, B;

void init()
{
	memset(dp, 0, sizeof(dp));
	int E;
	cin >> V;
	E = V - 1;
	int parent, child;
	for (int i_e = 0; i_e < E; i_e++)
	{
		cin >> parent >> child;
		dp[child][0] = parent;
	}
	cin >> A >> B;
	// dp 채우기
	for (int j = 1; j < 20; j++)
		for (int i = 1; i <= V; i++)
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
	return;
}

int get_d(int node)
{
	int cur = node;
	int result = 0;

	while (dp[cur][0] != 0)
	{
		int d = 0;
		while (dp[cur][d + 1] != 0)
			d++;
		result += pow(2, d);
		cur = dp[cur][d];
	}
	return result;
}

int sol()
{
	// 1. 높이를 맞춰줍니다.
	int da = get_d(A);
	int db = get_d(B);
	if (db > da)
	{
		swap(A, B);
		swap(da, db);
	}
	int dif = da - db;
	while (dif-- > 0)
		A = dp[A][0];
	if (A == B)
		return A;
	// 2. 공통 조상 찾습니다.
	while (dp[A][0] != dp[B][0])
	{
		int i = -1;
		while (dp[A][i + 1] != dp[B][i + 1])
			i++;
		A = dp[A][i];
		B = dp[B][i];
	}
	return dp[A][0];
}

int main()
{
	int T;
	cin >> T;
	for (int i_t = 0; i_t < T; i_t++)
	{
		init();
		cout << "#" << i_t + 1 << " " << sol() << "\n";
	}
	return 0;
}