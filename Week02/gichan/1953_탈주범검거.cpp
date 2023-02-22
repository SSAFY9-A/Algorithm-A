// 2023-02-10
// 시작 16:30
// 끝   17:37
// 겪은 문제점 : bfs를 다 돌았는데도 시간이 남을 때를 고려 못했다
//				 즉, 시간이 너무 충분해서 가능한 모든 통로에 다 들어갔을때를
//				 세지 않았음.

// [내용]
/*
	탈주범 잡아야함
	탈주범 지하터널로 도망감.
	지하터널 내에선 연결된 곳만 갈 수 있음.
	탈주범은 시간당 1의 거리만 움직일 수 있음.

	// [지하터널 종류]
	1 : 상 하 좌 우
	2 : 상 하
	3 :       좌 우
	4 : 상       우
	5 :    하    우
	6 :    하 좌
	7 : 상    좌

	탈출범은 1시간뒤 도달할 수 있는 지점은 한곳.
	즉, 1시간 부터 시작해야함.
*/
// [목적]
/*
	탈출범의 위치와 경과 시간이 주어졌을 때.
	탈출범이 위치할 수 있는 장소의 개수를 출력하는 프로그램
*/


// [입력]
/*
	H : 맵 세로 크기.
	W : 맵 가로 크기.
	R : 맨홀 뚜껑 y 위치 (인덱스값임).
	C : 맨홀 뚜껑 x 위치 (인덱스값임).
	L : 탈출 후 소요된 시간.

	5				// 총 테스트 케이스
	5 6 2 1 3		// H W R C L
	0 0 5 3 6 0		// 지하터널 지도 H x W
	0 0 2 0 2 0
	3 3 1 3 7 0
	0 0 0 0 0 0
	0 0 0 0 0 0
*/

// [출력]
/*

	#test_case 가능한 위치수
*/

