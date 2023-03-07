#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int R, C;
vector<char>v[20];

int QuestionD[20][20];
int checkloop[20][20][4][16];

int dy[4] = { -1,1,0,0 };//상하좌우
int dx[4] = { 0,0,-1,1 };

int Memory = 0;
int flag = 0;

void dfs(int cy, int cx,int d)
{
	checkloop[cy][cx][d][Memory]++;
	//cout << cy << "," << cy << " d= " << d << '\n';
	if (checkloop[cy][cx][d][Memory] > 2)
	{
		flag = 1;
		return;
	}
	if (v[cy][cx] == '@') {
		return;
	}
	
	//cout << cy << "," << cy << " d= " << d << '\n';
	if (v[cy][cx] >= '0' && v[cy][cx] <= '9')
		Memory = v[0][0] - '0';
	else if (v[cy][cx] == '-')
	{
		if (Memory == 0)
			Memory = 15;
		else Memory--;
	}
	else if (v[cy][cx] == '+')
	{
		if (Memory == 15)
			Memory = 0;
		else Memory++;
	}
	else if (v[cy][cx] == '<') d = 2;
	else if (v[cy][cx] == '>') d = 3;
	else if (v[cy][cx] == '^') d = 0;
	else if (v[cy][cx] == 'v') d = 1;

	else if (v[cy][cx] == '_')
	{
		if (Memory == 0) d = 3;
		else d = 2;
	}
	else if (v[cy][cx] == '|')
	{
		if (Memory == 0) d = 1;
		else d = 0;
	}
	//?가 나오면 4방향 설정 해줘야함. ->visited로..?
	else if (v[cy][cx] == '?')
	{
		QuestionD[cy][cx]= (QuestionD[cy][cx]+1)%4;
		d = QuestionD[cy][cx]; 
	}
	
	cy += dy[d];
	cx += dx[d];
	if (cx < 0 || cx >= C)
		cx = (cx + C) % C;
	if (cy < 0 || cy >= R)
		cy = (cy + R) % R;
	
	dfs(cy, cx,d);
}

int main()
{
	int T;
	char input;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> R >> C;
		Memory = 0;
		memset(QuestionD, 0, sizeof(QuestionD));
		memset(checkloop, 0, sizeof(checkloop));
		flag = 0;
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				cin >> input;
				v[i].push_back(input);
			}
		}

		
		dfs(0,0,3);
		
		if (flag == 1)
			cout << "#" << tc << " NO\n";
		else
			cout << "#" << tc << " YES\n";
		for (int i = 0; i < R; i++)
			v[i].clear();

	}
}
