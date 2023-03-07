//메모리 0~15
//각 문자와 메모리 상황에 따라 방향을 바꿔가며 이동한다
//@ 를 만나면 프로그램 종료한다
//해당 프로그램이 종료될 수 있는가?

//같은 곳을 반복해서 오면 불가능 ?
//메모리가 1인지 2인지에 따라서도 다름
//각 위치에 같은 메모리 상황으로 들어왔다면?
//방향을 바꾸는 문자 -> 메모리 상황 같은지로 visit
//방향을 랜덤으로 바꾸는 문자 -> 4방향 dfs, 메모리 상황 같은지로 visit 
//아무것도 하지 않는 문자 -> 메모리상황과 현재 방향 같은지로 visit
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int R, C; //R 행 C열 (2~20)
char map[20][20];
int visitedMem[16][20][20];
int visitedDir[4][20][20];
struct Node {
	int y, x;
};
Node now;
int d; //현재 방향
int mem; //현재 메모리
string ans;
int dir[4][2] = { -1,0,0,1,1,0,0,-1 };
void getDir(int y, int x) { //? 와 @는 skip
	char c = map[y][x];
	if (c == '.' || (c >= '0' && c <= '9') || c == '+' || c == '-') return;
	else if (c == '<') d = 3;
	else if (c == '>') d = 1;
	else if (c == '^') d = 0;
	else if (c == 'v') d = 2;
	else if (c == '_') {
		if (mem == 0) d = 1;
		else d = 3;
	}
	else if (c == '|') {
		if (mem == 0) d = 2;
		else d = 0;
	}
	return;
}
void getMem(int y, int x) {
	char c = map[y][x];
	if (c == '+') mem++;
	else if (c == '-') mem--;
	else if (c >= '0' && c <= '9') mem = c - '0';

	if (mem < 0) mem = 15;
	else if (mem > 15) mem = 0;
	return;
}
void func() {

	while (1) {

		int dy = now.y + dir[d][0];
		int dx = now.x + dir[d][1];


		if (dy < 0) dy = R - 1;
		if (dy >= R) dy = 0;
		if (dx < 0) dx = C - 1;
		if (dx >= C) dx = 0;
		//cout << dy << ' ' << dx << '\n';
		now.y = dy;
		now.x = dx;
		if (map[dy][dx] == '@') { //@ 면 ok
			ans = "YES";
		}
		if (ans == "YES") return;
		getDir(dy, dx);
		getMem(dy, dx);
		if (visitedDir[d][dy][dx] == 1 && visitedMem[mem][dy][dx] == 1)
			return;
		visitedDir[d][dy][dx] = 1;
		visitedMem[mem][dy][dx] = 1;

		if (map[dy][dx] == '?') {
			int tempMem = mem;
			for (int i = 0; i < 4; i++) {
				d = i;
				visitedDir[d][dy][dx] = 1;
				func();
				now.y = dy;
				now.x = dx;
				mem = tempMem;
			}
			return;
		}
	}
}
int main() {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> R >> C;

		for (int y = 0; y < R; y++) {
			for (int x = 0; x < C; x++) {
				char c;
				cin >> c;
				map[y][x] = c;
			}
		}
		d = 1;
		mem = 0;
		now = { 0,0 };
		ans = "NO";
		memset(visitedDir, 0, sizeof(visitedDir));
		memset(visitedMem, 0, sizeof(visitedMem));
		visitedMem[mem][0][0] = 1;
		visitedDir[d][0][0] = 1;
		// 처음에 ?이면
		if (map[0][0] == '?')
		{
			for (int i = 0; i < 4; i++)
			{
				d = i;
				visitedDir[d][0][0] = 1;
				func();
				mem = 0;
			}
		}
		else
		{
			if (map[0][0] == '@') { ans = "YES"; }
			else {
				getDir(0, 0);
				getMem(0, 0);
				func();
			}
		}
		cout << '#' << t + 1 << ' ' << ans << '\n';
	}

	return 0;
}
