/*
총 N*N개의 공간, K개의 미생물 군집, 테두리 약품, 미생물 못도망감

상하좌우 한 방향으로 1시간 1칸 이동, 약품에 도착후 절반 죽은 후 반대 방향 바뀜, 살아 남은 미생물 2로 나눈 수
이동 후 한셀에 있는 미생물 군비들은 합쳐짐, 이동방향은 미생물 수가 많은 군집의 이동방향

M시간 후 남아있는 미생물 수 총합

미생물 구조체, 방향 배열, 우선순위 큐로(좌표마다넣기)
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
struct micro
{
	int num;//개수
	int y, x;//좌표
	int dir;//방향

	bool operator<(micro next)const
	{
		if (num > next.num) return false;
		if (num < next.num) return true;
		return false;
	}
};
struct MAP
{
	int num;//개수
	int dir;//방향
};
int N, M, K;//공간 너비, 격리시간, 군집개수
MAP map[100][100]; //공간
int direct[5][2] = { 0,0,-1,0,1,0,0,-1,0,1 }; //방향 배열ㄴ
int sv(void)
{
	priority_queue<micro>pq;
	int Y, X, num, dir;
	int cnt = 0;
	cin >> N >> M >> K;
	for (int k = 0; k < K; k++)
	{
		cin >> Y >> X >> num >> dir;
		pq.push({ num,Y,X,dir });
	}



	for (int m = 0; m < M; m++)
	{
		//map 초기화
		memset(map, 0, sizeof(map));
		while (!pq.empty())
		{
			micro now = pq.top();
			pq.pop();
			//이동할 좌표 구하기
			int dy = now.y + direct[now.dir][0];
			int dx = now.x + direct[now.dir][1];
			
			// 이동할 좌표가 테두리 이면 방향 반대로 바꾸어 주기
			// 수도 반 줄여주기
			if (dy == 0 || dx == 0 || dy == N - 1 || dx == N - 1)
			{
				switch (now.dir)
				{
				case 1:
					now.dir = 2;
					break;
				case 2:
					now.dir = 1;
					break;
				case 3:
					now.dir = 4;
					break;
				case 4:
					now.dir = 3;
					break;
				default:
					break;
				}
				now.num /= 2;
			}
			// 처음으로 이동이된 좌표일때
			if (map[dy][dx].num == 0)
			{
				map[dy][dx].dir = now.dir;
				map[dy][dx].num = now.num;
			}
			// 이미 먼저 이동이 된 좌표면 양이 많은 것이므로
			//방향은 넣지 않음
			else
			{
				map[dy][dx].num += now.num;
			}
		}

		//M번 이동했으면미생물 수 구하기
		if (m == M - 1)
		{
			for (int y = 0; y < N; y++)
				for (int x = 0; x < N; x++)
					cnt += map[y][x].num;
			return cnt;
		}
		//M번 이동 안했으면 다음 이동을 위해 pq에 넣기
		else
		{
			for (int y = 0; y < N; y++)
				for (int x = 0; x < N; x++)
				{
					//y,x좌표에 미생물이 존재하면
					if (map[y][x].num != 0)
						pq.push({ map[y][x].num, y, x,map[y][x].dir });
				}
		}
	}
}
int main(void)
{
	//freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		int cnt = sv();
		cout<<'#'<<tc<<' '<< cnt<<'\n';
	}
}
