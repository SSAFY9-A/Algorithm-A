/*
혁진이 프로그램 검증
모든 경우의 수를 생각해라
자원을 어떻게 관리할 것인가

시뮬레이션 종료가 되나?

아이디어 : 같은 메모리의 상태와 방향을 가지고 같은 위치에 반복하면 종료
dat 배열(해시)

*/
#include <iostream>
#include <cstring>
using namespace std;

int R, C;
char ins[20][20];
bool visited[4][16][20][20];
bool start;
int direct[4][2] = { -1,0,1,0,0,-1,0,1 };
void init(void)
{
	memset(visited, 0, sizeof(visited));
	start = false;
}

void input(void)
{
	cin >> R >> C;
	for (int y = 0; y < R; y++)
		for (int x = 0; x < C; x++)
		{
			cin >> ins[y][x];
			if (ins[y][x] == '@') start = true;
		}
}

bool sv(int d, int m, int sy, int sx)
{
	//무한 반복
	int y = sy;
	int x = sx;
	char c = ins[y][x];
	int dir = d;
	int mem = m;

	//25600byte
	visited[dir][mem][y][x] = true;
	if (c == '<') dir = 2;
	else if (c == '>') dir = 3;
	else if (c == '^') dir = 0;
	else if (c == 'v') dir = 1;
	else if (c == '_') {
		if (mem == 0) dir = 3;
		else dir = 2;
	}
	else if (c == '|') {
		if (mem == 0) dir = 1;
		else dir = 0;
	}
	else if (c >= '0' && c <= '9')
	{
		mem = c - '0';
	}
	else if (c == '+') mem = (mem + 1) % 16;
	else if (c == '-') mem = (mem - 1 + 16) % 16;

	while (true)
	{
		y = (y + direct[dir][0] + R)%R;
		x = (x + direct[dir][1] + C)%C;

		if (visited[dir][mem][y][x]) return false;
		visited[dir][mem][y][x] = true;

		c = ins[y][x];

		if (c == '@') return true;
		else if (c == '<') dir = 2;
		else if (c == '>') dir = 3;
		else if (c == '^') dir = 0;
		else if (c == 'v') dir = 1;
		else if (c == '_') {
			if (mem == 0) dir = 3;
			else dir = 2;
		}
		else if (c == '|') {
			if (mem == 0) dir = 1;
			else dir = 0;
		}
		else if (c == '.') continue;
		else if (c >= '0' && c <= '9')
		{
			mem = c - '0';
		}
		else if (c == '+') mem = (mem + 1) % 16;
		else if (c == '-') mem = (mem - 1 + 16) % 16;
		else if (c == '?')
		{
			if (sv(0, mem, y,x)) return true;
			if (sv(1, mem, y,x)) return true;
			if (sv(2, mem, y,x)) return true;
			if (sv(3, mem, y,x)) return true;
			return false;
		}
	}
}

int main(void)
{
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		init();
		input();
		cout << '#' << tc << ' ';
		if (start && sv(3, 0, 0, 0))
			cout << "YES" << '\n';
		else
			cout << "NO" << '\n';
	}
}
