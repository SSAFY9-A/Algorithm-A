#include <iostream>
#include <queue>
#include <math.h>
using namespace std;
int N, M; 
int map[20][20];
int total;
struct Node {
	int y, x;
};
int dir[4][2] = { -1,0,0,1,1,0,0,-1 };
int getExpense(int K) { //최소 필요한 expense
	return pow(K, 2) + pow(K - 1, 2);
}
int isValid(int home, int expense) { // 현재 집 개수*M>= 현재 비용 -> true
	if (home * M >= expense)
		return true;
	return false;
}
int nextPossible(int expense) { // total*M<expense
	if (total * M < expense)
		return false;
	return true;
}
int floodfill(int start_y, int start_x ) {
	queue<Node>q;
	q.push({ start_y,start_x });
	int K[20][20] = { 0 };
	K[start_y][start_x] = 1;
	int ans=0;
	int home=0;
	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		if (map[now.y][now.x] == 1)
			home++;
		if (isValid(home, getExpense(K[now.y][now.x]))) {
			ans = home;
		}
		for (int i = 0; i < 4; i++) {
			int dy = now.y + dir[i][0];
			int dx = now.x + dir[i][1];
			if (dy < 0 || dx < 0 || dy >= N || dx >= N) continue;
			if (K[dy][dx] > 0) continue;
			int nextCost = K[now.y][now.x] + 1;
			if (!nextPossible(getExpense(nextCost))) continue;
			K[dy][dx] = nextCost;
			q.push({ dy,dx });
		}
	}
	return ans;
}
int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N >> M;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				cin >> map[y][x];
				if (map[y][x] == 1)
					total++;
			}
		}
		int Max = 0;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				int ret = floodfill(y, x);
				if (Max < ret)
					Max = ret;
			}
		}
		cout << '#' << t + 1 << ' ' << Max << '\n';
	}

	return 0;
}