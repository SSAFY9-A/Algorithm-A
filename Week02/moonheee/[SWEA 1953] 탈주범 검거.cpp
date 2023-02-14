// bfs로 풀면되겠다.
// bfs 구현 까먹음
// 파이프를 연결할 때 현재 node과 미래 node의 방향을 잘 봐야합니다.
// 인접 그래프나, 인접 행렬보다 그냥 맵을 사용하는 편이 좋겠다.
// 현재 노드에서 total를 갱신
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, M, R, C, L;
int map[50][50];
int dat[50][50];
int total; // 탈주범이 있을 수 있는 경우의 수
int direct[8][4] =
{
	0, 0, 0, 0, // 없음
	1, 1, 1, 1, // 1,상하좌우
	1, 1, 0, 0, // 2
	0, 0, 1, 1, // 3
	1, 0, 0, 1, // 4
	0, 1, 0, 1, // 5
	0, 1, 1, 0, // 6
	1, 0, 1, 0  // 7
};
int direct2[4][2] =
{
	-1, 0, // 상
	1, 0, // 하
	0, -1, // 좌
	0, 1	//우
};

void print_dat()
{
	cout << "print_dat\n";
	for (int i_n = 0; i_n < N; i_n++)
	{
		for (int i_m = 0; i_m < M; i_m++)
			cout << dat[i_n][i_m] << " ";
		cout << "\n";
	}
	return;
}

void bfs(pair<int, int> start)
{
	queue<pair<int, int>> q;
	dat[R][C] = 1;
	q.push(start);

	while (!q.empty())
	{
		pair<int, int> now = q.front();
		if (dat[now.first][now.second] > L)
		{
			//print_dat();
			return;
		}
		q.pop();
		total++;
		for (int i_d = 0; i_d < 4; i_d++)
		{
			// 현재 연결된 곳 찾기
			// i_d : 상, 하, 좌, 우
			if (direct[map[now.first][now.second]][i_d])
			{
				pair<int, int> next;
				next.first = now.first + direct2[i_d][0];
				next.second = now.second + direct2[i_d][1];
				// 다음 노드가 맴 범위에 있고
				// 아직 가보지 않았고
				if (next.first >= 0 && next.first < N
					&& next.second >= 0 && next.second < M
					&& dat[next.first][next.second] == 0)
				{
					// (상(i_d)->하(next_d)) (하->상) (좌->우) (우->좌)
					int next_d = i_d;
					if (next_d % 2)
						next_d--;
					else
						next_d++;
					// 다음 노드와 현재 노드와 연결 되어 있다면
					if (direct[map[next.first][next.second]][next_d])
					{
						dat[next.first][next.second] = dat[now.first][now.second] + 1;
						q.push(next);
					}
				}
			}
		}
	}
}

int main()
{
	int T;
	cin >> T;
	for (int i_t = 0; i_t < T; i_t++)
	{
		total = 0;
		memset(dat, 0, sizeof(dat));
		cin >> N >> M >> R >> C >> L;
		for (int i_n = 0; i_n < N; i_n++)
			for (int i_m = 0; i_m < M; i_m++)
				cin >> map[i_n][i_m];

		bfs(make_pair(R, C));
		cout << "#" << i_t + 1 << " " << total << "\n";
	}
	return 0;
}