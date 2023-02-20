#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

int N, M; //M은 10 이하 
int map[20][20];
int via[20][20];
int house[50];
int Max;
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
//floodfill다 해봐,,,?
struct node
{
	int y;
	int x;
};

void run(int y, int x)
{
	queue<node>q;
	q.push({ y,x });
	via[y][x] = 1;
	if (map[y][x] == 1) house[1]++;
	while (!q.empty())
	{
		node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int cy = dy[i] + now.y;
			int cx = dx[i] + now.x;
			if (cx < 0 || cy < 0 || cx >= N || cy >= N) continue;
			if (via[cy][cx] != 0) continue;
			via[cy][cx] = via[now.y][now.x] + 1;
			//최대값을 알아보기 위함 
			if (Max < via[cy][cx])Max = via[cy][cx];
			//map=1이라면 집이 있다는 얘기이므로 house를+1해줌. 
			if(map[cy][cx]==1) house[via[cy][cx]]++;
			q.push({ cy,cx });
		}
	}
}

int cntHouse()
{
	//cout << Max<<" ";
	int max=0;
	//house의 수 는 누적임으로 누적 처리 
	for (int i = 1; i <= Max; i++)
		house[i] += house[i - 1];
	//손해보지 않는 범위에서의 최대 집
	for (int i = 1; i <= Max; i++)
	{
		int num = i * i + (i - 1)*(i - 1);
		if (house[i] * M >= num) {
			//cout << house[i] << " ";
			max = house[i];
		}
	}
	return max;
}
int main()
{
	int T;
	int cnt;
	int MaxHouse;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		cnt = 0;
		MaxHouse = 0;
		cin >> N >> M;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> map[i][j];
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				memset(via, 0, sizeof(via));
				memset(house, 0, sizeof(house));
				Max = 0;
				run(i, j);
				cnt=cntHouse();
				//cout << cnt << " ";
				if (MaxHouse < cnt) MaxHouse = cnt;
			}
		}
		cout << "#" << t + 1 << " " << MaxHouse << '\n';
	}
}
