#include <iostream>

#define SIZE 10

using namespace std;

int t;

int papers[6] = {0, 5, 5, 5, 5, 5};
bool arr[SIZE][SIZE];
int answer = 26;
int used, total;
bool isAvailable = false;

bool check(int y, int x, int size) {
    if(y + size > SIZE || x + size > SIZE) return false;
    for(int i=0;i<size;i++)for(int j=0;j<size;j++) {
        if(!arr[y+i][x+j]) return false;
    }
    return true;
}

void fill(int y, int x, int size, bool type) {
    int nx = x;
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            arr[y+i][x+j] = type;
        }
        nx = 1;
    }
}

void dfs(int y, int x) {
    if(used >= answer) return;

    if(total == 0) { // 다 덮었으면
        isAvailable = true;
        if(answer > used) answer = used;
        return;
    }

    for(int i=y;i<SIZE;i++) {
        for(int j=x;j<SIZE;j++) {
            if(!arr[i][j]) continue;
            for(int size=5;size>0;size--) {
                if(!check(i, j, size)) continue;
                if(!papers[size]) continue;

                papers[size]--;
                fill(i, j, size, 0);
                total -= size * size;
                ++used;
                
                // cout << '\n';
                // for(int yy=0;yy<SIZE;yy++) {
                //     for(int xx=0;xx<SIZE;xx++) cout << arr[yy][xx] << ' ';
                //     cout << '\n';
                // }
                // cin >> t;

                dfs(i, j+size);
                --used;
                total += size * size;
                fill(i, j, size, 1);
                papers[size]++;
            }
            return;
        }
        x = 0;
    }
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);

    for(int i=0;i<SIZE;i++)for(int j=0;j<SIZE;j++) {
        cin >> arr[i][j];
        if(arr[i][j]) ++total;
    }

    dfs(0, 0);

    if(isAvailable) cout << answer;
    else cout << -1;

    return 0;
}