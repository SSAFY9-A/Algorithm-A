#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

int map[8][8];
int flag;
int MAX;
int maxcnt;
int N, K;
int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,-1,1 };
int via[8][8];
int CNT;
void run(int y, int x)
{
	via[y][x] = 1;
	for (int j = 0; j < 4; j++)
	{
		int cy = y + dy[j];
		int cx = x + dx[j];

		if (cy < 0 || cx < 0 || cy >= N || cx >= N) continue;
		if (via[cy][cx] == 1) continue;

		if (map[cy][cx] - map[y][x] >= K) continue;
		if (map[cy][cx] >= map[y][x] && flag == 1) continue;
		if (map[cy][cx]- map[y][x]>=0 && map[cy][cx] - map[y][x] < K)
		{
			
			for (int k = 1; k <=K; k++)
			{
				
				flag = 1;
				if ((map[cy][cx]-k)>= map[y][x])continue;
				map[cy][cx] -= k;
				CNT++;
				via[cy][cx] = 1;
				run(cy, cx);
				flag = 0;
				map[cy][cx] += k;
				via[cy][cx] = 0;
				CNT--;
			}
		}
		
		else {

			CNT++;
			via[cy][cx] = 1;
			run(cy, cx);
			via[cy][cx] = 0;
			CNT--;
		}

	}

	if (maxcnt < CNT)
		maxcnt = CNT;

}
void find()
{
	int count = 0;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++)
		{
			if (map[j][i] == MAX)
			{
				CNT = 0;
				run(j, i);
				memset(via, 0, sizeof(via));
				flag = 0;
			}
		}
	}
	
}
int main()
{
	int tc;
	cin >> tc;
	for (int t = 0; t < tc; t++) 
	{
		MAX=0;
		maxcnt=0;
		CNT = 0;
		cin >> N >> K;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cin >> map[i][j];
				if (MAX < map[i][j])
					MAX = map[i][j];
			}
		}
		find();
		cout << "#"<<t+1<<" "<<maxcnt+1<<'\n';
	}
}
