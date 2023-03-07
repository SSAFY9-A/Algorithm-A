#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int R, C;
vector<char>v[20];

int dy[4] = { -1,1,0,0 };//상하좌우
int dx[4] = { 0,0,-1,1 };

void run()
{
	int Memory = 0;
	int cy = 0;
	int cx = 0;
	int d = 3;
	int time = 0;
	int flag = 0;
	//초기설정. 
	if (v[0][0] >= '0' && v[0][0] <= '9')
		Memory = v[0][0] - '0';
	if (v[0][0] == '<' || v[0][0]=='_')
		d = 2;
	
	if (v[0][0] == '^' || v[0][0]=='|')
		d = 0;
	if (v[0][0] == 'v')
		d = 1;
	
	while (1)
	{
		//cout << cy << "," << cy << " d= " << d << '\n';
		if (v[cy][cx] == '@') {
			flag = 1;
			break;
		}
		if (time > 100) break;
		cy += dy[d];
		cx += dx[d];
		if (cx < 0 || cx >= C)
			cx = (cx + C) % C;
		if (cy < 0 || cy >= R)
			cy = (cy + R) % R;
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
			d = 3;
		time++;
	}
	if (flag == 1)
		cout << "YES\n";
	else cout << "NO\n";
}

int main()
{
	int T;
	char input;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> R >> C;
		
		for (int i = 0; i < R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				cin >> input;
				v[i].push_back(input);
			}
		}
		

		cout << "#" << tc << " " ;
		run();
		for (int i = 0; i < R; i++)
			v[i].clear();
	
	}
}
