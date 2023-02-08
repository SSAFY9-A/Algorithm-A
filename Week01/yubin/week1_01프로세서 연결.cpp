#include<iostream>

using namespace std;

int map[12][12];
int N;
int maxcore;
int flag = 0;
int CNT;
int MIN = 21e8;
int check(int y, int x, int d)
{
	//상,하,좌,우
	if (d == 0)
		for (int i = 0; i < y; i++)
			if (map[i][x] != 0) return 0;

	if (d == 1)
		for (int i =y+1; i <N; i++)
			if (map[i][x] != 0) return 0;

	if (d == 2)
		for (int i = 0; i < x; i++)
			if (map[y][i] != 0) return 0;

	if (d == 3)
		for (int i = x+1; i < N; i++)
			if (map[y][i] != 0) return 0;
	return 1;
}

int inoutMap(int y, int x, int d,int n)
{
	int count = 0;
	if (d == 0)
		for (int i = 0; i < y; i++)
		{
			map[i][x] = n;
			count++;
		}
	if (d == 1)
		for (int i = y + 1; i < N; i++)
		{
			map[i][x] = n;
			count++;
		}

	if (d == 2)
		for (int i = 0; i < x; i++)
		{
			map[y][i] = n;
			count++;
		}

	if (d == 3)
		for (int i = x + 1; i < N; i++)
		{
			map[y][i] = n;
			count++;
		}
	return count;
}


void run(int level, int now)
{
	if (level == N-1)
	{
		cout << "cnt" << CNT <<", min "<<MIN<< '\n';
		cout << maxcore << ":max\n";
		if (MIN > CNT)
		{
			MIN = CNT;
		}
		return;
	}
	//일단?! 한줄한줄 돌려야함. 
	for (int i = now; i < N - 1; i++)
	{
		if (map[level][i] !=1) continue;
		//방향확인
		flag = 0;
		for (int j = 0; j < 4; j++)
		{
			if (check(level, i, j) == 0) continue;
			int data = inoutMap(level, i, j, 2);
			//체크하고?? map에 넣을거임
			if (CNT + data > MIN) continue;
			CNT+=data;
			cout << level << "," << i << ") " << j << '\n';
			//1.일단 다음 1로감
			run(level,i+1);
			CNT-=inoutMap(level, i, j, 0);
			
			
			//근데 다 안된다..??
			flag = 1;
		}
		//flag=1이란 건 check에 걸리는 게 하나라도 있다는 얘기.core 수 ++ 해야함. 
		//flag=0은 주변이 다 안된다. 
		if (flag == 0) maxcore++;
	}
	//2.다음 1이 없으면 여기 
	run(level + 1,1);
	
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	run(1,1);
	cout << MIN;
}
