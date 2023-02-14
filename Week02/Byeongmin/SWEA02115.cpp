#include <iostream>
#include <cstring>
using namespace std;

#define MAX_N 10
#define MAX_M 5
#define MAX_C 30

int N, M, C;
int arr[MAX_N][MAX_N];
int collected[MAX_N][MAX_N];
int max_sum;

int max(int a, int b){return a>b?a:b;}

void init() {
    cin >> N >> M >> C;
    for(int i=0;i<N;i++)for(int j=0;j<N;j++) cin >> arr[i][j];
}

void dfs(int y, int x, int level, int limit, int sum) {
    if(level == M) {
        if(max_sum < sum) max_sum = sum;

        return;
    }

    if(limit >= arr[y][x]) dfs(y, x+1, level+1, limit-arr[y][x], sum+arr[y][x]*arr[y][x]); // 포함 가능여부 확인 후 포함
    dfs(y, x+1, level+1, limit, sum); // 미포함
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;
    for(int t=1;t<=T;t++) {
        init();

        for(int i=0;i<N;i++)for(int j=0;j<N-M+1;j++) {
            max_sum = 0;
            dfs(i, j, 0, C, 0);
            collected[i][j] = max_sum;
        }

        max_sum = 0;
        for(int i=0;i<N;i++)for(int j=0;j<N-M+1;j++) {
            for(int x=j+M;x<N-M+1;x++){
                int sum = collected[i][j] + collected[i][x];
                if(max_sum < sum) max_sum = sum;
            }
            for(int y=i+1;y<N;y++)for(int x=0;x<N-M+1;x++){
                int sum = collected[i][j] + collected[y][x];
                if(max_sum < sum) max_sum = sum;
            }
        }

        cout << '#' << t << ' ' << max_sum << '\n';
    }

    return 0;
}