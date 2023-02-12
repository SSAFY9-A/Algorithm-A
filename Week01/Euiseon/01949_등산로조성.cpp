#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
// highest 찾기 -> dfs 시작점
// *최대* K까지 -가능 한번 -> K를 최소한으로 사용해야 가능성 많음 now-next==1 !! 
// 정담 : 최대 등산로 길이 찾기

// level -> NODE
// branch -> dir

int N, K;
int map[9][9];
int highest; // 시작점
int lenMax;
int used; //K

struct NODE {
    int y;
    int x;
};
int dir[4][2] = { -1,0,0,1,1,0,0,-1 };
void dfs(int level, NODE now) {
    //기저 조건은 없으며, 갈곳이 없으면 들어오지 않는다.
    if (lenMax < level) {
        lenMax = level;
    }
    int curHeight = map[now.y][now.x];
    int flag;
    map[now.y][now.x] = 100; // visited처리 , 안 할시에 다음 곳에서 K를 사용하여 다시 되돌아올 수 있으니까..?
    //ex) 7 (1,4) -> (0,4) 2 -> 위x 오른쪽 x 아래-4 ==1 가능 이렇게...
    for (int i = 0; i < 4; i++) {
        int dy = now.y + dir[i][0];
        int dx = now.x + dir[i][1];
        flag = false;
        if (dy < 0 || dx < 0 || dy >= N || dx >= N) //범위 나갈경우
            continue;
        int nextHeight = map[dy][dx];
        //더 높다면 K 사용유무 확인해서 차이가 K-1이하로 난다면 다음 map을 현재 위치 -1해서 들어가기
        if (curHeight <= nextHeight) {
            if (used || (nextHeight - curHeight >= K))
                continue;
            flag = true;
            used = true;
            map[dy][dx] = curHeight - 1;
        }
        dfs(level + 1, { dy,dx });
        if (flag) {
            used = false;
            map[dy][dx] = nextHeight;
        }
    }
    map[now.y][now.x] = curHeight;
}
void input();
int main()
{
    int T;
    cin >> T;
    vector<int> ans;
    for (int t = 0; t < T; t++)
    {
        // 전역변수 초기화
        highest = INT_MIN;
        lenMax = INT_MIN;
        input();

        // start
        for (int y = 0; y < N; y++)
        {
            for (int x = 0; x < N; x++)
            {
                if (highest != map[y][x])
                    continue;
                used = false;
                dfs(1, { y,x });
            }
        }
        ans.push_back(lenMax);
    }
    for (int t = 0; t < T; t++) {
        cout << '#' << t + 1 << ' ' << ans[t] << '\n';
    }
    return 0;
}

void input()
{
    cin >> N >> K;
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            cin >> map[y][x];
            if (highest < map[y][x])
                highest = map[y][x];
        }
    }
}