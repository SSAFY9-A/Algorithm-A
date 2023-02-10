#include <iostream>
#define _CRT_SECURE_NO_WARNINGS 
using namespace std;

typedef struct node
{
	//좌표
	int y;
	int x;
}node;

int N; //맵 너비
int map[12][12]; //맵
int min_length;	//전선길이 최솟값
int acc_length;	//전선길이 누적값
int max_core;	//연결된 코어수 최댓값
int acc_core;	//연결된 코어수 누적값
node cord_core[12]; //코어의 좌표
int len_core_arr;  //코어 좌표 개수

// 코어의 좌표와 방향을 입력받아 전선을 연결할 수 있으면 1을 없으면 0을 리턴함.
int isValid(node n, int dir)
{
	// 위 연결이면
	if (dir == 1) {
		for (int t = 0; t < n.y; t++)
			if (map[t][n.x] != 0) return 0;
		return 1;
	}
	// 아래 연결이면
	if (dir == 2) {
		for (int t = n.y+1; t < N; t++)
			if (map[t][n.x] != 0) return 0;
		return 1;
	}
	// 왼쪽 연결이면
	if (dir == 3) {
		for (int t = 0; t < n.x; t++)
			if (map[n.y][t] != 0) return 0;
		return 1;
	}
	// 오른쪽 연결이면
	if (dir == 4) {
		for (int t = n.x+1; t < N; t++)
			if (map[n.y][t] != 0) return 0;
		return 1;
	}
}

//코어 좌표와 방향을 받아 전선을 연결하고 연결한 전선 수를 리턴하는 함수
int connect(node n, int dir)
{
	int cnt = 0; // 연결한 전선수
	// 위 연결이면
	if (dir == 1) {
		for (int t = 0; t < n.y; t++)
		{
			map[t][n.x] = -1;
			cnt++;
		}
		return cnt;
	}
	// 아래 연결이면
	if (dir == 2) {
		for (int t = n.y + 1; t < N; t++)
		{
			map[t][n.x] = -1;
			cnt++;
		}
		return cnt;
	}
	// 왼쪽 연결이면
	if (dir == 3) {
		for (int t = 0; t < n.x; t++)
		{
			map[n.y][t] = -1;
			cnt++;
		}
		return cnt;
	}
	// 오른쪽 연결이면
	if (dir == 4) {
		for (int t = n.x + 1; t < N; t++)
		{
			map[n.y][t] = -1;
			cnt++;
		}
		return cnt;
	}
 }
void dfs(int level)
{
	//최적 결과여도 코어수 가 최댓값보다 작으면
	if ((acc_core + len_core_arr - level) < max_core) return;
	//모든 코어를 돌았으면
	if (level == len_core_arr)
	{
		// 연결된 코어수가 최대값보다 크다면
		if (max_core < acc_core)
		{//코어수 최댓값과 전선길이 최솟값을 최신화해라
			max_core = acc_core;
			min_length = acc_length;
		}
		//연결된 코어수가 최대값이랑 같다면
		else if (max_core == acc_core)
		{//전선길이 최솟값보다 누적값이 작다면
			if (min_length > acc_length)
			{//전선길이 최솟값을 최신화 해라
				min_length = acc_length;
			}
		}
		return;
	}
	int back_up[12][12] = { 0, };	//백업 맵
	// 아무것도 연결하지 않는 경우
	dfs(level+1);
	//위 :1 아래 : 2 왼쪽 : 3 오른쪽 : 4
	// 위를 연결하는 경우
	if (isValid(cord_core[level], 1))
	{
		// 백업
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				back_up[y][x] = map[y][x];
		acc_core++; //연결 코어수 누적값 1 증가
		int cost = connect(cord_core[level], 1); //연결하고 전선수저장
		acc_length += cost;	//전선수 누적값 증가
		dfs(level + 1);
		acc_length -= cost; //전선수 누적값 복구
		acc_core--; //연결 코어수 누적값 복구
		//복구
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				map[y][x] = back_up[y][x];
	}
	// 아래를 연결하는 경우
	if (isValid(cord_core[level], 2))
	{
		// 백업
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				back_up[y][x] = map[y][x];
		acc_core++; //연결 코어수 누적값 1 증가
		int cost = connect(cord_core[level], 2); //연결하고 전선수저장
		acc_length += cost;	//전선수 누적값 증가
		dfs(level + 1);
		acc_length -= cost; //전선수 누적값 복구
		acc_core--; //연결 코어수 누적값 복구
		//복구
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				map[y][x] = back_up[y][x];

	}
	// 왼쪽을 연결하는 경우
	if (isValid(cord_core[level], 3))
	{
		// 백업
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				back_up[y][x] = map[y][x];
		acc_core++; //연결 코어수 누적값 1 증가
		int cost = connect(cord_core[level], 3); //연결하고 전선수저장
		acc_length += cost;	//전선수 누적값 증가
		dfs(level + 1);
		acc_length -= cost; //전선수 누적값 복구
		acc_core--; //연결 코어수 누적값 복구
		//복구
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				map[y][x] = back_up[y][x];
	}
	// 오른쪽을 연결하는 경우
	if (isValid(cord_core[level], 4))
	{
		// 백업
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				back_up[y][x] = map[y][x];
		acc_core++; //연결 코어수 누적값 1 증가
		int cost = connect(cord_core[level], 4); //연결하고 전선수저장
		acc_length += cost;	//전선수 누적값 증가
		dfs(level + 1);
		acc_length -= cost; //전선수 누적값 복구
		acc_core--; //연결 코어수 누적값 복구
		//복구
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				map[y][x] = back_up[y][x];
	}
}

int main(void)
{
	//freopen("input.txt", "r", stdin);

	//input
	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		//reset
		min_length = 21e8;	//전선길이 최솟값
		acc_length = 0;	//전선길이 누적값
		max_core = -21e8;	//연결된 코어수 최댓값
		acc_core = 0;	//연결된 코어수 누적값
		len_core_arr = 0;  //코어 좌표 개수
		cin >> N;
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				cin >> map[y][x];
		//core 좌표 수집
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				if (map[y][x] == 1)
				{
					if (y == 0 || x == 0 || y == N - 1 || x == N - 1)
					{
						acc_core++;// 테두리 코어는 제외해라
					}
					cord_core[len_core_arr++] = { y,x };
				}
		dfs(0);
		cout << '#' << (t + 1) << ' ' << min_length << '\n';
	}
}
