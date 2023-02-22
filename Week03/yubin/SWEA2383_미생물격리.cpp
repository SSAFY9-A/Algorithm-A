#include<iostream>
#include<vector>
#include<cstring>
#include<stdio.h>
using namespace std;
int N, M, K;
struct node
{
	int y;
	int x;
	int num;
	int d;
};
vector<node>v;
//int map[100][100];
int via[100][100]; //방문한 노드 넣을 거임. 
int Sum[100][100];// 미생물 수 여기에다가 넣을 거임. 

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int run()
{
	for (int m = 0; m < M; m++)
	{
		memset(via, 0, sizeof(via));
		memset(Sum, 0, sizeof(Sum));

		for (int k = 0; k < v.size(); k++)
		{
			if (v[k].num == 0) continue;

			//일단 움직이자. 
			int cy = v[k].y + dy[v[k].d - 1];
			int cx = v[k].x + dx[v[k].d - 1];

			if (cx < 0 || cy < 0 || cx >= N || cy >= N) continue;
			
			//1.만일 움직였는데 벽이다?
			if (cx == 0 || cy == 0 || cx == N - 1 || cy == N - 1)
			{
				//미생물 줄이고, sum 업데이트 하고, 방향 바꾸고 yx다시 넣어줌. 
				v[k].num /= 2;
				Sum[cy][cx] = v[k].num;
				if (v[k].d == 1 || v[k].d == 3) v[k].d++;
				else v[k].d--;
				via[cy][cx] = k + 1;
				v[k].y = cy;
				v[k].x = cx;
				continue;
			}
			
			//2.움직였는데 이미 누가 있다? via로 확인
			if (via[cy][cx] != 0)
			{
				//일단 미생물은 더함.
				Sum[cy][cx] += v[k].num;

				//via에 저장되어 있던 노드의 개체수와 비교해서 내가 더 크다?
				if (v[via[cy][cx] - 1].num < v[k].num)
				{
					//그 전에 저장되었던 노드의 개체를 0으로 만들고, via에는 내가 들어감
					v[via[cy][cx] - 1].num = 0;
					via[cy][cx] = k + 1;
				}
				//내가 더 작으면?
				else
				{
					//내 개체수가 0임
					v[k].num = 0;
				}
				v[k].y = cy;
				v[k].x = cx;
				continue;
			}
			//누가 없다면
			Sum[cy][cx] = v[k].num;
			via[cy][cx] = k + 1;
			v[k].y = cy;
			v[k].x = cx;
		}
		//via에 있는 것들 처리 해줌. ->via에 남아있다는건 개체수가 제일 컸다는 얘기. 
		//Sum에 저장한 값들을 via에 넣어준다. 
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (via[i][j] == 0) continue;
				v[via[i][j] - 1].num = Sum[i][j];
			}
		}
	}
	int S = 0;
	for (int i = 0; i < v.size(); i++)
	{
		//cout << i + 1 << " " << v[i].y << "," << v[i].x << " " << v[i].num << " " << v[i].d << '\n';
		S += v[i].num;
	}
	return S;
}
void exit()
{
	int sz = v.size();
	for (int i = 0; i < sz; i++)
		v.pop_back();
}
int main()
{
	//freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		cin >> N >> M >> K;
		
		for (int k = 0; k < K; k++)
		{
			int y, x, num, d;
			cin >> y >> x >> num >> d;
			v.push_back({ y,x,num,d });
		}
		cout << "#" << t + 1 << " ";
		cout << run() << '\n';
		//vector 초기화
		exit();

	}
}