// [전략]
/*
	bfs를 사용
	시작 위치부터
	큐에서 팝 할 때, 현재 큐 사이즈만큼 하고 시간 한시간 증가 -> 반복
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

class node {
public:
	int y;
	int x;
	node(int _y, int _x) {
		y = _y;
		x = _x;
	}
};

//H: 맵 세로 크기.
//W : 맵 가로 크기.
//R : 맨홀 뚜껑 y 위치(인덱스값임).
//C : 맨홀 뚜껑 x 위치(인덱스값임).
//L : 탈출 후 소요된 시간
int H, W, R, C, L;
int possible_pos = 1; // 정답이 될 변수. 도둑이 있을 수 있위치 수
int map[50][50] = { 0, }; // 지하터널 지도


vector<node> getWayVec(int way) 
{
	// [지하터널 종류]
	//	1 : 상 하 좌 우
	//	2 : 상 하
	//	3 :       좌 우
	//	4 : 상       우
	//	5 :    하    우
	//	6 :    하 좌
	//	7 : 상    좌

	int direct[4][2] = {
		{-1, 0}, // 상
		{ 1, 0}, // 하
		{ 0,-1}, // 좌
		{ 0, 1}  // 우
	};
	
	// 현재 map위치에서 갈 수 있는 방향 y,x offset을 담을 것.
	vector<node> ret;
	if (way == 1) {
		for (int i = 0; i < 4; ++i) {
			ret.push_back(node(direct[i][0], direct[i][1])); // y,x 다 추가.
		}
	}
	else if (way == 2) {
		for (int i = 0; i < 4; ++i) {
			if (i >= 2) continue;
			ret.push_back(node(direct[i][0], direct[i][1])); // y,x 다 추가.
		}
	}
	else if (way == 3) {
		for (int i = 0; i < 4; ++i) {
			if (i <= 1) continue;
			ret.push_back(node(direct[i][0], direct[i][1])); // y,x 다 추가.
		}
	}
	else if (way == 4) {
		//	4 : 상       우
		for (int i = 0; i < 4; ++i) {
			if (i == 1 || i == 2) continue;
			ret.push_back(node(direct[i][0], direct[i][1])); // y,x 다 추가.
		}
	}
	else if (way == 5) {
		//	5 : 하    우
		//	6 : 하 좌
		//	7 : 상    좌
		for (int i = 0; i < 4; ++i) {
			if (i == 0 || i == 2) continue;
			ret.push_back(node(direct[i][0], direct[i][1])); // y,x 다 추가.
		}
	}
	else if (way == 6) {
		for (int i = 0; i < 4; ++i) {
			if (i == 0 || i == 3) continue;
			ret.push_back(node(direct[i][0], direct[i][1])); // y,x 다 추가.
		}
	}
	else if (way == 7) {
		for (int i = 0; i < 4; ++i) {
			if (i == 1 || i == 3) continue;
			ret.push_back(node(direct[i][0], direct[i][1])); // y,x 다 추가.
		}
	}

	return ret;
}

int countPossiblePos(int _visited[][50])
{
	int cnt = 0;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (_visited[i][j] == 1)
				cnt++;
			//cout << _visited[i][j] << " ";
		}
		//cout << '\n';
	}
	return cnt;
}

// 서로 연결되어있는 길인지 검사하는 함수
bool isInterConnected(node from, node to)
{
	// 서로가 서로한데 갈 수 있으면 갈 수 있는거임.
	vector<node> dir_vec_from = getWayVec(map[from.y][from.x]);
	bool canGo1 = false;
	for (int i = 0; i < dir_vec_from.size(); ++i) {
		int dy = from.y + dir_vec_from[i].y;
		int dx = from.x + dir_vec_from[i].x;
	
		if (dy == to.y && dx == to.x) {
			canGo1 = true;
			break;
		}
	}

	vector<node> dir_vec_to = getWayVec(map[to.y][to.x]);
	bool canGo2 = false;
	for (int i = 0; i < dir_vec_to.size(); ++i) {
		int dy = to.y + dir_vec_to[i].y;
		int dx = to.x + dir_vec_to[i].x;

		if (dy == from.y && dx == from.x) {
			canGo2 = true;
			break;
		}
	}

	if (canGo1 == true && canGo2 == true)
		return true;
	else
		return false;
}

void bfs(node start)
{
	queue<node> q;
	q.push(start);
	int visited[50][50] = { 0, };
	visited[start.y][start.x] = 1;
	int hour = 0;

	while (!q.empty()) {
		int cursize = q.size();
		hour++; // 시간 증가.
		// 여기서 경과 시간 검사
		if (hour == L) {
			possible_pos = countPossiblePos(visited);
			return;
		}

		for (int k = 0; k < cursize; ++k) {
			node now = q.front();
			q.pop();

			// 현재 터널에서 어디 방향으로 갈 수 있는지 그 방향 벡터를 받는다.
			vector<node> wayVec = getWayVec(map[now.y][now.x]);

			for (int i = 0; i < wayVec.size(); ++i) {
				int dy = now.y + wayVec[i].y;
				int dx = now.x + wayVec[i].x;

				// 범위 체크
				if (dy >= 0 && dy < H && dx >= 0 && dx < W) {
					// 길인가?
					if (map[dy][dx] != 0) {
						// 서로 연결되어 있는가?
						if (isInterConnected(now, node(dy,dx))) {
							// 방문한 적 없는가?
							if (visited[dy][dx] == 0) {
								visited[dy][dx] = 1;
									q.push(node(dy, dx));
							}
						}
					}
				}
			}
		}


	}
	// 혹시 정해진 시간이 너무 크면 bfs 그냥 끝나니깐 끝났을때도 이거 해줘야함.
	possible_pos = countPossiblePos(visited);
}

void init()
{
	possible_pos = 1;
	memset(map, 0 , sizeof(map));
}

int main()
{
	int test_case;
	int T;
	
	//freopen("input.txt", "r", stdin);
	cin >> T;	// 전체 테스트 케이스 수
	//T = 1;
	for (test_case = 1; test_case <= T; ++test_case) {
		// reset
		init();

		// input
		cin >> H >> W >> R >> C >> L; // 맵 크기, 멘홀뚜껑 위치, 경과 시간
		//cout << H << W << R << C << L;
		//return 0;
		for (int i = 0; i < H; ++i) { // 지하터널 지도 입력
			for (int j = 0; j < W; ++j) {
				cin >> map[i][j];
			}
		}

		// solve
		bfs(node(R,C)); // 멘홀뚜껑 위치에서 bfs 시작.
	 
		// output
		cout << "#" << test_case << " " << possible_pos << '\n';
	}

	return 0;
}
