//dfs 로 모든 지역구를 탐색
//각 마을별로 A지역구인지 B지역구인지 dfs로 조합보기
//모든 마을 선택이 끝나고 가능 여부를 확인할 수 있음
//A지역구만 선택하면 나머진 B지역구
//가지치기는 A지역구 선택인원이 B지역구인원(남은인원)을 넘겼고, 동시에 최소 차이인원도 넘겼으면 return
//마지막에 연결됐는지 어떻게 확인? -> dfs로 확인, 같은지역구면 가고 DAT로 check후
//실제 선택한 결과와 확인한 결과가 일치하면 가능한 경우

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int N;
int map[8][8];
int p[8]; //각 마을의 인구
int total; //총인구

int visited[8];
int vil[8];//value 1은 A, 0은 B

int Min;
int AP;
int startB = -1;

int isValid(int v) {
	for (int i = 0; i < N; i++) {
		if (vil[i] == v && visited[i] != 1)
			return 0;
	}
    return 1;
}
void check(int now, int v) {
    visited[now] = 1;
    for (int i = 0; i < N; i++) {
        if (map[now][i] == 1 && vil[i] == v && visited[i] != 1) {
            check(i, v);
        }
    }
}
void dfs(int level) {
    //기저조건
    if (level == N) {
        if (Min > abs(AP - (total - AP))) {
            memset(visited, 0, sizeof(visited));
            check(0, 1); //0마을부터시작해서 연결된 1(A) 지역구 확인
            if (isValid(1) == 0) //모든 지역구를 연결 가능?
                return;
            memset(visited, 0, sizeof(visited));
            if (startB != -1) {
                check(startB, 0);
                if (isValid(0) == 0)
                    return;
            }
            Min = abs(AP - (total - AP));
        }
        return;
    }

    AP += p[level];
    vil[level] = 1;
    dfs(level + 1);
    vil[level] = 0;
    AP -= p[level];

    if (level == 0) //첫 마을은 A인지 B인지 중요하지 않음
        return;
    startB = level;
    dfs(level + 1);
}
int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        total = 0; // 총인구
        memset(vil, 0, sizeof(vil));
        Min = 21e8;
        AP = 0;
        startB = -1;
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                cin >> map[y][x];
            }
        }
        for (int i = 0; i < N; i++) {
            cin >> p[i];
            total += p[i];
        }
        dfs(0);
        cout <<'#'<<t+1<<' '<< Min<<'\n';
    }

    return 0;
}