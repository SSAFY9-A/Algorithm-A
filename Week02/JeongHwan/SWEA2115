#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int N, M, C;//벌통들의 크기,개수,채취할수 있는 최대양
int map[10][10]; //벌통
int acc_profit; //누적 수익
int max_profit; //수익 최댓값
int visited[10][10]; //방문 좌표 배열
int honey_visited[100];//채취한 꿀 배열	
int acc_honey; //채취한 누적 벌꿀
int acc_sale;//누적 판매금
int max_sale; // 최대 판매금


void init(void)
{
	acc_profit = 0;
	max_profit = -21e8;
	memset(visited, 0, sizeof(visited));
}

void init_honey(void)
{
	acc_honey = 0;
	acc_sale = 0;
	max_sale = -21e8;
	memset(honey_visited, 0, sizeof(honey_visited));
}

void input(void)
{
	cin >> N >> M >> C;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
			cin >> map[y][x];
}

bool check_visited(int y, int x)
{
	for (int t = x; t < x + M; t++)
		if (visited[y][t] == 1)
			return false;
	return true;
}

void visit(int y, int x)
{
	for (int t = x; t < x + M; t++)
		visited[y][t] = 1;
}

void unvisit(int y, int x)
{
	for (int t = x; t < x + M; t++)
		visited[y][t] = 0;
}

void bf2(int y, int x, int level)
{
	if (max_sale< acc_sale)
	{
		max_sale = acc_sale;
	}
	if (level == M)
		return;
	for (int t = 0; t < M; t++)
	{
		//이미 채취 했으면 
		if (honey_visited[x+t] == 1) continue;
		//할당량보다 많이 채취하면
		if (acc_honey + map[y][x + t] > C) continue;
		honey_visited[x + t] = 1;//방문 체크
		acc_honey += map[y][x + t]; //누적 채취량 갱신
		acc_sale += map[y][x + t] * map[y][x + t]; //누적 판매금

		bf2(y, x, level + 1);

		honey_visited[x + t] = 0;
		acc_honey -= map[y][x + t];
		acc_sale -= map[y][x + t] * map[y][x + t];
	}
}

void bf1(int level)
{
	if (level == 2)
	{
		if (max_profit < acc_profit)
			max_profit = acc_profit;
		return;
	}

	for(int y=0; y<N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			//가로로 M칸 뽑을때 범위 초과하면
			if (x + M-1>=N) continue;
			//방문한 곳이 있으면
			if (!check_visited(y, x)) continue;
			visit(y, x);//방문 체크
			init_honey();//꿀 채취하기 초기화
			bf2(y, x, 0);//최대 수익 획득
			int k = max_sale;	// 백업
			acc_profit += k; //누적 수익 갱신
			bf1(level + 1);
			acc_profit -= k;
			unvisit(y, x);
		}
	}
}

int main(void)
{
	//freopen("input.txt", "r", stdin);

	int T;//테스트 케이스
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		input();//입력
		init();//초기화
		bf1(0);
		cout << '#' << t + 1 << ' ' << max_profit << '\n';
		
	}
}
