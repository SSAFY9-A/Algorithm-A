#include<iostream>
#include<cstring>
using namespace std;
/*
* 크기가 N인공간에서 가로로 M만큼을 선택할 수 있음. ->그 크기만큼 배열 생성
* 배열의 합이 C를 넘어가면 안됨. 넘어가면 선택이 필요. 
* 선택은 제일 적은 수 선택
-> 여러개를 선택해도 선택한 숫자들의 제곱의 합< 큰 수의 제곱
*/

/*
4 2 13
6 1 9 7
9 8 5 8
3 4 5 3
8 2 6 7


1
4 1 10
8 1 8 2
4 6 1 6
4 9 6 3
7 4 1 3
*/
int N,M,C; //M만큼을 합한게 C를 넘으면 안됨. 
int map[10][10];
int savenum[5];
int path[5];
int via[5];
int SUM = 0;
int MAX = 0;

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

// 빼면서 최대값 구함
int outHoney(int y, int x)
{
	int max = 0;
	MAX = 0;
	for (int i = 0; i < M; i++)
	{
		savenum[i] = map[y][x + i];
	}
	//포문 돌려서 
	//만약에 4개라면,, 9,8,5,9 C가 16이다
	//일단 하나씩 뺌. 0 8 5 9 
	for (int i = M-1; i >=0; i--)
	{
		//1개부터 M-1개까지 선택
		//이건 DFS로 확인해야함. 
		//DFS 돌려서 i만큼 확인.
		//DFS 에서 C보다 큰지 확인. 
		//아니라면 담아서 return ;
		SUM = 0;
		memset(via, 0, sizeof(via));
		memset(path, 0, sizeof(path));
		dfs(i,0);
	}
	return MAX;
}

//최대값 구하기 
int func()
{
	int k = 0;
	int by,bx = 0;
	int Asum = 0;
	int Bsum = 0;
	int Amax = 0;
	int Bmax = 0;
	int ABmax = 0;
	//완탐 해야하나...
	//1.합이C가 넘어가지 않은제곱의 최댓값!
	//2.합이 C가 넘어가지만 선택했을 때 제곱의 최대값이 될 수 있금. 
	while(1)
	{
		for (int i = 0; i <= N - M; i = i ++)
		{
			Asum=Sum(k,i);
			if (Asum == -1)
				Asum=outHoney(k, i);
			
			//cout << "\nA sum: " << Asum << '\n';
			by = k;
			bx = i + M;
			Bmax = 0;
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
					Bsum = outHoney(by, bx);
				if (Bmax < Bsum)
					Bmax = Bsum;
				//cout << "\nB sum: " << Bsum << '\n';
				bx++;
			}
			if (ABmax < Asum+ Bmax)
			{
				ABmax = Asum + Bmax;
				//cout << "max값"<<ABmax;
			}
		}
		k++;
		if (k >= N)
			break;
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
