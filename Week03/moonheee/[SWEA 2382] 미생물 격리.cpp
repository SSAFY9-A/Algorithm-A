// M 시간 이후의 미생물 수 구하기
// 군집의 수 K <= 1000이다
// 장애물이 존재한다. x == 0 || y == 0 || x == N - 1 || y == N - 1
// M * ( K ) = 1000^4 = 1,000,000,000,000 = 10억
// 50개 5초 => 1개 0.1초
// 한번에 계산할 수 있을까?
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

// 군집의 정보
struct Node
{
	int y;
	int x;
	int direction;	// 방향 (상: 1, 하: 2, 좌: 3, 우: 4)
	int count;		// 미생물 수
};

struct COUNT
{
	int index;	// 군집번호
	int time;	// 0 ~ M (중복 방지)
};

COUNT m_count[100][100];	// 결과 저장
COUNT pre[100][100];		// 이전 정보 저장
// 0이면 군집없음
// 0이 아닌 수라면 군집 번호 collection의 인덱스

int N, M, K;
vector<Node> collection;	// 군집 정보 저장 (원소 삭제 X)

// (상: 1, 하: 2, 좌: 3, 우: 4)
int direct[5][2] =
{
	0, 0,
	-1, 0,
	1, 0,
	0, -1,
	0, 1
};

// 디버깅을 위한 함수
void print_m_count()
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
			cout << m_count[y][x].index << " ";

		cout << "      ";
		for (int x = 0; x < N; x++)
			cout << pre[y][x].index << " ";
		cout << "\n";
	}
	return;
}

// 초기화
void init()
{
	collection.clear();
	memset(m_count, 0, sizeof(m_count));

	cin >> N >> M >> K;		// 셀의 개수 / 시간 / 군집의 개수
	Node tmp;
	for (int i_k = 1; i_k <= K; i_k++)
	{
		cin >> tmp.y >> tmp.x >> tmp.count >> tmp.direction;
		collection.push_back(tmp);
		m_count[tmp.y][tmp.x].index = i_k;
		m_count[tmp.y][tmp.x].time = 0;
	}
	// 빈 깡통을 하나 넣어준다. (나중에 미생물이 가장 많은 군집의 초기화값
	tmp.count = 0;
	collection.push_back(tmp);
	//print_m_count();
	return;
}

void sol()
{
	//print_m_count();
	vector<pair<int, int>> position;	// 군집이 다음에 갈 곳
	for (int i_m = 1; i_m <= M; i_m++)	// 시간만큼 반복합니다
	{
		position.clear();
		// 다음 군집이 이동할 곳 찾기
		for (int idx = 0; idx < collection.size(); idx++)
			if (collection[idx].count)
			{
				// 미생물이 있다면 = 살아 있는 군집
				Node node = collection[idx];
				// 이전 정보 저장
				pre[node.y][node.x].index = idx + 1;
				int dy = node.y + direct[node.direction][0];
				int dx = node.x + direct[node.direction][1];
				if (dy < 0 || dx < 0 || dy >= N || dx >= N)
					continue;
				position.push_back(make_pair(dy, dx));
				// 시간 초기화
				m_count[dy][dx].time = 0;
			}
		//print_m_count();
		// 다음 군집이 이동할 곳에서
		for (pair<int, int> next : position)
		{
			// 이미 이동완료된 곳이라면 지나친다
			if (m_count[next.first][next.second].time >= i_m)
				continue;

			// 만약 그 자리에 군집이 있다면
			// 미래의 상하좌우를 확인해서 가장 많은 수의 군집 찾기
			int max_index = K;
			for (int i_d = 1; i_d < 5; i_d++)
			{
				int dy = next.first + direct[i_d][0];
				int dx = next.second + direct[i_d][1];

				if (dy < 0 || dx < 0 || dy >= N || dx >= N)
					continue;

				// 군집이 있다면
				if (pre[dy][dx].index)
				{
					// ex 군집을 현재 next에서 하에서 찾았다면 군집의 방향은 상이 되야 합니다.
					int tmp_i_d = collection[pre[dy][dx].index - 1].direction;
					if (tmp_i_d % 2)
						tmp_i_d++;
					else
						tmp_i_d--;
					// 그 군집이 다음에 올 군집이라면
					if (tmp_i_d == i_d)
						// 그 군집이 미생물이 가장 크다면
						if (collection[max_index].count < collection[pre[dy][dx].index - 1].count)
							max_index = pre[dy][dx].index - 1;
				}

			}
			//print_m_count();
			// 군집을 합친다 max_index로 먼저 합친다
			for (int i_d = 1; i_d < 5; i_d++)
			{
				int dy = next.first + direct[i_d][0];
				int dx = next.second + direct[i_d][1];

				if (dy < 0 || dx < 0 || dy >= N || dx >= N)
					continue;

				// 군집이 존재하고 max_index 가 아니면
				if (pre[dy][dx].index)
				{
					int tmp_i_d = collection[pre[dy][dx].index - 1].direction;
					if (tmp_i_d % 2)
						tmp_i_d++;
					else
						tmp_i_d--;
					// 그 군집이 다음에 올 군집이라면
					if (tmp_i_d == i_d && pre[dy][dx].index - 1 != max_index)
					{
						// 가장 많은 곳에 count를 더해준다.
						collection[max_index].count += collection[pre[dy][dx].index - 1].count;
						//cout << "+ " << collection[pre[dy][dx].index - 1].count << "(" << dy << "," << dx << ")" << "\n";
						// 군집 삭제
						collection[pre[dy][dx].index - 1].count = 0;
						// next에 이미 어떤 값을 저장 하지 않았다면
						if (m_count[dy][dx].index == pre[dy][dx].index)
							m_count[dy][dx].index = 0;
						pre[dy][dx].index = 0;
					}
				}
			}
			//print_m_count();
			// 가장 많은 군집 이동
			if (m_count[collection[max_index].y][collection[max_index].x].index == max_index + 1)
				m_count[collection[max_index].y][collection[max_index].x].index = 0;
			m_count[next.first][next.second].index = max_index + 1;
			pre[collection[max_index].y][collection[max_index].x].index = 0;
			collection[max_index].y = next.first;
			collection[max_index].x = next.second;
			//print_m_count();
			// 만약 시약에 닿았다면 미생물 수를 반으로 줄이고 방향을 바꾼다.
			if (next.second == 0 || next.first == 0 || next.second == N - 1 || next.first == N - 1)
			{
				collection[max_index].count /= 2;
				if (collection[max_index].count == 0)
					// 미생물 수가 0이라면 군집을 삭제한다.
					m_count[next.first][next.second].index = 0;
				else
				{
					// 방향을 바꾼다.
					int tmp_i_d = collection[max_index].direction;
					if (tmp_i_d % 2)
						tmp_i_d++;
					else
						tmp_i_d--;
					collection[max_index].direction = tmp_i_d;
				}
			}
			// 시간을 측정한다.
			m_count[next.first][next.second].time = i_m;
			//cout << "******************" << i_m << ":" << next.first << "," << next.second << "->" << max_index << "\n";
			//print_m_count();
		}
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

		int total_count = 0;
		for (Node x : collection)
			total_count += x.count;
		//print_m_count();
		cout << "#" << i_t + 1 << " " << total_count << "\n";
	}
	return 0;
}