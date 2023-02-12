#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
 
/*
요약
1.시작점은 최대값
2.다음 지역은 낮은 값, 상하좌우
3.한 지역 높이 최대 K까지 빼기 가능
*/
typedef struct node
{
    int y;
    int x;
}node;
 
int N, K;// 지도 한변(3 ≤ N ≤ 8), 최대 공사 가능 깊이(1 ≤ K ≤ 5)
int map[8][8]; //등산지도
int initial_max[5][2]; // 높이가 가장 높은 곳 좌표
int initial_MAX = -21e8; //가장 큰 높이 값
int initial_len; //initial_max의 길이
int visited[8][8];//방문좌표 체크
int direct[4][2] = { -1,0,0,-1,0,1,1,0 };//상하좌우 방향 배열
int dig_flag; // 땅 판거 확인 flag
int MAX = -21e8; //등산로 길이 최댓값
int length; // 등산로 길이
void dfs(int y, int x)
{
    if (MAX < length)
        MAX = length;
 
    for (int t = 0; t < 4; t++)
    {
        int dy = y + direct[t][0];
        int dx = x + direct[t][1];
        //맵 범위 초과 체크
        if (dy < 0 || dx < 0 || dy >= N || dx >= N)continue;
        //방문했는지 체크
        if (visited[dy][dx] > 0) continue;
        //파는 경우
         
        if (map[dy][dx] < map[y][x])
        {
            visited[dy][dx] = 1;
            length++;
            dfs(dy, dx);
            length--;
            visited[dy][dx] = 0;
        }
        else if (dig_flag == 0 && (map[dy][dx] - K)< map[y][x] )
        {
            // 팔수 있지만 안파는 경우 팔수 있으면 파는 경우 지금
            int tmp = map[dy][dx] - map[y][x] + 1;
            dig_flag = 1;
            visited[dy][dx] = 1;
            length++;
            map[dy][dx] -= tmp;
            dfs(dy, dx);
            map[dy][dx] += tmp;
            length--;
            visited[dy][dx] = 0;
            dig_flag = 0;
        }
    }
}
 
int main(void)
{
    int T;// test case
    //freopen("input.txt", "r",stdin);
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        //reset
        MAX = -21e8;
        initial_len = 0;
        initial_MAX = -21e8;
        cin >> N >> K;
        for(int y=0; y<N; y++)
            for (int x = 0; x < N; x++)
            {
                cin >> map[y][x];
                if (initial_MAX < map[y][x])
                {
                    initial_MAX = map[y][x];    //가장 큰 높이 최댓값 바꿈
                    initial_len = 0;    //길이 초기화
                    initial_max[initial_len][0] = y;
                    initial_max[initial_len][1] = x;
                    initial_len++;
                }
                else if (initial_MAX == map[y][x])
                {
                    initial_max[initial_len][0] = y;
                    initial_max[initial_len][1] = x;
                    initial_len++;
                }
            }
 
        for (int z = 0; z < initial_len; z++)
        {
            //reset
            length = 0;
            dig_flag = 0;
            memset(visited, 0, sizeof(visited));
            visited[initial_max[z][0]][initial_max[z][1]] = 1;
            dfs(initial_max[z][0], initial_max[z][1]);
        }
        cout << '#' << t + 1 << ' ' << MAX+1<<'\n';
    }
}
