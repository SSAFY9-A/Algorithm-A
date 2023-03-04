//각 각 위치에 들어갈 수 있는 사각형 종류는 여러개가 있을 수 있음
//무조건 큰 사각형 우선적으로 넣으면 가지고 있는 사각형 개수 안에 해결 못하는 경우도 있음
//ex) 1크기 6개 사용 등으로..
//따라서 각 위치에서 넣을 수 있는 사각형에 대한 모든 조합을 확인해봐야함

//#1 dfs 
// Level: 모든 좌표(visited 처리 안된), Branch : 각 사각형 종류, 기저조건 : 모든 1좌표 개수만큼 색종이 덮였으면
// 백트랙킹 : 이미 색종이 최소 사용개수 넘겼거나, 모든 해당 위치에 사용가능한 색종이가 없을때 
//#2 해당 크기의 사각형을 넣을 수 있는 지 유효성 확인 함수

#include <iostream>
#include <math.h>
using namespace std;

int map[10][10];
int visited[10][10];
int paper[5]; //각 종이당 5장 까지 사용가능
int cntPaper; //색종이 몇 장 썼는지
int total; //총 1 개수
int cntArea; //1 덮은 개수
int ans = 21e8; // 최댓값으로 초기화
int isValid(int dy, int dx, int size) { //출발지, 사이즈 0분터 들어옴
    if (dy + size >= 10 || dx + size >= 10) //색종이 사이즈가 밖으로 나가면 안 됨
        return 0;
    for (int y = dy; y <= dy + size; y++) {
        for (int x = dx; x <= dx + size; x++) {
            if (map[y][x] == 0 || visited[y][x] != 0) //1이 아니거나 이미 다른 도형이 차지하고 있는 경우
                return 0;
        }
    }
    return 1;
}
void check(int dy, int dx, int size, int isBefore) {
    int i;
    if (isBefore == 1) //1 이면 들어가기전
        i = 1;
    else i = 0;
    for (int y = dy; y <= dy + size; y++) {
        for (int x = dx; x <= dx + size; x++) {
            visited[y][x] = i;
        }
    }
}
void dfs(int level,int startY,int startX) { //level 은 색종이 사용개수랑 같음
    //백트랭킹
    if (level >= ans) // 현재 값보다 더 많은 색종이 사용할 경우
        return;
    //기저조건
    if (total == cntArea) {
        if (ans > level)
            ans = level;
    }
   // cout << level << '\n';
    for (int y = startY; y < 10; y++) {
        for (int x = startX; x < 10; x++) {
            if (map[y][x] == 0)
                continue;
            if (visited[y][x] != 0)
                continue;
            for (int i = 4; i >= 0; i--) { //각 색종이
                if (paper[i] >= 5) //5장 썼을경우..
                    continue;
                if (!isValid(y, x, i)) //해당 색종이를 넣을 수 있는지
                    continue;
                paper[i]++; //해당 종이 사용개수
                check(y, x, i, 1); //visited check
                cntArea += pow(i + 1, 2); //1 덮은 개수 cnt
                dfs(level + 1,y,x);
                cntArea -= pow(i + 1, 2);
                check(y, x, i, 0);
                paper[i]--;
            }
            return; //여기까지 왔다는 것은 이 level의 역할은 끝났다는 의미
        }
        startX = 0;
    }
}
int main() {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            cin >> map[y][x];
            if (map[y][x] == 1)
                total++;
        }
    }
    if (total != 0) {
        dfs(0,0,0);
        if (ans == 21e8) //1 이 존재하는데도 정답이 될 수 없으면 -1 출력
            ans = -1;
    }
    else ans = 0;
    cout << ans;
}
