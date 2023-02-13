/*
시간 : 50개 테스트케이스를 합쳐서 C의 경우 3초 / C++의 경우 3초 / Java의 경우 3초 / Python의 경우 15초
메모리 : 힙, 정적 메모리 합쳐서 256MB 이내, 스택 메모리 1MB 이내
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <string>
#include <cstring>
using namespace std;
//좌표 구조체
struct node
{
	int y;
	int x;
};
int map[50][50];//map
int visited[50][50];//방문체크맵
int N, M, R, C, L; //map의 세로와 너비, 맨홀 위치 좌표(R,C), 탈출후 소요시간
int direct[4][2] = { -1,0,1,0,0,-1,0,1 }; //상하좌우 방향 배열
int cnt; //탈주범 이동 장소 개수

// 원하는 방향으로 가기 위해서 현재 위치의 맨홀 뚜껑의 모양
// 이 될수 있는 경우 index는 상하좌우0123을 문자열은 맨홀 뚜껑의
// 모양을 의미함
string now_manhole_shape[4] = {
	"1247",
	"1256",
	"1367",
	"1345"
};
// 원하는 방향으로 가기 위해서 다음 위치의 맨홀 뚜껑의 모양
// 이 될수 있는 경우 index는 상하좌우0123을 문자열은 맨홀 뚜껑의
// 모양을 의미함
string next_manhole_shape[4] = {
	"1256",
	"1247",
	"1345",
	"1367"
};

void input(void)
{
	cin >> N >> M >> R >> C >> L;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < M; x++)
			cin >> map[y][x];
}

void bfs(int R, int C)
{
	queue<node>q;
	q.push({ R,C });	//시작 위치 넣기
	memset(visited, 0, sizeof(visited)); // 방문 초기화
	visited[R][C] = 1;	//시작 위치 중복 체크
	cnt = 1; //시작위치 장소 수 1증가
	while (!q.empty())
	{
		node now = q.front();
		q.pop();

		//현재 시간이 L이 소요된 경우 끝
		if (visited[now.y][now.x]  == L) return;

		//상하좌우 방향으로 이동
		for (int t = 0; t < 4; t++)
		{
			int dy = now.y + direct[t][0];
			int dx = now.x + direct[t][1];
			//다음 위치가 범위를 벗어날 경우 
			if (dy < 0 || dx < 0 || dy >= N || dx >= M) continue;
			// 다음 위치에 터널이 없는 경우
			if (map[dy][dx] == 0) continue;
			// 다음위치가 이미 갔던 곳일 경우
			if (visited[dy][dx] > 0) continue;
			//현재위치에서 맨홀뚜껑 모양이 갈 수 없는 방향인 경우
			if (now_manhole_shape[t].find(to_string(map[now.y][now.x])) == -1) continue;
			//다음위치에서 맨홀뚜껑 모양이 갈 수 없는 방향인 경우
			if (next_manhole_shape[t].find(to_string(map[dy][dx])) == -1) continue;
			//갈 수 있는 경우
			visited[dy][dx] = visited[now.y][now.x] + 1; //방문 체크
			cnt++; //장소수 추가
			q.push({ dy,dx });//큐에 삽입
 		}

	}
}

int main(void)
{
	//freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		input();
		bfs(R,C);
		cout << '#' << t+1 << ' ' << cnt<<'\n';
	}
}
