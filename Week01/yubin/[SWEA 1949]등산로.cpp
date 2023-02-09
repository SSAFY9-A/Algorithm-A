#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

int map[8][8]; //부지
int flag;  //깎았는지 flag로 확인 
int MAX; //가장 높은 봉우리 값
int maxcnt; // 등산로로 만들 수 있는 최대값
int N, K;
int CNT; //등산로를 세기 위한 count

int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,-1,1 };

int via[8][8];

//run 함수 : 일단 방문 check 하고 감. 
void run(int y, int x)
{
	via[y][x] = 1;
	
	for (int j = 0; j < 4; j++)
	{
		int cy = y + dy[j];
		int cx = x + dx[j];
		//해당 인덱스에서 상하좌우로 방향 확인.
		//배열의 범위를 넘어가도 안되며 
		if (cy < 0 || cx < 0 || cy >= N || cx >= N) continue;

		//방문했던 index도 안되고
		if (via[cy][cx] == 1) continue;

		//K 만큼 깎을 수 있기때문에 . 
		//다음에 올 위치와 지금의 차이가 K보다 커도 안되고 
		if (map[cy][cx] - map[y][x] >= K) continue;

		//flag=1이라면 값을 이미 바꿨다는 것을 뜻함. 
		//다음에 올 위치가 현재위치보다 커도 되지만, flag=1이라면 안됨
		if (map[cy][cx] >= map[y][x] && flag == 1) continue;

		//flag도 0이고(깎지 않았고) 차이가 K이하라면 돌림
		if (map[cy][cx]- map[y][x]>=0 && map[cy][cx] - map[y][x] < K)
		{
			//최대K이므로 K까지 완전탐색
			for (int k = 1; k <=K; k++)
			{
				flag = 1;

				//깎았는데도 크거나 같으면 안됨
				if ((map[cy][cx]-k)>= map[y][x])continue;

				//깎고, 방문처리함
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
		
		//이부분은 다음에 올 부분이 지금보다 작은 경우임
		else {

			//위의 방문처리와 동일
			CNT++;
			via[cy][cx] = 1;
			run(cy, cx);
			via[cy][cx] = 0;
			CNT--;
		}

	}

	//최대등산로 갱신
	if (maxcnt < CNT)
		maxcnt = CNT;

}

//find 함수 : max값이 들어가있는 인덱스를 run 함수로 넘김.
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
