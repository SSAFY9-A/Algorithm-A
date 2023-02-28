#include <iostream>
#include <cstring>

using namespace std;

int Ms, Ma, L, N;
int arr[16][16];
int stock[16];
int min_cost;
int budget;

void init() {
    memset(arr, 0, sizeof(arr));
    memset(stock, 0, sizeof(stock));
    budget = Ms;
}
int cnt;
void dfs(int month, int seed, int start) {
    if(seed < min_cost) {
        for(int i=0;i<N;i++) seed += stock[i] * (arr[i][month+1]);
        if(budget < seed) budget = seed;
        return;
    }

    for(int i=start;i<N;i++) {
        if(arr[i][month] >= arr[i][month+1] || seed < arr[i][month]) continue;
        ++stock[i];
        dfs(month, seed - arr[i][month], i);
        --stock[i];
    }
}

int getMinCost(int month) {
    int result = 2000;
    for(int i=0;i<N;i++) if(arr[i][month] < arr[i][month+1] && result > arr[i][month]) result = arr[i][month];
    return result;
}

int main() {
    int T;
    cin >> T;
    for(int t=1;t<=T;t++) {
        cin >> Ms >> Ma >> N >> L;
        init();

        for(int i=0;i<N;i++) for(int j=0;j<=L;j++) {
            cin >> arr[i][j];
        }

        for(int i=0;i<L;i++) {
            min_cost = getMinCost(i);
            //cout << "[" << i << "] " << budget << ' ' << min_cost << '\n';
            dfs(i, budget, 0);
            budget += Ma;
        }
        //cout << budget << '\n';
        cout << "#" << t << " " << budget - Ms - (Ma*L) << '\n';
    }

    return 0;
}