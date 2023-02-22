#include<iostream>
#include<cstring>
using namespace std;
/*
* 크기가 N인공간에서 가로로 M만큼을 선택할 수 있음. ->그 크기만큼 배열 생성
* 배열의 합이 C를 넘어가면 안됨. 넘어가면 선택이 필요. 
-> 여러개를 선택해도 선택한 숫자들의 제곱의 합< 큰 수의 제곱
*/

int N,M,C; //M만큼을 합한게 C를 넘으면 안됨. 
int map[10][10];

//제곱의 합을 return 하는 함수 
int Sum(int y, int x)
{
	int sum = 0;
	int Ccheck=0;
	for (int i = 0; i < M; i++)
	{
		sum += map[y][x + i] * map[y][x + i];
		//cout << map[y][x + i] << " ";
		Ccheck += map[y][x + i];
		if (Ccheck > C) return -1;
	}
	return sum;
}


//선택하면서 제곱의 합의 MAX를 구함. 
int savenum[5];
int path[5];
int via[5];
int SUM = 0;
int MAX = 0;
void dfs(int limit,int level)
{
	if (SUM > C) return;

	if(level==limit)
	{
		int calc = 0;
		for (int i = 0; i < level; i++) {
			calc += path[i] * path[i];
			//cout << path[i] << " ";
		}
		if (calc > MAX)
			MAX = calc;
		//cout << endl;
		return;
	}

	for (int i = level; i < M; i++)
	{
		path[level] = savenum[i];
		if (via[i] == 1)continue;
		SUM += savenum[i];
		via[i] = 1;

		dfs(limit, level + 1);

		path[level] = 0;
		via[i] = 0;
		SUM -= savenum[i];
	}
}

//M만큼의 크기가 C보다 클 경우. 빼면서 실행하는 작업
void outHoney(int y, int x)
{
	MAX = 0;
	//DFS돌리기 위해 따로 배열로 넘겨줌
	for (int i = 0; i < M; i++)
		savenum[i] = map[y][x + i];

	//반복문으로 M-1만큼 선택하는 경우 넘겨줌. 
	
	for (int i = M-1; i >=1; i--)
	{
		SUM = 0;
		memset(via, 0, sizeof(via));
		memset(path, 0, sizeof(path));
		//DFS 돌려서 i만큼 확인.
		//DFS 에서 C보다 큰지 확인. 
		dfs(i,0);
	}
}

int func()
{
	int k = 0;
	int by, bx;
	int Asum = 0;
	int Bsum = 0;
	int Bmax = 0;
	int ABmax = 0;

	//1.합이C가 넘어가지 않은제곱의 최댓값!
	//2.합이 C가 넘어가지만 선택했을 때 제곱의 최대값이 될 수 있금. 
	while(1)
	{
		for (int i = 0; i <= N - M; i ++)
		{
			Asum=Sum(k,i);
			//Asum 이 -1인경우는 합이 C를 넘기는 경우 
			if (Asum == -1)
			{
				outHoney(k, i);
				Asum = MAX;
			}
			//cout << "\nA sum: " << Asum << '\n';
			by = k;
			bx = i + M;
			Bmax = 0;
			//완전탐색으로 A구하고 나머지 B에서 최대값 찾음
			while (1)
			{
				if (bx+M > N)
				{
					by++;
					if (by >=N) break;
					bx = 0;
				}
				Bsum = Sum(by,bx);
				if (Bsum == -1)
				{
					outHoney(by, bx);
					Bsum = MAX;
				}
				if (Bmax < Bsum)
					Bmax = Bsum;
				//cout << "\nB sum: " << Bsum << '\n';
				bx++;
			}
			if (ABmax < Asum+ Bmax) ABmax = Asum + Bmax;
		}
		k++;
		if (k >= N) break;
	}
	return ABmax;
}


int main()
{
	int tc;
	cin >> tc;
	for (int t = 0; t < tc; t++) {
		int n;
		cin >> N >> M >> C;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> map[i][j];
		n = func();
		cout << "#" << t + 1 << " " << n << endl;
	}
}
