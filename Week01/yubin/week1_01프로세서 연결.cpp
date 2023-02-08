#include<iostream>

using namespace std;

int map[12][12]; // 프로세서가 담길 cell
int N; //map 크기
int maxcore; //core수 세기
int CNT; //전선 수 세기
int MIN ; //전선 수 의 최소
int MAX ; //core 수 의 최대

//check 함수 : 상하좌우 전선을 놓을 수 있는지 확인
//d=0 상, d=1 하, d=2좌, d=3 우.
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

//inoutmap 함수 . map[y][x]에서 d방향으로 n값을 채워줌.
//n 은 전선을 뜻하는 2와 이를 복구하기 위한 0이 들어감. 
void inoutMap(int y, int x, int d,int n)
{
	if (d == 0)
		for (int i = 0; i < y; i++) map[i][x] = n;

	if (d == 1)
		for (int i = y + 1; i < N; i++) map[i][x] = n;

	if (d == 2)
		for (int i = 0; i < x; i++) map[y][i] = n;
		

	if (d == 3)
		for (int i = x + 1; i < N; i++) map[y][i] = n;

}

//datamap 함수. 전선의 수를 미리 파악하기 위한 함수
//예약개념. 해당하는 d 방향으로 채운다면? return 전선수
int dataMap(int y, int x, int d)
{
	if (d == 0) return y;
	if (d == 1) return(N - y - 1);

	if (d == 2) return x;

	if (d == 3) return (N - x - 1);	
}

void run(int level, int now)
{
	//return 조건
	//level(행) 이 N-1인 경우. (N인경우 어차피 연결되므로 해당x)
	if (level == N-1)
	{
		//1. 만일 코어의 최대값이 같은 상태에서 전선이 최소라면 업데이트
		if (maxcore==MAX && MIN > CNT)
		{
			MIN = CNT;
			MAX = maxcore;
		}
		
		//2. 만일 코어의 최대값이 증가한다면, 전선의 최소는 상관 없으므로 코어 최대로 업데이트
		else if (maxcore > MAX)
		{
			MIN = CNT;
			MAX = maxcore;
		}

		return;
	}

	for (int i = now; i < N-1 ; i++)
	{
		if (map[level][i] !=1) continue;
		for (int d = 0; d < 4; d++) //
		{
			if (check(level, i, d) == 0) continue; //방향확인
			int data = dataMap(level, i, d); //최솟값을 확인하기 위해 미리 전선의 수 파악

			//return에서 업데이트 되지만 미리 가지치기(코어 최대보다 작은데 전선수가 큰 경우
			if (CNT + data > MIN && maxcore+1<MAX) continue;  
			
			//전선 수 증가. 전선부분 2로 채움. 코어수 증가
			CNT += data;
			inoutMap(level, i, d, 2);
			maxcore++;

			//같은 행에 또 있을 수 있으니 level은 같게, x값만 증가하게 돌림.
			run(level, i + 1);

			maxcore--;
			CNT -= data;
			inoutMap(level, i, d, 0);
		}
	}
	//해당level에 더 이상 코어가 없다면 행 증가. index는 1부터
	run(level + 1,1);
}

int main()
{
	int tc;
	cin >> tc;
	for (int T = 0; T < tc; T++)
	{

		CNT=0;
		MIN = 21e8;
		MAX = -1;
		maxcore = 0;
		cin >> N;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				cin >> map[i][j];

		run(1, 1);
		cout <<"#"<<T+1<<" "<< MIN<<'\n';
	}
}
