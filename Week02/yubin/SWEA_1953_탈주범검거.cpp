#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

int map[50][50];
int via[50][50];

int CNT;
int N, M;
int L;
int R, C;

int Ly, Lx; //마지막 좌표값이 안들어가는 것을 방지

vector<int> arr[7];

struct node {
	int y;
	int x;
};


void Pre()
{
	arr[0] = { 1,-1,0,0,0,0,1,-1 };
	arr[1] = { -1,1,0,0 };
	arr[2] = { 0,0,1,-1 };
	arr[3] = { -1,0,0,1 };
	arr[4] = { 0,1,1,0 };
	arr[5] = { 0,1,-1,0 };
	arr[6] = { 0,-1,-1,0 };

};

//cy,cx 에서도 반대로 y,x가 연결되는지 확인. 
int check(int cy, int cx, int y, int x)
{
	int mapNum = map[cy][cx] - 1;
	int sz = arr[mapNum].size();
	for (int i = 0; i < sz / 2; i++)
	{
		int dy = cy + arr[mapNum][i];
		int dx = cx + arr[mapNum][i + sz / 2];
		if (dy < 0 || dx < 0 || dy >= N || dx >= M) continue;
		if (dy == y && dx == x)return 1;
	}
	return 0;
}

void func(int y, int x) {
	queue<node>q;
	q.push({ y,x });
	via[y][x] = 1;
	while (!q.empty())
	{
		
		node now = q.front();
		q.pop();

		int mapYX = map[now.y][now.x] - 1;
		//구조물에 따라서 확인이 달라짐. S는 방향배열의 size.
		int S = arr[mapYX].size();
		for (int i = 0; i < S / 2; i++)
		{
			int cy = now.y + arr[mapYX][i];
			int cx = now.x + arr[mapYX][i + S / 2];
			if (cy < 0 || cx < 0 || cy >= N || cx >= M) continue;
			if (map[cy][cx] == 0)continue;
			if (via[cy][cx] != 0)continue;
			//여기서 한번 더 돌려서 가능한 범위인지 확인해야함. 
			//잘 이어지는지!
			if (check(cy, cx, now.y, now.x) == 0)continue;

			via[cy][cx] = via[now.y][now.x] + 1;
			//마지막 처리,,!
			if (via[cy][cx] > L) return ;

			//cout << now.y << "," << now.x << " " << cy << "," << cx ;
			CNT++;
			//cout << " cnt :" << CNT <<" via : "<<via[cy][cx]<< "\n";
			q.push({ cy,cx });
		}
		Ly = now.y;
		Ly = now.x;
	}
}



int main()
{
	int tc;
	cin >> tc;
	Pre();

	for (int t = 0; t < tc; t++)
	{
		cin >> N >> M >> R >> C >> L;
		CNT = 0;
		memset(via, 0, sizeof(via));

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cin >> map[i][j];

		cout << "#" << t + 1 << " ";
		func(R, C);

		if (via[Ly][Lx] <= L)CNT++;
		cout << CNT  << '\n';


	}

}
