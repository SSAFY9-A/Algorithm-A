#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
//map x
//vector로 각 군집 다 움직이고 // group  struct에 좌표값까지 추가
//used로 각 군집의 위치를 표시해둔다. 이미 used =군집번호가 되어있다면 // used 배열필요 
//겹치는 군집이 있다는 것이고, 해당 군집번호와 합쳐주고 비교해준다.
//두 군집을 비교하여 큰 군집으로 작은 군집 수를 옮겨주고 작은 군집은
//더이상 안 쓰인다는 의미로 masking 처리 해준다. =>masking(dead) 배열 필요
int N, M, K; //맵 크기, 격리 시간, 미생물 군집 수
int used[101][101];
int Max[101][101]; //여러 군집중 가장 미생물 수가 가장 큰곳으로 가기위해 체크
int dead[1001];
int dir[4][2] = { -1,0,1,0,0,-1,0,1 }; //상하좌우
struct group {
    int y, x;
    int num;
    int d;
};
int isBound(int y, int x) {
    if (y == 0 || x == 0 || y == N - 1 || x == N - 1)
        return true;
    return false;
}
vector<group>v;
int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N >> M >> K;
        memset(used, 0, sizeof(used));
        memset(Max, 0, sizeof(Max));
        memset(dead, 0, sizeof(dead));
        v.clear();
        v.push_back({ 0,0,0,0 }); //node를 1번부터쓰기위한 예외처리
        dead[0] = 1;

        for (int i = 0; i < K; i++) {
            int y, x, n, d; //d는 1부터이므로 dir[d-1]로 받는다
            cin >> y >> x >> n >> d;
            v.push_back({ y,x,n,d - 1 });
        }
        for (int i = 1; i <= M; i++) { //M시간 동안
            memset(used, 0, sizeof(used));
            memset(Max, 0, sizeof(Max));
            for (int j = 1; j < v.size(); j++) { //모든 벡터 움직임 
                group now = v[j];
                if (dead[j] == 1)
                    continue;
                now.y += dir[now.d][0]; //방향 한칸씩 이동
                now.x += dir[now.d][1];
                if (isBound(now.y, now.x)) {
                     //반대방향 0 <->1, 2<->3
                    if (now.d <= 1) {
                        now.d = (now.d + 1) % 2;
                    }
                    else now.d = 2+(now.d+1)%2;
                    now.num /= 2; //반타작
                    if (now.num == 0) //다죽었으면 dead
                        dead[j] = 1;
                }
                v[j] = now;
            }
            //끝나고나서 
            for (int j = 1; j < v.size(); j++) { //겹치는거 체크
                group now = v[j];
                if (dead[j] == 1)
                    continue;
                if (used[now.y][now.x] >= 1) { //이미 다른애가 있으면
                    int e = used[now.y][now.x];
                        
                    if (Max[now.y][now.x] < now.num) { //현재가 더 큰 군집이면
                        Max[now.y][now.x] = now.num;
                        used[now.y][now.x] = j;
                        now.num += v[e].num;
                        dead[e] = 1;
                    }
                    else { //현재가 더 작은 군집이면
                        v[e].num += now.num;
                        dead[j] = 1;
                    }
                }
                else { //첫 방문이면
                    used[now.y][now.x] = j;
                    Max[now.y][now.x] = now.num;
                }
                v[j] = now;
            }
        }
        int sum = 0;
        for (int i = 1; i < v.size(); i++) {
            if (dead[i] == 1)
                continue;
            sum += v[i].num;
        }
        cout <<'#'<<t+1<<' '<< sum<<'\n';
    }

    return 0;
}

//각 미생물 군집이 1시간마다 정해진 방향으로 움직임
//Edge에 닿으면 반으로 줄어들고 방향 반대
//겹치면 미생물 수 합쳐지고 방향은 둘 중 더 큰 군집의 방향을 따라감
//동일한 미생물수가 만날 일은 없음
